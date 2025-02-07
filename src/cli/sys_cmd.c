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
#include "sys_cmd.h"


/*-----------------------------------------------------------*/
static unsigned int cli_no_of_commands;

void cli_init( void )
{
  int i;

  for(i = 0; cli_commands[i].func != NULL; i++);

  cli_no_of_commands = i;
}


/*-----------------------------------------------------------*/
static int cmd_cmp( const void *e1, const void *e2 )
{
  struct cli_cmd_tab_t *p_cmd_1 = (struct cli_cmd_tab_t *)e1;
  struct cli_cmd_tab_t *p_cmd_2 = (struct cli_cmd_tab_t *)e2;

  return strncmp( p_cmd_1->cmd, p_cmd_2->cmd, MAX_CMD_LENGTH );
}


/*-----------------------------------------------------------*/
cli_cmd_tab_t *cli_find_command( cli_cmd_tab_t *cmd_to_check )
{
  struct cli_cmd_tab_t *cli_cmd;

  cli_cmd = (struct cli_cmd_tab_t *) bsearch( cmd_to_check, cli_commands, cli_no_of_commands, sizeof(struct cli_cmd_tab_t), cmd_cmp );

  return(cli_cmd);
}


/*-----------------------------------------------------------*/
static char func_help( const unsigned char argc, const char *argv[] )
{
  unsigned int i;

  PRINTF_MACRO( "Usage: cmd <arg1> <arg2> <arg3> ...\r\n" );
  PRINTF_MACRO( "\r\n" );
  PRINTF_MACRO( "Commands:\r\n" );

  for( i = 0; i < cli_no_of_commands; i++ )
    puts( cli_commands[i].help_string );

  return EXIT_SUCCESS;
}


/*-----------------------------------------------------------*/
static char func_comment( const unsigned char argc, const char *argv[] )
{
  PRINTF_MACRO( "# > ");
  return EXIT_SUCCESS;
}


/*-----------------------------------------------------------*/
static char func_peek( const unsigned char argc, const char *argv[] )
{
  volatile unsigned int *address = (volatile unsigned int *)( strtoul( argv[1], (char **)NULL, 16 ) );

  PRINTF_MACRO( "peek: %s => 0x%08x \r\n", argv[1], *address  );

  return EXIT_SUCCESS;
}


/*-----------------------------------------------------------*/
static char func_poke( const unsigned char argc, const char *argv[] )
{
  volatile unsigned int *address  = (volatile unsigned int *)( strtoul( argv[1], (char **)NULL, 16 ) );
  unsigned int value              = strtoul( argv[2], (char **)NULL, 16 );

  *((volatile unsigned int *)address) = value;

  PRINTF_MACRO( "poke: %s <= %s \r\n", argv[1], argv[2]  );

  return EXIT_SUCCESS;
}


/*-----------------------------------------------------------*/
#include "memtest.h"

static char func_memtest( const unsigned char argc, const char *argv[] )
{
  datum *address        = (datum *)( strtoul( argv[1], (char **)NULL, 16 ) );
  unsigned long nBytes  = strtoul( argv[2], (char **)NULL, 16 );

  if( argc != 3 || address == NULL || nBytes == 0 )
  {
    PRINTF_MACRO( "memtest:  bad args \r\n" );
    return( EXIT_FAILURE );
  }

  PRINTF_MACRO( "running memTestDataBus() ...   " );

  if( memTestDataBus( address ) )
    PRINTF_MACRO( "FAILED!!!\r\n" );
  else
    PRINTF_MACRO( "PASSED\r\n" );


  PRINTF_MACRO( "running memTestAddressBus() ...   " );

  if( memTestAddressBus( address, nBytes ) )
    PRINTF_MACRO( "FAILED!!!\r\n" );
  else
    PRINTF_MACRO( "PASSED\r\n" );


  PRINTF_MACRO( "running memTestDevice() ...   " );

  if( memTestDevice( address, nBytes ) )
    PRINTF_MACRO( "FAILED!!!\r\n" );
  else
    PRINTF_MACRO( "PASSED\r\n" );

    return EXIT_SUCCESS;
}


/*-----------------------------------------------------------*/
//  command table
#include "sys_cmd_table.h"


