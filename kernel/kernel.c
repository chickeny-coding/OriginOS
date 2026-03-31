#include <io.h>

const IOCharacter s [] = "OriginOS";

void _start(void)
{
	io_screen_clear();
	for (IOCursor i = 0; s[i]; ++i)
	{
		io_character_output(s[i], IO_DEFAULT_STYLE);
	}
	for (;;);
}
