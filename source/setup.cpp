/***************************************************************************
 *   Copyright (C) 2006-2011 by  Institute of Combustion Technology        *
 *   jens.henrik.goebbert@itv.rwth-aachen.de                               *
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
#include <math.h>
#include <iostream>

#include "setup.h"
#include "data.h"
#include "metrics.h"

//-----------------------------------------------------
bool setup( sData* data ) {
   std::cout << "\nSetup:\n-------\n";

   // setup x/y grid  **x,**y：输入标号获得真实坐标
   for( int i=0; i<data->nX; i++ ) {
      for( int j=0; j<data->nY; j++ ) {
         //FIXME 
         double delta_x = (data->xMax - data->xMin) / data->nX; 
         double delta_y = (data->yMax - data->yMin) / data->nY;
         data->x[i][j] = i * delta_x + data->xMin; 
         data->y[i][j] = j * delta_y + data->yMin;
      }
   }

   // set inital values of scalar s1 存放速度
   for( int i=0; i<data->nX; i++ ) {
      for( int j=0; j<data->nY; j++ ) {
         //FIXME
         data->s1[i][j] = 42;
      }
   }

   // set boundary conditions for scalar s1
   if( data->potentialFunc == PARALLELFLOW ) {
      //FIXME

   }
   
//--- sub task 2 ---------------------------------------
   // precompute derivatives for coordinate transformation
   for( int i=0; i<data->nX; i++ ) {
      for( int j=0; j<data->nY; j++ ) {
         //FIXME (subtask 2)
      }
   }

   // setup xi/eta grid
   for( int i=0; i<data->nX; i++ ) {
      for( int j=0; j<data->nY; j++ ) {
         //FIXME (Subtask 2)
      }
   }

   return true;
}
