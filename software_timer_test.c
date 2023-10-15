#include "software_timer.h"

sw_timer_t *swTimer1;
sw_timer_t *swTimer2;
char array[100];

void timer1_callback(void)
{
    sprintf(array, "%s\n", getRunTimeStr());
}

int software_timer_test(void)
{
    // INITS
    swTimer1 = swTimer_init(100, SW_TIMER_PERIODIC, timer1_callback);
    swTimer_start(swTimer1);

    swTimer2 = swTimer_init(1000, SW_TIMER_PERIODIC, NULL);
    swTimer_start(swTimer2);
    
    // INITS
    while (1)
    {
        //LOOP
    }
}