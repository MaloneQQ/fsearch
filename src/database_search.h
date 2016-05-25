/*
   FSearch - A fast file search utility
   Copyright © 2016 Christian Boxdörfer

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, see <http://www.gnu.org/licenses/>.
   */

#pragma once

#include <stdint.h>
#include "array.h"
#include "database_node.h"
#include "fsearch_thread_pool.h"

typedef struct _DatabaseSearch DatabaseSearch;
typedef struct _DatabaseSearchEntry DatabaseSearchEntry;

// search modes
enum {
    DB_SEARCH_MODE_NORMAL = 0,
    DB_SEARCH_MODE_REGEX = 1,
};

typedef enum {
    FSEARCH_FILTER_NONE,
    FSEARCH_FILTER_FOLDERS,
    FSEARCH_FILTER_FILES,
} FsearchFilter;

void
db_search_free (DatabaseSearch *search);

DatabaseSearch *
db_search_new (FsearchThreadPool *pool,
               DynamicArray *entries,
               uint32_t num_entries,
               const char *query,
               bool enable_regex,
               bool search_in_path);

GNode *
db_search_entry_get_node (DatabaseSearchEntry *entry);

uint32_t
db_search_entry_get_pos (DatabaseSearchEntry *entry);

void
db_search_entry_set_pos (DatabaseSearchEntry *entry, uint32_t pos);

void
db_search_set_query (DatabaseSearch *search, const char *query);

void
db_search_update (DatabaseSearch *search,
                  DynamicArray *entries,
                  uint32_t num_entries,
                  const char *query,
                  bool enable_regex,
                  bool search_in_path);

void
db_search_set_search_in_path (DatabaseSearch *search, bool search_in_path);

uint32_t
db_search_get_num_results (DatabaseSearch *search);

uint32_t
db_search_get_num_files (DatabaseSearch *search);

uint32_t
db_search_get_num_folders (DatabaseSearch *search);

GPtrArray *
db_search_get_results (DatabaseSearch *search);

void
db_search_remove_entry (DatabaseSearch *search, DatabaseSearchEntry *entry);

uint32_t
db_perform_search (DatabaseSearch *search,
                   FsearchFilter filter,
                   uint32_t max_results);
