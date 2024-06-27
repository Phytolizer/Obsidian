//------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------
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
//------------------------------------------------------------------------

#pragma once

#include <math.h>
#include <stdint.h>

constexpr const char *BLANKOUT = "                                                                                           "
                           "                                                                                           "
                           "                                                                    ";

// basic constants
#define OBSIDIAN_MSG_BUF_LEN  2000
#define OBSIDIAN_DIST_EPSILON (1.0 / 1024.0)
#define OBSIDIAN_ANG_EPSILON  (1.0 / 1024.0)
#define OBSIDIAN_PI           3.14159265358979323846

// basic math
#define OBSIDIAN_MAX(a, b)           ((a > b) ? a : b)
#define OBSIDIAN_MIN(a, b)           ((a < b) ? a : b)
#define OBSIDIAN_ABS(a)              ((a < 0) ? -a : a)
#define OBSIDIAN_CLAMP(low, x, high) ((x < low) ? low : ((x > high) ? high : x))
// formerly I_ROUND macros
inline int RoundToInteger(float x)
{
    return (int)roundf(x);
}
inline int RoundToInteger(double x)
{
    return (int)round(x);
}

//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
