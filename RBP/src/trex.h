/*
 * In The Name Of God
 * ========================================
 * [] File Name : proxy.h
 *
 * [] Creation Date : 26-04-2015
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2015 Parham Alvani.
*/
#ifndef PROXY_H
#define PROXY_H

void trex_callback(SoupServer *server, SoupMessage *msg,
	const char *path, GHashTable *query, const char *dest);

#endif
