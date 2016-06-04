#include <interface.h>
#include <template.h>
#include <field.h>
#include <unistd.h>


field *level = NULL;
int level_width = 15;
int level_height = 15;
int Pause = 1;
int Party = 0;
int End = 0;

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

	level = field_create(15);
	set_lattice(Base);
	fill_menu(Base);
	fill_info(Base);
	fill_templates(Base);
	fill_game(Base);

	gtk_box_pack_start(GTK_BOX(Box->content), Box->menu, FALSE, FALSE, 5);
	gtk_container_add(GTK_CONTAINER(Base->window), Box->content);

	gtk_window_resize(GTK_WINDOW(Base->window), 160, 250);

	gtk_widget_show_all(Base->window);
}

void fill_menu(struct base *Base)
{	
	struct box *Box = &(Base->boxes);
	GtkWidget *start;
	GtkWidget *info;
	GtkWidget *levels;
	GtkWidget *party;
	GtkWidget *leave;

	start = gtk_button_new_with_label("Play");
	info = gtk_button_new_with_label("Information");
	levels = gtk_button_new_with_label("Templates");
	party = gtk_button_new_with_label("PARTY MODE: OFF");
	leave = gtk_button_new_with_label("Exit");

	g_signal_connect(start, "clicked", G_CALLBACK(play), Base);
	g_signal_connect(info, "clicked", G_CALLBACK(text), Base);
	g_signal_connect(levels, "clicked", G_CALLBACK(templates), Base);
	g_signal_connect(party, "clicked", G_CALLBACK(party_time), NULL);
	g_signal_connect(leave, "clicked", G_CALLBACK(close_app), Base);

	gtk_box_pack_start(GTK_BOX(Box->menu), start, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(Box->menu), info, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(Box->menu), levels, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(Box->menu), party, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(Box->menu), leave, FALSE, FALSE, 0);
}

void fill_info(struct base *Base)
{
	struct box *Box = &(Base->boxes);
	GtkWidget *title;
	GtkWidget *text;
	GtkTextBuffer *buffer;
	GtkTextIter iter;
	GtkWidget *back;

	title = gtk_label_new("Game of life.");
	buffer = gtk_text_buffer_new(NULL);

  	gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

  	gtk_text_buffer_create_tag (buffer, "lmarg", "left_margin", 20, NULL);
  	gtk_text_buffer_insert(buffer, &iter, "The Game of Life, also known simply as Life, is a cellular automaton devised by the British \nmathematician John Horton Conway in 1970.\n", -1);
	gtk_text_buffer_insert_with_tags_by_name(buffer, &iter, "Any live cell with fewer than two live neighbours dies, as if caused by under-population.\n", -1, "lmarg", NULL);
	gtk_text_buffer_insert_with_tags_by_name(buffer, &iter, "Any live cell with two or three live neighbours lives on to the next generation.\n", -1, "lmarg", NULL);
	gtk_text_buffer_insert_with_tags_by_name(buffer, &iter, "Any live cell with more than three live neighbours dies, as if by over-population.\n", -1, "lmarg", NULL);
	gtk_text_buffer_insert_with_tags_by_name(buffer, &iter, "Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.", -1, "lmarg", NULL);

	text = gtk_text_view_new_with_buffer(buffer);


	gtk_text_view_set_editable(GTK_TEXT_VIEW(text), FALSE);
	back = gtk_button_new_with_label("Menu");

	g_signal_connect(back, "clicked", G_CALLBACK(call_menu), Base);

	gtk_box_pack_start(GTK_BOX(Box->rules), title, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(Box->rules), text, FALSE, FALSE, 0);
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
	template->file_name = search_templates(&(template->files_counter));
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
	// GtkWidget *status;
	GtkWidget *step;
	GtkWidget *randomize;
	GtkWidget *clean;
	struct box *Box = &(Base->boxes);

	back = gtk_button_new_with_label("Menu");
	// status = gtk_button_new_with_label("Start");
	step = gtk_button_new_with_label("Step");
	randomize = gtk_button_new_with_label("Randomize");
	clean = gtk_button_new_with_label("Clean");

	g_signal_connect(back, "clicked", G_CALLBACK(call_menu_clean), Base);
	// g_signal_connect(status, "clicked", G_CALLBACK(unpause), Base);
	g_signal_connect(step, "clicked", G_CALLBACK(steps), Base);
	g_signal_connect(randomize, "clicked", G_CALLBACK(field_random), Base);
	g_signal_connect(clean, "clicked", G_CALLBACK(field_clean), Base);

	gtk_box_pack_start(GTK_BOX(Box->game_box), Box->game, FALSE, FALSE, 10);
	// gtk_box_pack_start(GTK_BOX(Box->game_box), status, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(Box->game_box), step, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(Box->game_box), randomize, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(Box->game_box), clean, FALSE, FALSE, 0);
	gtk_box_pack_end(GTK_BOX(Box->game_box), back, FALSE, FALSE, 0);

}

