/*
 * Copyright (C) 2014 OpenSIPS Solutions
 *
 * This file is part of opensips, a free SIP server.
 *
 * opensips is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * opensips is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 * --------
 *  2014-10-30 initial version (liviu)
 */

/*
 * This header exposes the basic operations with an OpenSIPS context.
 *
 * A "context" is:
 *		- a data storage buffer
 *		- typically allocated next to the intended structure
 *			e.g. | struct cell | CONTEXT_BUFFER |
 *
 * !! All data registrations must be done in the pre-forking phases !!
 *		(see the register functions below)
 */

#ifndef __CONTEXT_H
#define __CONTEXT_H

#include <stdlib.h>

typedef void * context_p;
enum osips_context {
	CONTEXT_GLOBAL,
	CONTEXT_MSG,
	CONTEXT_TRAN,

	CONTEXT_COUNT,
};

#define context_of(entity_p) ((context_p)((entity_p) + 1))
#define context_size(enum_ctx) (context_sizes[enum_ctx])

extern context_p current_processing_ctx;
extern unsigned int context_sizes[];

/*
 * allocate a new GLOBAL context in pkg mem
 *
 * Note: this will not change the "current_ctx"
 */
context_p context_alloc(void);
#define   context_free(context_p) pkg_free(context_p)

/*
 * - the register functions should be called before any forks are made
 *		(mod_init(), function fixups)
 *
 * - they reserve and return a position in the context buffer of the given type
 */
inline int context_register_int(enum osips_context type);
inline int context_register_str(enum osips_context type);
inline int context_register_ptr(enum osips_context type);

inline void context_put_int(enum osips_context type, context_p ctx,
									 int pos, int data);
inline void context_put_str(enum osips_context type, context_p ctx,
									 int pos, str *data);
inline void context_put_ptr(enum osips_context type, context_p ctx,
									 int pos, void *data);

inline int   context_get_int(enum osips_context type, context_p ctx, int pos);
inline str  *context_get_str(enum osips_context type, context_p ctx, int pos);
inline void *context_get_ptr(enum osips_context type, context_p ctx, int pos);

#endif /* __CONTEXT_H */
