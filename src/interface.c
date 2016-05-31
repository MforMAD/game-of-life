#include <interface.h>

void start(GtkApplication *app, gpointer data)
{
	struct base *Base = (struct base *)data;
	struct box *Box = &(basement->boxes);
	struct tpl *Tpl = &(basement->templates);

	Base->window = gtk_application_window_new(Base->app);
	gtk_window_set_title(GTK_WINDOW(Base->window), "Game of life");
	gtk_container_set_border_width(GTK_CONTAINER(Base->window), 50);
	
	Box->content = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	Box->menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	Box->rules = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	Box->levels = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	Box->game = gtk_grid_new();

	gtk_container_add(GTK_CONTAINER(Base->window), Box->content);
	gtk_widget_show_all(Base->window);
}