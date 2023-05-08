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

#include "solve.h"
#include "data.h"
#include "output.h"

//------------------------------------------------------
bool solve(sData* data)
{
   std::cout << "\nCalculation:\n------------\n";
   
   double curTime = 0;
   sCell* curCell=NULL;
   sFace* curFace=NULL;
   
   // dump inital fields
   if(!output(data,curTime)) {
	  std::cout << "ERROR while data output...exiting";
	  getchar();
	  return 1;
   }
   
   // Time Loop
   while(curTime<(data->maxTime - data->dt)){
	  
	  // advance time
	  curTime+=data->dt;
	  std::cout << "\r\t Solving ... current Time: " << curTime << " s         \n";
	  
	  // FIXME
	  // M2: solve scalar transport equation
	  
	  // FIXME
	  // M3: solve momentum equation for fixed pressure field
	  
	  // FIXME
	  // M4: SIMPLE solver loop to solve full incompressible NS-equations
	  
	  // dump fields after time step
	  if(!output(data,curTime)) {
		 std::cout << "ERROR while data output...exiting";
		 getchar();
		 return 1;
	  }
	  
   } // end Time loop

   std::cout << "\n";
   return true;
}

//------------------------------------------------------
void calcFlux(sData* data)
{
   static sFace* curFace=0;

   for(int fId=0; fId<data->nFaces; fId++) {
      curFace=&data->faces[fId];
	  
      // FIXME M2
	  // compute numerical flux over each face
	  
   }
}

void precomputeMomentumCoeffs(sData* data, double dt) 
{
   static sFace* curFace=0;

   for(int fId=0; fId<data->nFaces; fId++) {
	  curFace=&data->faces[fId]; 
	  
	  // FIXME M3
	  // precompute a_i for faces
	  
   }
}

void calcMomentum(sData* data, double dt)
{
   static sFace* curFace=0;
   double curMaxResidual=MAXDOUBLE;
   double curResidual=MAXDOUBLE;
   int curIter=0;
 
   //while(curIter<data->maxIter && ABS( curMaxResidual ) > data->residual ) {
   while(ABS( curMaxResidual ) > data->residual ) {
	  curIter++;
	  curMaxResidual = 0;

	  for(int fId=0; fId<data->nFaces; fId++) {
		 curFace=&data->faces[fId];
		 
		 // FIXME M3
		 // calculate face velocities from momentum equation
		 
		 if( ABS( curResidual ) > ABS( curMaxResidual ) ) curMaxResidual=ABS( curResidual );
	  }
   }
}

double calcPCorr(sData* data, double dt) 
{
   static sCell* curCell=0;
   double curMaxResidual=MAXDOUBLE;
   double curResidual=MAXDOUBLE;
   double curMassErr=0;
   int curIter=0;

   while(ABS( curMaxResidual ) > data->residual ) {

	  curIter++;
	  curMaxResidual = 0;

	  for( int cId=0; cId<data->nCells; cId++ ) {
		 curCell=&data->cells[cId];
		 
		 // FIXME M4
		 // calculate pressure correction 

		 if( ABS( curResidual ) > ABS( curMaxResidual ) ) curMaxResidual=ABS( curResidual );
	  }
   }
   return curMassErr;
}

