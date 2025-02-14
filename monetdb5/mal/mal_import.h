/*
 * SPDX-License-Identifier: MPL-2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 1997 - July 2008 CWI, August 2008 - 2023 MonetDB B.V.
 */

#ifndef _MAL_IMPORT_H
#define _MAL_IMPORT_H

#include "mal_exception.h"
#include "mal_client.h"
#include "mal_prelude.h"

mal_export str malIncludeString(Client c, const char *name, str mal, int listing, MALfcn address);

mal_export str malInclude(Client c, const char *name, int listing);
mal_export void slash_2_dir_sep(str fname);
mal_export str compileString(Symbol *fcn, Client c, str s);
#endif /*  _MAL_IMPORT_H */
