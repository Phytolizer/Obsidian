//----------------------------------------------------------------------
//  COOKIE : Save/Load user settings
//----------------------------------------------------------------------
//
//  OBSIDIAN Level Maker
//
//  Copyright (C) 2021-2022 The OBSIDIAN Team
//  Copyright (C) 2006-2017 Andrew Apted
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
//----------------------------------------------------------------------

#include "m_cookie.h"

#include <locale.h>

#include <stdexcept>

#include "lib_argv.h"
#include "lib_util.h"
#include "m_lua.h"
#include "main.h"
#include "sys_assert.h"

enum struct cookie_context_e
{
    Load,
    Save,
    Arguments
};

static cookie_context_e context;

static std::string active_module;

static bool keep_seed;

static void Cookie_SetValue(std::string name, std::string value)
{
    if (context == cookie_context_e::Load)
    {
        DebugPrint("CONFIG: Name: [%s] Value: [%s]\n", name.c_str(), value.c_str());
    }
    else if (context == cookie_context_e::Arguments)
    {
        DebugPrint("ARGUMENT: Name: [%s] Value: [%s]\n", name.c_str(), value.c_str());
    }

    // the new style module syntax
    if (name.front() == '@')
    {
        active_module = name.substr(1);
        name          = "self";
    }

    if (!active_module.empty())
    {
        ob_set_mod_option(active_module, name, value);
        if (batch_mode)
        {
            ob_set_config(name, value);
        }
        return;
    }

    // need special handling for the 'seed' value
    if (StringCompare(name, "seed") == 0)
    {
        // ignore seed when loading a config file
        // unless the -k / --keep option is given.

        if (context == cookie_context_e::Arguments || keep_seed)
        {
            try
            {
                next_rand_seed = stoull(value);
                return;
            }
            catch (std::invalid_argument &e)
            {
                (void)e;
                if (!value.empty())
                {
                    string_seed = value;
                    ob_set_config("string_seed", value.c_str());
                    next_rand_seed = StringHash64(string_seed);
                }
                else
                {
                    LogPrint("Invalid argument. Will generate new seed.\n");
                }
            }
            catch (std::out_of_range &e)
            {
                (void)e;
                LogPrint("Resulting number would be out of range. Will generate new "
                         "seed.\n");
            }
        }

        return;
    }

    ob_set_config(name, value);
}

static bool Cookie_ParseLine(std::string buf)
{
    if (buf.find('=') == std::string::npos)
    {
        // Skip blank lines, comments, etc
        return true;
    }

    while (IsSpaceASCII(buf[0]))
    {
        buf.erase(buf.begin());
    }

    if (!(isalpha(buf.front()) || buf.front() == '@'))
    {
        LogPrint("Weird config line: [%s]\n", buf.c_str());
        return false;
    }

    std::string::size_type pos = buf.find('=');

    while (pos > 0 && IsSpaceASCII(buf[pos - 1]))
    {
        buf.erase(buf.begin() + (pos - 1));
        pos--;
    }
    while (pos + 1 < buf.size() && IsSpaceASCII(buf[pos + 1]))
    {
        buf.erase(buf.begin() + (pos + 1));
    }
    while (IsSpaceASCII(buf[buf.size() - 1]))
    {
        buf.erase(buf.end() - 1);
    }

    std::string name  = buf.substr(0, pos);
    std::string value = buf.substr(pos + 1);

    if (name.empty() || value.empty())
    {
        LogPrint("Name or value missing!\n");
        return false;
    }

    Cookie_SetValue(name, value);
    return true;
}

//----------------------------------------------------------------------

bool Cookie_Load(std::string filename)
{
    context = cookie_context_e::Load;

    keep_seed = (argv::Find('k', "keep") >= 0);

    active_module.clear();

    setlocale(LC_NUMERIC, "C");

    FILE *cookie_fp = FileOpen(filename, "r");

    if (!cookie_fp)
    {
        return false;
    }

    if (main_action != MAIN_SOFT_RESTART)
    {
        LogPrint("Loading config file: %s\n", filename.c_str());
    }

    int error_count = 0;

    std::string buffer;
    int         c = EOF;
    for (;;)
    {
        buffer.clear();
        while ((c = fgetc(cookie_fp)) != EOF)
        {
            buffer.push_back(c);
            if (c == '\n')
                break;
        }

        if (!Cookie_ParseLine(buffer))
        {
            error_count += 1;
        }

        if (feof(cookie_fp) || ferror(cookie_fp))
            break;
    }

    fclose(cookie_fp);

    if (main_action != MAIN_SOFT_RESTART)
    {
        if (error_count > 0)
        {
            LogPrint("DONE (found %d parse errors)\n\n", error_count);
        }
        else
        {
            LogPrint("DONE.\n\n");
        }
    }
    setlocale(LC_NUMERIC, numeric_locale.c_str());
    return true;
}

