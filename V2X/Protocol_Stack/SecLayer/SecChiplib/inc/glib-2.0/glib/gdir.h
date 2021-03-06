/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * gdir.c: Simplified wrapper around the DIRENT functions.
 *
 * Copyright 2001 Hans Breuer
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __G_DIR_H__
#define __G_DIR_H__

#if !defined(__GLIB_H_INSIDE__) && !defined(GLIB_COMPILATION)
#error "Only <glib.h> can be included directly."
#endif

#include "./gerror.h"

#ifdef G_OS_UNIX
#include <dirent.h>
#endif

G_BEGIN_DECLS

typedef struct _GDir GDir;

GLIB_AVAILABLE_IN_ALL
GDir *g_dir_open(const gchar *path,
                 guint flags,
                 GError **error);
GLIB_AVAILABLE_IN_ALL
const gchar *g_dir_read_name(GDir *dir);
GLIB_AVAILABLE_IN_ALL
void g_dir_rewind(GDir *dir);
GLIB_AVAILABLE_IN_ALL
void g_dir_close(GDir *dir);

#ifndef __GTK_DOC_IGNORE__
#ifdef G_OS_WIN32
#define g_dir_open g_dir_open_utf8
#define g_dir_read_name g_dir_read_name_utf8

GLIB_AVAILABLE_IN_ALL
GDir *g_dir_open_utf8(const gchar *path,
                      guint flags,
                      GError **error);
GLIB_AVAILABLE_IN_ALL
const gchar *g_dir_read_name_utf8(GDir *dir);
#endif /* G_OS_WIN32 */
#endif /* __GTK_DOC_IGNORE__ */

G_END_DECLS

#endif /* __G_DIR_H__ */
