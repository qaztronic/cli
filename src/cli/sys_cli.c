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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sys_cmd.h"
#include "sys_error.h"



/*-----------------------------------------------------------*/
void clear_screen(void)
{
  PRINTF_MACRO("\033[H\033[J");
}


/*-----------------------------------------------------------*/
#ifdef ANSI_ESCAPE_CODE
#define ASCII_ESC '\x1b'

static void send_csi(char c)
{
  putchar(ASCII_ESC);
  putchar('[');
  putchar(c);
}
#else
static void send_csi(char c) {};
#endif


/*-----------------------------------------------------------*/
static char *cli_edit_buffer(char *in_buffer, char *out_buffer, unsigned int line_length)
{
  static char *out_ptr;
  static char *begin_ptr;
  static char *end_ptr;

#ifdef ANSI_ESCAPE_CODE
  static char prev_char;
  static unsigned int csi;
#endif

#ifdef CLI_ECHO_UART
  fwrite(in_buffer,1,line_length,stdout);
#endif

  unsigned int i;

  if(out_buffer != NULL)
  {
    out_ptr   = out_buffer;
    begin_ptr = out_buffer;
    end_ptr   = out_buffer + INPUT_LINE_LENGTH;

#ifdef ANSI_ESCAPE_CODE
    prev_char = 0;
    csi = 0;
#endif
  }

  for(i = 0 ; i < line_length ; i++)
  {

    if(out_ptr >= end_ptr)
    {
      *end_ptr = '\0';
      return(NULL);
    }

    if(out_ptr < begin_ptr)
      sys_error_fatal(FATAL_ERROR_CLI);

    switch(in_buffer[i])
    {
      case '\0':
        return(NULL);
        break;

      case '\n':
        *out_ptr = '\0';
        return(NULL);
        break;

      case '\r':
        *out_ptr = '\0';
        return(NULL);
        break;

      case '\b':
        if(out_ptr != begin_ptr)
        {
          send_csi('P');
          out_ptr--;
        } else
        {
          putchar(' ');
          send_csi('\a');
        }
        break;

#ifdef ANSI_ESCAPE_CODE
      case ASCII_ESC:
        break;

      case '[':
        if(prev_char == ASCII_ESC)
        {
          csi = 1;
        } else
        {
          *out_ptr = in_buffer[i];
          out_ptr++;
        }
        break;

      case 'A':
        if(csi)
        {
          send_csi('B');
          send_csi('\a');

          csi = 0;
        } else
        {
          *out_ptr = in_buffer[i];
          out_ptr++;
        }
        break;

      case 'B':
        if(csi == 0)
        {
          *out_ptr = in_buffer[i];
          out_ptr++;
        }
        break;

      case 'C':
        if(csi)
        {
          send_csi('D');
          send_csi('\a');

          csi = 0;
        } else
        {
          *out_ptr = in_buffer[i];
          out_ptr++;
        }
        break;

      case 'D':
        if(csi)
        {
          send_csi('C');
          send_csi('\a');

          csi = 0;
        } else
        {
          *out_ptr = in_buffer[i];
          out_ptr++;
        }
        break;
#endif

      default:
        *out_ptr = in_buffer[i];
        out_ptr++;
        break;
    }

#ifdef ANSI_ESCAPE_CODE
    prev_char = in_buffer[i];
#endif
  }

  return(out_ptr);
}


/*-----------------------------------------------------------*/
void sys_cli_task(void)
{
  char last_return_value = EXIT_SUCCESS;
  char in_buffer[INPUT_LINE_LENGTH + 1];
  char out_buffer[INPUT_LINE_LENGTH + 1];
  char *cli_ptr;
  struct cli_cmd_tab_t cmd_to_check = { "", NULL, NULL };
  unsigned char cli_argc;
  char *cli_argv[MAX_CLI_ARGC];
  struct cli_cmd_tab_t *cli_cmd;
  unsigned int bytes_read;

  cli_init();

  for(;;)
  {
    PRINTF_MACRO("\r\n# > ");

    cli_argc = 0;
    last_return_value = EXIT_SUCCESS;

    bytes_read = (unsigned int)read(STDIN_FILENO, (void *)in_buffer, sizeof(in_buffer));
    cli_ptr = cli_edit_buffer(in_buffer, out_buffer, bytes_read);

    while(cli_ptr != NULL)
    {
      bytes_read = (unsigned int)read(STDIN_FILENO, (void *)in_buffer, sizeof(in_buffer));
      cli_ptr = cli_edit_buffer(in_buffer, NULL, bytes_read);
    }

    if(out_buffer[0] == '\0')
      last_return_value = EXIT_FAILURE;

    while(last_return_value != EXIT_FAILURE)
    {
      cli_ptr = strtok(out_buffer, " \t");

      strncpy(cmd_to_check.cmd, out_buffer, MAX_CMD_LENGTH);
      cli_cmd = cli_find_command(&cmd_to_check);

      if (cli_cmd == NULL)
      {
        PRINTF_MACRO("\r\n! > Command not found!!!");
        last_return_value = EXIT_FAILURE;
        break;
      }

      if(cli_ptr == NULL)
      {
        cli_argv[cli_argc] = out_buffer;
        cli_argc++;
      } else
      {
        while(cli_ptr != NULL)
        {
          cli_argv[cli_argc] = cli_ptr;
          cli_argc++;

          cli_ptr = strtok(NULL, " \t");
        }
      }

      last_return_value = cli_cmd->func(cli_argc, (const char **)cli_argv);
      break;
    }

  }
}

