/*
 * In The Name Of God
 * ========================================
 * [] File Name : proxy.h
 *
 * [] Creation Date : 23-03-2015
 *
 * [] Last Modified : Mon 23 Mar 2015 02:12:06 AM IRDT
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#ifndef PROXY_H
#define PROXY_H

void trex_callback(SoupServer *server, SoupMessage *msg,
	const char *path, GHashTable *query, const char *dest);

#endif
