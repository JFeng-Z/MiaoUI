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
#ifndef _CUSTOM_H
#define _CUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "core/ui.h"
#include "ui_conf.h"

void Draw_Home(ui_t *ui);
void Show_Version(ui_t *ui);
void Show_Logo(ui_t *ui);
void TaskLvel_Setting(ui_t *ui);

#ifdef __cplusplus
}
#endif

#endif
