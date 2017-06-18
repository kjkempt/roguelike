//
//  dungeon.c
//  
//
//  Created by Kyle Kempt on 1/18/17.
//
//


#include "dungeon.h"
#include "dijkstraAlgorithm.h"
#include "pri_que.h"
#include "game_priority_queue.h"




void create_blankGrid(dungeonGrid **grid) //initializes the struct array with spaces in its
                                                        //char cell member and creates an edge of hardness=255
                                                        //on the edges of the game grid
{
    //srand(time(NULL));
    
    
    //INITIALIZATION LOOP
    for(int i=0; i < Y; i++)
    {
        for(int j = 0; j < X; j++)
        {
            grid[i][j].cell = ' '; //each cell is an empty space at the start of the program
            grid[i][j].room_number = 20;
            grid[i][j].cellCount = (i * 160) + j; //gives total cell count [0-16799]
            
            if(i == 0) //top-edge
            {
                grid[i][j].hardness = 255;
                grid[i][j].cost = 10000000;

            }
            else if(i == 104) //bottom edge
            {
                grid[i][j].hardness = 255;
                grid[i][j].cost = 10000000;

            }
            else if(j == 0) //left edge
            {
                grid[i][j].hardness = 255;
                grid[i][j].cost = 10000000;

            }
            else if(j == 159) //right edge
            {
                grid[i][j].hardness = 255;
                grid[i][j].cost = 10000000;

            }
            else    //everything else (for now)+++++++++++++++++++++++++++++++++++
            {
                grid[i][j].hardness = 1 + rand() % (255 - 1); //hardness: [1, 254]
                //this initializes the cost grid based on hardness attribute
                if(grid[i][j].hardness > 0 && grid[i][j].hardness < 85)
                {
                    grid[i][j].cost = 1;
                }
                else if(grid[i][j].hardness > 84 && grid[i][j].hardness < 171)
                {
                    grid[i][j].cost = 2;

                }
                else if(grid[i][j].hardness > 170 && grid[i][j].hardness < 255)
                {
                    grid[i][j].cost = 3;

                }
            }

        }
    }
   
}


void printGrid(dungeonGrid **grid,  player &p1, vector<monster> & monsterList, WINDOW *win, int winy, int winx,
               vector<dungeonObjects> & objectList) //prints the game grid in its current iteration
{
    
    //updates the grid based on player's light in the fog of war
    fog_of_war(p1);
    
    
    init_pair(BLACK, COLOR_WHITE, COLOR_BLACK);
    init_pair(RED, COLOR_RED, COLOR_BLACK);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);

    if(monsterList.size() > 1)
    {
        for(unsigned int k = 0; k < monsterList.size(); k++)
        {
            for(unsigned int l = k + 1; l < monsterList.size(); l++)
            {
                if(monsterList[k].posX() == monsterList[l].posX() &&
                   monsterList[k].posY() == monsterList[l].posY())
                {
                       int move_success = 0;
                        while(move_success == 0)
                        {
                            int move = rand() % 8; //can move in one of 8 directions
                            
                            switch(move)
                            {
                                case 0 : //move up
                                    if(grid[monsterList[l].posY() - 1][ monsterList[l].posX()].cell != ' ')
                                    {
                                        if(p1.posX() == ( monsterList[l].posX() ) &&
                                           p1.posY() == ( monsterList[l].posY() - 1 )  )
                                        {
                                            
                                        }
                                        else
                                        {
                                            monsterList[l].setY( monsterList[l].posY() - 1);
                                            move_success++;
                                        }
                                    }
                                    break;
                                case 1 : //move right
                                    if(grid[monsterList[l].posY()][ monsterList[l].posX() + 1].cell != ' ')
                                    {
                                        if(p1.posX() == ( monsterList[l].posX() + 1 ) &&
                                           p1.posY() == ( monsterList[l].posY() )  )
                                        {
                                        }
                                        else
                                        {
                                            monsterList[l].setX( monsterList[l].posX() + 1);
                                            move_success++;
                                        }
                                    }
                                    break;
                                case 2 : //move down
                                    if(grid[monsterList[l].posY() + 1][ monsterList[l].posX()].cell != ' ')
                                    {
                                        if(p1.posX() == ( monsterList[l].posX() ) &&
                                           p1.posY() == ( monsterList[l].posY() + 1 )  )
                                        {
                                        }
                                        else
                                        {
                                            
                                            monsterList[l].setY( monsterList[l].posY() + 1);
                                            move_success++;

                                        }
                                    }
                                    break;
                                case 3 : //move left
                                    if(grid[monsterList[l].posY()][ monsterList[l].posX() - 1].cell != ' ')
                                    {
                                        if(p1.posX() == ( monsterList[l].posX() - 1 ) &&
                                           p1.posY() == ( monsterList[l].posY() )  )
                                        {
                                        }
                                        else
                                        {
                                            
                                            monsterList[l].setX( monsterList[l].posX() - 1);
                                            move_success++;

                                        }
                                    }
                                case 4 : //move upper left
                                    if(grid[monsterList[l].posY() - 1][ monsterList[l].posX() - 1].cell != ' ')
                                    {
                                        if(p1.posX() == ( monsterList[l].posX() - 1 ) &&
                                           p1.posY() == ( monsterList[l].posY() - 1 )  )
                                        {
                                        }
                                        else
                                        {
                                            
                                            monsterList[l].setX( monsterList[l].posX() - 1);
                                            monsterList[l].setY( monsterList[l].posY() - 1);
                                            move_success++;

                                            
                                        }
                                    }
                                    break;
                                case 5 : //move upper right
                                    if(grid[monsterList[l].posY() - 1][ monsterList[l].posX() + 1].cell != ' ')
                                    {
                                        if(p1.posX() == ( monsterList[l].posX() + 1) &&
                                           p1.posY() == ( monsterList[l].posY() - 1 )  )
                                        {
                                        }
                                        else
                                        {
                                            
                                            monsterList[l].setX( monsterList[l].posX() + 1);
                                            monsterList[l].setY( monsterList[l].posY() - 1);
                                            move_success++;

                                            
                                        }
                                    }
                                case 6 : //move lower right
                                    if(grid[monsterList[l].posY() + 1][ monsterList[l].posX() + 1].cell != ' ')
                                    {
                                        if(p1.posX() == ( monsterList[l].posX() + 1) &&
                                           p1.posY() == ( monsterList[l].posY() + 1 )  )
                                        {
                                        }
                                        else
                                        {
                                            
                                            monsterList[l].setY( monsterList[l].posY() + 1);
                                            monsterList[l].setX( monsterList[l].posX() + 1);
                                            move_success++;

                                            
                                        }
                                    }
                                    break;
                                case 7 : //move lower left
                                    if(grid[monsterList[l].posY() + 1][ monsterList[l].posX() - 1].cell != ' ')
                                    {
                                        if(p1.posX() == ( monsterList[l].posX() - 1) &&
                                           p1.posY() == ( monsterList[l].posY() + 1 )  )
                                        {
                                        }
                                        else
                                        {
                                            
                                            monsterList[l].setX( monsterList[l].posX() - 1);
                                            monsterList[l].setY( monsterList[l].posY() + 1);
                                            move_success++;

                                            
                                        }
                                    }
                                    break;
                        }
                            
                        }
                        
                    }
                    

                    
                
            }
        }
    }
    
    

    for(int i=0; i < 21; i++)
    {
        for(int j = 0; j < 80; j++)
        {
            
            int picked_up = -1;
            int killed = -1;

            int c = 0;
            
            
            //prints the symbol of the object
            for(unsigned int k = 0; k < objectList.size(); k++)
            {

                    if((objectList[k].posX() - winx) == j && (objectList[k].posY() - winy) == i
                    && (p1.getView( objectList[k].posX() - winx, objectList[k].posY() - winy) == 1))
                    {

                        wattron(win, COLOR_PAIR(objectList[k].get_color()));
                        mvwaddch(win, i + 1, j, objectList[k].returnChar());
                        wattroff(win, COLOR_PAIR(objectList[k].get_color()));
                        c++;
                        p1.setMemory( objectList[k].posX() - winx, objectList[k].posY() - winy,objectList[k].returnChar());
                        
                        //if a player is standing over an object
                        if(objectList[k].posX() == p1.posX() && objectList[k].posY() == p1.posY() && objectList[k].check_drop() == 0)
                           {
                               if(p1.setInventory(objectList[k]) == 1) //item was picked up
                               {
                                   picked_up = k;
                               }
                           }
                        
                         if((  objectList[k].posX() != p1.posX() || objectList[k].posY() != p1.posY()  )
                             && objectList[k].check_drop() == 1) //if an object was dropped but the player is not on top of it anymore
                         {
                             objectList[k].dec_drop(); //changes drop status back to 0 so the item can be picked up again
                         }
                        
                    }
            }
            
            
            if(picked_up != -1)
            {
                objectList.erase(objectList.begin() + picked_up);
            }

            
            
            
            
            
            for(unsigned int k = 0; k < monsterList.size(); k++)
            {
                
                    //prints symbol of an alive monster
                    if((monsterList[k].posX() - winx) == j && (monsterList[k].posY() - winy) == i
                       && (p1.getView( monsterList[k].posX() - winx, monsterList[k].posY() - winy) == 1))
                    {

                        if(monsterList[k].getAlive() == 1)
                        {
                            wattron(win, COLOR_PAIR(monsterList[k].get_color()));
                            mvwaddch(win, i + 1, j, monsterList[k].returnChar());
                            wattroff(win, COLOR_PAIR(monsterList[k].get_color()));
                    
                            c++; //something was printed
                            p1.setMemory( monsterList[k].posX() - winx, monsterList[k].posY() - winy,monsterList[k].returnChar());
                        }
                        else if(monsterList[k].getAlive() == 0) //monster was killed in most recent turn
                        {
                            killed = k;
                        }
                    }

            }
            
            if(killed != -1)
            {
                monsterList.erase(monsterList.begin() + killed);
            }
            
            //prints the character
            if(i == (p1.posY() - winy) && j == (p1.posX() - winx))
            {
                mvwaddch(win, i + 1, j, '@');
                c++;
            }

            
            //nothing has been printed in this space yet
            if(c == 0)
            {
                    if(p1.getView( j + winx, i + winy) == 1) //within the fog of war
                    {
                        
                        mvwaddch(win, i + 1, j, grid[i + winy][j + winx].cell);
                        
                        p1.setMemory( j + winx, i + winy, grid[i + winy][j + winx].cell);
         
                    }
                    else if(p1.getView( j + winx, i + winy) == 0) //if the player has not seen this cell
                    {
                        mvwaddch(win, i + 1, j, ' ');
                    }
                    else if(p1.getView( j + winx, i + winy) == 2) //player has seen but is only going off of memory
                    {
                        mvwaddch(win, i + 1, j, p1.getMemory( j + winx, i + winy));
                    }
            }
    
        }
        
    }
      
    
}




