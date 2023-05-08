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

#include "solve.h"
#include "data.h"
#include "setup.h"

//-----------------------------------------------------
bool solve( sData* data ) {
   std::cout << "\nSolve:\n-------\n";

   if( !gaussseidel( data,data->s1 ) )	{
      return false;
   }
   return true;
}

//--- Gauss-Seidel solver -----------------------------
bool gaussseidel( sData* data, double** s ) {
   int curIter = 0;
   double curResidual    = MAXDOUBLE;
   double curMaxResidual = MAXDOUBLE;
   
   std::cout << "\r\tRunning Gauss-Seidel solver... ";
   while( curIter<data->maxIter && ABS( curMaxResidual ) > data->maxResidual ) {
      curIter++;
      
      curMaxResidual = 0;
      for( int i=1; i<data->nX-1; i++ ) {
         for( int j=1; j<data->nY-1; j++ ) {
            
            curResidual = 42; // FIXME

            s[i][j] += curResidual;

            if( ABS( curResidual ) > ABS( curMaxResidual ) ) curMaxResidual=ABS( curResidual );
         }
      }

   }
   std::cout << "done." << std::endl;
   std::cout << "\n\tGauss-Seidel iterations: " << curIter << std::endl;
   std::cout << "\n\tMaximum residuum       : " << curMaxResidual << std::endl;

   return true;
}

//--- Jacobi solver -----------------------------------
bool jacobi( sData* data, double** s ) {
   //FIXME
   return true;
}

//--- Thomas algorithm --------------------------------
bool thomas( sData* data, double** s ) {
   // optional
   return true;
}
