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

/* $Header: /CounterStrike/MIXFILE.H 1     3/03/97 10:25a Joe_bostic $ */

#ifndef MIXFILE_H
#define MIXFILE_H


/*
**	The "bool" integral type was defined by the C++ committee in
**	November of '94. Until the compiler supports this, use the following
**	definition.
*/
#ifndef __BORLANDC__
#ifndef TRUE_FALSE_DEFINED
#define TRUE_FALSE_DEFINED
enum {false=0,true=1};
typedef int bool;
#endif
#endif

#include	<stdlib.h>
#include	"listnode.h"
#include	"pk.h"
#include "buff.h"

template<class T>
class MixFileClass : public Node<MixFileClass>
{
	public:
		char const * Filename;			// Filename of mixfile.


		MixFileClass(char const *filename, PKey const * key);
		~MixFileClass(void);

		static bool Free(char const *filename);
		void Free(void);
		bool Cache(Buffer const * buffer = NULL);
		static bool Cache(char const *filename, Buffer const * buffer=NULL);
		static bool Offset(char const *filename, void ** realptr = 0, MixFileClass ** mixfile = 0, long * offset = 0, long * size = 0);
		static void const * Retrieve(char const *filename);

		struct SubBlock {
			long CRC;				// CRC code for embedded file.
			long Offset;			// Offset from start of data section.
			long Size;				// Size of data subfile.

			int operator < (SubBlock & two) const {return (CRC < two.CRC);};
			int operator > (SubBlock & two) const {return (CRC > two.CRC);};
			int operator == (SubBlock & two) const {return (CRC == two.CRC);};
		};

	private:
		static MixFileClass * Finder(char const * filename);
		long Offset(long crc, long * size = 0) const;

		/*
		**	If this mixfile has an attached message digest, then this flag
		**	will be true. The digest is checked only when the mixfile is
		**	cached.
		*/
		unsigned IsDigest:1;

		/*
		**	If the header to this mixfile has been encrypted, then this flag
		**	will be true. Although the header of the mixfile may be encrypted,
		**	the attached data files are not.
		*/
		unsigned IsEncrypted:1;

		/*
		**	If the cached memory block was allocated by this routine, then this
		**	flag will be true.
		*/
		unsigned IsAllocated:1;

		/*
		**	This is the initial file header. It tells how many files are embedded
		**	within this mixfile and the total size of all embedded files.
		*/
		typedef struct {
			short	count;
			long	size;
		} FileHeader;

		/*
		**	The number of files within the mixfile.
		*/
		int Count;

		/*
		**	This is the total size of all the data file embedded within the mixfile.
		**	It does not include the header or digest bytes.
		*/
		long DataSize;

		/*
		**	Start of raw data in within the mixfile.
		*/
		long DataStart;

		/*
		**	Points to the file header control block array. Each file in the mixfile will
		**	have an entry in this table. The entries are sorted by their (signed) CRC value.
		*/
		SubBlock * HeaderBuffer;

		/*
		**	If the mixfile has been cached, then this points to the cached data.
		*/
		void * Data;						// Pointer to raw data.

		static List<MixFileClass> List;
};

#endif