void room_generator(dungeonGrid **grid, int rooms, roomData *rd) //generates the random rooms in the grid, 10 to 13 rooms at least
{
    
    
    //srand(time(NULL));
    //min + rand() % (max - min);
    
    
    int roomCount = 0;
    int errorCount = 0;
    int stairCount = 0;
    
    while(roomCount != rooms)
    {
        int overlap = 0; //keeps track of if a room overlaps another. 0 is no, 1 is yes
        int x = 1 + rand() % (X - 1); //starting point on x-axis
        int y = 1 + rand() % (Y - 1); //starting point on y-axis
        int bound_x = 7 + rand() % (18 - 7); //length (x) of the random room(changes every iteration)
        int bound_y = 5 + rand() % (14 - 5); //length (y) of the random room(changes every iteration)
        
        
        
        if((x + bound_x >= X) || (y + bound_y >= Y)) //if the bottom right corner goes out of bounds
                                                        //room is not implemented and the loop will start over
        {
            errorCount++; //keeps track of the number of failed room attempts for data purposes
        }
        
        else
        {
            
            if((y - 3) <= 0 || (bound_y+ y + 3 >= Y)) //if the perimeter cannot be extended by 3 in the Y direction because of the edge
            {
                //This loop specifically checks for room overlap++++++
                for(int i = y; i < (y + bound_y); i++)
                {
                    for(int j = x; j < (x + bound_x); j++)
                    {
                        if(grid[i][j].cell == '.')
                        {
                            overlap++; //there is an overlap with the rooms, so an error will be triggered and this room will not be    generated
                        }
                    }
                }
            //++++++++
            }
            else if((x - 3) <= 0 || (bound_x+ x + 3 >= X)) //if the perimeter cannot be extended by 3 in the X direction because of the edge
            {
                //This loop specifically checks for room overlap++++++
                for(int i = y; i < (y + bound_y); i++)
                {
                    for(int j = x; j < (x + bound_x); j++)
                    {
                        if(grid[i][j].cell == '.')
                        {
                            overlap++; //there is an overlap with the rooms, so an error will be triggered and this room will not be generated
                        }
                    }
                }
                //++++++++

            }
            else //the perimeter can be extended by 3 in both the X and Y direction to check for overlap to ensure there is at least 3 spaces between
                    //each room
            {
                //This loop specifically checks for room overlap++++++
                for(int i = (y - 3); i < (y + bound_y + 3); i++)
                {
                    for(int j = (x - 3); j < (x + bound_x + 3); j++)
                    {
                        if(grid[i][j].cell == '.')
                        {
                            overlap++; //there is an overlap with the rooms, so an error will be triggered and this room will not be generated
                        }
                    }
                }
                //++++++++
            }
            
            int s1 = 0;
            int s2 = 0;
            
            if(overlap == 0) // if there is no overlap then run the loop
            {
                //this sets up a single random room at the moment
                for(int i = y; i < (y + bound_y); i++)
                {
                    for(int j = x; j < (x + bound_x); j++)
                    {
                        int chance = rand() % 120; // [0-119],
                        
                        if(chance == 1 && stairCount < 2 && s1 == 0)
                        {
                            grid[i][j].cell = '>';
                            grid[i][j].hardness = 0; //rooms have 0 rock hardness
                            grid[i][j].cost = 1;
                            stairCount++;
                            s1++;
                        }
                        else if(chance == 30 && stairCount < 2 && s2 == 0)
                        {
                            grid[i][j].cell = '<';
                            grid[i][j].hardness = 0; //rooms have 0 rock hardness
                            grid[i][j].cost = 1;
                            stairCount++;
                            s2++;
                        }
                        else
                        {
                        grid[i][j].cell = '.';
                        grid[i][j].hardness = 0; //rooms have 0 rock hardness
                        grid[i][j].cost = 1;
                        }
                    }
                }
                

                rd[roomCount].x_start = x;
                rd[roomCount].y_start = y;
                rd[roomCount].x_width = bound_x;
                rd[roomCount].y_height = bound_y;
                
                

                grid[y + (bound_y / 2)][x + (bound_x / 2)].room_number = roomCount; //puts the room number near the middle of the room
                roomCount++; //if a room is successfully put onto the grid, the count will increase
            }
            else //overlap occured if this point is reached
            {
                errorCount++; //count this as a failed room attempt because of the overlap
            }
            
            
        }
        
    } //end of while loop
    
   
    
    
    
}


