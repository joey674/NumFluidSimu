/***************************************************************************
 *   Copyright (C) 2006-2011 by  Institute of Combustion Technology        *
 *   d.mayer@itv.rwth-aachen.de                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <iostream>

#include <stdio.h>
#include <math.h>

#include "setup.h"
#include "data.h"
#include "output.h"

//------------------------------------------------------
bool setup( sData* data )
{

   sCell* curCell=NULL;
   sFace* curFace=NULL;
   int i,j;

   /////////////////////////////////
   // construct mesh connectivity //
   /////////////////////////////////
   for( int cellId=0; cellId < data->nCells; cellId++ ) {
      // assign points to cells
      i = cellId%( data->nPointsX-1 );
      j = cellId/( data->nPointsX-1 );
      curCell = &data->cells[cellId];
      curCell->points[XMYM] = &data->points[j*data->nPointsX + i];
      curCell->points[XPYM] = &data->points[j*data->nPointsX + i + 1];
      curCell->points[XMYP] = &data->points[( j+1 )*data->nPointsX + i];
      curCell->points[XPYP] = &data->points[( j+1 )*data->nPointsX + i + 1];

      // assign faces to cells
      curCell->faces[YM] = &data->faces[cellId];
      curCell->faces[YP] = &data->faces[cellId + data->nPointsX - 1];
      curCell->faces[XM] = &data->faces[( data->nPointsX-1 ) * data->nPointsY + cellId + j];
      curCell->faces[XP] = &data->faces[( data->nPointsX-1 ) * data->nPointsY + cellId + j + 1];

      // assign cells to faces
      curCell->faces[YM]->neighCells[P] = curCell;
      curCell->faces[YP]->neighCells[M] = curCell;
      curCell->faces[XM]->neighCells[P] = curCell;
      curCell->faces[XP]->neighCells[M] = curCell;

      // assign points to faces
      curCell->faces[YM]->points[M] = curCell->points[XMYM];
      curCell->faces[YM]->points[P] = curCell->points[XPYM];
      curCell->faces[YP]->points[M] = curCell->points[XMYP];
      curCell->faces[YP]->points[P] = curCell->points[XPYP];
      curCell->faces[XM]->points[M] = curCell->points[XMYM];
      curCell->faces[XM]->points[P] = curCell->points[XMYP];
      curCell->faces[XP]->points[M] = curCell->points[XPYM];
      curCell->faces[XP]->points[P] = curCell->points[XPYP];

      //assign neighboring cells to cells
      if( i != 0 ) {
         curCell->neighCells[XM] = &data->cells[cellId - 1];
      }
      if( i != data->nPointsX - 2 ) {
         curCell->neighCells[XP] = &data->cells[cellId + 1];
      }
      if( j != 0 ) {
         curCell->neighCells[YM] = &data->cells[cellId - ( data->nPointsX-1 )];
      }
      if( j != data->nPointsY - 2 ) {
         curCell->neighCells[YP] = &data->cells[cellId + ( data->nPointsX-1 )];
      }
   }

   /////////////////////////////////////
   // compute face centers and deltas //
   /////////////////////////////////////
   for( int fId=0; fId < data->nFaces; fId++ ) {
      curFace=&data->faces[fId];
	  // FIXME
      // hint: use face points
   }

   //////////////////////////////////////
   // compute cell centers and volumes //
   //////////////////////////////////////
   for( int cellId=0; cellId < data->nCells; cellId++ ) {
      // FIXME
      // hint 1: assume cartesian mesh (for now)
      // hint 2: use cell points & neighboring face deltas
   }

   return true;
}
