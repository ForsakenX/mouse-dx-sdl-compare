#include "main.h"

void strtoupper(char *str)
{
	while (*str)
	{
		*str = (char) toupper(*str); 
		str++; 
	}
}

void l( char * str )
{
	static FILE * fp;

	if(!fp)
		fp = fopen( "log.txt", "w" );

	if( fp )
	{
		fprintf( fp, "%s", str );
		fflush( fp );
	}
}

void p( const char * format, ... )
{
	char buf[0x4000];
	va_list args;

	va_start( args, format );
	vsnprintf( buf, 0x4000, format, args );
	va_end( args );

#ifdef WIN32
	OutputDebugString( buf );
#else
	fputs( buf, stderr );
#endif

	l( buf );
}

BOOL sdl_print_info( void )
{
	SDL_version ver;
	SDL_VERSION(&ver);

	p("SDL compile-time version: %u.%u.%u\n", ver.major, ver.minor, ver.patch);

	ver = *SDL_Linked_Version();

	p("SDL runtime version: %u.%u.%u\n", ver.major, ver.minor, ver.patch);

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 || !SDL_GetVideoInfo() )
	{
		p("Failed to initialize sdl: %s\n",SDL_GetError());
		return FALSE;
	}

	return TRUE;
}

typedef struct {
	int w;
	int h;
} video_mode_t;

BOOL enumerate_video_mode( Uint32 flags, video_mode_t * mode )
{
	SDL_Rect** modes = SDL_ListModes(NULL, flags);

	if (modes == (SDL_Rect**)0) 
	{
		p("No video modes available for given format!\n");
		return FALSE;
	}

	if (modes != (SDL_Rect**)-1) 
	{
		mode->w = modes[0]->w;
		mode->h = modes[0]->h;
	}
	else
	{
		mode->w = 640;
		mode->h = 480;
	}

	return TRUE;
}

BOOL sdl_init( void )
{
	video_mode_t mode;
	SDL_Surface * screen;
	Uint32 flags = SDL_ANYFORMAT;// | SDL_FULLSCREEN;

	sdl_print_info();

	sdl_timer_init();

	if(!enumerate_video_mode( flags, &mode ))
		return FALSE;

	screen = SDL_SetVideoMode( mode.w, mode.h, 24, flags );

	if(!screen)
	{
		p("main_sdl: failed to create video surface: %s\n",SDL_GetError());
		return FALSE;
	}

	return TRUE;
}

//px_timer_t main_timer;

int main( int argc, char* argv[] )
{
/*
	int loops = 0;
	timer_clear(&main_timer);
	timer_run(&main_timer);
*/

#ifdef WIN32
	if(!dx_init())
		return FALSE;
#endif

	if(!sdl_init())
		return FALSE;

	while(1)
	{
/*
		loops++;
		if(timer_peek( &main_timer ) > 1.0f)
		{
			float fps = loops / timer_run( &main_timer );
			loops = 0;
			p("fps: %f\n",fps);
		}
*/
		
#ifdef WIN32
		dx_read_mouse();
#endif
		if(!sdl_handle_events())
			break;
	}

	SDL_Quit();

	return 0;
}
