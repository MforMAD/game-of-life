#include <interface.h>

void start(GtkApplication *app, gpointer data)
{
	struct base *Base = (struct base *)data;
	struct box *Box = &(Base->boxes);
	struct tpl *Tpl = &(Base->templates);

	Base->window = gtk_application_window_new(Base->app);
	gtk_window_set_title(GTK_WINDOW(Base->window), "Game of life");
	gtk_container_set_border_width(GTK_CONTAINER(Base->window), 50);
	
	Box->content = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	Box->menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	Box->rules = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	Box->levels = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	Box->game = gtk_grid_new();

	fill_menu(Base);
	fill_info(Base);

	gtk_box_pack_start(GTK_BOX(Box->content), Box->menu, FALSE, FALSE, 5);
	gtk_container_add(GTK_CONTAINER(Base->window), Box->content);

	gtk_window_set_default_size (GTK_WINDOW(Base->window), 550, 400);

	gtk_widget_show_all(Base->window);
}

void fill_menu(struct base *Base)
{	
	struct box *Box = &(Base->boxes);
	GtkWidget *start;
	GtkWidget *info;
	GtkWidget *levels;
	GtkWidget *leave;

	start = gtk_button_new_with_label("Play");
	info = gtk_button_new_with_label("Information");
	levels = gtk_button_new_with_label("Templates");
	leave = gtk_button_new_with_label("Exit");

	g_signal_connect(start, "clicked", G_CALLBACK(play), Box);
	g_signal_connect(info, "clicked", G_CALLBACK(text), Base);
	g_signal_connect(levels, "clicked", G_CALLBACK(templates), Box);
	g_signal_connect(leave, "clicked", G_CALLBACK(close_app), Base);

	gtk_box_pack_start(GTK_BOX(Box->menu), start, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(Box->menu), info, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(Box->menu), levels, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(Box->menu), leave, FALSE, FALSE, 0);
}

void fill_info(struct base *Base)
{
	struct box *Box = &(Base->boxes);
	GtkWidget *text[3];
	GtkWidget *rules;
	GtkWidget *title;
	GtkWidget *back;

	title = gtk_label_new("Game of life.");
	rules = gtk_label_new("Rules of the 'Game of life'");
	text[0] = gtk_label_new("Button Play starts the game.");
	text[1] = gtk_label_new("Button Templates let's you choose the template for your game.");
	text[2] = gtk_label_new("Button Exit let's you leave the game.");
	back = gtk_button_new_with_label("Menu");

	g_signal_connect(back, "clicked", G_CALLBACK(call_menu), Base);

	gtk_box_pack_start(GTK_BOX(Box->rules), title, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(Box->rules), rules, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(Box->rules), text[0], FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(Box->rules), text[1], FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(Box->rules), text[2], FALSE, FALSE, 0);
	gtk_box_pack_end(GTK_BOX(Box->rules), back, FALSE, FALSE, 0);
}

void play(GtkWidget *widget, gpointer data)
{
	g_print("Play!\n");
}

void call_menu(GtkWidget *widget, gpointer data)
{
	g_print("Menu!\n");
	struct base *Base = (struct base *)data;
	struct box *Box = &(Base->boxes);
	GtkWidget *parent = gtk_widget_get_parent(widget);

	g_object_ref(G_OBJECT(parent));
	gtk_container_remove(GTK_CONTAINER(Box->content), parent);
	gtk_box_pack_start(GTK_BOX(Box->content), Box->menu, FALSE, FALSE, 5);

	gtk_widget_show_all(Base->window);
}

void text(GtkWidget *widget, gpointer data)
{
	struct base *Base = (struct base *)data;
	struct box *Box = &(Base->boxes);
	
	g_object_ref(G_OBJECT(Box->menu));
	gtk_container_remove(GTK_CONTAINER(Box->content), gtk_widget_get_parent(widget));
	gtk_box_pack_start(GTK_BOX(Box->content), Box->rules, FALSE, FALSE, 5);
	
	gtk_widget_show_all(Base->window);
}

void templates(GtkWidget *widget, gpointer data)
{
	g_print("Templates!\n");
}

void close_app(GtkWidget *widget, gpointer data)
{
	struct base *Base = (struct base *)data;
	gtk_application_remove_window(GTK_APPLICATION(Base->app), GTK_WINDOW(Base->window));
}

