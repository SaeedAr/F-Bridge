/*
 * In The Name Of God
 * ========================================
 * [] File Name : main.c
 *
 * [] Creation Date : 26-04-2015
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2015 Parham Alvani.
*/
#include <glib.h>
#include <stdlib.h>
#include <stdbool.h>

#include "trap.h"

int main(int argc, char *argv[])
{
	GMainLoop *loop;

	/* Build soup server and event handler */
	trap_init();

	/* Create main event loop */
	loop = g_main_loop_new(NULL, true);
	g_main_loop_run(loop);
	g_main_loop_unref(loop);

	return 0;
}
