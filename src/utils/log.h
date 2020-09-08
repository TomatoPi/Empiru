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
/// \brief Basic logging library
///

#ifndef LOG_H
#define LOG_H

#define FG_BOLD "\033[1m"
#define FG_RESET "\033[0m"

#include <stdio.h>
#define LOG_ERROR(fmt, ...) {fprintf(stderr, "%-10s : %-3d : \033[1;31mERROR\033[0m : " fmt, __FILE__, __LINE__, ##__VA_ARGS__);}

#define LOG_INFO(fmt, ...) {printf("%-10s : %-3d : \033[1mINFO\033[0m  : " fmt, __FILE__, __LINE__, ##__VA_ARGS__);}

#ifndef __NO_DEBUG__
#define LOG_DEBUG(fmt, ...) {printf("%-10s : %-3d : \033[1;32mDEBUG\033[0m : " fmt, __FILE__, __LINE__, ##__VA_ARGS__);}
#else
#define LOG_DEBUG(...) {}
#endif
    
#define LOG_TODO(fmt, ...) {printf("%-10s : %-3d : \033[1;36mTODO\033[0m  : " fmt, __FILE__, __LINE__, ##__VA_ARGS__);}

#define LOG_WRN(fmt, ...) {printf("%-10s : %-3d :\033[1;35mWARNING\033[0m: " fmt, __FILE__, __LINE__, ##__VA_ARGS__);}

#define LOG_GEN(fmt, ...) {printf(fmt, ##__VA_ARGS__);}

#define OUPS() LOG_ERROR("OUPS\n");exit(EXIT_FAILURE);

#endif /* LOG_H */

