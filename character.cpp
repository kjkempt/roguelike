//
//  character.cpp
//  
//
//  Created by Kyle Kempt on 3/14/17.
//
//


#include "dungeon.h"











//class accessors

character::character(void)
{
    //constructor
}

player::player(void)
{
    for(int i = 0; i < 105; i++)
    {
        for(int j = 0; j < 160; j++)
        {
            grid[i][j] = 0; //0 means the player can't see this cell
            memory[i][j] = ' '; //empty memory of dungeon
        }
    }
}

monster::monster(void)
{
    characteristic = 0;
}

int character::posX()
{
    return position_x;
}

int character::posY()
{
    return position_y;

}

int character::getAlive()
{
    return alive;

}

void character::setHP(signed int h)
{
    hp = h;
}

signed int character::getHP()
{
    return hp;
}

unsigned int character::getSpeed()
{
    return speed;

}

void character::decHP(signed int h)
{
    hp = hp - h;
}



void character::setX(int d)
{
    position_x = d;
}

void character::setY(int d)
{
    position_y = d;
}

void character::setAlive(int d)
{
    alive = d;
}

void character::setSpeed(unsigned int d)
{
    speed = d;
}

void player::setSight(int d)
{
    sight = d;
}

void player::setView(int x, int y, int d)
{
    grid[y][x] = d;
}

void player::setMemory(int x, int y, char d)
{
    memory[y][x] = d;
}






int player::getSight()
{
    return sight;

}

int player::getView(int x, int y)
{
    return grid[y][x];
}

char player::getMemory(int x, int y)
{
    return memory[y][x];
}

void player::resetMem()
{
    for(int i = 0; i < 105; i++)
    {
        for(int j = 0; j < 160; j++)
        {
            grid[i][j] = 0; //0 means the player can't see this cell
            memory[i][j] = ' '; //empty memory of dungeon
        }
    }
}

int player::barehandDamage() //barehand damage dice 1d4, no base damage
{
    return (rand() % 4 + 1);
}

dungeonObjects player::setEquipment(dungeonObjects e)
{
    dungeonObjects swap;
    string token = e.get_type();
    
    if(token.find("WEAPON") != string::npos)
    {
        swap = equipment[0];
        equipment[0] = e;
    }
    else if(token.find("OFFHAND") != string::npos)
    {
        swap = equipment[1];

        equipment[1] = e;
        
    }
    else if(token.find("RANGED") != string::npos || token.find("BOOK") != string::npos)
    {
        swap = equipment[2];

        equipment[2] = e;
        
    }
    else if(token.find("ARMOR") != string::npos)
    {
        swap = equipment[3];

        equipment[3] = e;
        
    }
    else if(token.find("HELMET") != string::npos)
    {
        swap = equipment[4];

        equipment[4] = e;
        
    }
    else if(token.find("CLOAK") != string::npos)
    {
        swap = equipment[5];

        equipment[5] = e;
        
    }
    else if(token.find("GLOVES") != string::npos)
    {
        swap = equipment[6];

        equipment[6] = e;
        
    }
    else if(token.find("BOOTS") != string::npos)
    {
        swap = equipment[7];

        equipment[7] = e;
        
    }
    else if(token.find("AMULET") != string::npos)
    {
        swap = equipment[8];

        equipment[8] = e;
        
    }
    else if(token.find("LIGHT") != string::npos)
    {
        swap = equipment[9];

        equipment[9] = e;
        
    }
    else if(token.find("RING") != string::npos)
    {
        if(equipment[10].get_name().empty()) //if this ring is empty fill it, if not fill the other
        {
            swap = equipment[10];

            equipment[10] = e;
        }
        else
        {
            swap = equipment[11];

            equipment[11] = e;

        }
        
    }
    
    
    return swap;
}

dungeonObjects player::getEquipment(int i)
{
    
    return equipment[i];
    
}

int player::setInventory(dungeonObjects d)
{
    for(int i = 0; i < 10; i++)
    {
        if(inventory[i].get_name().empty())
        {
            inventory[i] = d;
            return 1;
        }
    }
    return 0;
}

dungeonObjects player::getInventory(int i)
{
    return inventory[i];
}

void player::attachEquipment(int i)
{
    
    dungeonObjects swap = setEquipment(inventory[i]);
    inventory[i] = swap;
}

