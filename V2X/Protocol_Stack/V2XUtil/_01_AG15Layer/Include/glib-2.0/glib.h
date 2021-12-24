/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Modified by the GLib Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GLib Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GLib at ftp://ftp.gtk.org/pub/gtk/.
 */

#ifndef __G_LIB_H__
#define __G_LIB_H__

#define __GLIB_H_INSIDE__

#include "../../../_01_AG15Layer/Include/glib-2.0/glib/galloca.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/garray.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gasyncqueue.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gatomic.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gbacktrace.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gbase64.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gbitlock.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gbookmarkfile.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gbytes.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gcharset.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gchecksum.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gconvert.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gdataset.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gdate.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gdatetime.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gdir.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/genviron.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gerror.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gfileutils.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/ggettext.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/ghash.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/ghmac.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/ghook.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/ghostutils.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/giochannel.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gkeyfile.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/glist.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gmacros.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gmain.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gmappedfile.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gmarkup.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gmem.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gmessages.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gnode.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/goption.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gpattern.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gpoll.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gprimes.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gqsort.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gquark.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gqueue.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/grand.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gregex.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gscanner.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gsequence.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gshell.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gslice.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gslist.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gspawn.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gstrfuncs.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gstring.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gstringchunk.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gtestutils.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gthread.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gthreadpool.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gtimer.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gtimezone.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gtrashstack.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gtree.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gtypes.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gunicode.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gurifuncs.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gutils.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/guuid.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gvarianttype.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gvariant.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gversion.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/gversionmacros.h"
#ifdef G_PLATFORM_WIN32
#include <glib/gwin32.h>
#endif

#ifndef G_DISABLE_DEPRECATED
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/deprecated/gallocator.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/deprecated/gcache.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/deprecated/gcompletion.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/deprecated/gmain.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/deprecated/grel.h"
#include "../../../_01_AG15Layer/Include/glib-2.0/glib/deprecated/gthread.h"
#endif /* G_DISABLE_DEPRECATED */

#include "../../../_01_AG15Layer/Include/glib-2.0/glib/glib-autocleanups.h"

#undef __GLIB_H_INSIDE__

#endif /* __G_LIB_H__ */
