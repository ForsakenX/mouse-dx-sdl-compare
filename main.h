#ifndef MAIN_INCLUDED
#define MAIN_INCLUDED

#ifdef WIN32
#include <windows.h>	// for various things
#include <ctype.h>	// for toupper
#include <io.h>
#endif

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <search.h>

#ifndef	TRUE
#define	TRUE	(1==1)
#endif

#ifndef	FALSE
#define	FALSE	(!TRUE)
#endif

typedef unsigned int		uint;
typedef	unsigned char		uint8;
typedef	char			int8;
typedef	unsigned short int	uint16;	
typedef	short int		int16;
typedef	unsigned long		uint32;	
typedef	long			int32;

typedef int                 BOOL;
typedef unsigned char       BYTE;

typedef unsigned long       DWORD;
typedef unsigned short      WORD;

typedef unsigned char uchar_t;

#ifdef WIN32
#include <string.h>
#define strcasecmp	_stricmp
#define strncasecmp _strnicmp
#define strdup _strdup
#include <stdio.h>
#define snprintf	_snprintf
#include <direct.h>
#define chdir		_chdir
#endif

void strtoupper(char *str);

void p( const char * format, ... );

#include "SDL.h"
#include "input.h"
#include "timer.h"

#endif	// MAIN_INCLUDED
