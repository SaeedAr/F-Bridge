/*
 * ################################################################################
 * #
 * #  Project F-Bridge                 [project home-page]
 * #
 * #  File:
 * #        /RBP/src/trap.c
 * #
 * #  Copyright notice:
 * #        Copyright (C) 2014, 2015 Project F-Bridge Group, CEIT Department,
 * #                       Amirkabir University of Technology (Tehran Polytechnic)
 * #
 * #  Author(s):
 * #	Parham Alvani (parham.alvani@gmail.com)
 * #
 * #  Description:
 * #	[Probably the most significant part of the header comment. A brief
 * #	description of file, including the module it belongs to, its relevance
 * #	to the project and other files or modules and the main tasks
 * #	it handles.]
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

#include "trap.h"
#include "rest.h"
#include "trex.h"

static void trap_callback(SoupServer *server, SoupMessage *msg,
	const char *path, GHashTable *query,
	SoupClientContext *client, gpointer user_data)
{
	g_print("%s\n", path);
	rest_parse(path, NULL);
	SoupHTTPVersion version = soup_message_get_http_version(msg);
	if (version == SOUP_HTTP_1_0)
		g_print("1\n");
	if (version == SOUP_HTTP_1_1)
		g_print("1.1\n");
	g_print("%s\n", soup_client_context_get_host(client));

	trex_callback(server, msg, path, query, "http://127.0.0.1");
}

void trap_init(void)
{
	GError *error = NULL;
	SoupServer *server;

	server = soup_server_new(SOUP_SERVER_SERVER_HEADER,
		"TRAP-1.0", NULL);
	soup_server_listen_all(server, 1373,
		SOUP_SERVER_LISTEN_IPV4_ONLY, &error);
	if (error) {
		g_critical("Unable to create soup server: %s\n", error->message);
		exit(1);
	}
	soup_server_add_handler(server, NULL, trap_callback, NULL, NULL);
}
