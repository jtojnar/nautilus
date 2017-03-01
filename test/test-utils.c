#include <glib.h>
#include <glib/gstdio.h>

#include "test-utils.h"

void
tmpdir_autocleanup (gchar **path)
{
    rmdir_recursive (*path);
    g_free (*path);
}

int
rmdir_recursive (const gchar *path)
{
    int result = -1;
    GDir *directory = g_dir_open (path, 0, NULL);

    if (directory)
    {
        const gchar *entry;
        result = 0;

        while (!result && (entry = g_dir_read_name (directory)))
        {
            g_autofree gchar *entry_path = g_strdup_printf ("%s/%s", path, entry);

            if (g_file_test (entry_path, G_FILE_TEST_IS_DIR))
            {
                result = rmdir_recursive (entry_path);
            }
            else
            {
                result = g_unlink (entry_path);
            }
        }

        g_dir_close (directory);
    }

    if (!result)
    {
        result = g_rmdir (path);
    }

    return result;
}
