/**
 ******************************************************************************
 * @file    controller_screen_layout.c
 * @authors Matthew McGowan
 ******************************************************************************
  Copyright (c) 2015 Brewpi/Matthew McGowan.  All rights reserved.

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

#ifndef CONTROLLER_SCREEN_LAYOUT_H
#define	CONTROLLER_SCREEN_LAYOUT_H


#define COL1_X (0)
#define COL1_CX (30)
#define COL_GAP (4)
#define COL1_GAP COL_GAP

#define UNIT_CX (85)

#define COL2_X (COL1_X+COL1_CX+COL1_GAP)
#define COL2_CX UNIT_CX
#define COL2_GAP COL_GAP

#define COL3_X (COL2_X+COL2_CX+COL2_GAP)
#define COL3_CX UNIT_CX
#define COL3_GAP COL_GAP

#define COL4_X (COL3_X+COL3_CX+COL3_GAP)
#define COL4_CX UNIT_CX
#define COL4_GAP COL_GAP

#define COL5_X (COL4_X+COL4_CX+COL4_GAP)

#define ROW_GAP (4)
#define ROW1_Y (0)
#define ROW1_CY (40)
#define ROW1_GAP ROW_GAP

#define ROW2_Y (ROW1_Y+ROW1_CY+ROW1_GAP)
#define ROW2_CY (20)
#define ROW2_GAP 0

#define ROW3_Y (ROW2_Y+ROW2_CY+ROW2_GAP)
#define ROW3_CY (50)
#define ROW3_GAP 0

#define ROW4_Y (ROW3_Y+ROW3_CY+ROW3_GAP)
#define ROW4_CY (30)
#define ROW4_GAP ROW_GAP

#define ROW5_Y (ROW4_Y+ROW4_CY+ROW4_GAP)
#define ROW5_CY (40)
#define ROW5_GAP ROW_GAP

#define ROW6_Y (ROW5_Y+ROW5_CY+ROW5_GAP)

#define LABEL_COLOR SECONDARY_TEXT_COLOR

#define ROWPV_Y ROW3_Y
#define ROWPV_CY ROW3_CY
#define ROWSV_Y ROW4_Y
#define ROWSV_CY ROW4_CY
#define ROWLAB_Y ROW2_Y
#define ROWLAB_CY ROW2_CY
#define ROWMODE_Y ROW5_Y
#define ROWMODE_CY ROW5_CY



#endif	/* CONTROLLER_SCREEN_LAYOUT_H */

