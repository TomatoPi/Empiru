/*
 * Copyright (C) 2020 DAGO Kokri Esaïe <dago.esaie@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/// 
/// \file   log.h
/// \author DAGO Kokri Esaïe <dago.esaie@protonmail.com>
///
/// \date 8 septembre 2020, 04:44
///
/// \brief Basic logging library
/// \see https://en.wikipedia.org/wiki/ANSI_escape_code
///

#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define FG_BOLD "\033[1m"   ///< ANSI escape code for bold font
#define FG_RESET "\033[0m"  ///< ANSI escape code for default font

/// \brief printf like formated output on stderr headed by ERROR
#define LOG_ERROR(fmt, ...) {fprintf(stderr, "%-10s : %-3d : \033[1;31mERROR\033[0m : " fmt, __FILE__, __LINE__, ##__VA_ARGS__);}

/// \brief printf like formated output on stdout headed by INFO
#define LOG_INFO(fmt, ...) {printf("%-10s : %-3d : \033[1mINFO\033[0m  : " fmt, __FILE__, __LINE__, ##__VA_ARGS__);}

#ifndef NDEBUG
/// \brief printf like formated output on stdout headed by DEBUG
///   define NDEBUG before include this header to disable theses prints
#define LOG_DEBUG(fmt, ...) {printf("%-10s : %-3d : \033[1;32mDEBUG\033[0m : " fmt, __FILE__, __LINE__, ##__VA_ARGS__);}
#else
#define LOG_DEBUG(...) {}
#endif

/// \brief printf like formated output on stdout headed by TODO
#define LOG_TODO(fmt, ...) {printf("%-10s : %-3d : \033[1;36mTODO\033[0m  : " fmt, __FILE__, __LINE__, ##__VA_ARGS__);}

/// \brief printf like formated output on stderr headed by WARNING
#define LOG_WRN(fmt, ...) {fprintf(stderr, "%-10s : %-3d :\033[1;35mWARNING\033[0m: " fmt, __FILE__, __LINE__, ##__VA_ARGS__);}

/// \brief printf like formated output on stdout, quite useless
#define LOG_GEN(fmt, ...) {printf(fmt, ##__VA_ARGS__);}

/// \brief Macro used for fast exit on critical sections
#define OUPS() LOG_ERROR("OUPS\n");exit(EXIT_FAILURE);

#endif /* LOG_H */

