//
//  dijkstraAlgorithm.c
//  
//
//  Created by Kyle Kempt on 1/25/17.
//
//

#include "dijkstraAlgorithm.h"
#include "dungeon.h"
#include "pri_que.h"
#include "main.h"

void tunneler_djk_output(dungeonGrid **grid, int startX, int startY, int parent[])
{
    
    int V = MAX;
    struct Graph* graph = createGraph(V);
    int src = startX + (startY * 160);
    
    
    
    
    
    
    for(int i = 0; i < Y; i++)
    {
        for(int j = 0; j < X; j++)
        {
            if(i == 0) //upper bound
            {
                if(j == 0) //upper left corner
                {
                    addEdge(graph, grid[i][j].cellCount, grid[i + 1][j].cellCount, grid[i + 1][j].cost);
                    addEdge(graph, grid[i][j].cellCount, grid[i][j + 1].cellCount, grid[i][j + 1].cost);
                    addEdge(graph, grid[i][j].cellCount, grid[i + 1][j + 1].cellCount, grid[i + 1][j + 1].cost);
                }
                else if(j == 159) //upper right corner
                {
                    addEdge(graph, grid[i][j].cellCount, grid[i + 1][j].cellCount, grid[i + 1][j].cost);
                    addEdge(graph, grid[i][j].cellCount, grid[i][j + 1].cellCount, grid[i][j - 1].cost);
                    addEdge(graph, grid[i][j].cellCount, grid[i + 1][j + 1].cellCount, grid[i + 1][j - 1].cost);
                    
                    
                    
                }
                else //anything on the upper boundary
                {
                     addEdge(graph, grid[i][j].cellCount, grid[i][j + 1].cellCount, grid[i][j + 1].cost);
                     addEdge(graph, grid[i][j].cellCount, grid[i + 1][j + 1].cellCount, grid[i + 1][j + 1].cost);
                     addEdge(graph, grid[i][j].cellCount, grid[i + 1][j].cellCount, grid[i + 1][j].cost);
                     addEdge(graph, grid[i][j].cellCount, grid[i][j - 1].cellCount, grid[i][j - 1].cost);
                     addEdge(graph, grid[i][j].cellCount, grid[i + 1][j - 1].cellCount, grid[i + 1][j - 1].cost);
                    
                }
                
            }
            
            else if(i == 104) //lower bound
            {
                if(j == 0) //lower left corner
                {
                     addEdge(graph, grid[i][j].cellCount, grid[i - 1][j].cellCount, grid[i - 1][j].cost);
                     addEdge(graph, grid[i][j].cellCount, grid[i][j + 1].cellCount, grid[i][j + 1].cost);
                     addEdge(graph, grid[i][j].cellCount, grid[i - 1][j + 1].cellCount, grid[i - 1][j + 1].cost);
        
                }
                else if(j == 159) //lower right corner
                {
                     addEdge(graph, grid[i][j].cellCount, grid[i - 1][j].cellCount, grid[i - 1][j].cost);
                     addEdge(graph, grid[i][j].cellCount, grid[i][j - 1].cellCount, grid[i][j - 1].cost);
                     addEdge(graph, grid[i][j].cellCount, grid[i - 1][j - 1].cellCount, grid[i - 1][j - 1].cost);
        
                }
                else //anything on the lower boundary
                {
                     addEdge(graph, grid[i][j].cellCount, grid[i][j + 1].cellCount, grid[i][j + 1].cost);
                     addEdge(graph, grid[i][j].cellCount, grid[i - 1][j + 1].cellCount, grid[i - 1][j + 1].cost);
                     addEdge(graph, grid[i][j].cellCount, grid[i - 1][j].cellCount, grid[i - 1][j].cost);
                     addEdge(graph, grid[i][j].cellCount, grid[i][j - 1].cellCount, grid[i][j - 1].cost);
                     addEdge(graph, grid[i][j].cellCount, grid[i - 1][j - 1].cellCount, grid[i - 1][j - 1].cost);
    
                }
            }
            
            
            
            else if(j == 0) //left bound    NO CORNER RULES NEEDED - already in upper/lower bound rules
            {
                 addEdge(graph, grid[i][j].cellCount, grid[i][j + 1].cellCount, grid[i][j + 1].cost);
                 addEdge(graph, grid[i][j].cellCount, grid[i - 1][j + 1].cellCount, grid[i - 1][j + 1].cost);
                 addEdge(graph, grid[i][j].cellCount, grid[i - 1][j].cellCount, grid[i - 1][j].cost);
                 addEdge(graph, grid[i][j].cellCount, grid[i + 1][j + 1].cellCount, grid[i + 1][j + 1].cost);
                 addEdge(graph, grid[i][j].cellCount, grid[i + 1][j].cellCount, grid[i + 1][j].cost);
                
            }
            
            else if(j == 159) //right bound    NO CORNER RULES NEEDED - already in upper/lower bound rules
            {
                 addEdge(graph, grid[i][j].cellCount, grid[i][j - 1].cellCount, grid[i][j - 1].cost);
                 addEdge(graph, grid[i][j].cellCount, grid[i - 1][j - 1].cellCount, grid[i - 1][j - 1].cost);
                 addEdge(graph, grid[i][j].cellCount, grid[i - 1][j].cellCount, grid[i - 1][j].cost);
                 addEdge(graph, grid[i][j].cellCount, grid[i + 1][j - 1].cellCount, grid[i + 1][j - 1].cost);
                 addEdge(graph, grid[i][j].cellCount, grid[i + 1][j].cellCount, grid[i + 1][j].cost);
                
                
            }
            
            else //all cells that are not on the corner or on one of the boundaries
                //should be 8 if statements
            {
                 addEdge(graph, grid[i][j].cellCount, grid[i][j - 1].cellCount, grid[i][j - 1].cost);
                 addEdge(graph, grid[i][j].cellCount, grid[i - 1][j - 1].cellCount, grid[i - 1][j - 1].cost);
                 addEdge(graph, grid[i][j].cellCount, grid[i - 1][j].cellCount, grid[i - 1][j].cost);
                 addEdge(graph, grid[i][j].cellCount, grid[i + 1][j - 1].cellCount, grid[i + 1][j - 1].cost);
                 addEdge(graph, grid[i][j].cellCount, grid[i + 1][j].cellCount, grid[i + 1][j].cost);
                 addEdge(graph, grid[i][j].cellCount, grid[i][j + 1].cellCount, grid[i][j + 1].cost);
                 addEdge(graph, grid[i][j].cellCount, grid[i - 1][j + 1].cellCount, grid[i - 1][j + 1].cost);
                 addEdge(graph, grid[i][j].cellCount, grid[i + 1][j + 1].cellCount, grid[i + 1][j + 1].cost);
            }
            

        }
    }
    
    
    dijkstra(graph, src, grid, 0, parent);
    

}

