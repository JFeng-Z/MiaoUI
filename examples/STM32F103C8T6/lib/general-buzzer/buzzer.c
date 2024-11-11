/*
 * buzzer.c
 *
 *  Created on: 9 de fev de 2022
 *      Author: pablo.jean
 */

#include "buzzer.h"

/**
 * Macros
 */

#define _HIGH	1
#define _LOW	0

/**
 * privates
 */

void __buzzer_stop_gpio(buzzer_t *buzzer){
	if (buzzer->fnx.gpioOut != NULL)
		buzzer->fnx.gpioOut(_LOW);
}

void __buzzer_stop_pwm(buzzer_t *buzzer){
	if (buzzer->fnx.pwmOut != NULL)
		buzzer->fnx.pwmOut(0);
}

void __buzzer_turn_on_gpio(buzzer_t *buzzer){
	if (buzzer->fnx.gpioOut != NULL)
		buzzer->fnx.gpioOut(_HIGH);
}

void __buzzer_turn_on_pwm(buzzer_t *buzzer, uint32_t freq){
	if (buzzer->fnx.pwmOut != NULL)
		buzzer->fnx.pwmOut(freq);
}

void __buzzer_play_loop_gpio(buzzer_t *buzzer){
    __buzzer_turn_on_gpio(buzzer);
}

void __buzzer_play_loop_pwm(buzzer_t *buzzer){
    __buzzer_turn_on_pwm(buzzer, buzzer->play_param.freq);
}


void __buzzer_play_loop_array_gpio(buzzer_t *buzzer){
    __buzzer_turn_on_gpio(buzzer);
    buzzer->play_param.time = buzzer->play_param.pTimes[0];

}

void __buzzer_play_loop_array_pwm(buzzer_t *buzzer){
    __buzzer_turn_on_pwm(buzzer, buzzer->play_param.pFreq[0]);
    buzzer->play_param.time = buzzer->play_param.pTimes[0];
}


/*
 * Publics
 */

/**
 * @brief �����������ص�������
 *
 * @param buzzer ������ָ�롣
 * ע�⣺�ú�����һ�������ź�����������Ӧ�ó��������¶��岢����Ĭ��ʵ�֡�
 */
void __attribute__((weak)) buzzer_end_callback(buzzer_t *buzzer) {
    // Ĭ��ʵ��Ϊ�գ�������Ӧ�ó��������¶��岢ʵ���ض��Ĳ���
}
/**
 * @brief �������жϴ���������
 *
 */
void buzzer_proc(buzzer_t *buzzer) {
    // ������������
    uint16_t i;
    
    // ���Ӽ�ʱ���ļ���
    buzzer->counting += buzzer->interruptMs;
    
    // ���������Ƿ��ڻ״̬�����Ų�����Ϊ���Ҽ�ʱ����������ʱ��
    if (buzzer->active &&
        buzzer->play_param.len > 0 &&
        buzzer->counting > buzzer->play_param.time) {
        
        // ��ȡ��ǰ���Ų���������
        i = buzzer->play_param.i;
        
        // ���ü�ʱ��
        buzzer->counting = 0;
        
        // ���Ӳ��Ų���������
        buzzer->play_param.i++;
        
        // ��鲥�Ų����������Ƿ�С���ܳ���
        if (buzzer->play_param.i < buzzer->play_param.len) {
            // ���Ų���������δ�ﵽ�ܳ���
            
            // ����Ƿ�ʹ���Զ���Ĳ���ʱ���Ƶ��
            if (buzzer->play_param.pTimes == NULL) {
                // δʹ���Զ���Ĳ���ʱ���Ƶ��
                
                // ���ѭ��ģʽΪѭ�����ţ�������������0��1֮��
                if (buzzer->play_param.loop == BUZZER_LOOP_ON) {
                    buzzer->play_param.i %= 2;
                }
                
                // ���ݷ���������ִ����Ӧ�Ĳ���
                if (buzzer->type == BUZZER_TYPE_ACTIVE) {
                    if (buzzer->play_param.i % 2 != 0) {
                        // �������Ϊ1����ֹͣ GPIO ����
                        __buzzer_stop_gpio(buzzer);
                    } else {
                        // �������Ϊ0����� GPIO
                        __buzzer_turn_on_gpio(buzzer);
                    }
                } 
								else {
                    if (buzzer->play_param.i % 2 != 0) {
                        // �������Ϊ1����ֹͣ PWM ����
                        __buzzer_stop_pwm(buzzer);
                    } else {
                        // �������Ϊ0����� PWM
                        __buzzer_turn_on_pwm(buzzer, buzzer->play_param.freq);
                    }
                }
            } 
						else {
                // ʹ���Զ���Ĳ���ʱ���Ƶ��
                
                // ��ȡ�Զ���Ĳ���ʱ���Ƶ��
                buzzer->play_param.time = buzzer->play_param.pTimes[i];
                buzzer->play_param.freq = buzzer->play_param.pFreq[i];
                
                // �� PWM ��ʹ���Զ����Ƶ��
                __buzzer_turn_on_pwm(buzzer, buzzer->play_param.freq);
            }
        }
				else {
            // ���Ŵ����ﵽָ��������ֹͣ�������Ĳ���
            
            if (buzzer->type == BUZZER_TYPE_ACTIVE) {
                // ֹͣ GPIO ����
                __buzzer_stop_gpio(buzzer);
            } else {
                // ֹͣ PWM ����
                __buzzer_stop_pwm(buzzer);
            }
            
            // ִ�н����ص�����
            buzzer_end_callback(buzzer);
            
            // ��������״̬����Ϊ�ǻ״̬
            buzzer->active = 0;
        }
    }
}

