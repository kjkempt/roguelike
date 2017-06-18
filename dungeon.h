//
//  dungeon.h
//  
//
//  Created by Kyle Kempt on 1/17/17.
//
//



#ifndef dungeon_h
#define dungeon_h




#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <new>
#include "main.h"
#include "game_priority_queue.h"
#include <unistd.h>
#include <stdlib.h> // rand() and srand()
#include <time.h> // srand(time(NULL));
#include <limits.h>
//#include <endian.h>
#include <stdint.h>
#include <unistd.h>
#include <ncurses.h>
#include <curses.h>
using namespace std;











#define X 160
#define Y 105
#define MAX 16800

//need macros for monster characteristics
#define NPC_NONE                            0x0         //0000
#define NPC_INT                             0x1         //0001
#define NPC_TEL                             0x2         //0010
#define NPC_INT_TEL                         0x3         //0011
#define NPC_TUN                             0x4         //0100
#define NPC_INT_TUN                         0x5         //0101
#define NPC_TEL_TUN                         0x6         //0110
#define NPC_INT_TEL_TUN                     0x7         //0111
#define NPC_ERA                             0x8         //1000
#define NPC_INT_ERA                         0x9         //1001
#define NPC_TEL_ERA                         0xa         //1010
#define NPC_INT_TEL_ERA                     0xb         //1011
#define NPC_TUN_ERA                         0xc         //1100
#define NPC_INT_TUN_ERA                     0xd         //1101
#define NPC_TEL_TUN_ERA                     0xe         //1110
#define NPC_ALL                             0xf         //1111


//macors for the colors ->not in numerical order
#define BLACK                               0x8
#define WHITE                               0x7
#define RED                                 0x1
#define BLUE                                0x4
#define GREEN                               0x2
#define CYAN                                0x6
#define MAGENTA                             0x5
#define YELLOW                              0x3




#define CHECK_BIT(var,pos) ((var) & (1<<(pos))) //found this off of stackoverflow.com
//at http://stackoverflow.com/questions/523724/c-c-check-if-one-bit-is-set-in-i-e-int-variable


#define TOGGLE_BIT(var, pos, x) (var = var ^ ((-x ^ var) & (1 << pos))) //found the algorithm on stackoverflow.com
//at http://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit-in-c-c
//and then I turned it into a macro

//number ^= (-x ^ number) & (1 << n);


class dungeonObjects
{
public:
    //method to create instances of this class
    void createObjectInstance(
                              int colorX,
                              int hitX,
                              int valX,
                              int defX,
                              int dodgeX,
                              int weightX,
                              int speedX,
                              int attrX,
                              int damDICEX,
                              int damSIDESX,
                              int damBASEX,
                              string nameX,
                              string typeX
                              );
    
    int get_hit();
    void setPosXY(int x, int y);
    int posX();
    int posY();
    char returnChar();
    string get_name();
    string get_type();
    void set_symbol();
    void push_desc(string str);
    string desc_line();
    int desc_size();
    int get_color();
    int check_drop();
    void set_drop();
    void dec_drop();
    int get_dam_dice();
    int get_dam_sides();
    int get_dam_base();
    int get_speed();
    dungeonObjects();
    ~dungeonObjects();
private:
    int x1;
    int y1;
    int color;
    int hit;
    int val;
    int def;
    int dodge;
    int weight;
    int speed;
    int attr;
    int damDICE;
    int damSIDES;
    int damBASE;
    string name;
    char symbol;
    string type;
    vector<string> desc;
    int dropped;
    unsigned int desc_count;
};




class character{
public:
    int posX();
    void setX(int d);
    int posY();
    void setY (int d);
    int getAlive();
    void setAlive(int d);
    unsigned int getSpeed();
    void setSpeed(unsigned int d);
    character();
    void setHP(signed int h);
    signed int getHP();
    void decHP(signed int h);
private:
    int position_x;
    int position_y;
    int alive;
    unsigned int speed;
    signed int hp;
};





class player: public character{
public:
    int getSight();
    void setSight(int d);
    int getView(int x, int y);
    void setView(int x, int y, int d);
    char getMemory(int x, int y);
    void setMemory(int x, int y, char d);
    void resetMem();
    int barehandDamage();
    dungeonObjects setEquipment(dungeonObjects e);
    dungeonObjects getEquipment(int i);
    int setInventory(dungeonObjects i);
    dungeonObjects getInventory(int d);
    void attachEquipment(int i);
    void takeEquipmentOff(int i);
    int checkFull();
    void drop(int num, vector<dungeonObjects> & objectList);
    void deleteItem(int num);
    void inspectItem(int num);
    int rollEquipmentDamage(int e);
    void updateSpeed();
    void recoveryItem(int num);
    
