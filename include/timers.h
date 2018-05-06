#ifndef TIMERS_H_INCLUDED
#define TIMERS_H_INCLUDED

#include <stdint.h>

typedef void (*timer_callback_t)(void);

void timer2_init(uint32_t period,int use_us);
void timer2_enableIRQ(timer_callback_t callback);
void timer2_start(void);
void timer2_stop(void);

void timer15_init(uint16_t period,int use_us);
void timer15_enableIRQ(timer_callback_t callback);
void timer15_start(void);
void timer15_stop(void);

void timer16_init(uint16_t period,int use_us);
void timer16_enableIRQ(timer_callback_t callback);
void timer16_start(void);
void timer16_stop(void);

void timer17_init(uint16_t period,int use_us);
void timer17_enableIRQ(timer_callback_t callback);
void timer17_start(void);
void timer17_stop(void);

void timer6_init(uint16_t period,int use_us);
void timer6_enableIRQ(timer_callback_t callback);
void timer6_start(void);
void timer6_stop(void);

#endif