void set_lattice(struct base *Base)
{
	int i;
	int j;
	Base->lattice = malloc(sizeof(struct pair *) * level_height);
	if (Base->lattice == NULL)
		perror("Something went wrong: ");

	for (i = 0; i < level_height; i++) {
		Base->lattice[i] = malloc(sizeof(struct pair) * level_width);
		if (Base->lattice[i] == NULL)
			perror("Something went wrong: ");
	}

	struct pair **Pair = Base->lattice;

	for (i = 0; i < level_height; i++) {
		for (j = 0; j < level_width; j++) {
			Pair[i][j].button = gtk_button_new();
			GtkImage *clean = (GtkImage *) gtk_image_new_from_file("./icons/transparent_20x20.png");
			gtk_button_set_image(GTK_BUTTON(Pair[i][j].button), (GtkWidget *) clean);
			Pair[i][j].row = i;
			Pair[i][j].col = j;
			g_signal_connect(Pair[i][j].button, "clicked", G_CALLBACK(change), &Pair[i][j]);
			gtk_grid_attach(GTK_GRID(Base->boxes.game), Pair[i][j].button, i, j, 1 , 1);
		}
	}
}

void play(GtkWidget *widget, gpointer data)
{
	struct base *Base = (struct base *)data;
	struct box *Box = &(Base->boxes);
	
	g_object_ref(G_OBJECT(Box->menu));
	gtk_container_remove(GTK_CONTAINER(Box->content), gtk_widget_get_parent(widget));
	gtk_box_pack_start(GTK_BOX(Box->content), Box->game_box, FALSE, FALSE, 5);
	gtk_container_set_border_width(GTK_CONTAINER(Base->window), 10);
	gtk_widget_show_all(Base->window);
}

// void unpause(GtkWidget *widget, gpointer data)
// {
// 	struct base *Base = (struct base *)data;

// 	// if (Pause) {
// 	// 	Pause = 0;
// 	// 	gtk_button_set_label(GTK_BUTTON(widget), "Play");
// 	// 	gtk_widget_show_all(Base->window);
// 	// }
// 	// else {
// 	// 	Pause = 1;
// 	// 	gtk_button_set_label(GTK_BUTTON(widget), "Pause");
// 	// 	gtk_widget_show_all(Base->window);
// 	// }

// 	while (!End) {
// 		steps(NULL, data);
// 		usleep(1000000);
// 	}
// }