void player::takeEquipmentOff(int i)
{
    if(checkFull() == 1)
    {
        setInventory(equipment[i]);
        dungeonObjects blank;
        equipment[i] = blank;
    }
    else
    {
        WINDOW * full = newwin(24, 80, 0, 0);
        keypad(full, TRUE);
        
        mvwprintw(full, 4, 5, "ERR: Inventory is full");
        
        wrefresh(full);
        
        int ch = wgetch(full);
        
        if(ch == 'd')
        {
            
        }

        
        delwin(full);
    }
}

int player::checkFull()
{
    for(int i = 0; i < 10; i++)
    {
        if(inventory[i].get_name().empty())
        {
            return 1;
        }
    }
    return 0;

}

void player::drop(int num, vector<dungeonObjects> & objectList)
{
    for(unsigned int i = 0; i < objectList.size(); i++) //check to see if an object was dropped on the ground already
        //or if the inventory is full and an item cannot be picked up
    {
            if(objectList[i].posX() == posX() && objectList[i].posY() == posY())
            {
                WINDOW * drop = newwin(24, 80, 0, 0);
                keypad(drop, TRUE);
                
                mvwprintw(drop, 4, 5, "ERR: Item on the ground");
                
                wrefresh(drop);
                
                int ch = wgetch(drop);
                
                if(ch == 'd')
                {
                    
                }
                
                
                delwin(drop);

                
                return;
            }
    }
    if(inventory[num].get_name().empty())
    {
            WINDOW * drop = newwin(24, 80, 0, 0);
            keypad(drop, TRUE);
            
            mvwprintw(drop, 4, 5, "ERR: No item in inventory slot");
            
            wrefresh(drop);
            
            int ch = wgetch(drop);
            
            if(ch == 'd')
            {
                
            }
            
            
            delwin(drop);
            
            
            return;
    }
    else
    {
            inventory[num].set_drop();
            inventory[num].setPosXY(posX(), posY()); //change the objects position to equal that of the players
            objectList.push_back(inventory[num]);
            dungeonObjects blank;
            inventory[num] = blank;
    }
    
}

void player::deleteItem(int num)
{
    dungeonObjects blank;
    inventory[num] = blank;
}

void player::inspectItem(int num)
{
    WINDOW * menu = newwin(24, 80, 0, 0);
    keypad(menu, TRUE);
    
    char output[80];
    
    mvwprintw(menu, 0, 2, "--DESCRIPTION--");
    
    for(int i = 0; i < inventory[num].desc_size(); i++)
    {
        
        string s = inventory[num].desc_line();
        if(s.empty())
        {
            s = "Empty";
            strcpy(output, s.c_str());
        }
        else
        {
            strcpy(output, s.c_str());
        }
        mvwprintw(menu, i + 1, 2, "%s", output);
    }
    wrefresh(menu);
    
    
    int ch = wgetch(menu);
    if(ch == '1')
    {
        
    }

    delwin(menu);
}



int player::rollEquipmentDamage(int e) //outputs damage of equipment e
{
    int totalRoll = 0;
    
    if(equipment[e].get_name().empty()) //nothing equppied in this slpt
    {
        return 0;
    }
    else
    {
        for(int i = 0; i < equipment[e].get_dam_dice(); i++)
        {
            totalRoll = totalRoll + (rand() % equipment[e].get_dam_sides() + 1); //the dice is rolled dice times and the value
            //is accumulated within the loop;
        }
        
        return (equipment[e].get_dam_base() + totalRoll);
    }
}

void player::updateSpeed()
{
    int totalSpeed = 0;
    
    for(int e = 0; e < 12; e++)
    {
            if(equipment[e].get_name().empty()) //nothing equppied in this slot
            {}
            else
            {
                totalSpeed = totalSpeed + equipment[e].get_speed();
            }
    }

    setSpeed(totalSpeed + 10); //accumulated speed from equipment + base player speed
}

void player::recoveryItem(int num)
{
    string token;
    signed int health_gained = 0;
    signed int current_health = getHP();
    token = inventory[num].get_type();
    if(token.find("FOOD") != string::npos)
    {
        for(int i = 0; i < inventory[num].get_dam_dice(); i++)
        {
            health_gained = health_gained + (rand() % inventory[num].get_dam_sides() + 1); //the dice is rolled dice times and the value
            //is accumulated within the loop;
        }
        
        health_gained = health_gained + inventory[num].get_dam_base();
        
        current_health = health_gained + current_health;
        
        setHP(current_health); //sets HP, can go past initial health pool since food will be fairly scarce
        
        dungeonObjects blank;
        inventory[num] = blank;
        
    }
}











