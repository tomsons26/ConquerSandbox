/*
**	Command & Conquer(tm)
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

/* $Header:   F:\projects\c&c\vcs\code\logic.cpv   2.17   16 Oct 1995 16:50:52   JOE_BOSTIC  $ */
/***********************************************************************************************
 ***             C O N F I D E N T I A L  ---  W E S T W O O D   S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : LOGIC.CPP                                                    *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : September 27, 1993                                           *
 *                                                                                             *
 *                  Last Update : December 23, 1994 [JLB]                                      *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   LogicClass::AI -- Handles AI logic processing for game objects.                           *
 *   LogicClass::Debug_Dump -- Displays logic class status to the mono screen.                 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include	"function.h"
#include	"logic.h"

static unsigned FramesPerSecond=0;

#ifdef CHEAT_KEYS

static unsigned TotalFrames;
static unsigned FPSDivider = 1;
static unsigned AverageFramesPerSecond;

/***********************************************************************************************
 * LogicClass::Debug_Dump -- Displays logic class status to the mono screen.                   *
 *                                                                                             *
 *    This is a debugging support routine. It displays the current state of the logic class    *
 *    to the monochrome monitor. It assumes that it is being called once per second.           *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   Call this routine only once per second.                                         *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/31/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
void LogicClass::Debug_Dump(MonoClass *mono) const
{
	#define RECORDCOUNT	40
	#define RECORDHEIGHT 21
	static struct {
		int Graphic;
	} _record[RECORDCOUNT];
	static int _framecounter = 0;

	TotalFrames+= FramesPerSecond;
	AverageFramesPerSecond = TotalFrames/FPSDivider++;

	mono->Set_Cursor(21, 9);
	mono->Print(
		"��������������������������������������������������������Ŀ\r"
		"�Units.....�   �Frame Rate:      Avg:      Frame:        �\r"
		"�Infantry..�   �����������������������������������������Ĵ\r"
		"�Aircraft..�   �                                         �\r"
		"�Buildings.�   �                                         �\r"
		"�Terrain...�   �                                         �\r"
		"�Bullets...�   �                                         �\r"
		"�Anims.....�   �                                         �\r"
		"�Teams.....�   �                                        Ĵ\r"
		"�Triggers..�   �                                         �\r"
		"�Factories.�   �                                         �\r"
		"�          �   �                                         �\r"
		"�          �   �                                         �\r"
		"����������������������������ĴSpare CPU Time��������������\r");

	_framecounter++;
	mono->Set_Cursor(70, 10);mono->Printf("%ld", Frame);
	if (ScenarioInit) {
		mono->Set_Cursor(21, 9);mono->Printf("%d", ScenarioInit);
	}

	mono->Set_Cursor(33, 10);mono->Printf("%3d", Units.Count());
	mono->Set_Cursor(33, 11);mono->Printf("%3d", Infantry.Count());
	mono->Set_Cursor(33, 12);mono->Printf("%3d", Aircraft.Count());
	mono->Set_Cursor(33, 13);mono->Printf("%3d", Buildings.Count());
	mono->Set_Cursor(33, 14);mono->Printf("%3d", Terrains.Count());
	mono->Set_Cursor(33, 15);mono->Printf("%3d", Bullets.Count());
	mono->Set_Cursor(33, 16);mono->Printf("%3d", Anims.Count());
	mono->Set_Cursor(33, 17);mono->Printf("%3d", Teams.Count());
	mono->Set_Cursor(33, 18);mono->Printf("%3d", Triggers.Count());
	mono->Set_Cursor(33, 19);mono->Printf("%3d", Factories.Count());

	mono->Set_Cursor(48, 10);mono->Printf("%d", FramesPerSecond);
	mono->Set_Cursor(58, 10);mono->Printf("%d", AverageFramesPerSecond);

	/*
	**	Advance to the next recorded performance record. If the record buffer
	**	is full then throw out the oldest record.
	*/
	memcpy(&_record[0], &_record[1], sizeof(_record[0])*(RECORDCOUNT-1));

	/*
	**	Fill in the data for the current frame's performance record.
	*/
	SpareTicks = MIN((long)SpareTicks, (long)TIMER_SECOND);
	_record[RECORDCOUNT-1].Graphic = Fixed_To_Cardinal(RECORDHEIGHT, Cardinal_To_Fixed(TIMER_SECOND, SpareTicks));

	/*
	**	Draw the bars across the performance record screen.
	*/
	for (int column = 0; column < RECORDCOUNT; column++) {
		for (int row = 1; row < RECORDHEIGHT; row += 2) {
			static char _barchar[4] = {' ', 220, 0, 219};
			char str[2];
			int index = 0;

			index |= (_record[column].Graphic >= row) ? 0x01 : 0x00;
			index |= (_record[column].Graphic >= row+1) ? 0x02: 0x00;

			str[1] = '\0';
			str[0] = _barchar[index];
			mono->Text_Print(str, 37+column, 21-(row/2));
		}
	}

	SpareTicks = 0;
	FramesPerSecond = 0;
}
#endif


