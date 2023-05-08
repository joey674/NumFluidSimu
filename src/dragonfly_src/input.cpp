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
#include <fstream>

#include <string.h>
#include <stdio.h>
#include <math.h>

#include "input.h"
#include "data.h"

//------------------------------------------------------
bool input( const char* cfgFilePath, const char* meshFilePath, sData* data ) {

   int section, lineNo;
   sCell*  curCell=0;
   sFace*  curFace=0;
   sPoint* curPoint=0;
   char    line[256]=" ";
   char    token[32]=" ";
   int     pointId;
   double  x;
   double  y;
   int     cellId;
   int 	   fId;
   int     bType_sc;
   int     bType_p;
   int     bType_u;
   double  value_sc;
   double  value_p;
   double  value_u;
   double  value_v;
   

   //////////////////////
   // READ JOB FILE  //
   //////////////////////

   // open input file
   std::ifstream cfgFile( cfgFilePath );
   if( !cfgFile ) {
      return false;
   }
   // read input file line by line
   lineNo=0;
   while( !cfgFile.eof() ) {
      lineNo++;
      cfgFile.getline( line,255 );
      if( sscanf( line,"%15s",token )<1 ) {
         continue;
      };

      if( !strcmp( token,"#" ) ) {
         // skip comment lines
         // numerical settings
      }
      else if( !strcmp( token,"maxTime" ) ) {
         if( sscanf( line,"%15s %lf",token,&data->maxTime )		!= 2 ) {
            return error( cfgFilePath,lineNo,line );
         };
      }
      else if( !strcmp( token,"dt" ) ) {
         if( sscanf( line,"%15s %lf",token,&data->dt )		!= 2 ) {
            return error( cfgFilePath,lineNo,line );
         };
	  }
      else if( !strcmp( token,"maxIter" ) ) {
         if( sscanf( line,"%15s %d",token,&data->maxIter )		!= 2 ) {
            return error( cfgFilePath,lineNo,line );
         };
      }
      else if( !strcmp( token,"residual" ) ) {
         if( sscanf( line,"%15s %lf",token,&data->residual)	!= 2 ) {
            return error( cfgFilePath,lineNo,line );
         };
	  }
	  else if( !strcmp( token,"relax_p" ) ) {
         if( sscanf( line,"%15s %lf",token,&data->relax_p)	!= 2 ) {
            return error( cfgFilePath,lineNo,line );
         };
	  }
         // physical settings
      else if( !strcmp( token,"alpha" ) ) {
         if( sscanf( line,"%15s %lf",token,&data->alpha )		!= 2 ) {
            return error( cfgFilePath,lineNo,line );
         };
      }
      else if( !strcmp( token,"eta" ) ) {
         if( sscanf( line,"%15s %lf",token,&data->eta )			!= 2 ) {
            return error( cfgFilePath,lineNo,line );
         };
      }
      else if( !strcmp( token,"rho" ) ) {
         if( sscanf( line,"%15s %lf",token,&data->rho )			!= 2 ) {
            return error( cfgFilePath,lineNo,line );
         };
      }
      else {
         std::cout << "unknown token: " << token << std::endl;
         return error( cfgFilePath,lineNo,line );
      }
   }
   cfgFile.close();

   /////////////////////
   // READ FACE FILE  //
   /////////////////////

   // open face file
   std::ifstream meshFile( meshFilePath );
   if( !meshFile ) {
      return false;
   }

   // read face data
   section=0;
   lineNo=0;
   int nX, nY;
   while( !meshFile.eof() ) {
      lineNo++;
      meshFile.getline( line,255 );
      if( sscanf( line,"%31s",token )<1 ) {
         continue;
      };

      if( !strcmp( token,"#" ) ) {
         // skip comment lines
      }
      else if( !strcmp( token,"pointDimensions" ) ) {
         if( sscanf( line,"%31s",token )	!= 1 ) {
            return error( meshFilePath,lineNo,line );
         };
         section=1;
      }
      else if( !strcmp( token,"points" ) ) {
         if( sscanf( line,"%31s",token )					!= 1 ) {
            return error( meshFilePath,lineNo,line );
         };
         section=2;
      }
      else if( !strcmp( token,"cellConditions" ) ) {
         if( sscanf( line,"%31s",token )					!= 1 ) {
            return error( meshFilePath,lineNo,line );
         };
         section=3;
      }
      else if( !strcmp( token,"faceConditions" ) ) {
         if( sscanf( line,"%31s",token )					!= 1 ) {
            return error( meshFilePath,lineNo,line );
         };
         section=4;
      }     
      else if( section==1 ) {	// reading dimensions
         if( sscanf( line,"%d %d",&nX,&nY )	!= 2 ) {
            return error( meshFilePath,lineNo,line );
         };
         data->nPointsX = nX;
         data->nPointsY = nY;
         data->nPoints  = nX*nY;
         data->nCells   = ( nX-1 )*( nY-1 );
         data->nFaces   = 2*nX*nY - nX - nY;
         data->points   = new sPoint[data->nPoints];
         data->cells    = new sCell[data->nCells];
         data->faces    = new sFace[data->nFaces];
      }
      else if( section==2 ) {	// reading point data section
         if( sscanf( line,"%d %lf %lf",&pointId,&x,&y )	!= 3 ) {
            return error( meshFilePath,lineNo,line );
         }
         curPoint     = &data->points[pointId];
         curPoint->id = pointId;
         curPoint->x  = x;
         curPoint->y  = y;
      }
      else if( section==3 ) {	// reading cell boundary condition and init section
         if( sscanf( line,"%d %d %d %lf %lf",&cellId,&bType_sc,&bType_p,&value_sc,&value_p)	!= 5 ) {
            return error( meshFilePath,lineNo,line );
         }
         curCell         		= &data->cells[cellId];
         curCell->id     		= cellId;
         curCell->bType_sc  	= bType_sc;
         curCell->bType_p  	= bType_p;
         curCell->sc     		= value_sc;
         curCell->p      		= value_p;
      }
      else if( section==4 ) {	// reading face boundary condition and init section
         if( sscanf( line,"%d %d %lf %lf",&fId,&bType_u,&value_u,&value_v)	!= 4 ) {
            return error( meshFilePath,lineNo,line );
         }
         curFace         	= &data->faces[fId];
         curFace->id     	= fId;
         curFace->bType_u 	= bType_u;
         curFace->u 	  	= value_u;
         curFace->v 	  	= value_v;
      }
   }
   meshFile.close();
   return true;
}

//------------------------------------------------------
bool error( const char* filePath, int lineNo, const char* line ) {
   std::cout << "ERROR reading " << filePath << ", line " << lineNo << ":" << std::endl;
   std::cout << "\t" << line << std::endl << std::endl;
   return false;
}