char monster::returnChar()
{
    return type;
}
int monster::pcposX()
{
    return pc_pos_x;

}
int monster::pcposY()
{
    return pc_pos_y;

}
int monster::getLOS()
{
    return LOS;

}
int monster::getCharacter()
{
    return characteristic;

}





void monster::setChar(char d)
{
    type = d;
}

void monster::setpcX(int d)
{
    pc_pos_x = d;
}

void monster::setpcY(int d)
{
    pc_pos_y = d;
}

void monster::setLOS(int d)
{
    LOS = d;
}

void monster::setCharacter()
{
    string delimit = " ";
    string temp = characteristicWords;
    size_t pos = 0;
    string token;
    while ((pos = temp.find(delimit)) != string::npos) {
        token = temp.substr(0, pos);
        
        
            if(token.find("SMART") != string::npos)
        {
            //intel = 1;
            TOGGLE_BIT(characteristic, 0, 1);
        }
        
        if(token.find("TELE") != string::npos)
        {
            //tele = 1;
            TOGGLE_BIT(characteristic, 1, 1);
            
        }
        
        if(token.find("TUNNEL") != string::npos)
        {
            //tun = 1;
            TOGGLE_BIT(characteristic, 2, 1);
            
            
        }
        
        if(token.find("ERRATIC") != string::npos)
        {
            // err = 1;
            TOGGLE_BIT(characteristic, 3, 1);
            
        }
    

        
        
        
        temp.erase(0, pos + delimit.length());
    }
    
    
    token = temp;
    if(token.find("SMART") != string::npos)
    {
        //intel = 1;
        TOGGLE_BIT(characteristic, 0, 1);
    }
    
    if(token.find("TELE") != string::npos)
    {
        //tele = 1;
        TOGGLE_BIT(characteristic, 1, 1);
        
    }
    
    if(token.find("TUNNEL") != string::npos)
    {
        //tun = 1;
        TOGGLE_BIT(characteristic, 2, 1);
        
        
    }
    
    if(token.find("ERRATIC") != string::npos)
    {
        // err = 1;
        TOGGLE_BIT(characteristic, 3, 1);
        
    }
    
}



void monster::createMonsterInstance( int speedX, int colorX, int damBASEX,
                                    int damDICEX, int damSIDESX, int hpX,
                                    string nameX, char symbol, string abilities)
{
    setSpeed(speedX);
    color = colorX;
    damBASE = damBASEX;
    damSIDES = damSIDESX;
    damDICE = damDICEX;
    setHP(hpX);
    name = nameX;
    type = symbol;
    characteristicWords = abilities;
}

string monster::get_name()
{
    return name;
}

void monster::push_desc(string str)
{
    desc.push_back(str);
}

int monster::get_color()
{
    return color;
}

int monster::rollAttack()
{
    int totalRoll = 0;
    for(int i = 0; i < damDICE; i++)
    {
        totalRoll = totalRoll + (rand() % damSIDES + 1); //the dice is rolled dice times and the value
        //is accumulated within the loop;
    }
    
    return (damBASE + totalRoll);
}











//Fog of War code


void fog_of_war(player& p1)
{
    //update the players view of the grid based on the Fog of War
    
    for(int i = 0; i < Y; i++)
    {
        for(int j = 0; j < X; j++)
        {
            if(p1.getView(j, i) == 1)
            {
                p1.setView(j, i, 2);
            }
             p1.setView(j, i, 1);
        }
    }
    
    
    
    
    int playerX = p1.posX();
    int playerY = p1.posY();
    int start_loop_x;
    int start_loop_y;
    int end_loop_x;
    int end_loop_y;
    
    if(playerX - 5 < 0) //light doesn't go past the dungeon borders on these set of if statements
    {
        start_loop_x = 0;
    }
    else{start_loop_x = playerX - 5;}
    
    if(playerX + 5 >= X)
    {
        end_loop_x = X - 1;
    }
    else{end_loop_x = playerX + 5;}
    
    if(playerY - 5 < 0) //light doesn't go past the dungeon borders on these set of if statements
    {
        start_loop_y = 0;
    }
    else{start_loop_y = playerY - 5;}
    
    if(playerY + 5 >= Y)
    {
        end_loop_y = Y - 1;
    }
    else{end_loop_y = playerY + 5;}
    
    
    for(int i = start_loop_y; i <= end_loop_y; i++)
    {
        for(int j = start_loop_x; j <= end_loop_x; j++)
        {
            p1.setView( j, i, 1);
        }
    }
    

}













