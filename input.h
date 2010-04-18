#ifndef INPUT_INCLUDED
#define INPUT_INCLUDED

#ifdef WIN32
#define DIRECTINPUT_VERSION 0x0700
#include <dinput.h>
BOOL dx_init( void );
void dx_read_mouse( void );
#endif // WIN32

BOOL sdl_handle_events( void );
void sdl_timer_init( void );

#endif
