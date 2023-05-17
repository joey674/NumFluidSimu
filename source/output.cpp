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


#ifdef WIN32
#define OS_SEP "\\"
#else
#define OS_SEP "/"
#endif


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>

#include "output.h"
#include "data.h"

//-----------------------------------------------------

bool output( sData* data ) {
   char savePath[80];

   std::cout << "\nOutput:\n-------\n";

   showScalar( data, "scalar 1", data->s1 );

   strcpy( savePath,"OutParaview" );
   strcat( savePath,OS_SEP );
   strcat( savePath,"hummingbird.vtk" );
   if( !saveVtk( data, savePath ,data->s1 ) )	{
      return false;
   }

   strcpy( savePath,"OutMatlab" );
   strcat( savePath,OS_SEP );
   strcat( savePath,"grid" );
   if( !saveMatlabGrid( data, savePath ) ) 				{
      return false;
   }

   strcpy( savePath,"OutMatlab" );
   strcat( savePath,OS_SEP );
   strcat( savePath,"scalar.dat" );
   if( !saveMatlabScalar( data, savePath,data->s1 ) )	{
      return false;
   }

   return true;
}

//--- shows the scalar on the console------------------
void showScalar( const sData* data, const char* scalarName, double** s ) {
   const int maxHoriz=5;
   const int maxVert =5;

   std::cout.precision( 1 );

   std::cout << "\nY\t------------------------- " << scalarName << " -------------------------\n"
             << "^\n"
             << "|\n";

   double iStep,jStep;
   if( data->nX<maxVert )  {
      iStep=1;
   }
   else {
      iStep=data->nX/ ( double ) maxVert;
   }
   if( data->nY<maxHoriz ) {
      jStep=1;
   }
   else {
      jStep=data->nY/ ( double ) maxHoriz;
   }

   double i,j=data->nY-1 + jStep;
   while( j>0 ) {
      j-=jStep;
      if( j<1 ) {
         j=0;
      }
      std::cout << std::fixed << ( int ) j << "\t";

      i=-iStep;
      while( i<data->nX-1 ) {
         i+=iStep;
         if( i>data->nX-2 ) {
            i=data->nX-1;
         }
         std::cout.setf( std::ios::showpos );
         std::cout << std::scientific << s[( int ) i][( int ) j] << "  ";
         std::cout.unsetf( std::ios::showpos );
      }
      std::cout << "\n|\n";
   }
   std::cout << " --\t";

   i=-iStep;
   while( i<data->nX-1 ) {
      i+=iStep;
      if( i>data->nX-2 ) {
         i=data->nX-1;
      }
      std::cout << "   -" << ( int ) i << "-    ";
   }
   std::cout << "->X\n\n";
}

//--- save the scalar on Matlab readable format -------
bool saveMatlabScalar( const sData* data, const char* scalarFilePath, double** s ) {
   std::ofstream scalarFile( scalarFilePath );
   if( !scalarFile ) {
      return false;
   }
   scalarFile.clear();
   for( int i=0; i<data->nX; i++ ) {
      for( int j=0; j<data->nY; j++ ) {
         scalarFile << " "<< s[i][j];
      }
      scalarFile << std::endl;
   }
   scalarFile.close();

   return true;
}

//--- saves the grid in Matlab readable format --------
bool saveMatlabGrid( const sData* data, const char* gridFilePath ) {
   char fileNameX[80];
   char fileNameY[80];

   sprintf( fileNameX,"%sX.dat",gridFilePath );
   sprintf( fileNameY,"%sY.dat",gridFilePath );
   std::ofstream meshXFile( fileNameX );
   std::ofstream meshYFile( fileNameY );
   if( !meshXFile ) {
      return false;
   }
   if( !meshYFile ) {
      return false;
   }
   meshXFile.clear();
   meshYFile.clear();
   for( int i=0; i<data->nX; i++ ) {
      for( int j=0; j<data->nY; j++ ) {
         meshXFile << data->x[i][j] << " ";
         meshYFile << data->y[i][j] << " ";
      }
      meshXFile << std::endl;
      meshYFile << std::endl;
   }
   meshXFile.close();
   meshYFile.close();

   return true;
}

//--- save grid and scalar in vtk format --------------
bool saveVtk( const sData* data, const char* vtkFilePath, double** s ) {

   // open file
   std::ofstream dataFile( vtkFilePath );
   if( !dataFile ) {
      return false;
   }
   dataFile.clear();

   // write header
   dataFile << "# vtk DataFile Version 2.0" << std::endl;
   dataFile << "Results formatted in VTK File Format" << std::endl;
   dataFile << "ASCII" << std::endl;
   dataFile << "DATASET STRUCTURED_GRID" << std::endl;
   dataFile << "DIMENSIONS " << data->nX << " " << data->nY << " 1" << std::endl;
   dataFile << "POINTS "<< data->nX*data->nY << " float" << std::endl;

   // write point coordinates
   for( int j=0 ; j<data->nY ; j++ ) {
      for( int i=0 ; i<data->nX ; i++ ) {
         dataFile<<data->x[i][j]<<" "<<data->y[i][j]<<" 0"<<std::endl;
      }
   }
   dataFile << std::endl;

   // write the scalar data to result file
   dataFile << "POINT_DATA "<<data->nX*data->nY<<std::endl;
   dataFile << "SCALARS scalar1 float" << std::endl;
   dataFile << "LOOKUP_TABLE default" << std::endl;
   for( int j=0 ; j<data->nY ; j++ ) {
      for( int i=0 ; i<data->nX ; i++ ) {
         dataFile << data->s1[i][j]<<std::endl;
      }
   }

   dataFile.close();

   return true;
}
