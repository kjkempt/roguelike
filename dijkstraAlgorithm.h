//
//  dijkstraAlgorithm.h
//  
//
//  Created by Kyle Kempt on 1/25/17.
//
//

#ifndef dijkstraAlgorithm_h
#define dijkstraAlgorithm_h

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "dungeon.h"

void tunneler_djk_output(dungeonGrid **grid, int startX, int startY, int parent[]);
void non_tunneler_djk_output(dungeonGrid **grid, int startX, int startY, int parent[]);

#endif /* dijkstraAlgorithm_h */
