#ifndef INTERFACE_H
#define INTERFACE_H

#include <glib/gi18n.h>
#include <gtk/gtk.h>

struct map {
	GtkWidget *text;
	GtkWidget *button;
};

struct box {
	GtkWidget *content;
	GtkWidget *menu;
	GtkWidget *rules;
	GtkWidget *levels;
	GtkWidget *game;
};

struct tpl {
	int files_counter;
	char **file_name;
};

struct base {
	GtkApplication *app;
	GtkWidget *window;
	struct tpl templates;
	struct box boxes;
	struct map **lattice;
};

void start(GtkApplication *app, gpointer data);
void fill_menu(struct base *Base);
void fill_info(struct base *Base);
void fill_templates(struct base *Base);
void call_menu(GtkWidget *widget, gpointer data);
void text(GtkWidget *widget, gpointer data);
void templates(GtkWidget *widget, gpointer data);
void close_app(GtkWidget *widget, gpointer data);
void play(GtkWidget *widget, gpointer data);


#endif