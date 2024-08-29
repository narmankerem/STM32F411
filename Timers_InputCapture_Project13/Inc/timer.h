
#ifndef TIMER_H_
#define TIMER_H_

#define TIMX_SR_UIF		(1U<<0)
#define TIMX_SR_CC1IF	(1U<<1)

void timer2_1hz_init (void);
void timer2_pa5_output_compare (void);
void timer3_pa6_input_capture (void);


#endif /* TIMER_H_ */
