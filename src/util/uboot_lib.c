//////////////////////////////////////////////////////////////////////
////                                                              ////
//// Copyright (C) 2015 Authors and OPENCORES.ORG                 ////
////                                                              ////
//// This source file may be used and distributed without         ////
//// restriction provided that this copyright statement is not    ////
//// removed from the file and that any derivative work contains  ////
//// the original copyright notice and the associated disclaimer. ////
////                                                              ////
//// This source file is free software; you can redistribute it   ////
//// and/or modify it under the terms of the GNU Lesser General   ////
//// Public License as published by the Free Software Foundation; ////
//// either version 2.1 of the License, or (at your option) any   ////
//// later version.                                               ////
////                                                              ////
//// This source is distributed in the hope that it will be       ////
//// useful, but WITHOUT ANY WARRANTY; without even the implied   ////
//// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR      ////
//// PURPOSE.  See the GNU Lesser General Public License for more ////
//// details.                                                     ////
////                                                              ////
//// You should have received a copy of the GNU Lesser General    ////
//// Public License along with this source; if not, download it   ////
//// from http://www.opencores.org/lgpl.shtml                     ////
////                                                              ////
//////////////////////////////////////////////////////////////////////

#include "uboot_lib.h"


/*-----------------------------------------------------------*/
int cmd_get_data_size(const char * arg, int default_size)
{
	/* Check for a size specification .b, .w or .l.
	 */
	int len = strlen(arg);
	if (len > 2 && arg[len-2] == '.') {
		switch (arg[len-1]) {
		case 'b':
			return 1;
		case 'w':
			return 2;
		case 'l':
			return 4;
		case 's':
			return -2;
		default:
			return -1;
		}
	}
	return default_size;
}


/*-----------------------------------------------------------*/
unsigned long simple_strtoul(const char *cp, char **endp,
				unsigned int base)
{
	unsigned long result = 0;

  result  = strtoul( cp, endp, base );

	return result;
}


/*-----------------------------------------------------------*/
#define MAX_LINE_LENGTH_BYTES (64)
#define DEFAULT_LINE_LENGTH_BYTES (16)
int print_buffer(ulong addr, const void *data, uint width, uint count,
		 uint linelen)
{
	/* linebuf as a union causes proper alignment */
	union linebuf {
#ifdef CONFIG_SYS_SUPPORT_64BIT_DATA
		uint64_t uq[MAX_LINE_LENGTH_BYTES/sizeof(uint64_t) + 1];
#endif
		uint32_t ui[MAX_LINE_LENGTH_BYTES/sizeof(uint32_t) + 1];
		uint16_t us[MAX_LINE_LENGTH_BYTES/sizeof(uint16_t) + 1];
		uint8_t  uc[MAX_LINE_LENGTH_BYTES/sizeof(uint8_t) + 1];
	} lb;
	int i;
#ifdef CONFIG_SYS_SUPPORT_64BIT_DATA
	uint64_t __maybe_unused x;
#else
	uint32_t __maybe_unused x;
#endif

	if (linelen*width > MAX_LINE_LENGTH_BYTES)
		linelen = MAX_LINE_LENGTH_BYTES / width;
	if (linelen < 1)
		linelen = DEFAULT_LINE_LENGTH_BYTES / width;

	while (count) {
		uint thislinelen = linelen;
		PRINTF_MACRO("%08lx:", addr);

		/* check for overflow condition */
		if (count < thislinelen)
			thislinelen = count;

		/* Copy from memory into linebuf and print hex values */
		for (i = 0; i < thislinelen; i++) {
			if (width == 4)
      {
				x = lb.ui[i] = *(volatile uint32_t *)data;
        PRINTF_MACRO(" %08x", x);
      }
#ifdef CONFIG_SYS_SUPPORT_64BIT_DATA
			else if (width == 8)
      {
				x = lb.uq[i] = *(volatile uint64_t *)data;
        PRINTF_MACRO(" %016llx", (long long)x);
      }
#endif
			else if (width == 2)
      {
				x = lb.us[i] = *(volatile uint16_t *)data;
        PRINTF_MACRO(" %04x", x);
      }
			else
      {
				x = lb.uc[i] = *(volatile uint8_t *)data;
        PRINTF_MACRO(" %02x", x);
      }
// #ifdef CONFIG_SYS_SUPPORT_64BIT_DATA
			// PRINTF_MACRO(" %0*llx", width * 2, (long long)x);
// #else
			// PRINTF_MACRO(" %0*x", width * 2, x);
// #endif
			data += width;
		}

		while (thislinelen < linelen) {
			/* fill line with whitespace for nice ASCII print */
			for (i=0; i<width*2+1; i++)
				puts(" ");
			linelen--;
		}

		/* Print data in ASCII characters */
		for (i = 0; i < thislinelen * width; i++) {
			if (!isprint(lb.uc[i]) || lb.uc[i] >= 0x80)
				lb.uc[i] = '.';
		}
		lb.uc[i] = '\0';
		PRINTF_MACRO("    %s\r\n", lb.uc);

		/* update references */
		addr += thislinelen * width;
		count -= thislinelen;

		// if (ctrlc())
			// return -1;
	}

	return 0;
}