void path_generator(dungeonGrid **grid, int rooms)
{
    
    int room_coordinates[rooms][2]; //holds the center coordinate of each room in the grid, the slots in each row for the x-y
 
    
     
    for(int i=0; i < Y; i++)
    {
        for(int j = 0; j < X; j++)
        {
            
            if(grid[i][j].room_number < 16)
            {
                room_coordinates[grid[i][j].room_number][0] = j;
                room_coordinates[grid[i][j].room_number][1] = i;

            }
        }
    }
    
    

    
    int b = 0;
    int b_x1;
    int b_x2;
    int b_y1;
    int b_y2;
    while(b != rooms-1)
    {
        b_x1 = room_coordinates[b][0];
        b_y1 = room_coordinates[b][1];
        b_x2 = room_coordinates[b + 1][0];
        b_y2 = room_coordinates[b + 1][1];
        connect(grid, b_x1, b_y1, b_x2, b_y2);
        b++;
    }

    
    
    
    
    
}


void connect(dungeonGrid **grid, int x1, int y1, int x2, int y2)
{
    
    
    
    
    
            while(x1 != x2 || y1 != y2)
            {
                int chance = rand();
                if(x1 < x2)
                {
                    if(y1 < y2)
                    {
                            //+++++++++this increments to the next point in the grid
                            chance = chance % 10;
                            if(x1 == x2) //reached the goal for x
                            {
                                y1++;
                            }
                            else if(y1 == y2) //reached the goal for y
                            {
                                x1++;
                            }
                            else //12.5% chance to change direction
                            {
                                if(chance == 0)
                                {
                                    y1++;
                                }
                                else
                                {
                                    x1++;
                                }
                            }
                            //+++++++++++++++++
                
                
                
                            //replaces a space with # if there is no room in the way
                            if(grid[y1][x1].cell == ' ')
                            {
                                grid[y1][x1].cell = '#';
                                grid[y1][x1].hardness = 0;
                                grid[y1][x1].cost = 1;
                            }
                    }
                    
                    //y1 > y2
                    else
                    {
                        
                        //+++++++++this increments to the next point in the grid
                        chance = chance % 10;
                        if(x1 == x2) //reached the goal for x
                        {
                            y1--;
                        }
                        else if(y1 == y2) //reached the goal for y
                        {
                            x1++;
                        }
                        else //12.5% chance to change direction
                        {
                            if(chance == 0)
                            {
                                y1--;
                            }
                            else
                            {
                                x1++;
                            }
                        }
                        //+++++++++++++++++
                        
                        
                        
                        //replaces a space with # if there is no room in the way
                        if(grid[y1][x1].cell == ' ')
                        {
                            grid[y1][x1].cell = '#';
                            grid[y1][x1].hardness = 0;
                            grid[y1][x1].cost = 1;
                        }
                    }
                }
                //x1 > x2
                else
                {
                    
                    if(y1 < y2)
                    {
                        
                        //+++++++++this increments to the next point in the grid
                        chance = chance % 10;
                        if(x1 == x2) //reached the goal for x
                        {
                            y1++;
                        }
                        else if(y1 == y2) //reached the goal for y
                        {
                            x1--;
                        }
                        else //12.5% chance to change direction
                        {
                            if(chance == 0)
                            {
                                y1++;
                            }
                            else
                            {
                                x1--;
                            }
                        }
                        //+++++++++++++++++
                        
                        
                        
                        //replaces a space with # if there is no room in the way
                        if(grid[y1][x1].cell == ' ')
                        {
                            grid[y1][x1].cell = '#';
                            grid[y1][x1].hardness = 0;
                            grid[y1][x1].cost = 1;
                        }
                    }
                    //x1 > x2 && y1 > y2
                    else
                    {
                        //+++++++++this increments to the next point in the grid
                        chance = chance % 10;
                        if(x1 == x2) //reached the goal for x
                        {
                            y1--;
                        }
                        else if(y1 == y2) //reached the goal for y
                        {
                            x1--;
                        }
                        else //12.5% chance to change direction
                        {
                            if(chance == 0)
                            {
                                y1--;
                            }
                            else
                            {
                                x1--;
                            }
                        }
                        //+++++++++++++++++
                        
                        
                        
                        //replaces a space with # if there is no room in the way
                        if(grid[y1][x1].cell == ' ')
                        {
                            grid[y1][x1].cell = '#';
                            grid[y1][x1].hardness = 0;
                            grid[y1][x1].cost = 1;
                        }
                    }
                }
                    
                
                
                
            }
    
    
}





char* dungeonFile() {
    char* full_path;
    char* home_directory;
    const char* relative_path = "/.rlg327/dungeon";
    
    home_directory = getenv("HOME");
    full_path = (char*) malloc(sizeof(char) * (strlen(home_directory) + strlen(relative_path) + 1));
    sprintf(full_path, "%s/.rlg327/dungeon", home_directory);
    return full_path;
}

int saveDungeon(dungeonGrid **grid, roomData *rd,  char* fileName, int rooms)
{
    FILE *f;            //pointer to the file f
    size_t byteWriter;  //keeps track of the number of members written when a write action is performed
    uint32_t fileSize;  //used for file size
    uint32_t fileVersion = 0;   //used for version
    
    fileSize = 12 + 4 + 4 + (160 * 105) + (4 * rooms);
    
  // fileVersion = htobe32(fileVersion);
   // fileSize = htobe32(fileSize);
    
    f = fopen(fileName, "w");   //open file and use write mode
    
    if(f == NULL)
    {
        return 1;
    }
    
    
    byteWriter = fwrite("RLG327-S2017", sizeof(char), 12, f);   //writes a 12 character word to the file f. 12 bytes long
    if (byteWriter != 12) {     //checks to make sure the correct number of members were written
        return 1;
    }
    
    byteWriter = fwrite(&fileVersion, sizeof(fileVersion), 1, f); //writes the file version to the file. 4 bytes long
    if (byteWriter != 1)
    {
        return 1;
    }
    
    
    byteWriter = fwrite(&fileSize, sizeof(fileSize), 1, f); //writes the file size to the file. 4 bytes long
    if(byteWriter != 1)
    {
        return 1;
    }
    
    for(int i = 0; i < Y; i++)
    {
        for(int j = 0; j < X; j++)
        {
            byteWriter = fwrite(&grid[i][j].hardness, sizeof(char), 1, f);
            if(byteWriter != 1)
            {
                return 1;
            }
        }
    }   //this loop should write 16,800 bytes to the file (105*160)
    
    
    for(int i = 0; i < rooms; i++)
    {
        fwrite(&rd[i].x_start, sizeof(uint8_t), 1, f);
        fwrite(&rd[i].y_start, sizeof(uint8_t), 1, f);
        fwrite(&rd[i].x_width, sizeof(uint8_t), 1, f);
        fwrite(&rd[i].y_height, sizeof(uint8_t), 1, f);
    } //bytes = rooms * 4
    
    
    
    
    fclose(f); //close file f
    
    
    return 0; //return 0 if ran correctly without any errors
}



