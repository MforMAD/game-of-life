#ifndef INTERFACE_H
#define INTERFACE_H

#include <glib/gi18n.h>
#include <gtk/gtk.h>

struct pair {
	GtkWidget *text;
	GtkWidget *button;
	int row;
	int col;
};

struct box {
	GtkWidget *content;
	GtkWidget *menu;
	GtkWidget *rules;
	GtkWidget *levels;
	GtkWidget *game_box;
	GtkWidget *game;
};

struct tpl {
	int files_counter;
	char **file_name;
	GtkWidget **buttons;
};

struct base {
	GtkApplication *app;
	GtkWidget *window;
	struct tpl templates;
	struct box boxes;
	struct pair **lattice;
};

void start(GtkApplication *app, gpointer data);
void fill_menu(struct base *Base);
void fill_info(struct base *Base);
void fill_templates(struct base *Base);
void fill_game(struct base *Base);
void call_menu(GtkWidget *widget, gpointer data);
void text(GtkWidget *widget, gpointer data);
void templates(GtkWidget *widget, gpointer data);
void close_app(GtkWidget *widget, gpointer data);
void play(GtkWidget *widget, gpointer data);
void set_level(GtkWidget *widget, gpointer data);
void base_free(struct base *Base);
void set_default_level(struct base *Base);
void unpause(GtkWidget *widget, gpointer data);
void change(GtkButton *button, gpointer data);
void steps(GtkWidget *window, gpointer data);
void set_lattice(struct base *Base);

#endif