bool Cookie_LoadString(std::string str, bool _keep_seed)
{
    context   = cookie_context_e::Load;
    keep_seed = _keep_seed;

    active_module.clear();

    LogPrint("Reading config data...\n");

    std::string::size_type oldpos = 0;
    std::string::size_type pos    = 0;
    while (pos != std::string::npos)
    {
        pos = str.find('\n', oldpos);
        if (pos != std::string::npos)
        {
            Cookie_ParseLine(str.substr(oldpos, pos - oldpos));
            oldpos = pos + 1;
        }
    }

    LogPrint("DONE.\n\n");
    return true;
}

bool Cookie_Save(std::string filename)
{
    context = cookie_context_e::Save;
    setlocale(LC_NUMERIC, "C");

    FILE *cookie_fp = FileOpen(filename, "w");

    if (!cookie_fp)
    {
        LogPrint("Error: unable to create file: %s\n(%s)\n\n", filename.c_str(), strerror(errno));
        return false;
    }

    if (main_action == MAIN_HARD_RESTART || main_action == MAIN_QUIT)
    {
        LogPrint("Saving config file...\n");
    }

    // header...
    fprintf(cookie_fp, "-- CONFIG FILE : OBSIDIAN %s \"%s\"\n", OBSIDIAN_SHORT_VERSION, OBSIDIAN_CODE_NAME.c_str());
    fprintf(cookie_fp, "-- Build %s\n", OBSIDIAN_VERSION);
    fprintf(cookie_fp, "-- Based on OBLIGE Level Maker (C) 2006-2017 Andrew Apted\n");
    fprintf(cookie_fp, "-- %s\n\n", OBSIDIAN_WEBSITE);

    // settings...
    std::vector<std::string> lines;

    ob_read_all_config(&lines, true /* need_full */);

    for (unsigned int i = 0; i < lines.size(); i++)
    {
        fprintf(cookie_fp, "%s\n", lines[i].c_str());
    }

    if (main_action == MAIN_HARD_RESTART || main_action == MAIN_QUIT)
    {
        LogPrint("DONE.\n\n");
    }

    fclose(cookie_fp);
    setlocale(LC_NUMERIC, numeric_locale.c_str());
    return true;
}

void Cookie_ParseArguments(void)
{
    context = cookie_context_e::Arguments;

    active_module.clear();

    for (int i = 0; i < argv::list.size(); i++)
    {
        const std::string &arg = argv::list[i];

        if (arg[0] == '-')
        {
            continue;
        }

        if (arg[0] == '{' || arg[0] == '}')
        {
            continue;
        }

        if (StringCompare(arg.c_str(), "@@") == 0)
        {
            active_module.clear();
            continue;
        }

        // support an isolated "=", like in: FOO = 3
        if (i + 2 < argv::list.size() && StringCompare(argv::list[i + 1].c_str(), "=") == 0 &&
            argv::list[i + 2][0] != '-')
        {
            Cookie_SetValue(arg, argv::list[i + 2]);
            i += 2;
            continue;
        }

        const char *eq_pos = strchr(arg.c_str(), '=');
        if (!eq_pos)
        {
            // allow module names to omit the (rather useless) value
            if (arg[0] == '@')
            {
                Cookie_SetValue(arg, "1");
            }

            continue;
        }

        // split argument into name/value pair
        int eq_offset = (eq_pos - arg.c_str());

        std::string name  = arg;
        const char *value = name.c_str() + eq_offset + 1;

        name[eq_offset] = 0;

        if (name[0] == 0 || value[0] == 0)
        {
            FatalError("Bad setting on command line: '%s'\n", arg.c_str());
        }

        Cookie_SetValue(name.c_str(), value);
    }
}

//----------------------------------------------------------------------
//   RECENT FILE HANDLING
//----------------------------------------------------------------------

