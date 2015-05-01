/*
 * ################################################################################
 * #
 * #  Project F-Bridge                 [project home-page]
 * #
 * #  File:
 * #        /RBP/src/trex.c
 * #
 * #  Copyright notice:
 * #        Copyright (C) 2014, 2015 Project F-Bridge Group, CEIT Department,
 * #                       Amirkabir University of Technology (Tehran Polytechnic)
 * #
 * #  Author(s):
 * #	Parham Alvani (parham.alvani@gmail.com)
 * #
 * #  Description:
 * #	T-REX module implementation. see trex.h for more information.
 * #
 * #  Licence:
 * #        This file is part of the F-Bridge Project package.
 * #
 * #        This file is free code: you can redistribute it and/or modify it under
 * #        the terms of the GNU Lesser General Public License version 2.1 as
 * #        published by the Free Software Foundation.
 * #
 * #        This package is distributed in the hope that it will be useful, but
 * #        WITHOUT ANY WARRANTY; without even the implied warranty of
 * #        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * #        Lesser General Public License for more details.
 * #
 * #        You should have received a copy of the GNU Lesser General Public
 * #        License along with the F-Bridge source package.  If not, see
 * #        http://www.gnu.org/licenses/.
 * #
 * #
*/
#include <glib.h>
#include <stdlib.h>
#include <libsoup/soup.h>
#include <stdbool.h>

#include "trex.h"

struct destination_info {
	SoupServer *server;
	SoupMessage *msg;
};

static void copy_header(const char *name, const char *value,
	gpointer dest_headers)
{
	soup_message_headers_append(dest_headers, name, value);
}

static void recv_headers(SoupMessage *from, gpointer data)
{
	SoupMessage *to = ((struct destination_info *) data)->msg;
	SoupServer *server = ((struct destination_info *) data)->server;

	g_print("[%p] HTTP/1.%d %d %s\n", to,
		soup_message_get_http_version(from),
		from->status_code, from->reason_phrase);

	soup_message_set_status_full(to,
		from->status_code, from->reason_phrase);

	soup_message_headers_foreach(from->response_headers,
		copy_header, to->response_headers);
	/* we remove it, because libsoup appending at the end */
	soup_message_headers_remove(to->response_headers, "Content-Length");

	soup_server_unpause_message(server, to);
}

static void recv_chunk(SoupMessage *from, SoupBuffer *chunk, gpointer data)
{
	SoupMessage *to = ((struct destination_info *) data)->msg;
	SoupServer *server = ((struct destination_info *) data)->server;

	g_print("[%p] writing chunk of %lu bytes\n", to,
		(unsigned long) chunk->length);

	soup_message_body_append_buffer(to->response_body,
		chunk);

	soup_server_unpause_message(server, to);
}

static void finish_msg(SoupSession *session, SoupMessage *new_msg, gpointer data)
{

	SoupMessage *to = ((struct destination_info *) data)->msg;
	SoupServer *server = ((struct destination_info *) data)->server;

	g_print("[%p] done\n\n", to);

	soup_message_body_complete(to->response_body);

	soup_server_unpause_message(server, to);
	free(data);
	g_object_unref(to);
}

void trex_callback(SoupServer *server, SoupMessage *msg,
	const char *path, GHashTable *query, const char *dest)
{
	SoupMessage *new_msg;
	SoupSession *session;
	char *uri_str;

	struct destination_info *to = malloc(sizeof(struct destination_info));
	to->server = server;
	to->msg = msg;

	session = soup_session_async_new();

	uri_str = soup_uri_to_string(soup_message_get_uri(msg), true);
	/*
	 * TODO Memory Leak :-)
	*/
	uri_str = g_strjoin(NULL, dest, uri_str, NULL);

	g_print("[%p] %s %s HTTP/1.%d\n", msg, msg->method, uri_str,
		soup_message_get_http_version(msg));

	/* build new request */
	new_msg = soup_message_new(msg->method, uri_str);
	soup_message_headers_foreach(msg->request_headers, copy_header,
		new_msg->request_headers);
	soup_message_headers_remove(new_msg->request_headers, "Host");
	if (msg->request_body->length) {
		SoupBuffer *request =
			soup_message_body_flatten(msg->request_body);
		soup_message_body_append_buffer(new_msg->request_body,
			request);
		soup_buffer_free(request);
	}
	soup_message_headers_set_encoding(msg->response_headers,
		SOUP_ENCODING_CHUNKED);

	soup_server_pause_message(server, msg);

	g_signal_connect(new_msg, "got_headers",
		G_CALLBACK(recv_headers), to);
	g_signal_connect(new_msg, "got_chunk",
		G_CALLBACK(recv_chunk), to);

	soup_session_queue_message(session, new_msg, finish_msg, to);

	g_object_ref(msg);

	g_object_unref(session);
}