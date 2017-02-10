#include <glib.h>
#include <glib/gstdio.h>

#include "src/nautilus-link.h"

static void
test_create_link ()
{
    gchar *tempdir_path;
    gchar *tempdir_uri;
    gboolean result;
    GMappedFile *generated_file;
    gchar *generated_file_path;
    gchar *generated_file_contents;
    gchar *expected_contents;

    tempdir_path = g_strdup ("/tmp/create_link_XXXXXX");
    g_assert_nonnull (g_mkdtemp (tempdir_path));
    tempdir_uri = g_strdup_printf ("file://%s", tempdir_path);

    result = nautilus_link_local_create (tempdir_uri,
                                         "test_link",
                                         "Test",
                                         NULL,
                                         "/usr/bin/test",
                                         NULL,
                                         0,
                                         FALSE);

    /* The function claims it succeeded */
    g_assert_true (result);

    generated_file_path = g_strdup_printf ("%s/test_link.desktop", tempdir_path);
    generated_file = g_mapped_file_new (generated_file_path,
                                        FALSE,
                                        NULL);
    g_assert_nonnull (generated_file);

    generated_file_contents = g_mapped_file_get_contents (generated_file);

    expected_contents = g_strdup ("[Desktop Entry]\n"
                                  "Encoding=UTF-8\n"
                                  "Name=Test\n"
                                  "Type=Link\n"
                                  "URL=/usr/bin/test\n\n");

    /* The generated file matches expectations */
    g_assert_cmpstr (expected_contents, ==, generated_file_contents);

    g_mapped_file_unref (generated_file);

    g_unlink (generated_file_path);
    g_rmdir (tempdir_path);

    g_free (tempdir_path);
    g_free (tempdir_uri);
    g_free (generated_file_path);
    g_free (expected_contents);
}


static void
test_create_link_with_icon ()
{
    gchar *tempdir_path;
    gchar *tempdir_uri;
    gboolean result;
    GMappedFile *generated_file;
    gchar *generated_file_path;
    gchar *generated_file_contents;
    gchar *expected_contents;

    tempdir_path = g_strdup ("/tmp/create_link_XXXXXX");
    g_assert_nonnull (g_mkdtemp (tempdir_path));
    tempdir_uri = g_strdup_printf ("file://%s", tempdir_path);

    result = nautilus_link_local_create (tempdir_uri,
                                         "test_link",
                                         "Test",
                                         "computer",
                                         "/usr/bin/test",
                                         NULL,
                                         0,
                                         FALSE);

    /* The function claims it succeeded */
    g_assert_true (result);

    generated_file_path = g_strdup_printf ("%s/test_link.desktop", tempdir_path);
    generated_file = g_mapped_file_new (generated_file_path,
                                        FALSE,
                                        NULL);
    g_assert_nonnull (generated_file);

    generated_file_contents = g_mapped_file_get_contents (generated_file);

    expected_contents = g_strdup ("[Desktop Entry]\n"
                                  "Encoding=UTF-8\n"
                                  "Name=Test\n"
                                  "Type=Link\n"
                                  "URL=/usr/bin/test\n"
                                  "Icon=computer\n");

    /* The generated file matches expectations */
    g_assert_cmpstr (expected_contents, ==, generated_file_contents);

    g_mapped_file_unref (generated_file);

    // g_unlink (generated_file_path);
    // g_rmdir (tempdir_path);

    g_free (tempdir_path);
    g_free (tempdir_uri);
    g_free (generated_file_path);
    g_free (expected_contents);
}


static void
setup_test_suite ()
{
    g_test_add_func ("/link/1.0", test_create_link);
    g_test_add_func ("/link/1.1", test_create_link_with_icon);
}

int
main (int   argc, char *argv[])
{
    g_test_init (&argc, &argv, NULL);

    g_test_set_nonfatal_assertions ();

    setup_test_suite ();

    return g_test_run ();
}
