/* print.h
 * Definitions for printing packet analysis trees.
 *
 * $Id: print.h,v 1.44 2004/05/09 10:03:37 guy Exp $
 *
 * Gilbert Ramirez <gram@alumni.rice.edu>
 *
 * Ethereal - Network traffic analyzer
 * By Gerald Combs <gerald@ethereal.com>
 * Copyright 1998 Gerald Combs
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef __PRINT_H__
#define __PRINT_H__

#include <epan/packet.h>


/* print output format */
typedef enum {
  PR_FMT_TEXT,    /* plain text */
  PR_FMT_PS,      /* postscript */
  PR_FMT_PSML,    /* packet summary markup language */
  PR_FMT_PDML     /* packet data markup language */
} print_format_e;

/* print_range, enum which frames should be printed */
typedef enum {
  print_range_selected_only,    /* selected frame(s) only (currently only one) */
  print_range_marked_only,      /* marked frames only */
  print_range_all_displayed,    /* all frames currently displayed */
  print_range_all_captured      /* all frames in capture */
} print_range_e;

/* print_dissections, enum how the dissections should be printed */
typedef enum {
  print_dissections_none,         /* no dissections at all */
  print_dissections_collapsed,    /* no dissection details */
  print_dissections_as_displayed, /* details as displayed */
  print_dissections_expanded      /* all dissection details */
} print_dissections_e;

typedef struct {
  print_format_e    format;		/* plain text, PostScript, PDML, ... */
  gboolean	to_file;	/* TRUE if we're printing to a file */
  char		*file;		/* file output pathname */
  char		*cmd;		/* print command string (not win32) */
  packet_range_t range;

  gboolean	print_summary;	/* TRUE if we should just print summary;
				   FALSE if we should print protocol tree. */
  print_dissections_e   print_dissections;
  gboolean	print_hex;	/* TRUE if we should also print hex data;
				   FALSE if we should print only if not dissected. */
  gboolean	print_formfeed; /* TRUE if a formfeed should be printed 
                   before each new packet */
} print_args_t;

/* Functions in print.h */

extern FILE *open_print_dest(int to_file, const char *dest);
extern gboolean close_print_dest(int to_file, FILE *fh);
extern void print_preamble(FILE *fh, print_format_e format, gchar *filename);
extern void print_packet_header(FILE *fh, print_format_e format, guint32 number, gchar *summary);
extern void print_formfeed(FILE *fh, print_format_e format);
extern void print_finale(FILE *fh, print_format_e format);
extern void proto_tree_print(print_args_t *print_args, epan_dissect_t *edt,
     FILE *fh);
extern void print_hex_data(FILE *fh, print_format_e format, epan_dissect_t *edt);
extern void print_line(FILE *fh, int indent, print_format_e format, char *line);

#endif /* print.h */
