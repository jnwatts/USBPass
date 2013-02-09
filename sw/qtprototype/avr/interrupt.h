#ifndef AVR_INTERRUPT_H
#define AVR_INTERRUPT_H
#ifdef __cplusplus
extern "C" {
#endif

#define ISR(x) void x(void)

void PCINT0_vect(void);

#ifdef __cplusplus
}
#endif
#endif // INTERRUPT_H
