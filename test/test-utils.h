#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#define dir_make_tmp_autoclean(variable) \
    _GLIB_CLEANUP(tmpdir_autocleanup) gchar *variable = g_dir_make_tmp (NULL, NULL)

void
tmpdir_autocleanup (gchar **path);

int
rmdir_recursive (const gchar *path);

#endif /* TEST_UTILS_H */
