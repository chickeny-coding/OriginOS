#ifndef _IO_H_
#define _IO_H_

typedef unsigned char	Character;
typedef unsigned short	Cursor;

#define IO_SCREEN		((Character *)(0x000B8000))
#define IO_SCREEN_HEIGHT	25
#define IO_SCREEN_WIDTH		80

void io_clear_screen(void);

#endif
