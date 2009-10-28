#include "config.h"
#include <string.h>

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <gtksourceview/gtksourceview.h>

static GtkSourceView *view = NULL;

static void
test_auto_indent (void)
{
	gboolean value;

	gtk_source_view_set_auto_indent (view, TRUE);
	value = gtk_source_view_get_auto_indent (view);
	g_assert (value == TRUE);
	g_object_get (view, "auto-indent", &value, NULL);
	g_assert (value == TRUE);
}

static void
test_indent_on_tab (void)
{
	gboolean value;

	gtk_source_view_set_indent_on_tab (view, TRUE);
	value = gtk_source_view_get_indent_on_tab (view);
	g_assert (value == TRUE);
	g_object_get (view, "indent-on-tab", &value, NULL);
	g_assert (value == TRUE);
}

#define INDENT_WIDTH 10

static void
test_indent_width (void)
{
	gint width;
	
	gtk_source_view_set_indent_width (view, INDENT_WIDTH);
	width = gtk_source_view_get_indent_width (view);
	g_assert (width == INDENT_WIDTH);
	g_object_get (view, "indent-width", &width, NULL);
	g_assert (width == INDENT_WIDTH);
}

static void
test_insert_spaces_instead_of_tabs (void)
{
	gboolean value;

	gtk_source_view_set_insert_spaces_instead_of_tabs (view, TRUE);
	value = gtk_source_view_get_insert_spaces_instead_of_tabs (view);
	g_assert (value == TRUE);
	g_object_get (view, "insert-spaces-instead-of-tabs", &value, NULL);
	g_assert (value == TRUE);
	
	/*FIXME: This produces an assertion
	gtk_test_widget_send_key (GTK_WIDGET (view), GDK_Tab, 0);
	text = gtk_test_text_get (GTK_WIDGET (view));*/
}

static void
test_smart_home_end (void)
{
	GtkSourceSmartHomeEndType smart_home;

	gtk_source_view_set_smart_home_end (view, GTK_SOURCE_SMART_HOME_END_ALWAYS);
	smart_home = gtk_source_view_get_smart_home_end (view);
	g_assert (smart_home == GTK_SOURCE_SMART_HOME_END_ALWAYS);
	g_object_get (view, "smart-home-end", &smart_home, NULL);
	g_assert (smart_home == GTK_SOURCE_SMART_HOME_END_ALWAYS);
}

static void
test_highlight_current_line (void)
{
	gboolean value;

	gtk_source_view_set_highlight_current_line (view, TRUE);
	value = gtk_source_view_get_highlight_current_line (view);
	g_assert (value == TRUE);
	g_object_get (view, "highlight-current-line", &value, NULL);
	g_assert (value == TRUE);
}

static void
test_show_right_margin (void)
{
	gboolean value;

	gtk_source_view_set_show_right_margin (view, TRUE);
	value = gtk_source_view_get_show_right_margin (view);
	g_assert (value == TRUE);
	g_object_get (view, "show-right-margin", &value, NULL);
	g_assert (value == TRUE);
}

#define MARGIN_POS 100

static void
test_right_margin_position (void)
{
	gint pos;
	
	gtk_source_view_set_right_margin_position (view, MARGIN_POS);
	pos = gtk_source_view_get_right_margin_position (view);
	g_assert (pos == MARGIN_POS);
	g_object_get (view, "right-margin-position", &pos, NULL);
	g_assert (pos == MARGIN_POS);
}

#define TAB_WIDTH 9

static void
test_tab_width (void)
{
	gint width;
	
	gtk_source_view_set_tab_width (view, TAB_WIDTH);
	width = gtk_source_view_get_tab_width (view);
	g_assert (width == TAB_WIDTH);
	g_object_get (view, "tab-width", &width, NULL);
	g_assert (width == TAB_WIDTH);
}

static void
test_draw_spaces (void)
{
	GtkSourceDrawSpacesFlags flags;

	gtk_source_view_set_draw_spaces (view, GTK_SOURCE_DRAW_SPACES_ALL);
	flags = gtk_source_view_get_draw_spaces (view);
	g_assert (flags == GTK_SOURCE_DRAW_SPACES_ALL);
	g_object_get (view, "draw-spaces", &flags, NULL);
	g_assert (flags == GTK_SOURCE_DRAW_SPACES_ALL);
}

#define CATEGORY "category"
#define PRIORITY 10
#define COLOR "#9090eeee9090"

static void
test_mark_category (void)
{
	gint prio;
	GdkColor color;
	gchar *color_name;

	gdk_color_parse (COLOR, &color);
	gtk_source_view_set_mark_category_background (view, CATEGORY, &color);
	gtk_source_view_get_mark_category_background (view, CATEGORY, &color);
	color_name = gdk_color_to_string (&color);
	g_assert_cmpstr (COLOR, ==, color_name);
	g_free (color_name);
	
	gtk_source_view_set_mark_category_priority (view, CATEGORY, PRIORITY);
	prio = gtk_source_view_get_mark_category_priority (view, CATEGORY);
	g_assert (prio == PRIORITY);
}

int
main (int argc, char** argv)
{
	gtk_test_init (&argc, &argv);

	view = GTK_SOURCE_VIEW (gtk_source_view_new ());

	g_test_add_func ("/SourceView/auto-indent", test_auto_indent);
	g_test_add_func ("/SourceView/indent-on-tab", test_indent_on_tab);
	g_test_add_func ("/SourceView/indent-width", test_indent_width);
	g_test_add_func ("/SourceView/insert-spaces-instead-of-tabs",
			 test_insert_spaces_instead_of_tabs);
	g_test_add_func ("/SourceView/smart-home-end", test_smart_home_end);
	g_test_add_func ("/SourceView/hightlight-current-line",
			 test_highlight_current_line);
	g_test_add_func ("/SourceView/show-right-margin", test_show_right_margin);
	g_test_add_func ("/SourceView/right-margin-position",
			 test_right_margin_position);
	g_test_add_func ("/SourceView/tab-width", test_tab_width);
	g_test_add_func ("/SourceView/draw-spaces", test_draw_spaces);
	g_test_add_func ("/SourceView/mark-category",
			 test_mark_category);

	return g_test_run();
}
