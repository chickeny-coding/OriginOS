#include <bool.h>
#include <io.h>

IOPortValue io_inb(const IOPort p)
{
	IOPortValue r;
	__asm__ ("inb %1, %0" : "=a"(r) : "d"(p) : "memory");
	return r;
}

void io_outb(const IOPort p, const IOPortValue v)
{
	__asm__ ("outb %0, %1" :: "a"(v), "Nd"(p));
}

void io_screen_clear(void)
{
	for (IOCursor i = 0; i < IO_SCREEN_HEIGHT * IO_SCREEN_WIDTH; ++i)
	{
		IO_SCREEN[i << 1] = ' ';
		IO_SCREEN[i << 1 | 1] = IO_DEFAULT_STYLE;
	}
}

IOCursor io_cursor;

void io_cursor_update(void)
{
	io_outb(IO_VGA_SELECT, 0x0E);
	io_outb(IO_VGA_VALUE, io_cursor >> 8);
	io_outb(IO_VGA_SELECT, 0x0F);
	io_outb(IO_VGA_VALUE, io_cursor & 0xFF);
}

void io_character_output(const IOCharacter c, const IOStyle s)
{
	switch (c)
	{
		case '\b':
		{
			--io_cursor;
			IO_SCREEN[io_cursor << 1] = ' ';
			IO_SCREEN[io_cursor << 1 | 1] = IO_DEFAULT_STYLE;
			break;
		}
		case '\n':
		{
			io_cursor += IO_SCREEN_WIDTH;
			io_cursor -= io_cursor % IO_SCREEN_WIDTH;
			break;
		}
		default:
		{
		        IO_SCREEN[io_cursor << 1] = c;
		        IO_SCREEN[io_cursor << 1 | 1] = s;
			++io_cursor;
		}
	}
	io_cursor_update();
}

IOScanCode io_character_input(void)
{
	while (!(io_inb(0x0064) & 0x01));
	return io_inb(0x0060);
}

bool shift;

const IOCharacter io_scancode_ascii_table_unshifted[IO_SCANCODE_ASCII_TABLE_SIZE] = "\0\0001234567890-=\b qwertyuiop[]\n\0asdfghjkl;'`\0\\zxcvbnm,./\0\0\0 ";

const IOCharacter io_scancode_ascii_table_shifted[IO_SCANCODE_ASCII_TABLE_SIZE] = "\0\0!@#$%^&*()_+\b QWERTYUIOP{}\n\0ASDFGHJKL:\"~\0|ZXCVBNM<>?\0\0\0 ";

IOCharacter io_handle_scancode_ascii(const IOScanCode v)
{
	if (v == 0x2A || v == 0x36)
	{
		shift = true;
		return '\0';
	}
	if (v == 0xAA || v == 0xB6)
	{
		shift = false;
		return '\0';
	}
	if (v < IO_SCANCODE_ASCII_TABLE_SIZE)
	{
		return (shift ? io_scancode_ascii_table_shifted : io_scancode_ascii_table_unshifted)[v];
	}
	return '\0';
}
