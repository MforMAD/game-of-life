#ifndef INTERFACE_H
#define INTERFACE_H

#include <glib/gi18n.h>
#include <gtk/gtk.h>

struct base {
	GtkApplication *app;
	GtkWidget *window;
	struct tpl templates;
	struct box boxes;
	struct map **lattice;
};

struct tpl {
	int files_counter;
	char **file_name;
};

struct box {
	GtkWidget *content;
	GtkWidget *menu;
	GtkWidget *rules;
	GtkWidget *levels;
	GtkWidget *game;
};

struct map {
	GtkWidget *text;
	GtkWidget *button;
};


void start(GtkApplication *app, gpointer data);

#endif