int loadDungeon(dungeonGrid **grid, char* fileName, roomData *rd)
{
    FILE* f;
    size_t byteReader;
    uint32_t fileSize;
    uint32_t fileVersion;
    uint32_t load_room_num = 0;
    char title[12];
    
    f = fopen(fileName, "r");
    
    if(f == NULL)
    {
        return 1;
    }
    
    byteReader = fread(title, sizeof(char), 12, f);
    if (byteReader < 12) {
        return 1;
    }
    if (strncmp("RLG327-S2017", title, 12) != 0)
    {
        return 1;
    }
    
   
    
    byteReader = fread(&fileVersion, sizeof(fileVersion), 1, f);
    if(byteReader != 1)
    {
        return 1;
    }
    
   // fileVersion = be32toh(fileVersion);
    
    byteReader = fread(&fileSize, sizeof(fileSize), 1, f);
    if(byteReader != 1)
    {
        return 1;
    }
    
    //fileSize = be32toh(fileSize);

    
    
    for(int i = 0; i < Y; i++)
    {
        for(int j = 0; j < X; j++)
        {
            byteReader = fread(&grid[i][j].hardness, sizeof(char), 1, f);
            if(byteReader != 1)
            {
                return 1;
            }
            if(grid[i][j].hardness == 0)
            {
                grid[i][j].cell = '#';
                grid[i][j].cost = 1;
            }
            else
            {
                grid[i][j].cell = ' ';
                if(grid[i][j].hardness > 0 && grid[i][j].hardness < 85)
                {
                    grid[i][j].cost = 1;
                }
                else if(grid[i][j].hardness > 84 && grid[i][j].hardness < 171)
                {
                    grid[i][j].cost = 2;
                    
                }
                else if(grid[i][j].hardness > 170 && grid[i][j].hardness < 255)
                {
                    grid[i][j].cost = 3;
                    
                }
            }
        }
    }
    
    
    
    
   load_room_num  = (fileSize - (12 + 4 + 4 + (160 * 105))) / 4;     //loadRooms will give me the number of rooms now

    roomData *temp = (roomData*) realloc(rd ,load_room_num * sizeof(roomData));
    if(temp != NULL)
    {
        rd = temp;
    }
    else
    {
        printf("Error with pointer\n");
        return 1;
    }
    
    
    for(uint32_t i = 0; i < load_room_num; i++)
    {
        fread(&rd[i].x_start, sizeof(uint8_t), 1, f);
        fread(&rd[i].y_start, sizeof(uint8_t), 1, f);
        fread(&rd[i].x_width, sizeof(uint8_t), 1, f);
        fread(&rd[i].y_height, sizeof(uint8_t), 1, f);
        
        //this double nested loop will run through the rooms
        //listed in the file and replace the # character with
        // a . character
        for(int k = rd[i].y_start; k < (rd[i].y_start + rd[i].y_height); k++)
        {
            for(int j = rd[i].x_start; j < (rd[i].x_start + rd[i].x_width); j++)
            {
                grid[k][j].cell = '.';
            }
        }
        
        
    } //bytes = rooms * 4

    
    fclose(f);
    
    return 0;
}


void game(dungeonGrid **grid, roomData *rd, player &p1, vector<monster> & monsterList, int rooms, int *stairs,
          vector<dungeonObjects> & objectList)
{

    
   heap_t *h = (heap_t *)calloc(1, sizeof (heap_t));
    
   //intialize the queue
    

    
    event *e = (event*) malloc(sizeof(event));
    

    
    //push character into the queue
    e->p.pc = &p1;
    e->type = e_pc;
    e->time = 1000 / e->p.pc->getSpeed();
    

    
    push(h, 0, e); //all turns start at priority 0
    
    
    event *e2 = (event*) malloc(monsterList.size() * sizeof(event));
    
    //push all monsters into the queue
    for(unsigned int i = 0; i < monsterList.size(); i++)
    {

        e2[i].p.npc = &monsterList[i];

        e2[i].type = e_npc;

        
        e2[i].time = 1000 / e2[i].p.npc->getSpeed();

        push(h, 0, &e2[i]);
    }
    
    
    
    /*
     combat checklist
     -don't allow players to move to occupied monster spaces/visa versa
     -delete monsters from the monsterlist once they die
     -fill in attack function
     -delete monster from the event queue??
     
     
     */
    
    
    


   

    
    
    
    int tun_parent[MAX]; //keeps track of the shortest path for tunnelers
    int non_tun_parent[MAX]; //keeps track of the shortest path for non tunnelers
    //the two arrays above will update everytime the player moves
    
    
    
    int winx = 0;
    int winy = 0;
    
    
     WINDOW * win = newwin(24, 80, 0, 0);
    
    keypad(win, TRUE);
    
    //scrollok(win, TRUE);
    
    printGrid(grid, p1, monsterList, win, winy, winx, objectList);
    
    wmove(win, 0, 0);
    
    wrefresh(win);

    
    
    tunneler_djk_output(grid, p1.posX(), p1.posY(), tun_parent);
    non_tunneler_djk_output(grid, p1.posX(), p1.posY(), non_tun_parent);

    int quit = 0;
    
    

    
    
    while(p1.getAlive() == 1 && /*monsterList.size() != 0 &&*/ *stairs == 0 && quit == 0)
    {

        //update the camera based on the player's position
        
        
        //if the player is close to the left boundary of the dungeon
        if(p1.posX() - 40 < 0)
        {
            winx = 0;
        }
        else if(p1.posX() + 40 >= X) //if player is close to the right boundary
        {
            winx = X - 81;
        }
        else //puts the camera somewhat in the center
        {
            winx = p1.posX() - 40;
        }
        
        if(p1.posY() - 10 < 0)
        {
            winy = 0;
        }
        else if(p1.posY() + 10 >= Y) //if player is close to the right boundary
        {
            winy = Y - 22;
        }
        else //puts the camera somewhat in the center
        {
            winy = p1.posY() - 10;
        }

        printGrid(grid, p1, monsterList, win, winy, winx, objectList);
        wrefresh(win);

        
        
        if(peek(h) == 1)
        {
            
            
        
            event *e3 = (event*) malloc(sizeof(event));
            e3 = pop(h);
        
                if(e3->type == e_pc)
                    {
                        
                        if(e3->p.pc->getAlive() == 1) //if PC is not alive game will be over and loop will end so no need for else statement
                            {
                                if(player_move(grid, *e3->p.pc, monsterList, win, &winx, &winy, stairs,
                                               objectList) == 0)
                                {
                                    quit++;
                                }
                                
                                
                                //update player's speed
                                e3->p.pc->updateSpeed();
                                e3->time = 1000 / e3->p.pc->getSpeed();

                                
                                
                                tunneler_djk_output(grid, p1.posX(), p1.posY(), tun_parent);
                                non_tunneler_djk_output(grid, p1.posX(), p1.posY(), non_tun_parent);
                                decrement_queue_priority(h);
                                push(h, e3->time, e3);
                            
                        }
                        
                    }
            
            
                    else if(e3->type == e_npc)
                    {

                        if(CHECK_BIT(e3->p.npc->getCharacter(), 2) == 4)
                        {
                            if(e3->p.npc->getAlive() == 1)
                            {
                                monster_move(grid, p1, *e3->p.npc, tun_parent, win);
                                
                                decrement_queue_priority(h);
                                push(h, e3->time, e3);
                            }
                        
                        }
                        else
                        {
                            if(e3->p.npc->getAlive() == 1)
                            {
                                monster_move(grid, p1, *e3->p.npc, tun_parent, win);
                              
                                decrement_queue_priority(h);
                                push(h, e3->time, e3);
                            }
                           
                        }
                    }
        
            e3 = NULL;
            printGrid(grid, p1, monsterList, win, winy, winx, objectList);
            
            wrefresh(win);
       
            
        }
        else
        {
            decrement_queue_priority(h); //decrease each turn count by 1
        }
        
        
    }
   
    
    if(quit == 1)
    {
        mvwprintw(win, 22, 2, "         GAME OVER                           " );
        mvwprintw(win, 23,  2, "     Player quit!                          ");
        wrefresh(win);

    }
    else if(p1.getAlive() == 0)
    {
    mvwprintw(win, 22, 2, "         GAME OVER                           " );
    mvwprintw(win, 23,  2, "     Player killed!                          ");
    wrefresh(win);
    }
    int ch = wgetch(win);
    
    if(ch == 'd')
    {
        
    }
    
    delwin(win);
    free(h);
    free(e);
    free(e2);
    
    
}