void non_tunneler_djk_output(dungeonGrid **grid, int startX, int startY, int parent[])
{
    
    int G = MAX; //just create a grpah the size of the numbers of .'s and #'s
    struct Graph* graph2 = createGraph(G);
    int src = startX + (startY * 160);
    
    
    
    for(int i = 0; i < Y; i++)
    {
        for(int j = 0; j < X; j++)
        {
            if(grid[i][j].cell == '.' || grid[i][j].cell == '#')
            {
                //set of if statements that checks each neighboring cell of
                //the corridor or room cell and connects to it in the graph it
                //is a room or corridor cell
            
                if(grid[i - 1][j - 1].cell == '.' || grid[i - 1][j - 1].cell == '#') //top left
                {
                    addEdge(graph2, grid[i][j].cellCount, grid[i - 1][j - 1].cellCount, grid[i - 1][j - 1].cost);

                }
                if(grid[i - 1][j].cell == '.' || grid[i - 1][j].cell == '#') //top
                {
                    addEdge(graph2, grid[i][j].cellCount, grid[i - 1][j].cellCount, grid[i - 1][j].cost);
                }
                if(grid[i - 1][j + 1].cell == '.' || grid[i - 1][j + 1].cell == '#') //top right
                {
                    addEdge(graph2, grid[i][j].cellCount, grid[i - 1][j + 1].cellCount, grid[i - 1][j + 1].cost);

                }
                if(grid[i][j + 1].cell == '.' || grid[i][j + 1].cell == '#') //right
                {
                    addEdge(graph2, grid[i][j].cellCount, grid[i][j + 1].cellCount, grid[i][j + 1].cost);

                }
                if(grid[i + 1][j + 1].cell == '.' || grid[i + 1][j + 1].cell == '#') //bottom right
                {
                    addEdge(graph2, grid[i][j].cellCount, grid[i + 1][j + 1].cellCount, grid[i + 1][j + 1].cost);
                }
                if(grid[i + 1][j].cell == '.' || grid[i + 1][j].cell == '#') //bottom
                {
                    addEdge(graph2, grid[i][j].cellCount, grid[i + 1][j].cellCount, grid[i + 1][j].cost);
                }
                if(grid[i + 1][j - 1].cell == '.' || grid[i + 1][j - 1].cell == '#') //bottom left
                {
                    addEdge(graph2, grid[i][j].cellCount, grid[i + 1][j - 1].cellCount, grid[i + 1][j - 1].cost);
                }
                if(grid[i][j - 1].cell == '.' || grid[i][j - 1].cell == '#') //left
                {
                    addEdge(graph2, grid[i][j].cellCount, grid[i][j - 1].cellCount, grid[i][j - 1].cost);
                }
                
                
            } //end if . || #
            
        } //end for
    } // end for
    dijkstra(graph2, src, grid, 1, parent);

    
} //end function





