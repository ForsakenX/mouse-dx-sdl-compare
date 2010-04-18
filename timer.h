#ifndef TIMER
#define TIMER
#include "main.h"

/*
	setup:

			timer t;
			timer_clear( & t );

	time passed between two points:

			while(1)
			{
				timer_run( &t );
				sleep( 10 );
				duration = timer_run( &t );
				// duration is always 10
			}

	peeking at the time without modifing last time:

			duration = timer_peek( &t );

*/

typedef struct timer {
  Uint32  last;
  float   best;
  float   worst;
  float   seconds;
} px_timer_t;

float timer_run   ( px_timer_t* );
float timer_peek  ( px_timer_t* );
void  timer_clear ( px_timer_t* );
void  timer_debug ( char*, px_timer_t* );

#endif
