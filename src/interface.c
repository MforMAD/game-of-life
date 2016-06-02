#include <interface.h>
#include <template.h>

char **level = NULL;
int level_width = 5;
int level_height = 5;
const char DEAD[] = " ";
const char ALIVE[] = "#";

void start(GtkApplication *app, gpointer data)
{
	struct base *Base = (struct base *)data;
	struct box *Box = &(Base->boxes);

	Base->window = gtk_application_window_new(Base->app);
	gtk_window_set_title(GTK_WINDOW(Base->window), "Game of life");
	gtk_container_set_border_width(GTK_CONTAINER(Base->window), 50);
	
	Box->content = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	Box->menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	Box->rules = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	Box->levels = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	Box->game_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	Box->game = gtk_grid_new();
	// gtk_grid_set_column_homogeneous(GTK_GRID(Box->game), TRUE);
	// gtk_grid_set_row_homogeneous(GTK_GRID(Box->game), TRUE);

	fill_menu(Base);
	fill_info(Base);
	fill_templates(Base);
	fill_game(Base);

	gtk_box_pack_start(GTK_BOX(Box->content), Box->menu, FALSE, FALSE, 5);
	gtk_container_add(GTK_CONTAINER(Base->window), Box->content);

	gtk_window_set_default_size (GTK_WINDOW(Base->window), 550, 400);

	gtk_widget_show_all(Base->window);
}

void set_default_level(struct base *Base)
{
	int i;
	int j;
	level = malloc(sizeof(char *) * level_height);
	Base->lattice = malloc(sizeof(struct pair *) * level_height);

	if (level == NULL || Base->lattice == NULL)
		perror("Something went wrong: ");

	for (i = 0; i < level_height; i++) {
		level[i] = malloc(sizeof(char) * level_width);
		Base->lattice[i] = malloc(sizeof(struct pair) * level_width);
		if (level[i] == NULL || Base->lattice[i] == NULL)
			perror("Something went wrong: ");
	}

	struct pair **Pair = Base->lattice;

	for (i = 0; i < level_height; i++) {
		for (j = 0; j < level_width; j++) {
			level[i][j] = '#';
			char content[2] = {'\0', '\0'};
			content[0] = level[i][j];
			// Pair[i][j].button = gtk_button_new_with_label(_(content));
			Pair[i][j].button = gtk_button_new();
			GtkImage *smile = (GtkImage *) gtk_image_new_from_file("./icons/smile_40x40.png");
			gtk_button_set_image(GTK_BUTTON(Pair[i][j].button), (GtkWidget *) smile);
			Pair[i][j].text = gtk_label_new(_(content));
			Pair[i][j].row = i;
			Pair[i][j].col = j;
			gtk_widget_hide(Pair[i][j].text);
			g_signal_connect(Pair[i][j].button, "clicked", G_CALLBACK(change), &Pair[i][j]);
			gtk_grid_attach(GTK_GRID(Base->boxes.game), Pair[i][j].button, i, j, 1 , 1);
			gtk_grid_attach(GTK_GRID(Base->boxes.game), Pair[i][j].text, i, j, 1 , 1);
		}
	}
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

	g_signal_connect(start, "clicked", G_CALLBACK(play), Base);
	g_signal_connect(info, "clicked", G_CALLBACK(text), Base);
	g_signal_connect(levels, "clicked", G_CALLBACK(templates), Base);
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

void fill_templates(struct base *Base)
{
	int i;
	struct box *Box = &(Base->boxes);
	struct tpl *template = &(Base->templates);
	GtkWidget *menu;

	menu = gtk_button_new_with_label("Menu");
	g_signal_connect(menu, "clicked", G_CALLBACK(call_menu), Base);;
	template->file_name = search_templates("/home/evgerher/SibSutis/game-of-life/tpl", &(template->files_counter));
	if (template->files_counter > 0) {
		template->buttons = malloc(sizeof(GtkWidget *) * template->files_counter);
		for (i = 0; i < template->files_counter; i++) {
			template->buttons[i] = gtk_button_new_with_label(_(template->file_name[i]));
			gtk_box_pack_start(GTK_BOX(Box->levels), template->buttons[i], FALSE, FALSE, 0);
			g_signal_connect(template->buttons[i], "clicked", G_CALLBACK(set_level), Base);
		}
	}

	gtk_box_pack_end(GTK_BOX(Box->levels), menu, FALSE, FALSE, 5);
}

void fill_game(struct base *Base)
{
	GtkWidget *back;
	struct box *Box = &(Base->boxes);

	back = gtk_button_new_with_label("Menu");
	g_signal_connect(back, "clicked", G_CALLBACK(call_menu), Base);
	gtk_box_pack_start(GTK_BOX(Box->game_box), Box->game, FALSE, FALSE, 10);
	gtk_box_pack_end(GTK_BOX(Box->game_box), back, FALSE, FALSE, 0);
	set_default_level(Base);
}

void play(GtkWidget *widget, gpointer data)
{
	g_print("Play!\n");
	struct base *Base = (struct base *)data;
	struct box *Box = &(Base->boxes);
	
	g_object_ref(G_OBJECT(Box->menu));
	gtk_container_remove(GTK_CONTAINER(Box->content), gtk_widget_get_parent(widget));
	gtk_box_pack_start(GTK_BOX(Box->content), Box->game_box, FALSE, FALSE, 5);
	
	gtk_widget_show_all(Base->window);
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
	struct base *Base = (struct base *)data;
	struct box *Box = &(Base->boxes);
	
	g_object_ref(G_OBJECT(Box->menu));
	gtk_container_remove(GTK_CONTAINER(Box->content), gtk_widget_get_parent(widget));
	gtk_box_pack_start(GTK_BOX(Box->content), Box->levels, FALSE, FALSE, 5);
	
	gtk_widget_show_all(Base->window);
}

void close_app(GtkWidget *widget, gpointer data)
{
	struct base *Base = (struct base *)data;
	gtk_application_remove_window(GTK_APPLICATION(Base->app), GTK_WINDOW(Base->window));
}

void set_level(GtkWidget *widget, gpointer data)
{
	const char *text;
	text = gtk_button_get_label(GTK_BUTTON(widget));
	g_print("Set the level \"%s\"\n", text);
	// free(level);
	// level = ...
}

void base_free(struct base *Base)
{
	int i;
	for (i = 0; i < level_height; i++) {
		free(level[i]);
		free(Base->lattice[i]);
	}
	free(level);
	free(Base->lattice);
	free(Base->templates.file_name);
	free(Base->templates.buttons);
}

void change(GtkButton *button, gpointer data)
{
	const char *text;
	struct pair *Pair = (struct pair *)data;

	text = gtk_label_get_text(GTK_LABEL(Pair->text));
	if (strcmp(text, DEAD) == 0) {
		GtkImage *alive = (GtkImage *) gtk_image_new_from_file("./icons/smile_40x40.png");
		gtk_button_set_image(GTK_BUTTON(Pair->button), (GtkWidget *) alive);
		gtk_label_set_text(GTK_LABEL(Pair->text), _(ALIVE));
		level[Pair->row][Pair->col] = ALIVE[0];
	}
	else {
		GtkImage *dead = (GtkImage *) gtk_image_new_from_file("./icons/clean_40x40.png");
		gtk_button_set_image(GTK_BUTTON(Pair->button), (GtkWidget *) dead);
		gtk_label_set_text(GTK_LABEL(Pair->text), _(DEAD));
		level[Pair->row][Pair->col] = DEAD[0];
	}
}
