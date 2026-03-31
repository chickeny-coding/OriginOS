#include <io.h>

IOPortValue io_inb(const IOPort p)
{
	IOPortValue r;
	__asm__ ("inb %1, %0" : "=a"(r) : "d"(p));
	return r;
}

void io_outb(const IOPort p, const IOPortValue v)
{
	__asm__ ("outb %0, %1" :: "a"(v), "d"(p));
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
	IO_SCREEN[io_cursor << 1] = c;
	IO_SCREEN[io_cursor << 1 | 1] = s;
	++io_cursor;
	io_cursor_update();
}