#define MAX_RECENT 10

class RecentFiles_c
{
  public:
    int size;

    // newest is at index [0]
    std::string filenames[MAX_RECENT];

  public:
    RecentFiles_c() : size(0)
    {
        for (int k = 0; k < MAX_RECENT; k++)
        {
            filenames[k].clear();
        }
    }

    ~RecentFiles_c()
    {
        clear();
    }

    void clear()
    {
        for (int k = 0; k < size; k++)
        {
            filenames[k].clear();
        }

        size = 0;
    }

    int find(const std::string &file)
    {
        // ignore the path when matching filenames
        const std::string a = GetFilename(file);

        for (int k = 0; k < size; k++)
        {
            if (a == GetFilename(filenames[k]))
            {
                return k;
            }
        }

        return -1; // not found
    }

    void erase(int index)
    {
        SYS_ASSERT(index < size);

        size--;

        SYS_ASSERT(size < MAX_RECENT);

        for (; index < size; index++)
        {
            filenames[index] = filenames[index + 1];
        }

        filenames[index].clear();
    }

    void push_front(const std::string &file)
    {
        if (size >= MAX_RECENT)
        {
            erase(MAX_RECENT - 1);
        }

        // shift elements up
        for (int k = size - 1; k >= 0; k--)
        {
            filenames[k + 1] = filenames[k];
        }

        filenames[0] = file;

        size++;
    }

    void insert(const std::string &file)
    {
        // ensure filename (without any path) is unique
        int f = find(file);

        if (f >= 0)
        {
            erase(f);
        }

        push_front(file);
    }

    void remove(std::string file)
    {
        int f = find(file);

        if (f >= 0)
        {
            erase(f);
        }
    }

    void write_all(FILE *fp, std::string keyword) const
    {
        // Files are written in opposite order, newest at the end.
        // This allows the parser to merely insert() items in the
        // order they are read.

        for (int k = size - 1; k >= 0; k--)
        {
            fprintf(fp, "%s = %s\n", keyword.c_str(), filenames[k].c_str());
        }

        if (size > 0)
        {
            fprintf(fp, "\n");
        }
    }

    bool get_name(int index, std::string buffer, bool for_menu) const
    {
        if (index >= size)
        {
            return false;
        }

        const std::string &name = filenames[index];

        if (for_menu)
        {
            buffer = StringFormat("%-.32s", name.c_str());
        }
        else
        {
            buffer = name;
        }

        return true;
    }
};

static RecentFiles_c recent_wads;
static RecentFiles_c recent_configs;

void Recent_Parse(const std::string &name, const std::string &value)
{
    if (StringCompare(name, "recent_wad") == 0)
    {
        recent_wads.insert(value);
    }
    else if (StringCompare(name, "recent_config") == 0)
    {
        recent_configs.insert(value);
    }
}

void Recent_Write(FILE *fp)
{
    fprintf(fp, "---- Recent Files ----\n\n");
    recent_wads.write_all(fp, "recent_wad");
    recent_configs.write_all(fp, "recent_config");
}

void Recent_AddFile(int group, std::string filename)
{
    SYS_ASSERT(0 <= group && group < RECG_NUM_GROUPS);

    switch (group)
    {
    case RECG_Output:
        recent_wads.insert(filename);
        break;

    case RECG_Config:
        recent_configs.insert(filename);
        break;
    }

    // push to disk now -- why wait?
    if (!batch_mode)
    {
        Options_Save(options_file);
    }
}

void Recent_RemoveFile(int group, std::string filename)
{
    SYS_ASSERT(0 <= group && group < RECG_NUM_GROUPS);

    switch (group)
    {
    case RECG_Output:
        recent_wads.remove(filename);
        break;

    case RECG_Config:
        recent_configs.remove(filename);
        break;
    }

    // push to disk now -- why wait?
    if (!batch_mode)
    {
        Options_Save(options_file);
    }
}

bool Recent_GetName(int group, int index, std::string name_buf, bool for_menu)
{
    SYS_ASSERT(0 <= group && group < RECG_NUM_GROUPS);
    SYS_ASSERT(index >= 0);

    switch (group)
    {
    case RECG_Output:
        return recent_wads.get_name(index, name_buf, for_menu);

    case RECG_Config:
        return recent_configs.get_name(index, name_buf, for_menu);
    }

    return false;
}

//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
