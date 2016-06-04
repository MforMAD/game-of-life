#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <interface.h>

int main(int argc, char *argv[])
{
	int status;
	struct base basement;

	basement.app = gtk_application_new("game.of.life", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(basement.app, "activate", G_CALLBACK(start), &basement);
	status = g_application_run(G_APPLICATION(basement.app), argc, argv);
	g_object_unref(basement.app);
	base_free(&basement);

	return status;
}