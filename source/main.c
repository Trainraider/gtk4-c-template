#include "data.h"
#include "version.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The macros VERSION, NAME, TARGET, AUTHOR and COPYRIGHT are available for this program to reference
information about itself. These macros are defined in config.mk */

static GtkBuilder* builder;
static GtkApplication* app;

void check_gobject(GObject* obj, gchar* failure_msg)
{
        if (obj)
                return;
        if (failure_msg) {
                g_printerr("%s", failure_msg);
        } else {
                g_printerr("Error: Failed to get GObject\n");
        }
        g_application_quit(G_APPLICATION(app));
        exit(1);
}

typedef struct {
        GtkLabel* label;
        int       value;
        char      text[32];
} CounterLabel;

void connect_button_to_label(gchar* button_name, gchar* label_name, CounterLabel* state, GtkBuilder* builder)
{
        GObject* button = gtk_builder_get_object(builder, button_name);
        check_gobject(button, NULL);
        GObject* label = gtk_builder_get_object(builder, label_name);
        check_gobject(label, NULL);
        state->label = GTK_LABEL(label);
        g_object_set_data(button, "state", state);
}

static CounterLabel label_1_state;
static CounterLabel label_2_state;

void on_button_1_clicked(GtkWidget* widget, gpointer data)
{
        (void)data;
        CounterLabel* state = g_object_get_data(G_OBJECT(widget), "state");
        state->value++;
        snprintf(state->text, sizeof(state->text), "%d", state->value);
        gtk_label_set_label(state->label, state->text);
}

void on_button_2_clicked(GtkWidget* widget, gpointer data)
{
        (void)widget;
        CounterLabel* state = (CounterLabel*)data;
        state->value++;
        snprintf(state->text, sizeof(state->text), "%d", state->value);
        gtk_label_set_label(state->label, state->text);
}

void activate(GtkApplication* app, gpointer user_data)
{
        (void)user_data;
        GtkBuilderScope* scope = gtk_builder_cscope_new();
        gtk_builder_cscope_add_callback(scope, on_button_1_clicked);

        /* If you register signals in the xml/blueprint, you also must now register */
        /* your callbacks via a new scope system in GTK 4. */
        builder = gtk_builder_new();
        gtk_builder_set_scope(builder, scope);
        GError* error = NULL;
        gtk_builder_add_from_resource(builder, APP_PREFIX "/window_main.ui", &error);
        if (error) {
                g_printerr("Error: Failed to load UI resource: %s\n", error->message);
                g_clear_error(&error);
                exit(1);
        }
        g_object_unref(scope);
        /*
        If you manage signals/callbacks entirely in your code source files, it's
        a simple one liner to initialize the builder:

        builder = gtk_builder_new_from_resource(APP_PREFIX "/window_main.ui");
        */

        GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(builder, "window_main"));
        check_gobject(G_OBJECT(window), "Error: Failed to get the main window.\n");
        gtk_window_set_application(window, app);
        gtk_window_present(window);

        connect_button_to_label("counter_1", "label_1", &label_1_state, builder);
        connect_button_to_label("counter_2", "label_2", &label_2_state, builder);

        GObject* button_2 = gtk_builder_get_object(builder, "counter_2");

        g_signal_connect(button_2, "clicked", G_CALLBACK(on_button_2_clicked), &label_2_state);
}

int main(int argc, char* argv[])
{
        if (argc >= 2) {
                if (0 == strcmp(argv[1], "--version"))
                        version();
        }

        app = gtk_application_new(APP_ID, G_APPLICATION_DEFAULT_FLAGS);
        g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
        int status = g_application_run(G_APPLICATION(app), argc, argv);

        if (builder)
                g_object_unref(builder);
        g_object_unref(app);

        return status;
}