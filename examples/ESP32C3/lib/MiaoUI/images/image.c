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
#include "images/image.h"

const unsigned char home_09_stroke_rounded [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x03, 0x00, 0x00, 0xf8, 0x07, 0x00, 
	0x00, 0x1e, 0x1e, 0x00, 0x00, 0x07, 0x38, 0x00, 0x80, 0x03, 0x70, 0x00, 0xc0, 0x00, 0xe0, 0x00, 
	0x60, 0x00, 0x80, 0x01, 0x30, 0x00, 0x00, 0x03, 0x18, 0x00, 0x00, 0x06, 0x18, 0x00, 0x00, 0x06, 
	0x18, 0x00, 0x00, 0x06, 0x18, 0x00, 0x00, 0x06, 0x18, 0x00, 0x00, 0x06, 0x18, 0x00, 0x00, 0x06, 
	0x18, 0x00, 0x00, 0x06, 0x18, 0x00, 0x00, 0x06, 0x18, 0xf0, 0x03, 0x06, 0x18, 0xf8, 0x07, 0x06, 
	0x18, 0x0c, 0x0c, 0x06, 0x18, 0x0c, 0x0c, 0x06, 0x18, 0x0c, 0x0c, 0x06, 0x18, 0x0c, 0x0c, 0x06, 
	0x18, 0x0c, 0x0c, 0x06, 0x30, 0x0c, 0x0c, 0x03, 0xf0, 0xff, 0xff, 0x03, 0xc0, 0xff, 0xff, 0x00, 
	0x00, 0xf8, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char configuration_01_stroke_rounded [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0xf0, 0x03, 0x00, 0x00, 0x78, 0x07, 0x00, 
	0x00, 0x18, 0x06, 0x00, 0x20, 0x0c, 0x0c, 0x01, 0xf0, 0x0f, 0xfc, 0x03, 0xf8, 0x07, 0xf8, 0x07, 
	0x18, 0x00, 0x00, 0x06, 0x0c, 0xf0, 0x03, 0x0c, 0x0c, 0xfc, 0x03, 0x0c, 0x1c, 0x8c, 0x03, 0x0e, 
	0x38, 0xc6, 0x19, 0x07, 0x30, 0xc6, 0x1c, 0x03, 0x30, 0xc6, 0x1f, 0x03, 0x30, 0xc6, 0x1b, 0x03, 
	0x30, 0x86, 0x19, 0x03, 0x38, 0x07, 0x18, 0x07, 0x9c, 0x03, 0x18, 0x0e, 0xcc, 0xe1, 0x0f, 0x0c, 
	0xe0, 0xf0, 0x07, 0x0c, 0x70, 0x38, 0x00, 0x06, 0x38, 0x1c, 0xf8, 0x07, 0x1c, 0x0e, 0xfc, 0x03, 
	0x0c, 0x07, 0x0c, 0x01, 0x8c, 0x1b, 0x06, 0x00, 0xfc, 0xf9, 0x07, 0x00, 0xf8, 0xf0, 0x03, 0x00, 
	0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char album_02_stroke_rounded [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0x1f, 0x00, 0xf8, 0xff, 0x3f, 0x00, 
	0x18, 0x00, 0x30, 0x00, 0x0c, 0x00, 0x60, 0x00, 0x0c, 0x00, 0x60, 0x00, 0x0c, 0x00, 0xe0, 0x03, 
	0x0c, 0x80, 0xe1, 0x07, 0x0c, 0x80, 0x61, 0x06, 0x0c, 0x00, 0x60, 0x0c, 0x0c, 0x00, 0x60, 0x0c, 
	0x0c, 0x00, 0x60, 0x0c, 0xfc, 0x03, 0x60, 0x0c, 0xfc, 0x1f, 0x60, 0x0c, 0x0c, 0x7c, 0x60, 0x0c, 
	0x0c, 0xf0, 0x60, 0x0c, 0x0c, 0xc0, 0x61, 0x0c, 0x0c, 0x80, 0x63, 0x0c, 0x0c, 0x00, 0x63, 0x0c, 
	0x18, 0x00, 0x36, 0x0c, 0xf8, 0xff, 0x3f, 0x0c, 0xe0, 0xff, 0x1f, 0x0c, 0x80, 0x01, 0x00, 0x0c, 
	0x80, 0x01, 0x00, 0x0c, 0x80, 0x03, 0x00, 0x06, 0x00, 0xff, 0xff, 0x07, 0x00, 0xfe, 0xff, 0x03, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char github_stroke_rounded [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0xc0, 0x07, 0x80, 0xff, 0xff, 0x07, 
	0x80, 0xf9, 0x7f, 0x06, 0x80, 0x01, 0x00, 0x06, 0x80, 0x01, 0x00, 0x06, 0x80, 0x01, 0x00, 0x06, 
	0xc0, 0x00, 0x00, 0x06, 0xc0, 0x00, 0x00, 0x0c, 0x60, 0x00, 0x00, 0x0c, 0x60, 0x00, 0x00, 0x0c, 
	0x60, 0x00, 0x00, 0x0c, 0x40, 0x00, 0x00, 0x0c, 0xc0, 0x00, 0x00, 0x0c, 0xc0, 0x00, 0x00, 0x0c, 
	0xc0, 0x00, 0x00, 0x06, 0x80, 0x01, 0x00, 0x07, 0x00, 0x07, 0x80, 0x03, 0x00, 0x1e, 0xe0, 0x01, 
	0x04, 0x38, 0x70, 0x00, 0x0c, 0x30, 0x30, 0x00, 0x0c, 0x30, 0x30, 0x00, 0x18, 0x10, 0x30, 0x00, 
	0x78, 0x10, 0x30, 0x00, 0xf0, 0x3f, 0x30, 0x00, 0xc0, 0x3f, 0x30, 0x00, 0x00, 0x10, 0x30, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char ai_video_stroke_rounded [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0xc0, 0xff, 0xc1, 0x01, 
	0xf0, 0xff, 0xe1, 0x01, 0x78, 0x00, 0xf8, 0x07, 0x18, 0x00, 0x3c, 0x0f, 0x0c, 0x00, 0x3c, 0x0f, 
	0x0c, 0x00, 0xf0, 0x03, 0x0c, 0x00, 0xe0, 0x01, 0x0c, 0x18, 0xc0, 0x00, 0x0c, 0x7c, 0xc0, 0x00, 
	0x0c, 0xec, 0x01, 0x00, 0x0c, 0x8c, 0x03, 0x06, 0x0c, 0x0c, 0x07, 0x06, 0x0c, 0x0c, 0x06, 0x06, 
	0x0c, 0x0c, 0x07, 0x06, 0x0c, 0x8c, 0x03, 0x06, 0x0c, 0xec, 0x01, 0x06, 0x0c, 0xfc, 0x00, 0x06, 
	0x0c, 0x38, 0x00, 0x06, 0x0c, 0x00, 0x00, 0x06, 0x0c, 0x00, 0x00, 0x06, 0x0c, 0x00, 0x00, 0x02, 
	0x1c, 0x00, 0x00, 0x03, 0x38, 0x00, 0x80, 0x03, 0xf0, 0xff, 0xff, 0x01, 0xc0, 0xff, 0xff, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char user_account_stroke_rounded [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0x00, 
	0xf0, 0xff, 0xff, 0x03, 0x38, 0x00, 0x00, 0x07, 0x18, 0x00, 0x00, 0x06, 0x0c, 0x00, 0x00, 0x0c, 
	0x0c, 0x1e, 0x00, 0x0c, 0x0c, 0x3f, 0x00, 0x0c, 0x84, 0x31, 0x7e, 0x08, 0x84, 0x31, 0x7e, 0x08, 
	0x84, 0x3b, 0x00, 0x08, 0x04, 0x1f, 0x00, 0x08, 0x04, 0x0e, 0x00, 0x08, 0x04, 0x00, 0x3e, 0x08, 
	0x04, 0x00, 0x1c, 0x08, 0x84, 0x3f, 0x00, 0x08, 0xc4, 0x7f, 0x00, 0x08, 0xe4, 0xe0, 0x00, 0x08, 
	0x4c, 0xc0, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x0c, 0x18, 0x00, 0x00, 0x06, 
	0x38, 0x00, 0x00, 0x07, 0xf0, 0xff, 0xff, 0x03, 0xc0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char sine_02_stroke_rounded [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 
	0x80, 0x1f, 0x00, 0x00, 0xc0, 0x18, 0x00, 0x00, 0x60, 0x30, 0x00, 0x00, 0x60, 0x30, 0x00, 0x00, 
	0x30, 0x60, 0x00, 0x00, 0x30, 0x60, 0x00, 0x00, 0x30, 0x60, 0x00, 0x04, 0x30, 0x60, 0x00, 0x06, 
	0x18, 0xe0, 0x00, 0x06, 0x18, 0xc0, 0x00, 0x06, 0x7c, 0xde, 0x9e, 0x0f, 0x7c, 0xde, 0x9e, 0x0f, 
	0x18, 0xc0, 0x00, 0x06, 0x18, 0xc0, 0x01, 0x06, 0x18, 0x80, 0x01, 0x03, 0x08, 0x80, 0x01, 0x03, 
	0x00, 0x80, 0x01, 0x03, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x83, 0x01, 0x00, 0x00, 0x83, 0x01, 
	0x00, 0x00, 0xc6, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char* logo_allArray[] = {
	home_09_stroke_rounded,
	configuration_01_stroke_rounded,
	album_02_stroke_rounded,
	github_stroke_rounded,
	ai_video_stroke_rounded,
	user_account_stroke_rounded,
	sine_02_stroke_rounded
};