//destructors

dungeonObjects::~dungeonObjects(void)
{
    
}

player::~player(void)
{

}

monster::~monster(void)
{
    
}















//++++++++++++++++++Code for dungeonObjects classes


dungeonObjects::dungeonObjects(void)
{
    //constructor
}


void dungeonObjects::createObjectInstance(int colorX,int hitX,int valX,int defX,int dodgeX,
                                          int weightX,int speedX,int attrX,int damDICEX,
                                        int damSIDESX,int damBASEX,string nameX, string typeX)
{
    color = colorX;
    hit = hitX;
    val = valX;
    def = defX;
    dodge = dodgeX;
    weight = weightX;
    speed = speedX;
    attr = attrX;
    damDICE = damDICEX;
    damSIDES = damSIDESX;
    damBASE = damBASEX;
    name = nameX;
    type = typeX;
    dropped = 0;
    desc_count = 0;
}

int dungeonObjects::get_hit()
{
    return hit;
}




void dungeonObjects::set_symbol()
{
    string token = type;
    
    if(token.find("WEAPON") != string::npos)
    {
        symbol = '|';
    }
    else if(token.find("OFFHAND") != string::npos)
    {
        symbol = ')';

    }
    else if(token.find("RANGED") != string::npos)
    {
        symbol = '}';

    }
    else if(token.find("ARMOR") != string::npos)
    {
        symbol = '[';

    }
    else if(token.find("HELMET") != string::npos)
    {
        symbol = ']';

    }
    else if(token.find("CLOAK") != string::npos)
    {
        symbol = '(';
        
    }
    else if(token.find("GLOVES") != string::npos)
    {
        symbol = '{';
        
    }
    else if(token.find("BOOTS") != string::npos)
    {
        symbol = '^';
        
    }
    else if(token.find("RING") != string::npos)
    {
        symbol = '=';
        
    }
    else if(token.find("AMULET") != string::npos)
    {
        symbol = '"';
        
    }
    else if(token.find("LIGHT") != string::npos)
    {
        symbol = '_';
        
    }
    else if(token.find("SCROLL") != string::npos)
    {
        symbol = '~';
        
    }
    else if(token.find("BOOK") != string::npos)
    {
        symbol = '?';
        
    }
    else if(token.find("FLASK") != string::npos)
    {
        symbol = '!';
        
    }
    else if(token.find("GOLD") != string::npos)
    {
        symbol = '$';
        
    }
    else if(token.find("AMMUNITION") != string::npos)
    {
        symbol = '/';
        
    }
    else if(token.find("FOOD") != string::npos)
    {
        symbol = ',';
        
    }
    else if(token.find("WAND") != string::npos)
    {
        symbol = '-';
        
    }
    else if(token.find("CONTAINER") != string::npos)
    {
        symbol = '%';
        
    }
    else if(token.find("STACK") != string::npos)
    {
        symbol = '&';
        
    }
    else
    {
        symbol = '*';
        
    }
 
}


int dungeonObjects::posX()
{
    return x1;
}


int dungeonObjects::posY()
{
    return y1;
    
}


void dungeonObjects::setPosXY(int x, int y)
{
    x1 = x;
    y1 = y;
}

char dungeonObjects::returnChar()
{
    return symbol;
}

void dungeonObjects::push_desc(string str)
{
    desc.push_back(str);
}

string dungeonObjects::desc_line()
{
    if(desc_count == desc.size())
    {
        desc_count = 0; //reset count if it equals size of vector
    }
    
    string temp;
    temp = desc[desc_count];
    desc_count++;
    
    return temp;
}

int dungeonObjects::desc_size()
{
    return desc.size();
}



int dungeonObjects::get_color()
{
    return color;
}

string dungeonObjects::get_name()
{
    return name;
}
string dungeonObjects::get_type()
{
    return type;
}

int dungeonObjects::check_drop()
{
    return dropped;
}

void dungeonObjects::set_drop()
{
    dropped = 1;
}
void dungeonObjects::dec_drop()
{
    dropped = 0;
}

int dungeonObjects::get_dam_dice()
{
    return damDICE;
}

int dungeonObjects::get_dam_sides()
{
    return damSIDES;
}

int dungeonObjects::get_dam_base()
{
    return damBASE;
}

int dungeonObjects::get_speed()
{
    return speed;
}




