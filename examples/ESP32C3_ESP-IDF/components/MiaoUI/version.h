/**
<one line to give the program's name and a brief idea of what it does.>
Copyright (C) <2024>  <JianFeng>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef __VERSION_H
#define __VERSION_H

#ifdef __cplusplus
extern "C" {
#endif

/* Firmware Version */
#define VERSION_UI_NAME   "MiaoUI"
#define VERSION        "v1.2"
#define VERSION_AUTHOR_NAME     "JFeng-Z"
#define VERSION_PROJECT_LINK    "github.com/JFeng-Z/MiaoUI"

/* Build Time */
#define VERSION_BUILD_TIME    __DATE__ "\n" __TIME__

#ifdef __cplusplus
}
#endif

#endif
