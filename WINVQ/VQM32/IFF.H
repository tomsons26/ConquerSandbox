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

#ifndef VQMIFF_H
#define VQMIFF_H
/****************************************************************************
*
*         C O N F I D E N T I A L --- W E S T W O O D   S T U D I O S
*
*----------------------------------------------------------------------------
*
* FILE
*     iff.h
* 
* DESCRIPTION
*     IFF (Interchange File Format) manager definitions.
*     (32-Bit protected mode)
*
* PROGRAMMER
*     Denzil E. Long, Jr.
*
* DATE
*     January 26, 1995
*
****************************************************************************/

/* FormHeader - Structure associated with IFF forms.
 *
 * id   - IFF form id (IE: "FORM")
 * size - Length of IFF in bytes
 * type - Form type (IE: "ILBM")
 */
typedef struct _FormHeader {
	long id;
	long size;
	long type;
} FormHeader;

/* Context - Structure associated with chunks.
 *
 * id   - Chunk identifier.
 * size - Size of chunk in bytes.
 * scan - Bytes read/written.
 */
typedef struct _Context {
	long id;
	long size;
	long scan;
} Context;

/* IFFHandle - Structure associated with an active IFF read\write session.
 *
 * fh    - DOS filehandle
 * flags - Internal flags used by IFF routines.
 * form  - IFF form information.
 * scan  - Bytes read/written
 * cn    - Context of current chunk.
 */
typedef struct _IFFHandle {
	long       fh;
	long       flags;
	FormHeader form;
	long       scan;
	Context    cn;
} IFFHandle;

/*	bit masks for "flags" field. */
#define IFFB_READ  0
#define IFFB_WRITE 1
#define IFFF_READ  (1<<IFFB_READ)
#define IFFF_WRITE (1<<IFFB_WRITE)

/* IFF return codes. Most functions return either zero for success or
 * one of these codes. The exceptions are the read/write functions which,
 * return positive values for number of bytes read or written, or a negative
 * error code.
 *
 * IFFERR_EOF   - End of file.
 * IFFERR_READ  - Read error.
 * IFFERR_WRITE - Write error.
 * IFFERR_NOMEM - Unable to allocate memory.
 */
#define IFFERR_EOF   -1
#define IFFERR_READ  -2
#define IFFERR_WRITE -3
#define IFFERR_NOMEM -4

/* Macros to make things easier. */
#define REVERSE_LONG(id) (unsigned long)((((unsigned long)(id)>>24) \
		&0x000000FFL)|(((unsigned long)(id)>>8) \
		&0x0000FF00L)|(((unsigned long)(id)<<8) \
		&0x00FF0000L)|(((unsigned long)(id)<<24)&0xFF000000L))

#define REVERSE_WORD(id) ((unsigned short)((((unsigned short)(id)<<8) \
		&0x00FF00)|(((unsigned short)(id)>>8)&0x0FF)))

#define PADSIZE(size) (((size)+1)&(~1))

#ifndef MAKE_ID
#define MAKE_ID(a,b,c,d) ((long)((long)(d)<<24)|((long)(c)<<16)| \
		((long)(b)<<8)|(long)(a))
#endif

/* Universal IFF identifiers */
#define ID_FORM MAKE_ID('F','O','R','M')
#define ID_LIST MAKE_ID('L','I','S','T')
#define ID_PROP MAKE_ID('P','R','O','P')
#define ID_NULL MAKE_ID(' ',' ',' ',' ')

/* Prototypes */
IFFHandle *OpenIFF(char *, long);
void CloseIFF(IFFHandle *);
long ReadForm(IFFHandle *, FormHeader *);
long WriteForm(IFFHandle *, FormHeader *);
long ReadChunkHeader(IFFHandle *);
long WriteChunkHeader(IFFHandle *, long, long);
long WriteChunk(IFFHandle *, long, char *, long);
long WriteChunkBytes(IFFHandle *, char *, long);
long ReadChunkBytes(IFFHandle *, char *, long);
long SkipChunkBytes(IFFHandle *, long);
long FindChunk(IFFHandle *, long);
char *IDtoStr(long, char *);
long CurrentFilePos(IFFHandle *);

#endif /* VQMIFF_H */