int player_move(dungeonGrid **grid, player& p1, vector<monster> & monsterList, WINDOW *win, int *winx, int *winy, int *stairs, vector<dungeonObjects> & objectList)
{
    int mode = 1;
    

    
    do{
        
        if(mode == 0)
        {
            
            mvwprintw(win, 0, 0, "Look Mode                                                  ");

            
            //LOOK MODE
            
            int ch = 0;
            
            ch = wgetch(win);
                
            
            if(ch == '8' || ch == 'k') // move up
            {
                if(*winy - 1 < 0)
                {
                    mvwprintw(win, 0, 0, "Attempted look out of bounds                        ");
                }
                else
                {
                    *winy = *winy - 1;
                }
           
            }
            else if(ch == '6' || ch == 'l') //right
            {
                if(*winx + 80 >= X)
                {
                    mvwprintw(win, 0, 0, "Attempted look out of bounds                        ");
                }
                else
                {
                    *winx = *winx + 1;
                }

            }
            else if(ch == '2' || ch == 'j') //down
            {
                
                if(*winy + 21 >= Y)
                {
                    mvwprintw(win, 0, 0, "Attempted look out of bounds                        ");
                }
                else
                {
                    *winy = *winy + 1;
                }

            }
            else if(ch == '4' || ch == 'h') //left
            {
                
                if(*winx - 1 < 0)
                {
                    mvwprintw(win, 0, 0, "Attempted look out of bounds                        ");
                }
                else
                {
                    *winx = *winx - 1;
                }

            }
            else if(ch == 27) //in look mode enter control mode
            {
                mode = 1;
                //if the player is close to the left boundary of the dungeon
                if(p1.posX() - 40 < 0)
                {
                    *winx = 0;
                }
                else if(p1.posX() + 40 >= X) //if player is close to the right boundary
                {
                    *winx = X - 81;
                }
                else //puts the camera somewhat in the center
                {
                    *winx = p1.posX() - 40;
                }
                
                if(p1.posY() - 10 < 0)
                {
                    *winy = 0;
                }
                else if(p1.posY() + 10 >= Y) //if player is close to the right boundary
                {
                    *winy = Y - 22;
                }
                else //puts the camera somewhat in the center
                {
                    *winy = p1.posY() - 10;
                }
                
                printGrid(grid, p1, monsterList, win, *winy, *winx, objectList); //update the camera
                wrefresh(win);

            }
            else if(ch == 'Q') //quit game - both
            {
                return 0;
            }
            else
            {
                mvwprintw(win, 0, 0, "Wrong key                                                ");

            }
         
        }
        if(mode == 1)
        {
        //++++++
        
            mvwprintw(win, 0, 0, "Control Mode                                                  ");

            
            
            //CONTROL MODE
            
            int move = 0;
                
            while(move == 0)
            {
                int ch = wgetch(win);
                
                if(ch == '7' || ch == 'y') //move upper left ->move this to control mode
                {
                    for(unsigned int i = 0; i < monsterList.size(); i++)
                    {
                        if(monsterList[i].posX() == ( p1.posX() - 1 )  &&
                           monsterList[i].posY() == ( p1.posY() - 1 )  )
                        {
                            attack(p1, monsterList[i], 0, win);
                            move++;
                        }
                    }
                    if(move == 0)
                    {
                        
                        
                        
                        if(grid[p1.posY() - 1][p1.posX() - 1].cell == '#' ||
                           grid[p1.posY() - 1][p1.posX() - 1].cell == '.' ||
                           grid[p1.posY() - 1][p1.posX() - 1].cell == '>' ||
                           grid[p1.posY() - 1][p1.posX() - 1].cell == '<')
                        {
                            p1.setX(p1.posX() - 1);
                            p1.setY(p1.posY() - 1);
                            move++;
                        }
                        else
                        {
                            mvwprintw(win, 0, 0, "Attempted move to an area filled with rock            ");
                        }
                    }
                }
                else if(ch == '8' || ch == 'k') // move up
                {
                    for(unsigned int i = 0; i < monsterList.size(); i++)
                    {
                        if(monsterList[i].posX() == ( p1.posX() )  &&
                           monsterList[i].posY() == ( p1.posY() - 1 )  )
                        {
                            attack(p1, monsterList[i], 0, win);
                            move++;
                        }
                    }
                    if(move == 0)
                    {
                        

                    
                        
                        if(grid[p1.posY() - 1][p1.posX()].cell == '#' ||
                           grid[p1.posY() - 1][p1.posX()].cell == '.' ||
                           grid[p1.posY() - 1][p1.posX()].cell == '<' ||
                           grid[p1.posY() - 1][p1.posX()].cell == '>')
                        {
                            p1.setY(p1.posY() - 1);
                            move++;
                        }
                        else
                        {
                            mvwprintw(win, 0, 0, "Attempted move to an area filled with rock            ");
                        }
                    }
                    
                }
                else if(ch == '9' || ch == 'u') //upper right
                {
                    
                    for(unsigned int i = 0; i < monsterList.size(); i++)
                    {
                        if(monsterList[i].posX() == ( p1.posX() + 1 )  &&
                           monsterList[i].posY() == ( p1.posY() - 1 )  )
                        {
                            attack(p1, monsterList[i], 0, win);
                            move++;
                        }
                    }
                    if(move == 0)
                    {
                        

                        if(grid[p1.posY() - 1][p1.posX() + 1].cell == '#' ||
                           grid[p1.posY() - 1][p1.posX() + 1].cell == '.' ||
                           grid[p1.posY() - 1][p1.posX() + 1].cell == '<' ||
                           grid[p1.posY() - 1][p1.posX() + 1].cell == '>')
                        {
                            p1.setY(p1.posY() - 1);
                            p1.setX(p1.posX() + 1);
                            move++;
                        }
                        else
                        {
                            mvwprintw(win, 0, 0, "Attempted move to an area filled with rock            ");
                        }
                    }
                }
                else if(ch == '6' || ch == 'l') //right
                {
                    for(unsigned int i = 0; i < monsterList.size(); i++)
                    {
                        if(monsterList[i].posX() == ( p1.posX() + 1 )  &&
                           monsterList[i].posY() == ( p1.posY() )  )
                        {
                            attack(p1, monsterList[i], 0, win);
                            move++;
                        }
                    }
                    if(move == 0)
                    {
                        

                        if(grid[p1.posY()][p1.posX() + 1].cell == '#' ||
                           grid[p1.posY()][p1.posX() + 1].cell == '.' ||
                           grid[p1.posY()][p1.posX() + 1].cell == '>' ||
                           grid[p1.posY()][p1.posX() + 1].cell == '<')
                        {
                            p1.setX(p1.posX() + 1);
                            move++;
                        }
                        else
                        {
                            mvwprintw(win, 0, 0, "Attempted move to an area filled with rock            ");
                        }
                    }

                }
                else if(ch == '3' || ch == 'n') //lower right
                {
                    
                    for(unsigned int i = 0; i < monsterList.size(); i++)
                    {
                        if(monsterList[i].posX() == ( p1.posX() + 1 )  &&
                           monsterList[i].posY() == ( p1.posY() + 1 )  )
                        {
                            attack(p1, monsterList[i], 0, win);
                            move++;
                        }
                    }
                    if(move == 0)
                    {
                        

                        if(grid[p1.posY() + 1][p1.posX() + 1].cell == '#' ||
                           grid[p1.posY() + 1][p1.posX() + 1].cell == '.' ||
                           grid[p1.posY() + 1][p1.posX() + 1].cell == '>' ||
                           grid[p1.posY() + 1][p1.posX() + 1].cell == '<')
                        {
                            p1.setY(p1.posY() + 1);
                            p1.setX(p1.posX() + 1);
                            move++;
                        }
                        else
                        {
                            mvwprintw(win, 0, 0, "Attempted move to an area filled with rock            ");
                        }
                    }

                }
                else if(ch == '2' || ch == 'j') //down
                {
                    for(unsigned int i = 0; i < monsterList.size(); i++)
                    {
                        if(monsterList[i].posX() == ( p1.posX() )  &&
                           monsterList[i].posY() == ( p1.posY() + 1 )  )
                        {
                            attack(p1, monsterList[i], 0, win);
                            move++;
                        }
                    }
                    if(move == 0)
                    {
                        

                        if(grid[p1.posY() + 1][p1.posX()].cell == '#' ||
                           grid[p1.posY() + 1][p1.posX()].cell == '.' ||
                           grid[p1.posY() + 1][p1.posX()].cell == '<' ||
                           grid[p1.posY() + 1][p1.posX()].cell == '>')
                        {
                            p1.setY(p1.posY() + 1);
                            move++;
                        }
                        else
                        {
                            mvwprintw(win, 0, 0, "Attempted move to an area filled with rock            ");
                        }
                    }
                    
                }
                else if(ch == '1' || ch == 'b') //lower left
                {
                    for(unsigned int i = 0; i < monsterList.size(); i++)
                    {
                        if(monsterList[i].posX() == ( p1.posX() - 1 )  &&
                           monsterList[i].posY() == ( p1.posY() + 1 )  )
                        {
                            attack(p1, monsterList[i], 0, win);
                            move++;
                        }
                    }
                    if(move == 0)
                    {
                        

                        
                        if(grid[p1.posY() + 1][p1.posX() - 1].cell == '#' ||
                           grid[p1.posY() + 1][p1.posX() - 1].cell == '.' ||
                           grid[p1.posY() + 1][p1.posX() - 1].cell == '>' ||
                           grid[p1.posY() + 1][p1.posX() - 1].cell == '<')
                        {
                            p1.setY(p1.posY() + 1);
                            p1.setX(p1.posX() - 1);
                            move++;
                        }
                        else
                        {
                            mvwprintw(win, 0, 0, "Attempted move to an area filled with rock            ");
                        }
                            
                    }

                }
                else if(ch == '4' || ch == 'h') //left
                {
                    for(unsigned int i = 0; i < monsterList.size(); i++)
                    {
                        if(monsterList[i].posX() == ( p1.posX() - 1 )  &&
                           monsterList[i].posY() == ( p1.posY() )  )
                        {
                            attack(p1, monsterList[i], 0, win);
                            move++;
                        }
                    }
                    if(move == 0)
                    {
                        if(grid[p1.posY()][p1.posX() - 1].cell == '#' ||
                           grid[p1.posY()][p1.posX() - 1].cell == '.' ||
                           grid[p1.posY()][p1.posX() - 1].cell == '<' ||
                           grid[p1.posY()][p1.posX() - 1].cell == '>')
                        {
                            p1.setX(p1.posX() - 1);
                            move++;
                        }
                        else
                        {
                            mvwprintw(win, 0, 0, "Attempted move to an area filled with rock            ");
                        }
                    }
                    
                }
                else if(ch == '5' || ch == ' ') //rest - control
                {
                    mvwprintw(win, 0, 0, "Resting this turn.                                        ");
                    move++;
                }
                else if(ch == '>') //down stairs
                {
                    if(grid[p1.posY()][p1.posX()].cell == '>')
                    {
                        *stairs = *stairs + 1;
                        move++;
                    }
                    else
                    {
                        mvwprintw(win, 0, 0, "There are no stairs here                             ");

                    }
                }
                else if(ch == '<') //up stairs
                {
                    if(grid[p1.posY()][p1.posX()].cell == '<')
                    {
                        *stairs = *stairs + 1;
                    }
                    else
                    {
                        mvwprintw(win, 0, 0, "There are no stairs here                             ");
                        
                    }
                }
                else if(ch == 'L') //enter look mode while in control mode
                {
                    mode = 0;
                    move++;
                }
                else if(ch == 'Q') //quit game - both
                {
                    return 0;
                }
                else if(ch == 'e')
                {
                    menu(p1, 0, objectList);
                    wmove(win, 0 ,0);
                    wclrtoeol(win);
                    printGrid(grid, p1, monsterList, win, *winy, *winx, objectList); //update the grid based on look mode or movement
                    wrefresh(win);

                }
                else if(ch == 'i')
                {
                    menu(p1, 1, objectList);
                    wmove(win, 0 ,0);
                    wclrtoeol(win);
                    printGrid(grid, p1, monsterList, win, *winy, *winx, objectList); //update the grid based on look mode or movement
                    wrefresh(win);
                    
                }
                else if(ch == 'w')
                {
                    menu(p1, 3, objectList);
                    wmove(win, 0 ,0);
                    wclrtoeol(win);
                    printGrid(grid, p1, monsterList, win, *winy, *winx, objectList); //update the grid based on look mode or movement
                    wrefresh(win);
                    
                }
                else if(ch == 't')
                {
                    menu(p1, 2, objectList);
                    wmove(win, 0 ,0);
                    wclrtoeol(win);
                    printGrid(grid, p1, monsterList, win, *winy, *winx, objectList); //update the grid based on look mode or movement
                    wrefresh(win);
                    
                }
                else if(ch == 'd')
                {
                    menu(p1, 4, objectList);
                    wmove(win, 0 ,0);
                    wclrtoeol(win);
                    printGrid(grid, p1, monsterList, win, *winy, *winx, objectList); //update the grid based on look mode or movement
                    wrefresh(win);
                    
                }
                else if(ch == 'x')
                {
                    menu(p1, 5, objectList);
                    wmove(win, 0 ,0);
                    wclrtoeol(win);
                    printGrid(grid, p1, monsterList, win, *winy, *winx, objectList); //update the grid based on look mode or movement
                    wrefresh(win);
                    
                }
                else if(ch == 'I')
                {
                    menu(p1, 6, objectList);
                    wmove(win, 0 ,0);
                    wclrtoeol(win);
                    printGrid(grid, p1, monsterList, win, *winy, *winx, objectList); //update the grid based on look mode or movement
                    wrefresh(win);
                    
                }
                else if(ch == 'r')
                {
                    ranged_attack(p1, win, monsterList, *winx, *winy, grid);
                    wmove(win, 0 ,0);
                    wclrtoeol(win);
                    printGrid(grid, p1, monsterList, win, *winy, *winx, objectList); //update the grid based on look mode or movement
                    wrefresh(win);
                    
                }
                else if(ch == 'a')
                {
                    recovery(p1);
                    wmove(win, 0 ,0);
                    wclrtoeol(win);
                    printGrid(grid, p1, monsterList, win, *winy, *winx, objectList); //update the grid based on look mode or movement
                    wrefresh(win);
                    
                }
                else if(ch == 'v')
                {
                    wmove(win, 22, 0);
                    wclrtoeol(win);
                    wmove(win, 23, 0);
                    wclrtoeol(win);
                
                    mvwprintw(win, 22, 2, "Current HP:  %d", p1.getHP());
 
                   
                    printGrid(grid, p1, monsterList, win, *winy, *winx, objectList); //update the grid based on look mode or movement
                    wrefresh(win);
                    
                }


                else
                {
                    mvwprintw(win, 0, 0, "Wrong key                                                ");
                    
                }
                
            }
            
        }
        
        printGrid(grid, p1, monsterList, win, *winy, *winx, objectList); //update the grid based on look mode or movement
        wrefresh(win);
        
        
    }while(mode == 0); //loop runs again if the user decides to enter look mode
 
    return 1;
    
    
    
}











