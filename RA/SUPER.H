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

/* $Header: /CounterStrike/SUPER.H 1     3/03/97 10:25a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : SUPER.H                                                      *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 07/28/95                                                     *
 *                                                                                             *
 *                  Last Update : July 28, 1995 [JLB]                                          *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef SUPER_H
#define SUPER_H

#include	"ftimer.h"

class SuperClass {
	public:
		SuperClass(NoInitClass const & x) : Control(x) {};
		SuperClass(void) : Control(NoInitClass()) {};
		SuperClass(int recharge, bool powered, VoxType charging=VOX_NONE, VoxType ready=VOX_NONE, VoxType impatient=VOX_NONE, VoxType suspend=VOX_NONE);

		bool Suspend(bool on);
		bool Enable(bool onetime = false, bool player=false, bool quiet=false);
		void Forced_Charge(bool player=false);
		bool AI(bool player=false);
		bool Remove(void);
		void Impatient_Click(void) const;
		int Anim_Stage(void) const;
		bool Discharged(bool player);
		bool Is_Ready(void) const {return(IsReady);}
		bool Is_Present(void) const {return(IsPresent);}
		bool Is_One_Time(void) const {return(IsOneTime && IsPresent);}
		bool Is_Powered(void) const {return(IsPowered);}

	private:
		bool Recharge(bool player=false);

		unsigned IsPowered:1;
		unsigned IsPresent:1;
		unsigned IsOneTime:1;
		unsigned IsReady:1;

		CDTimerClass<FrameTimerClass> Control;
		int OldStage;

		VoxType VoxRecharge;
		VoxType VoxCharging;
		VoxType VoxImpatient;
		VoxType VoxSuspend;
		int RechargeTime;

		enum {
			ANIMATION_STAGES=54
		};
};



#endif
