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
#ifndef DATA_H
#define DATA_H

#include <limits>

#define MIN(a,b) ( ((a)<(b)) ? (a):(b) )
#define MAX(a,b) ( ((a)>(b)) ? (a):(b) )
#define ABS(x)   ( ((x)> 0)  ? (x):-(x))

#define MAXDOUBLE   (std::numeric_limits<double>::max())
#define MINDOUBLE   (std::numeric_limits<double>::min())
#ifndef MAXFLOAT
#define MAXFLOAT    (std::numeric_limits<float>::max())
#endif 
#define MINFLOAT    (std::numeric_limits<float>::min())
#define MAXINT	    (std::numeric_limits<int>::max())
#define MININT	    (std::numeric_limits<int>::min())

#define PARALLELFLOW 0


struct sData {
   sData() {};

   // grid & geometry settings
   int nX;
   int nY;
   double xMin;
   double xMax;
   double yMin;
   double yMax;

   // potential flow settings
   int potentialFunc;
   double uInfty;
   double vInfty;

   // solver settings
   int    maxIter;
   double maxResidual;

   // fields
   double** x;
   double** y;
   double** s1;
   
};

double**  allocGrid1Mem( const sData* const data, const double preset );
void freeGrid1Mem( const sData* const data, double** mem );
double*** allocGridXMem( const sData* const data, const int vSize, const double preset );

#endif
