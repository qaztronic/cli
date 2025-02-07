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

#ifndef _UTIL_BITS_H_
#define _UTIL_BITS_H_



/*-----------------------------------------------------------*/
extern void inline 
  util_set_bits
  (
    unsigned int address, 
    unsigned int bit_offset, 
    unsigned int bit_mask, 
    unsigned int data
  );
  

/*-----------------------------------------------------------*/
extern unsigned int inline 
  util_get_bits
  (
    unsigned int address, 
    unsigned int bit_offset, 
    unsigned int bit_mask
  );
  
  
/*-----------------------------------------------------------*/
extern unsigned char ReverseBits7ops32bit(unsigned char v);




#endif  //  _UTIL_BITS_H_