/***********************************************************************************************
 * LogicClass::AI -- Handles AI logic processing for game objects.                             *
 *                                                                                             *
 *    This routine is used to perform the AI processing for all game objects. This includes    *
 *    all houses, factories, objects, and teams.                                               *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/29/1994 JLB : Created.                                                                 *
 *   12/17/1994 JLB : Must perform one complete pass rather than bailing early.                *
 *   12/23/1994 JLB : Esures that no object gets skipped if it was deleted.                    *
 *=============================================================================================*/
void LogicClass::AI(void)
{
	int index;

	FramesPerSecond++;

	/*
	**	Crate regeneration is handled here.
	*/
	if (GameToPlay != GAME_NORMAL && CrateMaker && CrateTimer.Expired()) {
		Map.Place_Random_Crate();
		CrateTimer = TICKS_PER_MINUTE * Random_Pick(7, 15);
	}

	/*
	**	Team AI is processed.
	*/
	for (index = 0; index < Teams.Count(); index++) {
		Teams.Ptr(index)->AI();
	}

//	Heap_Dump_Check( "After Team AI" );

	/*
	**	AI for all sentient objects is processed.
	*/
	for (index = 0; index < Count(); index++) {
		ObjectClass * obj = (*this)[index];

		obj->AI();

		/*
		**	If the object was destroyed in the process of performing its AI, then
		**	adjust the index so that no object gets skipped.
		*/
		if (obj != (*this)[index]) {
//		if (!obj->IsActive) {
			index--;
		}
	}

//	Heap_Dump_Check( "After Object AI" );

	/*
	**	A second pass through the sentient objects is required so that the appropriate scan
	**	bits will be set for the owner house.
	*/
	for (index = 0; index < Units.Count(); index++) {
		UnitClass const * unit = Units.Ptr(index);
		if (unit->IsLocked && (GameToPlay != GAME_NORMAL || !unit->House->IsHuman || unit->IsDiscoveredByPlayer)) {
			unit->House->NewUScan |= (1L << unit->Class->Type);
			if (!unit->IsInLimbo) unit->House->NewActiveUScan |= (1L << unit->Class->Type);
		}
	}
	for (index = 0; index < Infantry.Count(); index++) {
		InfantryClass const * infantry = Infantry.Ptr(index);
		if (infantry->IsLocked && (GameToPlay != GAME_NORMAL || !infantry->House->IsHuman || infantry->IsDiscoveredByPlayer)) {
			infantry->House->NewIScan |= (1L << infantry->Class->Type);
			if (!infantry->IsInLimbo) infantry->House->NewActiveIScan |= (1L << infantry->Class->Type);
		}
	}
	for (index = 0; index < Aircraft.Count(); index++) {
		AircraftClass const * aircraft = Aircraft.Ptr(index);
		if (aircraft->IsLocked && (GameToPlay != GAME_NORMAL || !aircraft->House->IsHuman || aircraft->IsDiscoveredByPlayer)) {
			aircraft->House->NewAScan |= (1L << aircraft->Class->Type);
			if (!aircraft->IsInLimbo) aircraft->House->NewActiveAScan |= (1L << aircraft->Class->Type);
		}
	}
	for (index = 0; index < Buildings.Count(); index++) {
		BuildingClass const * building = Buildings.Ptr(index);
		if (building->IsLocked && (GameToPlay != GAME_NORMAL || !building->House->IsHuman || building->IsDiscoveredByPlayer)) {
			building->House->NewBScan |= (1L << building->Class->Type);
			if (!building->IsInLimbo) building->House->NewActiveBScan |= (1L << building->Class->Type);
		}
	}

//	Heap_Dump_Check( "After Object AI 2" );

	/*
	**	Map related logic is performed.
	*/
	Map.Logic();

//	Heap_Dump_Check( "After Map.Logic" );

	/*
	**	Factory processing is performed.
	*/
	for (index = 0; index < Factories.Count(); index++) {
		Factories.Ptr(index)->AI();
	}

//	Heap_Dump_Check( "After Factory AI" );

	/*
	**	House processing is performed.
	*/
	for (HousesType house = HOUSE_FIRST; house < HOUSE_COUNT; house++) {
		HouseClass * hptr = HouseClass::As_Pointer(house);
		if (hptr && hptr->IsActive) {
			hptr->AI();
		}
	}

//	Heap_Dump_Check( "After House AI" );
}


