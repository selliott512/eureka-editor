//------------------------------------------------------------------------
//  RECENT FILES / KNOWN IWADS / BACKUPS
//------------------------------------------------------------------------
//
//  Eureka DOOM Editor
//
//  Copyright (C) 2012-2013 Andrew Apted
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//------------------------------------------------------------------------

#ifndef __EUREKA_M_FILES_H__
#define __EUREKA_M_FILES_H__

#include "m_strings.h"
#include "sys_type.h"

#include <deque>
#include <ostream>

#include "filesystem.hpp"
namespace fs = ghc::filesystem;

class Wad_file;



//------------------------------------------------------------------------
//  RECENT FILE HANDLING
//------------------------------------------------------------------------

#define MAX_RECENT  24


// this is for the "File/Recent" menu callbacks
class recent_file_data_c
{
public:
	fs::path file;
	SString map;

public:
	recent_file_data_c(const fs::path &_file, const SString &_map) :
		file(_file), map(_map)
	{ }

	recent_file_data_c(const recent_file_data_c &other) = default;

	recent_file_data_c() = default;
};


class RecentFiles_c
{
private:
	typedef std::deque<recent_file_data_c> Deque;

	void push_front(const fs::path &file, const SString &map);
	Deque::iterator find(const fs::path &file);

	Deque list;

public:

	int getSize() const
	{
		return (int)list.size();
	}

	recent_file_data_c *getData(int index) const;
	void clear()
	{
		list.clear();
	}
	
	void insert(const fs::path &file, const SString &map);
	void Write(std::ostream &stream) const;
	SString Format(int index) const;
	void Lookup(int index, fs::path *file_v, SString *map_v) const;
};

struct port_path_info_t
{
	fs::path exe_filename;
};

//
// Holds recently collected knowledge
//
struct RecentKnowledge
{
	void load(const fs::path &home_dir);
	void save(const fs::path &home_dir) const;
	void addRecent(const fs::path &filename, const SString &map_name, const fs::path &home_dir);

	RecentFiles_c files;
	std::map<SString, fs::path> known_iwads;
	std::map<SString, port_path_info_t> port_paths;
};

void M_OpenRecentFromMenu(void *priv_data);

void M_LookForIWADs();
void M_AddKnownIWAD(const fs::path &path, std::map<SString, fs::path> &known_iwads);
fs::path M_QueryKnownIWAD(const SString &game, const std::map<SString, fs::path> &known_iwads);
SString M_CollectGamesForMenu(int *exist_val, const char *exist_name, const std::map<SString, fs::path> &known_iwads);

void M_ValidateGivenFiles();
int  M_FindGivenFile(const char *filename);

void M_BackupWad(Wad_file *wad);

namespace global
{
	extern RecentKnowledge recent;
}

port_path_info_t * M_QueryPortPath(const SString &name, std::map<SString, port_path_info_t> &port_paths, bool create_it = false);

bool M_IsPortPathValid(const port_path_info_t *info);

bool readBuffer(FILE* f, size_t size, std::vector<byte>& target);

#endif  /* __EUREKA_M_FILES_H__ */

//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