/**
 * @brief ��ʼ����������
 *
 * @param buzzer ������ָ�롣
 * @return ��ʼ������Ĵ�����롣
 *
 * �ú������ڳ�ʼ�����������󡣸��ݷ���������Ĺ��ܺ�����ȷ�������������ͣ������ͻ򱻶��ͣ���������Ӧ�ĳ�ʼ��������
 * �������������Ϊ�ջ�δ�ṩ��Ч�Ĺ��ܺ��������ʼ��ʧ�ܡ�
 * ��ʼ���ɹ�ʱ������ BUZZER_ERR_OK�����򣬷��� BUZZER_ERR_PARAMS��
 */
buzzer_err_e buzzer_init(buzzer_t *buzzer){
    if (buzzer != NULL){
    	// nothing to do here yet
    	if (buzzer->fnx.gpioOut){
    		buzzer->type = BUZZER_TYPE_ACTIVE;
    		buzzer->fnx.gpioOut(0);

    		return BUZZER_ERR_OK;
    	}
    	else if (buzzer->fnx.pwmOut){
    		buzzer->type = BUZZER_TYPE_PASSIVE;
    		buzzer->fnx.pwmOut(0);

    		return BUZZER_ERR_OK;
    	}
    }

    return BUZZER_ERR_PARAMS;
}

/**
 * @brief ֹͣ�������Ĳ��š�
 *
 * @param buzzer ������ָ�롣
 *
 * �ú�������ֹͣ�������Ĳ��š�����������״̬����Ϊ�ǻ״̬����ֹͣ��Ӧ�Ĳ��Ų�����
 * ע�⣺�ڵ��øú���֮ǰ����Ҫȷ�������������Ѿ���ȷ��ʼ����
 */
void buzzer_stop(buzzer_t *buzzer) {
    if (buzzer != NULL) {
        buzzer->active = BUZZER_IS_NOT_ACTIVE;

        if (buzzer->type == BUZZER_TYPE_ACTIVE) {
            __buzzer_stop_gpio(buzzer);
        }
        else if (buzzer->type == BUZZER_TYPE_PASSIVE) {
            __buzzer_stop_pwm(buzzer);
        }
    }
}

/**
 * @brief �򿪷�����������Ƶ�ʡ�
 *
 * @param buzzer ������ָ�롣
 * @param freq ����Ƶ�ʣ��������ڱ����ͷ���������
 *
 * �ú������ڴ򿪷�����������ָ����Ƶ�ʡ����ݷ����������ͣ�����ѡ��ʹ��Ƶ�ʲ������������������ԡ�
 * ע�⣺�ڵ��øú���֮ǰ����Ҫȷ�������������Ѿ���ȷ��ʼ����
 */
