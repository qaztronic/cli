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

#ifndef _QAZ_SYS_CMD_H_
#define _QAZ_SYS_CMD_H_

#define INPUT_LINE_LENGTH   50
#define MAX_CMD_LENGTH      20
#define MAX_CLI_ARGC        6

// #include <xil_printf.h>

// #define ANSI_ESCAPE_CODE
// #define CLI_ECHO_UART

// #define PRINTF_MACRO xil_printf
// #define PRINTF_MACRO iprintf
#define PRINTF_MACRO printf

typedef char (*cli_cmd_func)( const unsigned char argc, const char * argv[] );

typedef struct cli_cmd_tab_t
{
  char          cmd[MAX_CMD_LENGTH];
  cli_cmd_func  func;
  const char    *help_string;
} cli_cmd_tab_t;

extern struct cli_cmd_tab_t cli_commands[];

/*-----------------------------------------------------------*/
extern void sys_cli_task(void);
extern cli_cmd_tab_t *cli_find_command( cli_cmd_tab_t *cmd_to_check);
extern void cli_init(void);
extern char func_mw(const unsigned char argc, const char *argv[]);
extern char func_md(const unsigned char argc, const char *argv[]);

/*-----------------------------------------------------------*/
#endif  //  _QAZ_SYS_CMD_H_
