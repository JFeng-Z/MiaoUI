/*
 * ringtones.h
 *
 *  Created on: Nov 28, 2022
 *      Author: pablo
 */

#ifndef BUZZER_RINGTONES_H_
#define BUZZER_RINGTONES_H_

#include <stdint.h>

#include "notes.h"

// mario mais theme
extern  uint16_t mario_theme_melody[];
extern  uint16_t mario_theme_time[];
extern  uint16_t mario_theme_len;

// Underworld melody
extern  uint16_t underworld_melody[];
extern  uint16_t underworld_time[];
extern  uint16_t underworld_len;

extern  uint16_t happy_birthday_melody[];
extern  uint16_t happy_birthday_time[];
extern  uint16_t happy_birthday_len;


extern uint16_t bootMusicTimes[] ;
extern uint16_t bootMusicFreq[] ;
extern uint16_t bootMusicLength ;

#endif /* BUZZER_RINGTONES_H_ */
