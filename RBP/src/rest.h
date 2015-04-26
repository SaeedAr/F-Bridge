/*
 * In The Name Of God
 * ========================================
 * [] File Name : rest.h
 *
 * [] Creation Date : 26-04-2015
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2015 Parham Alvani.
*/
#ifndef REST_H
#define REST_H

/*
 * Items are queried using the HTTP GET method.
 * The form of the URL is:
 * http://<domain-or-ip-address>/rest/v1/model/<data-type>/<optional-id>?<optional-query-params>
 * You can optionally include a trailing slash at the end of the path portion of the URL.
 */

struct rest_sdn {
	const char *data_type;
	const char *optional_id;
};

void rest_parse(const char *path, struct rest_sdn *sdn);

struct rest_sdn *rest_sdn_new(void);

void rest_sdn_delete(struct rest_sdn *sdn);

#endif