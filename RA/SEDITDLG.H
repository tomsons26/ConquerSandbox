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

#ifdef WOLAPI_INTEGRATION

//	SEditDlg.h - "SimpleEditDlgClass": An ok/cancel type dialog with a single edit box.
//	ajw 07/21/98

#include "function.h"

class SimpleEditDlgClass
{
public:
	SimpleEditDlgClass( int iDialogWidth, const char* szTitle, const char* szPrompt, int iEditCharsAccept,
							const char* szPrompt2 = NULL, int iEditCharsAccept2 = 0 );
	virtual ~SimpleEditDlgClass();

	const char* Show();					//	Shows dialog, returns text of button pressed.
										//	Unless SetButtons() is used, value will be TXT_OK or TXT_CANCEL string values.

	void		SetButtons( const char* szOk, const char* szCancel, const char* szMiddle = NULL );

	char		szEdit[ 300 ];			//	iEditCharsAccept upper limit.
	char		szEdit2[ 300 ];

protected:
	int			iDialogWidth;			//	X pixels width of entire dialog.
	char*		szTitle;				//	Title of dialog, or NULL for no title.

	char*		szPrompt;				//	Text appearing to the left of edit box.
	int			iEditCharsAccept;		//	Max length of string allowed in edit, includes null-terminator.

	char*		szPrompt2;
	int			iEditCharsAccept2;

	const char*	szOkButton;				//	Text of button that acts like an Ok button. Appears on left.
	const char*	szCancelButton;			//	Text of button that acts like an Cancel button. Appears on right.
	const char* szMiddleButton;			//	Optional middle button text. Null = no middle button.
};

#endif
