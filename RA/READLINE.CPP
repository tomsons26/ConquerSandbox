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


#include	<ctype.h>
#include	<string.h>
#include	"wwfile.h"
#include	"xstraw.h"
#include	"readline.h"


// Disable the "temporary object used to initialize a non-constant reference" warning.
#pragma warning 665 9


void strtrim(char * buffer)
{
	if (buffer) {

		/*
		**	Strip leading white space from the string.
		*/
		char * source = buffer;
		while (isspace(*source)) {
			source++;
		}
		if (source != buffer) {
			strcpy(buffer, source);
		}

		/*
		**	Clip trailing white space from the string.
		*/
		for (int index = strlen(buffer)-1; index >= 0; index--) {
			if (isspace(buffer[index])) {
				buffer[index] = '\0';
			} else {
				break;
			}
		}
	}
}



int Read_Line(FileClass & file, char * buffer, int len, bool & eof)
{
	return(Read_Line(FileStraw(file), buffer, len, eof));
}


int Read_Line(Straw & file, char * buffer, int len, bool & eof)
{
	if (len == 0 || buffer == NULL) return(0);

	int count = 0;
	for (;;) {
		char c;
		if (file.Get(&c, sizeof(c)) != sizeof(c)) {
			eof = true;
			buffer[0] = '\0';
			break;
		}

		if (c == '\x0A') break;
		if (c != '\x0D' && count+1 < len) {
			buffer[count++] = c;
		}
	}
	buffer[count] = '\0';

	strtrim(buffer);
	return(strlen(buffer));
}
