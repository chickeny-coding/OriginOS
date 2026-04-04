#ifndef _IO_H_
#define _IO_H_

typedef unsigned short	IOPort;
typedef unsigned char	IOPortValue;
typedef unsigned short	IOCursor;
typedef unsigned char	IOCharacter;
typedef unsigned char	IOStyle;
typedef IOPortValue	IOScanCode;

#define IO_SCREEN			((IOCharacter *)(0x000B8000))
#define IO_SCREEN_HEIGHT		25
#define IO_SCREEN_WIDTH			80
#define IO_VGA_SELECT			0x03D4
#define IO_VGA_VALUE			0x03D5
#define IO_DEFAULT_STYLE		0x07
#define IO_SCANCODE_ASCII_TABLE_SIZE	58

IOPortValue io_inb(const IOPort p);
void io_outb(const IOPort p, const IOPortValue v);

void io_screen_clear(void);

void io_cursor_update(void);

void io_character_output(const IOCharacter c, const IOStyle s);
IOScanCode io_character_input(void);

IOCharacter io_handle_scancode_ascii(const IOScanCode v);

#endif
