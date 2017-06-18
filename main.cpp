//
//  main.c
//  
//
//  Created by Kyle Kempt on 2/3/17.
//
//

#include "dungeon.h"


//use new windows to give menus for inventory and equpiment!!



int main(int argc, char *argv[])
{
   
  initscr();
    
    clear();
    noecho();
    cbreak();
    nonl();
    start_color();
    
    
    srand(time(NULL));
    int rooms = 10 + rand() % (14 - 10);
    int save = 0;
    int load = 0;
    int nummon = 0;
    int stairs;
    int* s_ptr;
    
    //+++Command Line argument section
    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "--save") == 0)
        {
            printf("Save dungeon activated\n");
            save = i;
        }
        else if(strcmp(argv[i], "--load") == 0)
        {
            printf("Load dungeon activated\n");
            load = i;
        }
        else if(strcmp(argv[i], "--nummon") == 0)
        {
            printf("Enter the number of monsters: ");
            scanf("%d", &nummon);
        }
        
    }
    
   
    //+++

    if(nummon == 0)
    {
        nummon = 1;
    }

    
    
    //+++Struct declarations
    dungeonGrid **grid = (dungeonGrid **) malloc(Y * sizeof(dungeonGrid *));
    int i;
    for(i = 0; i < Y; i++)
    {
        grid[i] = (dungeonGrid *) malloc(X * sizeof(dungeonGrid));
    }
    roomData *rd = (roomData *) malloc(rooms * sizeof(roomData));
 
    player p1;
    p1.setSpeed(10);
    p1.setAlive(1);
    p1.setHP(200);
    
    
    vector<dungeonObjects> objectList;
    
    dungeonObjects object;
    
    if(item_parse(objectList, object) == 1)
    {
        endwin();
        cout << "Wrong item parse file" << endl;
        return 0;
    }
    
    monster m1;
    vector<monster> monsterList;
    
    if(monster_parse(monsterList, m1, nummon) == 1)
    {
        endwin();
        cout << "Wrong monster parse file" << endl;
        return 0;
    }
    
    
    
    
    
    
    
    
    

    do{
        stairs = 0;
        
        p1.resetMem();
        
        if(load == 1)
        {
            if(!loadDungeon(grid, dungeonFile(), rd))
            {
                printf("Dungeon Loaded\n");
            }
            else
            {
                printf("Dungeon Load Error\n Exiting program...\n");
                return 0;
                
            }
        }
        else //if load isn't called in the command line
        {
            create_blankGrid(grid);
            room_generator(grid, rooms, rd);
            path_generator(grid, rooms);
            
            //place PC somewhere on the grid//
            
            
            
            int k = 0;
            while(k == 0)
            {
                int x2 = 1 + rand() % (X - 1); //starting point on x-axis
                int y2 = 1 + rand() % (Y - 1); //starting point on y-axis
                if(grid[y2][x2].cell == '.')
                {
                    p1.setX(x2);
                    p1.setY(y2);
                    k++;
                }
            }
            
        }
        
        
         //+++Monster Creation
        
        
        for(unsigned int i = 0; i < monsterList.size(); i++)
        {
                monsterList[i].setAlive(1);
                
                //assumption that PC is somewhere in the middle of the map at the beginning
                monsterList[i].setpcX(80);
                monsterList[i].setpcY(55);
                monsterList[i].setCharacter();
            
                if(CHECK_BIT(monsterList[i].getCharacter(), 2) == 4)
                {
                    do
                    {
                        monsterList[i].setX( rand() % 159 + 1);
                        monsterList[i].setY( rand() % 104 + 1);
                    } while((  monsterList[i].posX() == p1.posX() && monsterList[i].posY() == p1.posY()  )
                            && (  grid[monsterList[i].posY()][monsterList[i].posX()].cell == '.'));
                    
                    grid[monsterList[i].posY()][monsterList[i].posX()].cell = '#';
                    grid[monsterList[i].posY()][monsterList[i].posX()].hardness = 0;
                    grid[monsterList[i].posY()][monsterList[i].posX()].cost = 1;

                }
                else
                {
                    do
                    {
                        int r = rand() % rooms; //pick a random room for non tun monster to be placed in
                        monsterList[i].setX( rd[r].x_start + (rand() % rd[r].x_width));
                        monsterList[i].setY( rd[r].y_start + (rand() % rd[r].y_height));
                    } while(monsterList[i].posX() == p1.posX() && monsterList[i].posY() == p1.posY());
                    
                }
            
        }
        
        
        
        for(unsigned int i = 0; i < objectList.size(); i++)
        {
            objectList[i].set_symbol();

            int x, y;
            do
            {
                int r = rand() % rooms; //pick a random room for non tun monster to be placed in
                x =  rd[r].x_start + (rand() % rd[r].x_width);
                y =  rd[r].y_start + (rand() % rd[r].y_height);
            } while(x == p1.posX() && y == p1.posY());
            objectList[i].setPosXY(x,y);
            

        }
        
        
        
        //+++

        s_ptr = &stairs;
        
       
        
        

   game(grid, rd, p1, monsterList, rooms, s_ptr, objectList);
        
        
        
    }while(*s_ptr == 1);
    
  
    if(save == 1 || save == 2) //if save is the first or second parameter in the command line
    {
        if(!saveDungeon(grid, rd, dungeonFile(), rooms))
        {
            printf("Dungeon Saved\n");
        }
        else
        {
            printf("Dungeon Save Error\n");
            
        }
    }
    
    
    if(load == 2) //if load is the second parameter in the command line
    {
        if(!loadDungeon(grid, dungeonFile(), rd))
        {
            printf("Dungeon Loaded\n");
            
        }
        else
        {
            printf("Dungeon Load Error\n Exiting program...\n");
            return 0;
            
        }
        
    }
      endwin();
 
    

    
    
    vector<dungeonObjects>().swap(objectList); //frees up the memory

    
    vector<monster>().swap(monsterList); //frees up memory
    
    free(rd);
    
    
    
    for(i = 0; i < Y; i++)
    {
        free(grid[i]);
    }
    free(grid);
    return 0;
}

