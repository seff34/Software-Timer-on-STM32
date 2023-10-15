
## API Kullanımı

### BASIC Usage with SYSTICK
 * Basic usage is basic :)
 * Include header file on your source file .
 * Define a Software Timer;
 * Init the Timer
 * Init the Callback function
 * Start the Timer
 * thats all.

#### Example
```c
#include "software_timer.h"
...
void timer1_callback(void)
{
    ...
}
...
void INIT() {
    sw_timer_t* swTimer1;
    swTimer1 = swTimer_init(1000, SW_TIMER_PERIODIC,timer1_callback);
    swTimer_start(swTimer1);
}
...
```

### ADVANGE Usage with TIMER
* Advanced usage not hard but its not basic.
 * This usage start same as basic usage.
 * Include header file on your source file .
 * Define a Software Timer;
 * Init the Timer
 * Init the Callback function
 * Start the Timer
 * Comment BASIC_USAGE definition in this header.
 * Create a Real Timer by CubeMx.
 * The timer set 1 millisecond.
 * Start the timer.
 * You must call swTimer_proses(swTimerX); function every software timer in your Timer handler.
#### Example
```c
// (100MHz Prosesor) / (99 (Prescaler) * 999 *(Period)) =~ 1Khz =~ 1ms Timer
static void MX_TIM1_Init(void)
{
    ...
    htimx.Init.Prescaler = 100;
    htimx.Init.Period = 1000;
    ...
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
if ( htim->Instance == htimx.Instance ) {
    swTimer_proses(swTimer1);
    swTimer_proses(swTimer2);
}
...
void INIT(){
    HAL_TIM_Base_Start_IT(&htimx);  // START TIMER
    ...
}
```


### Timeout Functions
 *	Timeout Functions use SYSTICK_TIMER
 *	swTimer_delay 			-> Standard delay function similar to  HAL_Delay()
 *	swTimer_waitFlag		-> Timeout Function: Control of a flag
 *	swTimer_waitDoubleFlag  -> Timeout Function: Control of two flag

#### Example
 *	In this use, a delay of 10 seconds is set.
 *	If within 10 seconds the flag given as a parameter becomes true via another interrupt,
 *	the function returns true immediately. If not, it returns false.
```c
	if (swTimer_waitFlag(10000,&flag))
		foo();
```

### API Functions
```c
#define SW_TIMER_LIMIT 	   100
#define SW_TIMER_MAX_VALUE UINT32_MAX
#define SW_TIMER_PERIODIC  true
#define SW_TIMER_ONESHOT   false
#define SW_TIMER_START     true
#define SW_TIMER_STOP      false

typedef struct SOFTWARE_TIMER_INIT
{
	volatile uint32_t counter;			// Timer Millisecond currunt value
	uint32_t target;					// Timer Millisecond target/interrupt value
	bool status;						// Timer Status (SW_TIMER_START-SW_TIMER_STOP)
	bool type;							// Timer Type   (SW_TIMER_PERIODIC-SW_TIMER_ONESHOT)
	void(*callback)(void);				// Timer Callback Function
}sw_timer_t;

/**
  * @brief Software Timer Initalize
  * @param uint32_t 	 Timer Value on millisecond
  * @param bool 		 Timer Type( SW_TIMER_PERIODIC - SW_TIMER_ONESHOT)
  * @param void(*)(void) Software Timer Callback Function
  * @retval sw_timer_t   Software Timer Pointer
  */
sw_timer_t* swTimer_init(const uint32_t target,const bool type,void(*callback)(void));

/**
  * @brief Software Timer Get Status
  * @param sw_timer_t Software Timer Pointer
  * @retval bool Software Timer Status ( Running = true / Stop = false )
  */
bool swTimer_status(sw_timer_t* swTimer);

/**
  * @brief Software Timer Start
  * @param sw_timer_t Software Timer Pointer
  * @retval none
  */
void swTimer_start(sw_timer_t* swTimer);

/**
  * @brief Software Timer Stop
  * @param sw_timer_t Software Timer Pointer
  * @retval none
  */
void swTimer_stop(sw_timer_t* swTimer);

/**
  * @brief Software Timer Reset
  * @note  Counter value reset but timer status unchanged
  * @param sw_timer_t Software Timer Pointer
  * @retval none
  */
void swTimer_reset(sw_timer_t* swTimer);

/**
  * @brief Software Timer Restart
  * @note  Counter value reset and timer started
  * @param sw_timer_t Software Timer Pointer
  * @retval none
  */
void swTimer_restart(sw_timer_t* swTimer);

/**
  * @brief  Software   Timer Set Target Value
  * @param  sw_timer_t Software Timer Pointer
  * @param  uint32_t   New Timer Target Value
  * @retval uint32_t   Old Timer Target Value
  */
uint32_t swTimer_setTargetValue(sw_timer_t* swTimer,uint32_t newTarget);

/**
  * @brief  Software   Timer Get Target Value
  * @param  sw_timer_t Software Timer Pointer
  * @retval uint32_t   Timer Target Value
  */
uint32_t swTimer_getTargetValue(const sw_timer_t* swTimer);

#ifndef USE_SYSTICK_TIMER
/**
  * @note  This function has been removed in the interface.
  * 	   If you want to use a different timer. Comment to USE_SYSTICK_TIMER on top.
  * @brief Software Timer Proses
  * @param sw_timer_t Software Timer Pointer
  * @retval none
  */
void swTimer_proses(sw_timer_t* swTimer);
#endif

/**
  * @brief  Standart Delay
  * @param  uint32_t Delay Period
  * @retval none
  */
void swTimer_delay(const uint32_t delay);

/**
  * @brief  Delay With a Flag
  * @param  uint32_t Delay Period
  * @param  bool*    First Flag
  * @retval bool 	 Returns true if delay ended early
  */
bool swTimer_waitFlag(const uint32_t delay,bool* flag);

/**
  * @brief  Delay With a Flag
  * @param  uint32_t Delay Period
  * @param  bool*    First Flag
  * @param  bool*	 Second Flag
  * @retval bool     Returns true if delay ended early
  */
bool swTimer_waitDoubleFlag(const uint32_t delay,bool* flag1,bool* flag2);

/**
  * @brief  Get Run Time Seceond
  * @retval uint32_t Run Time Second Value
  */
uint32_t getRunTimeSec();

/**
  * @brief  Get Run Time Miliseceond
  * @retval uint32_t Run Time Miliseceond Value
  */
uint32_t getRunTimeMsec();

/**
  * @brief  Get Run Time Value on string
  * @retval char* Run Time Value on string
  */
const char* getRunTimeStr();
  