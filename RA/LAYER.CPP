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

/* $Header: /CounterStrike/LAYER.CPP 1     3/03/97 10:25a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : LAYER.CPP                                                    *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : May 31, 1994                                                 *
 *                                                                                             *
 *                  Last Update : March 10, 1995 [JLB]                                         *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   LayerClass::Sort -- Perform an incremental sort pass on the layer's objects.              *
 *   LayerClass::Sorted_Add -- Adds object in sorted order to layer.                           *
 *   LayerClass::Submit -- Adds an object to a layer list.                                     *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include	"function.h"
#include	"layer.h"


/***********************************************************************************************
 * LayerClass::Submit -- Adds an object to a layer list.                                       *
 *                                                                                             *
 *    This routine is used to add an object to the layer list. If the list is full, then the   *
 *    object is not added.                                                                     *
 *                                                                                             *
 * INPUT:   object   -- Pointer to the object to add.                                          *
 *                                                                                             *
 * OUTPUT:  bool; Was the object added successfully?                                           *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/31/1994 JLB : Created.                                                                 *
 *   05/31/1994 JLB : Allows sorted insert.                                                    *
 *   01/02/1995 JLB : Fixed to work with EMSListOf template.                                   *
 *=============================================================================================*/
bool LayerClass::Submit(ObjectClass const * object, bool sort)
{
	/*
	**	Add the object to the layer. Either at the end (if "sort" is false) or at the
	**	appropriately sorted position.
	*/
	if (sort) {
		return(Sorted_Add(object));
	}
	return(Add((ObjectClass *)object));
}


/***********************************************************************************************
 * LayerClass::Sort -- Handles sorting the objects in the layer.                               *
 *                                                                                             *
 *    This routine is used if the layer objects must be sorted and sorting is to occur now.    *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   Don't call this routine too often since it does take a bit of time to           *
 *             execute. It is a single pass binary sort and thus isn't horribly slow,          *
 *             but it does take some time.                                                     *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   10/17/1994 JLB : Created.                                                                 *
 *   03/10/1995 JLB : Uses comparison operator.                                                *
 *=============================================================================================*/
void LayerClass::Sort(void)
{
	for (int index = 0; index < Count()-1; index++) {
		if (*(*this)[index+1] < *(*this)[index]) {
			ObjectClass * temp;

			temp = (*this)[index+1];
			(*this)[index+1] = (*this)[index];
			(*this)[index] = temp;
		}
	}
}


/***********************************************************************************************
 * DynamicVectorClass<T>::Sorted_Add -- Adds object in sorted order to vector.                 *
 *                                                                                             *
 *    Use this routine to add an object to the vector but it will be inserted in sorted        *
 *    order. This depends on the ">" operator being defined for the vector object.             *
 *                                                                                             *
 * INPUT:   object   -- Reference to the object that will be added to the vector.              *
 *                                                                                             *
 * OUTPUT:  bool; Was the object added to the vector successfully?                             *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   03/10/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
int LayerClass::Sorted_Add(ObjectClass const * const object)
{
	if (ActiveCount >= Length()) {
		if ((IsAllocated || !VectorMax) && GrowthStep > 0) {
			if (!Resize(Length() + GrowthStep)) {

				/*
				**	Failure to increase the size of the vector is an error condition.
				**	Return with the error flag.
				*/
				return(false);
			}
		} else {

			/*
			**	Increasing the size of this vector is not allowed! Bail this
			**	routine with the error code.
			*/
			return(false);
		}
	}

	/*
	**	There is room for the new object now. Add it to the right sorted position.
	*/
	for (int index = 0; index < ActiveCount; index++) {
		if ((*(*this)[index]) > (*object)) {
			break;
		}
	}

	/*
	**	Make room if the insertion spot is not at the end of the vector.
	*/
	for (int i = ActiveCount-1; i >= index; i--) {
		(*this)[i+1] = (*this)[i];
	}
	(*this)[index] = (ObjectClass *)object;
	ActiveCount++;
	return(true);
}


