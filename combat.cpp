//
//  combat.c
//  
//
//  Created by Kyle Kempt on 4/10/17.
//
//

#include "dungeon.h"


void menu(player& p1, int mode, vector<dungeonObjects> & objectList)
{
    /*mode inputs
     0 = list equipment
     1 = list inventory
     2 = take off an item
     3 = wear an item
     4 = drop an item from inventory
     5 = delete an item
     6 = inspect an item in inventory
     */
    WINDOW * menu = newwin(24, 80, 0, 0);
    keypad(menu, TRUE);
   
    
    if(mode == 0)
    {
        char output[80];
        
        char letter[] = "abcdefghijkl";
        
        mvwprintw(menu, 0, 2, "--Equipment--");
        
        for(int i = 0; i < 12; i++)
        {
            dungeonObjects e = p1.getEquipment(i);
            string s = e.get_name();
            if(s.empty())
            {
                s = "Empty";
                strcpy(output, s.c_str());
            }
            else
            {
                strcpy(output, s.c_str());
            }
            mvwprintw(menu, i + 1, 2, "%c - %s",letter[i], output);
        }
        wrefresh(menu);
        
        int ch = wgetch(menu);
         
        if(ch == 'd')
        {
            
        }
    }
    else if(mode == 1) //display inventory
    {
        char output[80];
        
        char number[] = "0123456789";
        
        mvwprintw(menu, 0, 2, "--Inventory--");
        
        for(int i = 0; i < 10; i++)
        {
            dungeonObjects e = p1.getInventory(i);
            string s = e.get_name();
            if(s.empty())
            {
                s = "Empty";
                strcpy(output, s.c_str());
            }
            else
            {
                strcpy(output, s.c_str());
            }
            mvwprintw(menu, i + 1, 2, "%c - %s",number[i], output);
        }
        wrefresh(menu);
        
        int ch = wgetch(menu);
        
        if(ch == 'd')
        {
            
        }
    }
    else if(mode == 2) //take off an item
    {
        char output[80];
        int choice = 12;
        char letter[] = "abcdefghijkl";
        
        mvwprintw(menu, 0, 2, "--Equipment--");
        
        for(int i = 0; i < 12; i++)
        {
            dungeonObjects e = p1.getEquipment(i);
            string s = e.get_name();
            if(s.empty())
            {
                s = "Empty";
                strcpy(output, s.c_str());
            }
            else
            {
                strcpy(output, s.c_str());
            }
            mvwprintw(menu, i + 1, 2, "%c - %s",letter[i], output);
        }
        wrefresh(menu);
        
        int ch = wgetch(menu);
        
        for(int i = 0; i < 12; i++)
        {
            if(ch == letter[i])
            {
                choice = i;
            }
        }
        
        if(choice != 12)
        {
            p1.takeEquipmentOff(choice);
        }
        
        
    }
    else if (mode == 3) //wear an item
    {
            char output[80];
            
            char number[] = "0123456789";
            
            mvwprintw(menu, 0, 2, "--Select an item to move to equipment--");
            
            for(int i = 0; i < 10; i++)
            {
                dungeonObjects e = p1.getInventory(i);
                string s = e.get_name();
                if(s.empty())
                {
                    s = "Empty";
                    strcpy(output, s.c_str());
                }
                else
                {
                    strcpy(output, s.c_str());
                }
                mvwprintw(menu, i + 1, 2, "%c - %s",number[i], output);
            }
            wrefresh(menu);
            
            int ch = wgetch(menu);
            if(ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' ||
               ch == '6' || ch == '7' || ch == '8' || ch == '9' || ch == '0')
            {
                int num = (int)((char)ch - '0');
                p1.attachEquipment(num);
            }
        
        

    }
    else if(mode == 4) //drop
    {
            char output[80];
            
            char number[] = "0123456789";
            
            mvwprintw(menu, 0, 2, "--SELECT AN ITEM TO DROP--");
            
            for(int i = 0; i < 10; i++)
            {
                dungeonObjects e = p1.getInventory(i);
                string s = e.get_name();
                if(s.empty())
                {
                    s = "Empty";
                    strcpy(output, s.c_str());
                }
                else
                {
                    strcpy(output, s.c_str());
                }
                mvwprintw(menu, i + 1, 2, "%c - %s",number[i], output);
            }
            wrefresh(menu);
            
            
            int ch = wgetch(menu);
            if(ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' ||
               ch == '6' || ch == '7' || ch == '8' || ch == '9' || ch == '0')
            {
                int num = (int)((char)ch - '0');
                p1.drop(num, objectList);
            }

    }
    else if(mode == 5) //delete an item forever from an inventory
    {
            char output[80];
            
            char number[] = "0123456789";
            
            mvwprintw(menu, 0, 2, "--SELECT AN ITEM TO DELETE FOREVER--");
            
            for(int i = 0; i < 10; i++)
            {
                dungeonObjects e = p1.getInventory(i);
                string s = e.get_name();
                if(s.empty())
                {
                    s = "Empty";
                    strcpy(output, s.c_str());
                }
                else
                {
                    strcpy(output, s.c_str());
                }
                mvwprintw(menu, i + 1, 2, "%c - %s",number[i], output);
            }
            wrefresh(menu);
            
            
            int ch = wgetch(menu);
            if(ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' ||
               ch == '6' || ch == '7' || ch == '8' || ch == '9' || ch == '0')
            {
                int num = (int)((char)ch - '0');
                p1.deleteItem(num);
            }
        
    }
    else if(mode == 6) //delete an item forever from an inventory
    {
        char output[80];
        
        char number[] = "0123456789";
        
        mvwprintw(menu, 0, 2, "--SELECT AN ITEM TO INSPECT--");
        
        for(int i = 0; i < 10; i++)
        {
            dungeonObjects e = p1.getInventory(i);
            string s = e.get_name();
            if(s.empty())
            {
                s = "Empty";
                strcpy(output, s.c_str());
            }
            else
            {
                strcpy(output, s.c_str());
            }
            mvwprintw(menu, i + 1, 2, "%c - %s",number[i], output);
        }
        wrefresh(menu);
        
        
        int ch = wgetch(menu);
        if(ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' ||
           ch == '6' || ch == '7' || ch == '8' || ch == '9' || ch == '0')
        {
            int num = (int)((char)ch - '0');
            p1.inspectItem(num);
        }
        
    }


    
    
    delwin(menu);
    
}



