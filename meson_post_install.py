#!/usr/bin/env python3

import os
import subprocess

prefix = os.environ['MESON_INSTALL_PREFIX']

schemadir = os.path.join(prefix, 'share', 'glib-2.0', 'schemas')
icondir = os.path.join(prefix, 'share', 'icons', 'hicolor')
appdir = os.path.join(prefix, 'share', 'applications')
mimedir = os.path.join(prefix, 'share', 'mime')

if not os.environ.get('DESTDIR'):
    print('Compiling GSettings schemas…')
    subprocess.call(['glib-compile-schemas', schemadir])

    print('Updating icon cache…')
    subprocess.call(['gtk-update-icon-cache', '-q', '-t', '-f', icondir])

    print('Updating desktop database…')
    subprocess.call(['update-desktop-database', '-q', appdir])

    print('Updating MIME database…')
    subprocess.call(['update-mime-database', mimedir])