    player();
    ~player();
private:
    //array of equipment objects - size 12, pre-determined
    /*
     WEAPON - a
     OFFHAND - b
     RANGED - c
     ARMOR - d
     HELMET - e
     CLOAK - f
     GLOVES - g
     BOOTS - h
     AMULET - i
     LIGHT - j
     RING1 - k
     RING2 - l
     */
    dungeonObjects equipment[12];
    dungeonObjects inventory[10];
    int sight;
    int grid[105][160];
    char memory[105][160];
};





class monster: public character{
public:
    //need a function to create an instance of a monster
    //from the text file inserted
    void createMonsterInstance( int speedX, int colorX, int damBASEX,
                               int damDICEX, int damSIDESX, int hpX,
                               string nameX, char symbol, string abilities);
    void setChar(char d);
    char returnChar();
    int pcposX();
    void setpcX(int d);
    int pcposY();
    void setpcY(int d);
    int getLOS();
    void setLOS(int d);
    int getCharacter();
    void setCharacter();
    string get_name();
    void push_desc(string str);
    int get_color();
    int rollAttack();
    monster();
    ~monster();
private:
    char type;
    int pc_pos_x;       //either current known or last known position of PC
    int pc_pos_y;
    int LOS;            //line of sight switch on the PC
    int color;
    int characteristic;
    string characteristicWords;
    string name;
    int damDICE;
    int damSIDES;
    int damBASE;
    vector<string> desc;
};








typedef struct
{
    unsigned char hardness;   //hardness of rock [0 - 255]
    char cell;      //character that shows up on the game grid
    int room_number;    //puts a room number at the center of each room, used for the paths
    int cost;           //weighted cost of each space for Dijkstras
    int cellCount;
}dungeonGrid;

typedef struct
{
    uint8_t x_start;    //coordinate of top-left corner x
    uint8_t y_start;    //coordinate of top-left corner y
    uint8_t x_width;    //width of room
    uint8_t y_height;   //height of room
}roomData;


//This code is from Professor Scheaffer on the Discussion Board at
//https://bb.its.iastate.edu/webapps/discussionboard/do/message?action=list_messages&forum_id=_266142_1&nav=discussion_board_entry&conf_id=_180756_1&course_id=_59386_1&message_id=_2375833_1#msg__2375833_1Id
//I added the event type enum on my own





enum event_type
{
    e_pc,
    e_npc
};


typedef struct event{
    unsigned int time;
    enum event_type type;
    union {
        player *pc;
        monster *npc;
    } p;
} event ;

    
    //+++++++++In character.cpp


    

    void fog_of_war(player& p1);


    
    
    //++++++++++In dungeon.cpp

void create_blankGrid(dungeonGrid **grid);
void printGrid(dungeonGrid **grid,  player& p1,vector<monster> & monsterList,
            WINDOW *win, int winy, int winx, vector<dungeonObjects> & objectList);
void room_generator(dungeonGrid **grid, int rooms, roomData *rd);
void path_generator(dungeonGrid **grid, int rooms);
void connect(dungeonGrid **grid, int x1, int y1, int x2, int y2);


char* dungeonFile();
int saveDungeon(dungeonGrid **grid, roomData *rd, char* fileName, int rooms);
int loadDungeon(dungeonGrid **grid, char* fileName, roomData *rd);


void game(dungeonGrid **grid, roomData *rd, player& p1, vector<monster> & monsterList,
        int rooms, int *stairs, vector<dungeonObjects> & objectList);
int player_move(dungeonGrid **grid, player& p1, vector<monster> & monsterList,
                WINDOW *win, int *winx, int *winy, int *stairs, vector<dungeonObjects> & objectList);
void monster_move(dungeonGrid **grid, player& p1, monster& m, int parent[],  WINDOW *win);
void telepathic(monster& m, player& p1);
void tunnel(dungeonGrid **grid, monster& m, int x, int y, player &p1,  WINDOW *win);
void intelligent(dungeonGrid **grid, monster& m, player& p1, int parent[],  WINDOW *win);





//+++++++++in parse.cpp


int monster_parse(vector<monster> & monsterList, monster& m, int nummon);
int item_parse(vector<dungeonObjects> & objectList, dungeonObjects& objectInstance);
char* monsterFile();
char* objectFile();
int rollDice(int base, int dice, int sides);




//++++++++++in combat.cpp

void menu(player& p1, int mode, vector<dungeonObjects> & objectList);
void attack(player& p1, monster& m, int aggressor,  WINDOW *win);
void ranged_attack(player& p1, WINDOW *win, vector<monster> & monsterList, int winx, int winy, dungeonGrid **grid);
void recovery(player& p1);

#endif /* dungeon_h */
    
    
    
    

