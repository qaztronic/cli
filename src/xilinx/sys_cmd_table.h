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
//// either version 2.1 of the License or (at your option) any   ////
//// later version.                                               ////
////                                                              ////
//// This source is distributed in the hope that it will be       ////
//// useful but WITHOUT ANY WARRANTY; without even the implied   ////
//// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR      ////
//// PURPOSE.  See the GNU Lesser General Public License for more ////
//// details.                                                     ////
////                                                              ////
//// You should have received a copy of the GNU Lesser General    ////
//// Public License along with this source; if not download it   ////
//// from http://www.opencores.org/lgpl.shtml                     ////
////                                                              ////
//////////////////////////////////////////////////////////////////////
/*-----------------------------------------------------------*/
//  command table
/*-----------------------------------------------------------*/
/* put in alphabetical order by command name */
//   12345678901234567890
extern struct cli_cmd_tab_t cli_commands[] =
{ { "#"                   , func_comment , " #        comment is ingored\r"                          }
, { "help"                , func_help    , " help     ~ print help message\r"                        }
, { "md"                  , func_md      , " md       address [# of objects] ~ memory display\r"     }
, { "md.b"                , func_md      , " md.b     address [# of objects] ~ memory display\r"     }
, { "md.w"                , func_md      , " md.w     address [# of objects] ~ memory display\r"     }
, { "memtest"             , func_memtest , " memtest  base_address size\r"                           }
, { "mw"                  , func_mw      , " mw       address value [count] ~ memory write (fill)\r" }
, { "mw.b"                , func_mw      , " mw.b     address value [count] ~ memory write (fill)\r" }
, { "mw.w"                , func_mw      , " mw.w     address value [count] ~ memory write (fill)\r" }
, { "peek"                , func_peek    , " peek     address\r"                                     }
, { "poke"                , func_poke    , " poke     address value\r"                               }
, { "~"                   , NULL         , NULL                                                      }
};
