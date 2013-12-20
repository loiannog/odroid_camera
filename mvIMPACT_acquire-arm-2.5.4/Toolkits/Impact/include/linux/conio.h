#ifndef CONIO_H
#define CONIO_H

#include <stdio.h>

int _kbhit( void );
int _getch( void );
int _getche( void ); 


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	int _getc( FILE *stream );
	int _getchar( void );
	int _mvkbhit( void );

#ifdef __cplusplus  
}
#endif /* __cplusplus */

#endif