void attack(player& p1, monster& m, int aggressor,  WINDOW *win) //attack between a player and monster, agressor indicates if monster or
//player is attacking
{
    signed int attack_points = 0;
    
    if(aggressor == 0) //player is attacking
    {
        if(p1.getEquipment(0).get_name().empty()) //if the player does not have a weapon equipped
            //bare-hand is rolled for the weapon slot
        {
            attack_points = p1.barehandDamage();
        }
        else
        {
            attack_points = p1.rollEquipmentDamage(0);
        }
        
        for(int i = 1; i < 12; i++)
        {
            attack_points = attack_points + p1.rollEquipmentDamage(i);
        }
        
        m.decHP(attack_points);
        
        if(m.getHP() <= 0)
        {
            m.setAlive(0);
            mvwprintw(win, 22, 2, "Player landed an attack of %d             ", attack_points);
            mvwprintw(win, 23,  2, "Monster killed!                          " );
        }
        else
        {
            mvwprintw(win, 22, 2, "Player landed an attack of %d             ", attack_points);
            mvwprintw(win, 23,  2, "Monster's HP: %d                         ", m.getHP());
        }

        
        
    }
    else if(aggressor == 1)
    {
        attack_points = m.rollAttack();
        
        p1.decHP(attack_points);
        if(p1.getHP() <= 0)
        {
            p1.setAlive(0);
            mvwprintw(win, 22, 2, "Monster landed an attack of %d           ", attack_points);
            mvwprintw(win, 23,  2, "Player killed!                          ");
        }
        else
        {
            mvwprintw(win, 22, 2, "Monster landed an attack of %d           ", attack_points);
            mvwprintw(win, 23,  2, "Players's HP: %d                        ", p1.getHP());
        }
    }
    
}


