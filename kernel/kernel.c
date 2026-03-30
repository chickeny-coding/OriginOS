#include <io.h>

#define STYLE	0x07

const char s [] = "OriginOS";

void _start(void)
{
	io_clear_screen();
	for (Cursor i = 0; s[i]; ++i)
	{
		IO_SCREEN[i << 1] = s[i];
		IO_SCREEN[i << 1 | 1] = STYLE;
	}
	for (;;);
}