void call_menu(GtkWidget *widget, gpointer data)
{
	struct base *Base = (struct base *)data;
	struct box *Box = &(Base->boxes);
	GtkWidget *parent = gtk_widget_get_parent(widget);

	g_object_ref(G_OBJECT(parent));
	gtk_container_remove(GTK_CONTAINER(Box->content), parent);
	gtk_box_pack_start(GTK_BOX(Box->content), Box->menu, FALSE, FALSE, 5);
	gtk_window_resize(GTK_WINDOW(Base->window), 160, 250);
	gtk_container_set_border_width(GTK_CONTAINER(Base->window), 50);

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
	struct base *Base = (struct base *)data;	
	const char *text;
	char path[50] = "./tpl/";
	char *end = path + strlen(path);
	char extension[] = ".tpl";

	text = gtk_button_get_label(GTK_BUTTON(widget));
	strcpy(end, text);
	end = path + strlen(path);
	strcpy(end, extension);
	FILE *f = fopen(path, "r");
	level = field_read_template(level, f);
	fclose(f);

	lattice_update(Base->lattice);
}

void base_free(struct base *Base)
{
	int i;
	for (i = 0; i < level_height; i++) {
		free(Base->lattice[i]);
	}
	level = field_delete(level);
	free(Base->lattice);
	free(Base->templates.file_name);
	free(Base->templates.buttons);
}

void change(GtkButton *button, gpointer data)
{
	struct pair *Pair = (struct pair *)data;

	if (level->current_table[Pair->row][Pair->col] == DEAD) {
		GtkImage *alive;
		if (Party)
			alive = (GtkImage *) gtk_image_new_from_file("./icons/parrot_20x20.gif");
		else
			alive = (GtkImage *) gtk_image_new_from_file("./icons/smile_transparent_20x20.png");
		gtk_button_set_image(GTK_BUTTON(Pair->button), (GtkWidget *) alive);
		level->current_table[Pair->row][Pair->col] = LIVING;
	}
	else {
		GtkImage *dead = (GtkImage *) gtk_image_new_from_file("./icons/transparent_20x20.png");
		gtk_button_set_image(GTK_BUTTON(Pair->button), (GtkWidget *) dead);
		level->current_table[Pair->row][Pair->col] = DEAD;
	}
}

void steps(GtkWidget *window, gpointer data)
{
	struct base *Base = (struct base *)data;
	struct pair **Pair = Base->lattice;

	End = field_next_gen(level);
	lattice_update(Pair);
	gtk_widget_show_all(Base->window);
}

void party_time(GtkWidget *widget, gpointer data)
{
	if (Party == 0) {
		Party = 1;
		gtk_button_set_label(GTK_BUTTON(widget), "PARTY MODE: ON");
	}
	else {
		Party = 0;
		gtk_button_set_label(GTK_BUTTON(widget), "PARTY MODE: OFF");

	}
}

void field_random(GtkWidget *widget, gpointer data)	
{
	struct base *Base = (struct base *)data;
	field_random_gen(level);
	lattice_update(Base->lattice);
	End = 0;
	gtk_widget_show_all(Base->window);
}

void field_clean(GtkWidget *widget, gpointer data)	
{
	struct base *Base = (struct base *)data;
	field_clear(level);
	lattice_update(Base->lattice);
	End = 0;
	gtk_widget_show_all(Base->window);
}

void lattice_update(struct pair **Pair)
{
	int i;
	int j;

	for (i = 0; i < level_width; i++) {
		for (j = 0; j < level_height; j++)  {
			if (level->current_table[i][j] == DEAD) {
				GtkImage *dead = (GtkImage *) gtk_image_new_from_file("./icons/transparent_20x20.png");
				gtk_button_set_image(GTK_BUTTON(Pair[i][j].button), (GtkWidget *) dead);
			}
			else {
				GtkImage *alive;
				if (Party)
					alive = (GtkImage *) gtk_image_new_from_file("./icons/parrot_20x20.gif");
				else
					alive = (GtkImage *) gtk_image_new_from_file("./icons/smile_transparent_20x20.png");
				gtk_button_set_image(GTK_BUTTON(Pair[i][j].button), (GtkWidget *) alive);
			}
		}
	}
}

void call_menu_clean(GtkWidget *widget, gpointer data)
{
	struct base *Base = (struct base *)data;

	End = 0;
	field_clear(level);
	lattice_update(Base->lattice);
	call_menu(widget, data);
}