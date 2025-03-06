/*
**	Command & Conquer Red Alert(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* $Header: /CounterStrike/MPU.H 1     3/03/97 10:25a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : MPU.H                                                        *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 07/15/96                                                     *
 *                                                                                             *
 *                  Last Update : July 17, 1996 [JLB]                                          *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   Get_CPU_Clock -- Fetches the current CPU clock time.                                      *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef MPU_H
#define MPU_H


/***********************************************************************************************
 * Get_CPU_Clock -- Fetches the current CPU clock time.                                        *
 *                                                                                             *
 *    This routine will return the internal Pentium clock accumulator. This accumulator is     *
 *    incremented every clock tick. Since this clock value can get very very large, the value  *
 *    returned is in 64 bits. The low half is returned directly, the high half is stored in    *
 *    location specified.                                                                      *
 *                                                                                             *
 * INPUT:   high  -- Reference to the high value of the 64 bit clock number.                   *
 *                                                                                             *
 * OUTPUT:  Returns with the low half of the CPU clock value.                                  *
 *                                                                                             *
 * WARNINGS:   This instruction is only available on Pentium or later processors.              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/17/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
unsigned long Get_CPU_Clock(unsigned long & high);
#ifndef __BORLANDC__
#pragma aux Get_CPU_Clock parm [esi] \
	modify [edx] \
	value [eax] = \
	"db 0fh,031h" \
	"mov [esi],edx"
#endif

#endif
