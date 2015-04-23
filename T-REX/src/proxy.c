/*
 * In The Name Of God
 * ========================================
 * [] File Name : proxy.c
 *
 * [] Creation Date : 23-03-2015
 *
 * [] Last Modified : Thu 23 Apr 2015 09:51:35 AM IRDT
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <glib.h>
#include <stdlib.h>
#include <libsoup/soup.h>
#include <stdbool.h>

#include "proxy.h"

static SoupServer *server;

#define DEST_URL "http://127.0.0.1:8080"

static void copy_header(const char *name, const char *value,
		gpointer dest_headers)
{
	soup_message_headers_append(dest_headers, name, value);
}

static void recv_headers(SoupMessage *from, SoupMessage *to)
{
	g_print("[%p] HTTP/1.%d %d %s\n", to,
			soup_message_get_http_version(from),
			from->status_code, from->reason_phrase);

	soup_message_set_status_full(to,
			from->status_code, from->reason_phrase);

	soup_message_headers_foreach(from->response_headers,
			copy_header, to->response_headers);
	soup_message_headers_remove(to->response_headers, "Content-Length");

	soup_server_unpause_message(server, to);
}

static void recv_chunk(SoupMessage *from, SoupBuffer *chunk, SoupMessage *to)
{
	g_print("[%p] writing chunk of %lu bytes\n", to,
			(unsigned long) chunk->length);

	soup_message_body_append_buffer(to->response_body,
			chunk);

	soup_server_unpause_message(server, to);
}

static void finish_msg(SoupSession *session, SoupMessage *msg2, gpointer data)
{
	SoupMessage *msg = data;

	g_print("[%p] done\n\n", msg);

	soup_message_body_complete(msg->response_body);

	soup_server_unpause_message(server, msg);
	g_object_unref(msg);
}

static void trex_callback(SoupServer *server, SoupMessage *msg,
                          const char *path, GHashTable *query,
                          SoupClientContext *client, gpointer user_data)
{
	SoupMessage *msg2;
	SoupSession *session;
	char *uristr;

	session = soup_session_async_new();

	uristr = soup_uri_to_string(soup_message_get_uri(msg), true);
	/* TODO Memory Leak :-) */
	uristr = g_strjoin(NULL, DEST_URL, uristr, NULL);
	g_print("[%p] %s %s HTTP/1.%d\n", msg, msg->method, uristr,
	        soup_message_get_http_version(msg));

	msg2 = soup_message_new(msg->method, uristr);
	soup_message_headers_foreach(msg->request_headers, copy_header,
	                             msg2->request_headers);
	soup_message_headers_remove(msg2->request_headers, "Host");
	if (msg->request_body->length) {
		SoupBuffer *request =
			soup_message_body_flatten(msg->request_body);
		soup_message_body_append_buffer(msg2->request_body,
		                                request);
		soup_buffer_free(request);
	}
	soup_message_headers_set_encoding(msg->response_headers,
	                                  SOUP_ENCODING_CHUNKED);

	soup_server_pause_message(server, msg);

	g_signal_connect(msg2, "got_headers",
	                 G_CALLBACK(recv_headers), msg);
	g_signal_connect(msg2, "got_chunk",
	                 G_CALLBACK(recv_chunk), msg);

	soup_session_queue_message(session, msg2, finish_msg, msg);

	g_object_ref(msg);

	g_object_unref(session);
}

void trex_init(void)
{
	GError *error = NULL;

	server = soup_server_new(SOUP_SERVER_SERVER_HEADER,
	                         "T-REZ-1.0", NULL);
	soup_server_listen_all(server, 1373,
	                       SOUP_SERVER_LISTEN_IPV4_ONLY, &error);
	if (error) {
		g_printerr("Unable to create server: %s\n",
		           error->message);
		exit(1);
	}
	soup_server_add_handler(server, NULL, trex_callback, NULL, NULL);
}
