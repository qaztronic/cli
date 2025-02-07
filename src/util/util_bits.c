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

#include "util_bits.h"


/*-----------------------------------------------------------*/
void inline 
  util_set_bits
  (
    unsigned int address, 
    unsigned int bit_offset, 
    unsigned int bit_mask, 
    unsigned int data
  )
{
  volatile unsigned int *word_pointer = (volatile unsigned int *)(address);
  unsigned int buffer;
  
  data <<= bit_offset;
  data &= bit_mask;

  buffer = *word_pointer;
  buffer &= ~bit_mask;
  buffer |= data;

  *word_pointer = buffer;
}


/*-----------------------------------------------------------*/
unsigned int inline 
  util_get_bits
  (
    unsigned int address, 
    unsigned int bit_offset, 
    unsigned int bit_mask
  )
{
  volatile unsigned int *word_pointer = (volatile unsigned int *)(address);
  unsigned int buffer;

  buffer = *word_pointer;
  buffer &= bit_mask;
  buffer >>= bit_offset;
  
  return(buffer);
}


/*-----------------------------------------------------------*/
unsigned char ReverseBits7ops32bit(unsigned char v)
{
    return ((v * 0x0802LU & 0x22110LU) |
            (v * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
}



