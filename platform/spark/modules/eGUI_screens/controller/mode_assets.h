/**
 ******************************************************************************
  Copyright (c) 2015 Brewpi/Matthew McGowan/Elco Jacobs.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************
 */


#ifndef MODE_ASSETS_H
#define	MODE_ASSETS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "d4d.h"    
   
#define CONTROLLER_MODE_COUNT (5)
// maximum mode text including 
#define CONTROLLER_MODE_TEXT_LENGTH (8)

extern const char mode_ids[CONTROLLER_MODE_COUNT];


extern const char* mode_names[CONTROLLER_MODE_COUNT];
extern const D4D_COLOR mode_colors[CONTROLLER_MODE_COUNT];


#ifdef	__cplusplus
}
#endif

#endif	/* MODE_ASSETS_H */

