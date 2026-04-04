#include <io.h>

void _start(void)
{
	io_screen_clear();
	io_cursor_update();
	for (;;)
	{
		const IOCharacter c = io_handle_scancode_ascii(io_character_input());
		if (!c)
		{
			continue;
		}
//		if (c == '\t')
//		{
//			io_character_output(' ', IO_DEFAULT_STYLE);
//			io_character_output(' ', IO_DEFAULT_STYLE);
//		}
		else
		{
			io_character_output(c, IO_DEFAULT_STYLE);
		}
	}
}
