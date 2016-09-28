#!/bin/sh
test -n "$srcdir" || srcdir=$(dirname "$0")
test -n "$srcdir" || srcdir=.

cd $srcdir

VERSION=$(git describe --abbrev=0)
NAME="nautilus-$VERSION"

echo "Updating submodules…"
git submodule update --init

echo "Creating git tree archive…"
scripts/git-archive-all.sh --prefix "$NAME/" "$NAME.tar"

echo "Compressing archive…"
xz -f "$NAME.tar"
