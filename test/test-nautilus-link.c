#include <glib.h>
#include <glib/gstdio.h>

#include "src/nautilus-link.h"
#include "test-utils.h"

static void
test_create_link ()
{
    dir_make_tmp_autoclean (tempdir_path);
    g_assert_nonnull (tempdir_path);
    g_autofree gchar *tempdir_uri = g_strdup_printf ("file://%s", tempdir_path);

    gboolean result = nautilus_link_local_create (tempdir_uri,
                                                  "test_link",
                                                  "Test",
                                                  NULL,
                                                  "/usr/bin/test",
                                                  NULL,
                                                  0,
                                                  FALSE);

    /* The function claims it succeeded */
    g_assert_true (result);

    g_autofree gchar *generated_file_path = g_strdup_printf ("%s/test_link.desktop", tempdir_path);
    g_autoptr (GMappedFile) generated_file = g_mapped_file_new (generated_file_path,
                                                                FALSE,
                                                                NULL);
    g_assert_nonnull (generated_file);

    gchar *generated_file_contents = g_mapped_file_get_contents (generated_file);

    g_autofree gchar *expected_contents = g_strdup ("[Desktop Entry]\n"
                                                    "Encoding=UTF-8\n"
                                                    "Name=Test\n"
                                                    "Type=Link\n"
                                                    "URL=/usr/bin/test\n\n");

    /* The generated file matches expectations */
    g_assert_cmpstr (expected_contents, ==, generated_file_contents);
}


static void
test_create_link_null_directory ()
{
    if (g_test_subprocess ())
    {
        nautilus_link_local_create (NULL,
                                    "test_link",
                                    "Test",
                                    NULL,
                                    "/usr/bin/test",
                                    NULL,
                                    0,
                                    FALSE);
    }

    g_test_trap_subprocess (NULL, 0, 0);
    g_test_trap_assert_failed ();
}


static void
test_create_link_null_base_name ()
{
    if (g_test_subprocess ())
    {
        dir_make_tmp_autoclean (tempdir_path);
        g_assert_nonnull (tempdir_path);
        g_autofree gchar *tempdir_uri = g_strdup_printf ("file://%s", tempdir_path);

        nautilus_link_local_create (tempdir_uri,
                                    NULL,
                                    "Test",
                                    NULL,
                                    "/usr/bin/test",
                                    NULL,
                                    0,
                                    FALSE);
    }

    g_test_trap_subprocess (NULL, 0, 0);
    g_test_trap_assert_failed ();
}


static void
test_create_link_null_display_name ()
{
    if (g_test_subprocess ())
    {
        dir_make_tmp_autoclean (tempdir_path);
        g_assert_nonnull (tempdir_path);
        g_autofree gchar *tempdir_uri = g_strdup_printf ("file://%s", tempdir_path);

        nautilus_link_local_create (tempdir_uri,
                                    "test_link",
                                    NULL,
                                    NULL,
                                    "/usr/bin/test",
                                    NULL,
                                    0,
                                    FALSE);
    }

    g_test_trap_subprocess (NULL, 0, 0);
    g_test_trap_assert_failed ();
}


static void
test_create_link_null_target ()
{
    if (g_test_subprocess ())
    {
        dir_make_tmp_autoclean (tempdir_path);
        g_assert_nonnull (tempdir_path);
        g_autofree gchar *tempdir_uri = g_strdup_printf ("file://%s", tempdir_path);

        nautilus_link_local_create (tempdir_uri,
                                    "test_link",
                                    "Test",
                                    NULL,
                                    NULL,
                                    NULL,
                                    0,
                                    FALSE);
    }

    g_test_trap_subprocess (NULL, 0, 0);
    g_test_trap_assert_failed ();
}


static void
test_create_link_with_icon ()
{
    dir_make_tmp_autoclean (tempdir_path);
    g_assert_nonnull (tempdir_path);
    g_autofree gchar *tempdir_uri = g_strdup_printf ("file://%s", tempdir_path);

    gboolean result = nautilus_link_local_create (tempdir_uri,
                                                  "test_link",
                                                  "Test",
                                                  "computer",
                                                  "/usr/bin/test",
                                                  NULL,
                                                  0,
                                                  FALSE);

    /* The function claims it succeeded */
    g_assert_true (result);

    g_autofree gchar *generated_file_path = g_strdup_printf ("%s/test_link.desktop", tempdir_path);
    g_autoptr (GMappedFile) generated_file = g_mapped_file_new (generated_file_path,
                                                                FALSE,
                                                                NULL);
    g_assert_nonnull (generated_file);

    gchar *generated_file_contents = g_mapped_file_get_contents (generated_file);

    g_autofree gchar *expected_contents = g_strdup ("[Desktop Entry]\n"
                                                    "Encoding=UTF-8\n"
                                                    "Name=Test\n"
                                                    "Type=Link\n"
                                                    "URL=/usr/bin/test\n"
                                                    "Icon=computer\n");

    /* The generated file matches expectations */
    g_assert_cmpstr (expected_contents, ==, generated_file_contents);
}


static void
test_set_text ()
{
    dir_make_tmp_autoclean (tempdir_path);
    g_assert_nonnull (tempdir_path);
    g_autofree gchar *tempdir_uri = g_strdup_printf ("file://%s", tempdir_path);

    gboolean result = nautilus_link_local_create (tempdir_uri,
                                                  "test_link",
                                                  "Test",
                                                  "computer",
                                                  "/usr/bin/test",
                                                  NULL,
                                                  0,
                                                  FALSE);

    /* The function claims it succeeded */
    g_assert_true (result);

    g_autofree gchar *generated_file_path = g_strdup_printf ("%s/test_link.desktop", tempdir_path);
    g_autoptr (GMappedFile) generated_file = g_mapped_file_new (generated_file_path,
                                                                FALSE,
                                                                NULL);
    g_assert_nonnull (generated_file);

    gchar *generated_file_contents = g_mapped_file_get_contents (generated_file);

    g_autofree gchar *expected_contents = g_strdup ("[Desktop Entry]\n"
                                                    "Encoding=UTF-8\n"
                                                    "Name=Test\n"
                                                    "Type=Link\n"
                                                    "URL=/usr/bin/test\n"
                                                    "Icon=computer\n");

    /* The generated file matches expectations */
    g_assert_cmpstr (expected_contents, ==, generated_file_contents);
}


static void
setup_test_suite ()
{
    g_test_add_func ("/link/1.0", test_create_link);
    g_test_add_func ("/link/1.1", test_create_link_null_directory);
    g_test_add_func ("/link/1.2", test_create_link_null_base_name);
    g_test_add_func ("/link/1.3", test_create_link_null_display_name);
    g_test_add_func ("/link/1.4", test_create_link_null_target);
    g_test_add_func ("/link/1.5", test_create_link_with_icon);
    g_test_add_func ("/link/2.0", test_set_text);
}

int
main (int   argc,
      char *argv[])
{
    g_test_init (&argc, &argv, NULL);

    g_test_set_nonfatal_assertions ();

    setup_test_suite ();

    return g_test_run ();
}