void ranged_attack(player& p1, WINDOW *win, vector<monster> & monsterList, int winx, int winy, dungeonGrid **grid)
{
    //throwing range for weapons is within a 5x5 radius of the player's current position
    
    int select = 0;
    int attack_points = 0;
    int cursor_x = p1.posX() - winx;
    int cursor_y = p1.posY() - winy + 1;
    int player_x = p1.posX() - winx;
    int player_y = p1.posY() - winy + 1;
    
    mvwprintw(win, 22, 2, "Select a cell to attack (l-left/h-right/j-up/k-down)  ");
    mvwprintw(win, 23, 2, "Confirm the select with SPACE/cancel witn ESC    ");
    wmove(win, cursor_y, cursor_x);
 
    do{
        
        int ch = 0;
        
        ch = wgetch(win);
        
        if(ch == 27)
        {
            return;
        }
        else if(ch == 'l')
        {
            if(cursor_x + 1 < 80 && grid[cursor_y + winy - 1][cursor_x + winx + 1].cell != ' ')
            {
                if(cursor_x + 1 < player_x + 6)
                {
                cursor_x++;
                }
            }
            wmove(win, cursor_y, cursor_x);
        }
        else if(ch == 'h')
        {
            if(cursor_x - 1 > -1 && grid[cursor_y + winy - 1][cursor_x + winx - 1].cell != ' ')
            {
                if(cursor_x - 1 > player_x - 6)
                {
                cursor_x--;
                }
            }
            wmove(win, cursor_y, cursor_x);
        }
        else if(ch == 'j' )
        {
            if(cursor_y - 1 > 0 && grid[cursor_y + winy - 2][cursor_x + winx].cell != ' ')
            {
                if(cursor_y - 1 > player_y - 6)
                {
                cursor_y--;
                }
            }
            wmove(win, cursor_y, cursor_x);
        }
        else if(ch == 'k' && grid[cursor_y + winy][cursor_x + winx].cell != ' ')
        {
            if(cursor_y + 1 < 22)
            {
                if(cursor_y + 1 < player_y + 6)
                {
                cursor_y++;
                }
            }
            wmove(win, cursor_y, cursor_x);
        }
        else if(ch == ' ')
        {
            //selection confirmed, confirm if the target is there/what type
            //of ranged attack this is
            
            if(p1.getEquipment(2).get_type().find("RANGED") != string::npos)
            {
                wmove(win, 22, 0);
                wclrtoeol(win);
                mvwprintw(win, 22, 2, "Attack with a ranged weapon   %d      ", monsterList.size());
                
                
                
                for(unsigned int i = 0; i < monsterList.size(); i++)
                {
                    if(monsterList[i].posY() - (winy - 1) == cursor_y &&
                        monsterList[i].posX() - winx == cursor_x  )
                    {
                        //monster is damaged
                        //contact was made
                        
                        for(int j = 0; j < 12; j++)
                        {
                            attack_points = attack_points + p1.rollEquipmentDamage(j);
                        }
                        monsterList[i].decHP(attack_points);
                        
                        wmove(win, 22, 0);
                        wclrtoeol(win);
                        wmove(win, 23, 0);
                        wclrtoeol(win);

                        if(monsterList[i].getHP() <= 0)
                        {
                            monsterList[i].setAlive(0);
                            mvwprintw(win, 22, 2, "Player landed an attack of %d", attack_points);
                            mvwprintw(win, 23,  2, "Monster killed!" );
                        }
                        else
                        {
                            mvwprintw(win, 22, 2, "Player landed an attack of %d", attack_points);
                            mvwprintw(win, 23,  2, "Monster's HP: %d", monsterList[i].getHP());
                        }

                        return;

                    }
                    
                    
                }

            }
            else if(p1.getEquipment(2).get_type().find("BOOK") != string::npos)
            {
                wmove(win, 22, 0);
                wclrtoeol(win);
                mvwprintw(win, 22, 2, "Attack with a spellbook");
                
                int three_by_search_y = cursor_y - 3;
                int three_by_search_x = cursor_x - 3;
                int end_x = cursor_x + 3;
                int end_y = cursor_y + 3;

                if(three_by_search_x < 0)
                {
                    three_by_search_x = 0;
                }
                if (three_by_search_y < 0)
                {
                    three_by_search_y = 0;
                }
                if(end_x > 79)
                {
                    end_x = 79;
                }
                if(end_y > 21)
                {
                    end_y = 21;
                }
                
                
                /*
                 Search through a 3x3 grid around the selected point
                 effecting an AOE on every monster within the AOE.
                 All spells have same range and AOE of 3x3 but 
                 different spell books have varying damage
                 */
                
                for(int y = three_by_search_y; y <= end_y; y++)
                {
                    for(int x = three_by_search_x; x <= end_x; x++)
                    {
                        for(unsigned int i = 0; i < monsterList.size(); i++)
                        {
                            if(monsterList[i].posY() - (winy - 1) == y &&
                               monsterList[i].posX() - winx == x  )
                            {
                                //monster is damaged
                                //contact was made
                                
                                for(int j = 0; j < 12; j++)
                                {
                                    attack_points = attack_points + p1.rollEquipmentDamage(i);
                                }
                                monsterList[i].decHP(attack_points);
                                
                                wmove(win, 22, 0);
                                wclrtoeol(win);
                                wmove(win, 23, 0);
                                wclrtoeol(win);
                                
                                if(monsterList[i].getHP() <= 0)
                                {
                                    monsterList[i].setAlive(0);
                                    mvwprintw(win, 22, 2, "Player landed an attack of %d", attack_points);
                                    mvwprintw(win, 23,  2, "Monster killed!" );
                                }
                                else
                                {
                                    mvwprintw(win, 22, 2, "Player landed an attack of %d", attack_points);
                                    mvwprintw(win, 23,  2, "Monster's HP: %d", monsterList[i].getHP());
                                }
                                
                                
                            }
                        }
                    }
                }

                
                
            }
            
            
            
            
            select++;
        }
    
        
        
    }while(select == 0);

}

void recovery(player& p1) //player selects an item from the inventory that can be used for HP recovery
{
    WINDOW * menu = newwin(24, 80, 0, 0);
    keypad(menu, TRUE);

    
    
    char output[80];
    
    char number[] = "0123456789";
    
    mvwprintw(menu, 0, 2, "--Select a food item to recover HP--");
    
    for(int i = 0; i < 10; i++)
    {
        dungeonObjects e = p1.getInventory(i);
        string s = e.get_name();
        if(s.empty())
        {
            s = "Empty";
            strcpy(output, s.c_str());
        }
        else
        {
            strcpy(output, s.c_str());
        }
        mvwprintw(menu, i + 1, 2, "%c - %s",number[i], output);
    }
    wrefresh(menu);
    
    int ch = wgetch(menu);
    if(ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' ||
       ch == '6' || ch == '7' || ch == '8' || ch == '9' || ch == '0')
    {
        int num = (int)((char)ch - '0');
        p1.recoveryItem(num);
    }
    
    
    
    delwin(menu);


}













