/***************************************************************************
 *   Copyright (C) 2006-2014 by  Institute of Combustion Technology        *
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
#include <stdio.h>
#include <iostream>
#include <math.h>

#include "setup.h"
#include "data.h"
#include "output.h"

//------------------------------------------------------
bool setup(sData* data)
{
  std::cout << "\nSetup:\n-------\n";
  
  data->nPointsX = data->nCellsX+1;
  data->nPointsY = data->nCellsY+1;
  
  // allocate memory
  data->pointsX = new double*[data->nPointsX];
  data->pointsY = new double*[data->nPointsX];
  for(int i=0; i < data->nPointsX; i++) {
    data->pointsX[i] = new double[data->nPointsY];
    data->pointsY[i] = new double[data->nPointsY];
  }
  
  // calculate point coordinates
  double deltaX = (data->xMax - data->xMin) / data->nCellsX;
  double deltaY = (data->yMax - data->yMin) / data->nCellsY; 
  for(int i=0; i < data->nPointsX; i++) {
    for(int j=0; j < data->nPointsY; j++) {
      data->pointsX[i][j] = data->xMin + deltaX*i;
      data->pointsY[i][j] = data->yMin + deltaY*j;
    }
  }
  
   data->cells    = new sCell[(data->nPointsX-1) * (data->nPointsY-1)];
   data->faces    = new sFace[2*data->nPointsX*data->nPointsY - data->nPointsX - data->nPointsY];
   
   sCell* curCell=NULL;
   sFace* curFace=NULL;
   int i,j;

   /////////////////////////////////
   // construct mesh connectivity //
   /////////////////////////////////
   
   for( int cellId=0; cellId < ((data->nPointsX-1) * (data->nPointsY-1)); cellId++ ) {
      // assign points to cells
      i = cellId%( data->nPointsX-1 );
      j = cellId/( data->nPointsX-1 );
      curCell = &data->cells[cellId];

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
  
   for( int cellId=0; cellId < (data->nPointsX-1) * (data->nPointsY-1); cellId++ ) {

	  int i = cellId%( data->nPointsX-1 );
	  int j = cellId/( data->nPointsX-1 );
	  curCell = &data->cells[cellId];

	  // set up boundary and initial conditions for cells
	  // FIXME

  }
  
  for(int fId=0; fId<(2*data->nPointsX*data->nPointsY - data->nPointsX - data->nPointsY); fId++) {
	  curFace = &data->faces[fId];

	  // set up boundary and initial conditions for faces
	  // FIXME
  
  }
  
  return true;
}
