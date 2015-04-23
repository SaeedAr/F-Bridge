/*
 * In The Name Of God
 * ========================================
 * [] File Name : main.c
 *
 * [] Creation Date : 22-03-2015
 *
 * [] Last Modified : Mon 23 Mar 2015 02:27:09 AM IRDT
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <glib.h>
#include <stdlib.h>
#include <stdbool.h>

#include "proxy.h"

int main(int argc, char *argv[])
{
	GMainLoop *loop;

	trex_init();

	loop = g_main_loop_new(NULL, true);
	g_main_loop_run(loop);
	g_main_loop_unref(loop);
}