void monster_move(dungeonGrid **grid, player &p1, monster &m, int parent[],  WINDOW *win)
{
    //check for LOS
    if(grid[m.posY()][ m.posX()].cell == '.') //monster is in a room so LOS is applicable
    {
        //find the four edges
        int top, bottom, left, right;
        top = m.posY();
        bottom = m.posY();
        right = m.posX();
        left = m.posX();
        
        while(grid[bottom - 1][m.posX()].cell != ' ' && grid[bottom - 1][m.posX()].cell != '#')
        {
            bottom--;
        }
        
        while(grid[top + 1][m.posX()].cell != ' ' && grid[top + 1][m.posX()].cell != '#')
        {
            top++;
        }
        
        while(grid[m.posY()][left - 1].cell != ' ' && grid[m.posY()][left - 1].cell != '#')
        {
            left--;
        }
        
        while(grid[m.posY()][right + 1].cell != ' ' && grid[m.posY()][right + 1].cell != '#')
        {
            right++;
        }

        
        //run through the room in a nested loop looking for pc
        
        for(int i = top; i < bottom + 1; i++)
        {
            for(int j = left; j < right + 1; j++)
            {
                if(i == p1.posY() && j == p1.posX()) //if found in room update monsters last known
                {
                    m.setpcX(  p1.posX());
                    m.setpcY(  p1.posY());
                }
            }
        }
        
    }
    
    //end LOS check
    
    int chance = 0; //will always equal 0 for non erratics
    //movement structure for monsters
    
    if(CHECK_BIT(m.getCharacter(), 3) == 8) //if a monster has an erratic characteristic
    {
        chance = rand() % 2;
    }
    
    
    if(chance == 0) //will always run for non erratics
        //order: telepathic - intelligent - tunnel
    {
        if(CHECK_BIT(m.getCharacter(), 1) == 2) //if telepathic
        {
            telepathic(m, p1);
        }
        
        
        if(CHECK_BIT(m.getCharacter(), 0) == 1 && CHECK_BIT(m.getCharacter(), 2) == 4) //checks for intelligent and tunneler
        {
            intelligent(grid, m, p1, parent, win); //runs both the intelligent and tunneler function
        }
        else if(CHECK_BIT(m.getCharacter(), 0) == 0 && CHECK_BIT(m.getCharacter(), 2) == 4) //checks for just tunnel with no intelligence
        {
                int tunX = m.posX();
                int tunY = m.posY();
                
                if(m.pcposX() > m.posX())
                {
                    if(grid[m.posY()][ m.posX() + 1].hardness != 255)
                    {
                        tunX++;
                    }
                }
                else if(m.pcposX() < m.posX())
                {
                    if(grid[m.posY()][ m.posX() - 1].hardness != 255)
                    {
                        tunX--;
                    }
                }
                else
                {
                    if(m.pcposY() > m.posY())
                    {
                        if(grid[m.posY() + 1][ m.posX()].hardness != 255)
                        {
                            tunY++;
                        }
                    }
                    else if(m.pcposY() < m.posY())
                    {
                        if(grid[m.posY() - 1][ m.posX()].hardness != 255)
                        {
                            tunY--;
                        }
                    }
                    
                }

                tunnel(grid, m, tunX, tunY, p1, win);
            
        }
        
        else //for monsters with no tunneling or intelligence
            //move in straight line towards visible pc or some random direction
        {
           
            if(m.pcposX() > m.posX())
            {
                if(grid[m.posY()][ m.posX() + 1].cell != ' ')
                {
                    if(p1.posX() == ( m.posX() + 1 ) &&
                       p1.posY() == ( m.posY() )  )
                    {
                        attack(p1, m, 1, win);
                    }
                    else
                    {
                        m.setX( m.posX() + 1);
                    }
                }
            }
            else if(m.pcposX() < m.posX())
            {
                if(grid[m.posY()][ m.posX() - 1].cell != ' ')
                {
                    if(p1.posX() == ( m.posX() - 1 ) &&
                       p1.posY() == ( m.posY() )  )
                    {
                        attack(p1, m, 1, win);
                    }
                    else
                    {
                        m.setX( m.posX() - 1);
                    }
                }
            }
            else
            {
                    if(m.pcposY() > m.posY())
                    {
                        if(grid[m.posY() + 1][ m.posX()].cell != ' ')
                        {
                            if(p1.posX() == ( m.posX() ) &&
                               p1.posY() == ( m.posY() + 1 )  )
                            {
                                attack(p1, m, 1, win);
                            }
                            else
                            {
                                m.setY( m.posY() + 1);
                            }
                        }
                    }
                    else if(m.pcposY() < m.posY())
                    {
                        if(grid[m.posY() - 1][ m.posX()].cell != ' ')
                        {
                            if(p1.posX() == ( m.posX() ) &&
                               p1.posY() == ( m.posY() - 1 )  )
                            {
                                attack(p1, m, 1, win);
                            }
                            else
                            {
                                m.setY( m.posY() - 1);
                            }
                        }
                    }

            }
            
            //unintelligent monsters will move randomly if they lose their LOS on a player
            m.setpcY( rand() % 102 + 2);
            m.setpcX( rand() % 157 + 2);
            
            
        }
        
    }
    
    else //erratic behavior, move to random cell
    {
        if(CHECK_BIT(m.getCharacter(), 2) == 4)
        {
            int move = rand() % 8; //can move in one of 8 directions
            
            int tunX = m.posX();
            int tunY = m.posY();

            
            switch(move)
            {
                case 0 : //move up
                    if(grid[m.posY() - 1][ m.posX()].hardness != 255)
                    {
                        tunY--;
                    }
                    break;
                case 1 : //move right
                    if(grid[m.posY()][ m.posX() + 1].hardness != 255)
                    {
                        tunX++;
                    }
                    break;
                case 2 : //move down
                    if(grid[m.posY() + 1][ m.posX()].hardness != 255)
                    {
                        tunY++;
                    }
                    break;
                case 3 : //move left
                    if(grid[m.posY()][ m.posX() - 1].hardness != 255)
                    {
                        tunX--;
                    }
                case 4 : //move upper left
                    if(grid[m.posY() - 1][ m.posX() - 1].hardness != 255)
                    {
                        tunX--;
                        tunY--;
                    }
                    break;
                case 5 : //move upper right
                    if(grid[m.posY() - 1][ m.posX() + 1].hardness != 255)
                    {
                        tunX++;
                        tunY--;
                    }
                case 6 : //move lower right
                    if(grid[m.posY() + 1][ m.posX() + 1].hardness != 255)
                    {
                        tunY++;
                        tunX++;
                    }
                    break;
                case 7 : //move lower left
                    if(grid[m.posY() + 1][ m.posX() - 1].hardness != 255)
                    {
                        tunX--;
                        tunY++;
                    }
                    break;
               
            }
            
            tunnel(grid, m, tunX, tunY, p1, win);

        }
        else
        {
            int move = rand() % 8; //can move in one of 8 directions
            
            switch(move)
            {
                case 0 : //move up
                    if(grid[m.posY() - 1][ m.posX()].cell != ' ')
                    {
                        if(p1.posX() == ( m.posX() ) &&
                           p1.posY() == ( m.posY() - 1 )  )
                        {
                            attack(p1, m, 1, win);
                        }
                        else
                        {
                            m.setY( m.posY() - 1);
                        }
                    }
                    break;
                case 1 : //move right
                    if(grid[m.posY()][ m.posX() + 1].cell != ' ')
                    {
                        if(p1.posX() == ( m.posX() + 1 ) &&
                           p1.posY() == ( m.posY() )  )
                        {
                            attack(p1, m, 1, win);
                        }
                        else
                        {
                            m.setX( m.posX() + 1);
                        }
                    }
                    break;
                case 2 : //move down
                    if(grid[m.posY() + 1][ m.posX()].cell != ' ')
                    {
                        if(p1.posX() == ( m.posX() ) &&
                           p1.posY() == ( m.posY() + 1 )  )
                        {
                            attack(p1, m, 1, win);
                        }
                        else
                        {

                            m.setY( m.posY() + 1);
                        }
                    }
                    break;
                case 3 : //move left
                    if(grid[m.posY()][ m.posX() - 1].cell != ' ')
                    {
                        if(p1.posX() == ( m.posX() - 1 ) &&
                           p1.posY() == ( m.posY() )  )
                        {
                            attack(p1, m, 1, win);
                        }
                        else
                        {

                            m.setX( m.posX() - 1);
                        }
                    }
                case 4 : //move upper left
                    if(grid[m.posY() - 1][ m.posX() - 1].cell != ' ')
                    {
                        if(p1.posX() == ( m.posX() - 1 ) &&
                           p1.posY() == ( m.posY() - 1 )  )
                        {
                            attack(p1, m, 1, win);
                        }
                        else
                        {

                        m.setX( m.posX() - 1);
                        m.setY( m.posY() - 1);
                            
                        }
                    }
                    break;
                case 5 : //move upper right
                    if(grid[m.posY() - 1][ m.posX() + 1].cell != ' ')
                    {
                        if(p1.posX() == ( m.posX() + 1) &&
                           p1.posY() == ( m.posY() - 1 )  )
                        {
                            attack(p1, m, 1, win);
                        }
                        else
                        {

                        m.setX( m.posX() + 1);
                        m.setY( m.posY() - 1);
                            
                        }
                    }
                case 6 : //move lower right
                    if(grid[m.posY() + 1][ m.posX() + 1].cell != ' ')
                    {
                        if(p1.posX() == ( m.posX() + 1) &&
                           p1.posY() == ( m.posY() + 1 )  )
                        {
                            attack(p1, m, 1, win);
                        }
                        else
                        {

                        m.setY( m.posY() + 1);
                        m.setX( m.posX() + 1);
                            
                        }
                    }
                    break;
                case 7 : //move lower left
                    if(grid[m.posY() + 1][ m.posX() - 1].cell != ' ')
                    {
                        if(p1.posX() == ( m.posX() - 1) &&
                           p1.posY() == ( m.posY() + 1 )  )
                        {
                            attack(p1, m, 1, win);
                        }
                        else
                        {

                        m.setX( m.posX() - 1);
                        m.setY( m.posY() + 1);
                            
                        }
                    }
                    break;
                
            }

        }
        
        
        
    }

}




