/*
 * SPDX-License-Identifier: MPL-2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 1997 - July 2008 CWI, August 2008 - 2023 MonetDB B.V.
 */

#ifndef _MAL_DATAFLOW_H
#define _MAL_DATAFLOW_H

#ifndef LIBMONETDB5
#error this file should not be included outside its source directory
#endif

#include "mal.h"
#include "mal_client.h"

extern str runMALdataflow(Client cntxt, MalBlkPtr mb, int startpc, int stoppc, MalStkPtr stk);
extern str deblockdataflow(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci);

#endif /*  _MAL_DATAFLOW_H*/
