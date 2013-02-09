#ifndef AVR_TIME_H
#define AVR_TIME_H
#ifdef __cplusplus
extern "C" {
#endif

void time_init();
unsigned long avr_time(void);
void delay_ms(unsigned long delay);

#ifdef __cplusplus
}
#endif
#endif // AVR_TIME_H