void telepathic(monster &m, player &p1) //update the monsters whereabouts of the PC with PC's current position
{
    m.setpcX( p1.posX());
    m.setpcY( p1.posY());
}



void tunnel(dungeonGrid **grid, monster &m, int x, int y, player &p1,  WINDOW *win)
//tunnels through the given cell and replaces that cell with a corridor character
// if its hardness reaches 0
{
    if(grid[y][x].hardness == 0)
    {
        if(p1.posX() == x  &&
           p1.posY() == y  )
        {
            attack(p1, m, 1, win);
        }
        else
        {
            m.setY( y);
            m.setX( x);
        }
    }
    else if((grid[y][x].hardness - 85) < 0)
    {
        //create new corridor cell if the rock is completely tunneled
        grid[y][x].hardness = 0;
         grid[y][x].cost = 1;
        grid[y][x].cell = '#';
        m.setX( x);
        m.setY( y);
    }
    else
    {
        grid[y][x].hardness = grid[y][x].hardness - 85;
        grid[y][x].cost =  grid[y][x].cost - 1;
        
    }
    
}



void intelligent(dungeonGrid **grid, monster &m, player &p1, int parent[],  WINDOW *win) //moves towards position using
//shortest path algorithm
{
    int pos = (m.posY() * 160) + m.posX(); //1D position of monster
    int move = parent[pos];
    
    
    if(CHECK_BIT(m.getCharacter(), 2) == 4) //if it is an intelligent tunneler, it'll use its tunnel function
    {
        tunnel(grid, m, (move % 160),(move / 160), p1, win);
    }
    else //for all non tunnelers
    {
        if(p1.posX() == ( move % 160 ) &&
           p1.posY() == ( move / 160 )  )
        {
            attack(p1, m, 1, win);
        }
        else
        {
                m.setY( move / 160);
                m.setX( move % 160);
        }
    }
}










