/*
 * In The Name Of God
 * ========================================
 * [] File Name : main.c
 *
 * [] Creation Date : 22-03-2015
 *
 * [] Last Modified : Fri 24 Apr 2015 01:01:21 AM IRDT
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <glib.h>
#include <stdlib.h>
#include <stdbool.h>

#include "trap.h"

int main(int argc, char *argv[])
{
	GMainLoop *loop;

	trap_init();

	loop = g_main_loop_new(NULL, true);
	g_main_loop_run(loop);
	g_main_loop_unref(loop);
}
