#ifdef WIN32
#include "main.h"
#include "dinput.h"

LPDIRECTINPUT lpdi = NULL;
LPDIRECTINPUTDEVICE lpdiMouse;
DIMOUSESTATE mouse;

px_timer_t dx_mouse_timer;

void dx_timer_init( void )
{
	timer_clear( &dx_mouse_timer );
}

BOOL dx_init( void )
{
	HRESULT  err;
	GUID guid_mouse = GUID_SysMouse;

	dx_timer_init();

	err = DirectInputCreate(GetModuleHandle(NULL), DIRECTINPUT_VERSION, &lpdi, NULL);
	if (FAILED(err))
		return FALSE;

	err = IDirectInput_CreateDevice(lpdi, &guid_mouse, &lpdiMouse, NULL);
	if ( err != DI_OK )
		return FALSE;

	err = IDirectInputDevice_SetDataFormat(lpdiMouse, &c_dfDIMouse);
	if(err != DI_OK)
		return FALSE;

	err = IDirectInputDevice_SetCooperativeLevel(
		lpdiMouse, GetActiveWindow(), DISCL_NONEXCLUSIVE | DISCL_BACKGROUND
	);
	if(err != DI_OK)
		return FALSE;

	err = IDirectInputDevice_Acquire(lpdiMouse);

	return TRUE;
}

void dx_read_mouse( void )
{
	static float runs = 0.0f;
	HRESULT hr = IDirectInputDevice_GetDeviceState(
		lpdiMouse, sizeof(DIMOUSESTATE), &mouse
	);
	runs++;
	if( hr == DI_OK )
	{
		if(mouse.lX + mouse.lY > 0)
		{
			//float seconds = timer_run( &dx_mouse_timer );
			//float ms = seconds * 1000.0f;
			//float per_second = runs / seconds;
			//p("dx/s:  %f s:%f ms:%f r:%f\n",per_second,seconds,ms,runs);
			//p("x %d y %d\n", mouse.lX, mouse.lY);
			p("dx runs  %f\n",runs);
			runs = 0.0f;
		}
	}
	else if( hr == DIERR_INPUTLOST )
	{
		p("dx input lost - reacuiring...\n");
		IDirectInputDevice_Acquire(lpdiMouse);
	}
	else
	{
		p("mouse error: %d\n",hr);
	}
}

#endif // WIN32
