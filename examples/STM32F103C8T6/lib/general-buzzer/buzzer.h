/**
 * @file buzzer.h
 * @author Pablo Jean Rozario (pablo.jean.eel@gmail.com)
 * @brief This library is to handle Buzzer devices, without
 * chipset depedency, can be used in any microcontroller
 * @version 1.0
 * @date 2022-12-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef APPLICATION_BUZZER_H_
#define APPLICATION_BUZZER_H_

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "notes.h"
#include "ringtones.h"

/*
 * Enumerates
 */

/**
 * @brief Defines the buzzer type
 * 
 * BUZZER_TYPE_PASSIVE are devices that need PWM to work.
 *                    Can reproduce any frequency
 * BUZZER_TYPE_ACTIVE work only with a simple GPIO
 *                    has a fixed frequency
 */
typedef enum{
    BUZZER_TYPE_PASSIVE,
    BUZZER_TYPE_ACTIVE
}buzzer_type_e;

/**
 * @brief when call buzzer_play_loop, you can play only for a fixed
 * time, or play intermittently
 * BUZZER_LOOP_OFF will only play for the provided time
 * BUZZER_LOOP_ON will turnon and turnoff with privided time
 */
typedef enum{
	BUZZER_LOOP_OFF,
	BUZZER_LOOP_ON
}buzzer_loop_e;

/**
 * @brief indicate if a logic is handle the buzzer. Not necesary
 * indicate if buzzer is vibrating.
 * 
 * BUZZER_IS_NOT_ACTIVE: no routine is applied on buzzer
 * BUZZER_IS_ACTIVE buzzer is working with a logic
 */
typedef enum{
	BUZZER_IS_NOT_ACTIVE,
	BUZZER_IS_ACTIVE
}buzzer_active_e;

/**
 * BUZZER_ERR_OK : Eveything is OK
 * BUZZER_ERR_FAIL : failed to initialize the buzzer
 * BUZZER_ERR_PARAMS : some parameter is missing or incorrect
 * 
 */
typedef enum{
	BUZZER_ERR_OK,
	BUZZER_ERR_FAIL,
	BUZZER_ERR_PARAMS,

	BUZZER_ERR_UNKNOWN = 0xFF
}buzzer_err_e;

/*
 * Functions typedefs
 */

/**
 * @brief Function pointers. For Pwm or GPIO
 * 
 */
typedef void (*pwmOutFx)(uint32_t);
typedef void (*gpioOutFx)(uint32_t);


/*
 * Structs and Unions
 */

typedef struct{
	// user must define these parameters
    struct{
        /**
         * @brief Function to handle with PWM frequency
         * 0 value must turnoff the PWM, don't forget this
         * case
         * USE THIS FOR PASSIVE DEVICES
         */
    	pwmOutFx pwmOut;
        /**
         * @brief Function to handle with GPIO that will
         * handle the Buzzer.
         * USE THIS FOR ACTIVE DEVICES
         */
    	gpioOutFx gpioOut;

        // Jut pick only one function, the other must be NULL
    }fnx;

    // the interrupt period that you will call buzzer_proc()
    // necessary for buzzer_play_loop() and buzzer_play_loop_array()
    uint_fast16_t interruptMs;

    // internal library variables, no need to work with these
    uint8_t started;
    buzzer_type_e type;
    buzzer_active_e active;
    uint_fast16_t counting;
    struct{
        uint16_t *pTimes;
        uint16_t *pFreq;
        uint_fast16_t i;
        uint_fast16_t len;

        int_fast32_t time;
        uint_fast16_t freq;

        buzzer_loop_e loop;
    }play_param;
}buzzer_t;

/*
 * Functions Prototypes
 */

/**
 * @brief Initialize the buzzer
 * 
 * @param buzzer : pointer to the handle of the buzzer
 * @return buzzer_err_e 
 */
buzzer_err_e buzzer_init(buzzer_t *buzzer);

/**
 * @brief Turnoff the buzzer imediatly
 * 
 * @param buzzer : pointer to the handle of the buzzer
 */
void buzzer_stop(buzzer_t *buzzer);

/**
 * @brief Turnon buzzer immediately
 * 
 * @param buzzer : pointer to the handle of the buzzer
 * @param freq : frequency that will inserted on buzzer.
 * 
 * @note freq parameters is relevant only in passive devices
 */
void buzzer_turn_on(buzzer_t *buzzer, uint16_t freq);

/**
 * Start buzzer for a determined period
 * If loop is BUZZER_LOOP_ON the buzzer will turn on and turn off
 * with the period
 * buzzer_proc must be working
 */

/**
 * @brief  Start buzzer for a determined period
 * If loop is BUZZER_LOOP_ON the buzzer will turn on and turn off
 * with the period
 * buzzer_proc must be working
 * 
 * @param buzzer : pointer to the handle of the buzzer
 * @param freq : frequency of the device
 * @param period : period that buzzer will stay on, or period
 * of beeps
 * @param loop : BUZZER_LOOP_ON buzzer will turned on and off with
 * provided period
 * BUZZER_LOOP_OFF will keep device vibrating only for period prived.
 * 
 * @note : freq is relevant only for Passive devices
 */
void buzzer_play_loop(buzzer_t *buzzer, uint16_t freq, uint16_t period, buzzer_loop_e loop);
void buzzer_play_times(buzzer_t *buzzer, uint16_t freq, uint16_t period, uint8_t count);
/**
 * Start to play a array of period and frequencies, generally used to play ringtones
 * buzzer_proc must be working
 */

/**
 * @brief : Start to play a array of period and frequencies, generally used to play ringtones
 * buzzer_proc must be working
 * 
 * @param buzzer : pointer to the handle of the buzzer
 * @param pPeriod : array of period
 * @param pFreq : array of frequency values, must have the same len of pPeriod
 * @param len : number of values on pFreq and/or pPeriod
 * 
 * @note pFreq is relevant only for Passive devices
 */
void buzzer_play_loop_array(buzzer_t *buzzer, uint16_t *pPeriod, uint16_t *pFreq, uint16_t len);

/**
 * Return if Buzzer is active
 */

/**
 * @brief Return if Buzzer is active
 * 
 * @param buzzer : pointer to the handle of the buzzer
 * @return buzzer_active_e 
 */
buzzer_active_e buzzer_is_active(buzzer_t *buzzer);

/**
 * @brief call this function in a periodic timing, if you're using a RTOS
 * we suggest you to use a task to handle this with a sleep
 * the period of interrupt is configured on buzzer_t structure
 * 
 * @param buzzer : pointer to the handle of the buzzer
 */
void buzzer_proc(buzzer_t *buzzer);

/**
 * @brief callback when an array has your execution finished
 * 
 * @param buzzer : pointer to the handle of the buzzer
 */
void buzzer_end_callback(buzzer_t *buzzer);


#endif /* APPLICATION_BUZZER_H_ */

