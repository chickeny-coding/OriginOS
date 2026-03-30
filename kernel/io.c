#include <io.h>

void io_clear_screen(void)
{
	for (Cursor i = 0; i < IO_SCREEN_HEIGHT * IO_SCREEN_WIDTH; ++i)
	{
		IO_SCREEN[i << 1] = ' ';
		IO_SCREEN[i << 1 | 1] = 0x00;
	}
}
