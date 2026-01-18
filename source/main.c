#include "data.h"
#include "version.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The macros VERSION, NAME, TARGET, AUTHOR and COPYRIGHT are available for this program to reference
information about itself. These macros are defined in config.mk */

static GtkBuilder*     builder;
static GtkApplication* app;

void activate(GtkApplication* app, gpointer user_data)
{
        (void)user_data;
        builder = gtk_builder_new_from_resource(APP_PREFIX "/window_main.ui");

        GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(builder, "window_main"));
        gtk_window_set_application(window, app);
        gtk_window_present(window);
        g_object_unref(builder);
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

        g_object_unref(app);
        return status;
}