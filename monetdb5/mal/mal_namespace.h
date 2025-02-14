/*
 * SPDX-License-Identifier: MPL-2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 1997 - July 2008 CWI, August 2008 - 2023 MonetDB B.V.
 */

#ifndef _MAL_NAMESPACE_H
#define _MAL_NAMESPACE_H

mal_export void initNamespace(void);
mal_export const char *putName(const char *nme);
mal_export const char *putNameLen(const char *nme, size_t len);
mal_export const char *getName(const char *nme);
mal_export const char *getNameLen(const char *nme, size_t len);

#endif /* _MAL_NAMESPACE_H */