void buzzer_turn_on(buzzer_t *buzzer, uint16_t freq){
    if (buzzer != NULL){
        buzzer->active = BUZZER_IS_ACTIVE;
        buzzer->play_param.loop = 0;
        buzzer->play_param.len = 0;
        if (buzzer->type == BUZZER_TYPE_ACTIVE){
            __buzzer_turn_on_gpio(buzzer);
        }
        else if (buzzer->type == BUZZER_TYPE_PASSIVE){
        	buzzer->play_param.freq = freq;
            __buzzer_turn_on_pwm(buzzer, freq);
        }
    }
}

/**
 * @brief �����������Բ��ŵ���������
 *
 * @param buzzer ������ָ�롣
 * @param freq ����Ƶ�ʣ��������ڱ����ͷ���������
 * @param period ��������ʱ�䡣
 * @param loop ѭ������ģʽ��
 */
void buzzer_play_loop(buzzer_t *buzzer, uint16_t freq, uint16_t period, buzzer_loop_e loop){
    if (buzzer != NULL){
        buzzer->play_param.i = 0;
				buzzer->counting = 0;
        buzzer->play_param.time = period;
        buzzer->play_param.loop = loop;
        buzzer->play_param.pTimes = NULL;
        buzzer->play_param.pFreq = NULL;
        buzzer->play_param.len = 2 + (loop == BUZZER_LOOP_ON);
  
			buzzer->active = BUZZER_IS_ACTIVE;
        if (buzzer->type == BUZZER_TYPE_ACTIVE){
            __buzzer_play_loop_gpio(buzzer);
        }
        else if (buzzer->type == BUZZER_TYPE_PASSIVE){
        	buzzer->play_param.freq = freq;
            __buzzer_play_loop_pwm(buzzer);
        }
    }
}
void buzzer_play_times(buzzer_t *buzzer, uint16_t freq, uint16_t period, uint8_t count) {
    if (buzzer != NULL) {
        buzzer->play_param.i = 0;
				buzzer->counting = 0;
        buzzer->play_param.time = period;
        buzzer->play_param.loop = BUZZER_LOOP_OFF;
        buzzer->play_param.pTimes = NULL;
        buzzer->play_param.pFreq = NULL;
        buzzer->active = BUZZER_IS_ACTIVE;
        buzzer->play_param.len = count * 2;

        if (buzzer->type == BUZZER_TYPE_ACTIVE) {
            __buzzer_play_loop_gpio(buzzer);
        }
        else if (buzzer->type == BUZZER_TYPE_PASSIVE) {
            buzzer->play_param.freq = freq;
            __buzzer_play_loop_pwm(buzzer);
        }
    }
}
/**
 * @brief �����������Բ����������顣
 *
 * @param buzzer ������ָ�롣
 * @param pPeriod ��������ʱ�������ָ�롣
 * @param pFreq ����Ƶ�������ָ�루�������������ͷ���������
 * @param len ��������ĳ��ȡ�
 */
void buzzer_play_loop_array(buzzer_t *buzzer, uint16_t *pPeriod, uint16_t *pFreq, uint16_t len){
    if (buzzer != NULL && pPeriod != NULL &&
    		(pFreq != NULL || buzzer->type == BUZZER_TYPE_ACTIVE)){
        buzzer->play_param.len = len;
        buzzer->play_param.i = 0;
        buzzer->play_param.pTimes = pPeriod;
        buzzer->play_param.pFreq = pFreq;
        buzzer->play_param.loop = BUZZER_LOOP_OFF;
        buzzer->active = BUZZER_IS_ACTIVE;
        if (buzzer->type == BUZZER_TYPE_ACTIVE){
            __buzzer_play_loop_array_gpio(buzzer);
        }
        else if (buzzer->type == BUZZER_TYPE_PASSIVE){
            __buzzer_play_loop_array_pwm(buzzer);
        }
    }
}

/**
 * @brief ���������Ƿ��ڻ״̬��
 *
 * @param buzzer ������ָ�롣
 * @return ������������ڻ״̬���򷵻� @ref buzzer_active_e ö�������еĻ״̬��
 *         ���������Ϊ NULL���򷵻� @ref BUZZER_IS_NOT_ACTIVE��
 */
buzzer_active_e buzzer_is_active(buzzer_t *buzzer) {
    if (buzzer != NULL) {
        return buzzer->active;
    }
    return BUZZER_IS_NOT_ACTIVE;
}
