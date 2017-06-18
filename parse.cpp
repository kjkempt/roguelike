//
//  parse.cpp
//  
//
//  Created by Kyle Kempt on 3/28/17.
//
//

#include "dungeon.h"

int monster_parse(vector<monster> & monsterList, monster& m, int nummon)
{
    
    ifstream f(monsterFile());
    int a = 0;
    int b = 0;
    int count = 0;
    
    string str;
    string name;
    string symb;
    string desc;
    string color;
    string speed;
    string abil;
    string hp;
    string dam;
    
    int nameF, symbF, descF, colorF, speedF, abilF, hpF, damF;
    int colorD, speedD, hpD, damBASE, damSIDES, damDICE;
    
    
    getline(f, str);
    
    if(str.compare("RLG327 MONSTER DESCRIPTION 1")==0)
    {
        //cout << "RLG327 MONSTER DESCRIPTION 1" << endl;
    }
    else
    {
        cout << "Aborting program, incorrect file..." << endl;
        return 1;
    }
    
    while(a == 0)
    {
        getline(f, str);
        
        
        
        //search for begin monster text
        if(str.find("BEGIN MONSTER") != string::npos)
        {
            b = 0;
            int i = 0;
            nameF = 0;
            symbF = 0;
            descF = 0;
            colorF = 0;
            speedF = 0;
            abilF = 0;
            hpF = 0;
            damF = 0;
            while(b==0)
            {
                getline(f, str);
                string temp = str;
                string delimit = " ";
                int pos = temp.find(delimit);
                string firstWord = temp.substr(0, pos);

                if(firstWord.find("SYMB") != string::npos)
                {
                    if(str.length() == 4 || str.length() == 5) //there is nothing in the field
                    {
                            //nothing included past the field so monster is discarded
                        break;
                    }
                    else
                    {
                        symb = str.substr(5);
                        if(symb.find_first_not_of(' ') == std::string::npos)
                        {
                            //empty string so monster is passed
                            break;
                        }
                        else
                        {
                            symbF++;

                        }

                    }
                                        
                }
                else if(firstWord.find("DESC") != string::npos)
                {
                    descF++;
                    
                    while(str.compare(".") != 0)
                    {
                        getline(f, str);
                        if(str.length() > 77)
                        {
                            //cout << "Description text too long on singular line " << endl;
                            cout << endl;
                            descF = 0;
                            break;
                        }
                        i++;
                        m.push_desc(str);
                    }
                    
                    
                    
                    
                    
                    
                }
                else if(firstWord.find("COLOR") != string::npos)
                {
                    
                    if(str.length() == 6 || str.length() == 5) //there is nothing in the field
                    {
                        break;

                        //nothing included past the field so monster is discarded
                    }
                    else
                    {
                        color = str.substr(6);
                        if(color.find_first_not_of(' ') == std::string::npos)
                        {
                            break;

                            //empty string so monster is passed
                        }
                        else
                        {
                            string delimit = " ";
                            string temp = color;
                            size_t pos = 0;
                            string token;
                            int c = 0;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                if(token.find("RED") == string::npos &&
                                   token.find("BLUE") == string::npos &&
                                   token.find("GREEN") == string::npos &&
                                   token.find("CYAN") == string::npos &&
                                   token.find("MAGENTA") == string::npos &&
                                   token.find("BLACK") == string::npos &&
                                   token.find("WHITE") == string::npos &&
                                   token.find("YELLOW") == string::npos
                                   )
                                {
                                    break;
                                }
                                
                                if(c == 0)
                                {
                                    if(token.find("RED") != string::npos)
                                    {
                                        colorD = RED;
                                    }
                                    else if(token.find("BLUE") != string::npos)
                                    {
                                        colorD = BLUE;
                                    }
                                    else if(token.find("MAGENTA") != string::npos)
                                    {
                                        colorD = MAGENTA;
                                    }
                                    else if(token.find("YELLOW") != string::npos)
                                    {
                                        colorD = YELLOW;
                                    }
                                    else if(token.find("BLACK") != string::npos)
                                    {
                                        colorD = BLACK;
                                    }
                                    else if(token.find("GREEN") != string::npos)
                                    {
                                        colorD = GREEN;
                                    }
                                    else if(token.find("CYAN") != string::npos)
                                    {
                                        colorD = CYAN;
                                    }
                                    else if(token.find("WHITE") != string::npos)
                                    {
                                        colorD = WHITE;
                                    }
                                    c++;
                                }
                                
                                
                                
                                
                                temp.erase(0, pos + delimit.length());
                            }
                            token = temp;
                            if(token.find("RED") == string::npos &&
                               token.find("BLUE") == string::npos &&
                               token.find("GREEN") == string::npos &&
                               token.find("CYAN") == string::npos &&
                               token.find("MAGENTA") == string::npos &&
                               token.find("BLACK") == string::npos &&
                               token.find("WHITE") == string::npos &&
                               token.find("YELLOW") == string::npos
                               )
                            {
                                break;
                            }
                            
                            if(c == 0)
                            {
                                if(token.find("RED") != string::npos)
                                {
                                    colorD = RED;
                                }
                                else if(token.find("BLUE") != string::npos)
                                {
                                    colorD = BLUE;
                                }
                                else if(token.find("MAGENTA") != string::npos)
                                {
                                    colorD = MAGENTA;
                                }
                                else if(token.find("YELLOW") != string::npos)
                                {
                                    colorD = YELLOW;
                                }
                                else if(token.find("BLACK") != string::npos)
                                {
                                    colorD = BLACK;
                                }
                                else if(token.find("GREEN") != string::npos)
                                {
                                    colorD = GREEN;
                                }
                                else if(token.find("CYAN") != string::npos)
                                {
                                    colorD = CYAN;
                                }
                                else if(token.find("WHITE") != string::npos)
                                {
                                    colorD = WHITE;
                                }
                                c++;
                            }

                            

                            colorF++;
                            
                        }
                        
                    }
                }
                else if(firstWord.find("SPEED") != string::npos)
                {
                    if(str.length() == 6 || str.length() == 5) //there is nothing in the field
                    {
                        break;

                        //nothing included past the field so monster is discarded
                    }
                    else
                    {
                        speed = str.substr(6);
                        if(speed.find_first_not_of(' ') == std::string::npos)
                        {
                            break;

                            //empty string so monster is passed
                        }
                        else
                        {
                            string delimit = "+";
                            string temp = speed;
                            size_t pos = 0;
                            int speedBASE;
                            string token;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                speedBASE = atoi(token.c_str());
                                temp.erase(0, pos + delimit.length());
                            }
                            
                            delimit = "d";
                            pos = 0;
                            int speedDICE;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                speedDICE = atoi(token.c_str());
                                temp.erase(0, pos + delimit.length());
                            }

                            token = temp;
                            int speedSIDES = atoi(token.c_str());
                            
                            speedD = rollDice(speedBASE, speedDICE, speedSIDES);
                            
                            speedF++;
                            
                        }
                        
                    }

                }
                else if(firstWord.find("ABIL") != string::npos)
                {

                    if(str.length() == 4 || str.length() == 5) //there is nothing in the field
                    {
                        break;

                        //nothing included past the field so monster is discarded
                    }
                    else
                    {

                        abil = str.substr(5);
                        
                        if(abil.find_first_not_of(' ') == string::npos)
                        {
                            break;

                            //empty string so monster is passed
                        }
                        else
                        {
                            string delimit = " ";
                            string temp = abil;
                            size_t pos = 0;
                            string token;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                if(token.find("SMART") == string::npos &&
                                   token.find("TELE") == string::npos &&
                                   token.find("TUNNEL") == string::npos &&
                                   token.find("ERRATIC") == string::npos &&
                                   token.find("PASS") == string::npos &&
                                   token.find("PICKUP") == string::npos &&
                                   token.find("DESTROY") == string::npos
                                   )
                                {
                                    break;
                                }
                                temp.erase(0, pos + delimit.length());
                            }
                            token = temp;
                            if(token.find("SMART") == string::npos &&
                               token.find("TELE") == string::npos &&
                               token.find("TUNNEL") == string::npos &&
                               token.find("ERRATIC") == string::npos &&
                               token.find("PASS") == string::npos &&
                               token.find("PICKUP") == string::npos &&
                               token.find("DESTROY") == string::npos
                               )
                            {
                                break;
                            }
                            
                            abilF++;
                            
                        }
                        
                    }

                }
                else if(firstWord.find("HP") != string::npos)
                {

                    if(str.length() == 2 || str.length() == 3) //there is nothing in the field
                    {
                        break;

                        //nothing included past the field so monster is discarded
                    }
                    else
                    {

                        hp = str.substr(3);
                        if(hp.find_first_not_of(' ') == std::string::npos)
                        {
                            break;

                            //empty string so monster is passed
                        }
                        else
                        {
                            string delimit = "+";
                            string temp = hp;
                            size_t pos = 0;
                            int hpBASE;
                            string token;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                hpBASE = atoi(token.c_str());
                                temp.erase(0, pos + delimit.length());
                            }
                            
                            delimit = "d";
                            pos = 0;
                            int hpDICE;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                hpDICE = atoi(token.c_str());
                                temp.erase(0, pos + delimit.length());
                            }
                            
                            token = temp;
                            int hpSIDES = atoi(token.c_str());
                            
                            hpD = rollDice(hpBASE, hpDICE, hpSIDES);
                            
                            hpF++;
                            
                        }
                        
                    }

                }
                else if(firstWord.find("DAM") != string::npos)
                {
                    if(str.length() == 4 || str.length() == 3) //there is nothing in the field
                    {
                        break;

                        //nothing included past the field so monster is discarded
                    }
                    else
                    {
                        dam = str.substr(4);
                        if(dam.find_first_not_of(' ') == std::string::npos)
                        {
                            break;

                            //empty string so monster is passed
                        }
                        else
                        {
                            string delimit = "+";
                            string temp = dam;
                            size_t pos = 0;
                            string token;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                damBASE = atoi(token.c_str());
                                temp.erase(0, pos + delimit.length());
                            }
                            
                            delimit = "d";
                            pos = 0;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                damDICE = atoi(token.c_str());
                                temp.erase(0, pos + delimit.length());
                            }
                            
                            token = temp;
                            damSIDES = atoi(token.c_str());
                            
                            

                            damF++;
                            
                        }
                        
                    }

                }
                else if(firstWord.find("NAME") != string::npos)
                {
                    if(str.length() == 4 || str.length() == 5) //there is nothing in the field
                    {
                        break;
                        //nothing included past the field so monster is discarded
                    }
                    else
                    {
                        name = str.substr(5);
                        if(name.find_first_not_of(' ') == std::string::npos)
                        {
                            break;
                            //empty string so monster is passed
                        }
                        else
                        {
                            nameF++;
                            
                        }
                        
                    }

                }
                else if(firstWord.find("END") != string::npos)
                {
                    if(
                       nameF == 1 && symbF == 1 && descF == 1
                       && colorF == 1 && speedF == 1 && abilF == 1
                       && hpF == 1 && damF == 1
                       )
                    {
//                        cout << name << endl;
//                        cout << symb << endl;
//                        for(int j = 0; j < i - 1; j++)
//                        {
//                            cout << descArr[j] <<  endl;
//                        }
//                        cout << color << endl;
//                        cout << speed << endl;
//                        cout << abil << endl;
//                        cout << hp << endl;
//                        cout << dam << endl;
//                        cout<<endl;
                        char type = symb[0];
                        m.createMonsterInstance(speedD, colorD, damBASE,
                                                          damDICE, damSIDES, hpD,
                                                          name, type, abil);
                        
                        
                        monsterList.push_back(m);
                        count++;
                        if(count == nummon)
                        {
                            //cout << "Returning now..." << endl;
                            return 0;
                        }
                        
                        
                    }
                    b++;
                    
                }
                
            }
        }
        else if(f.eof())
        {
            if(count < nummon)
            {
                f.clear();
                f.seekg(0, ios::beg);
            }
            else
            {
            a++;
            }
        }
        
    }
    
    f.close();
    return 0;
}


int item_parse(vector<dungeonObjects> & objectList, dungeonObjects& objectInstance)
{
    ifstream f(objectFile());
    int a = 0;
    int b = 0;
    int count = 0;
    int loop_ran = 0;

    
    string str;
    string name;
    string tipe;
    string desc;
    string color;
    string speed;
    string attr;
    string hit;
    string dam;
    string val, dodge, def, weight;
    
    int nameF, tipeF, descF, colorF, speedF, attrF, hitF, damF, valF, dodgeF, defF,
    weightF, damBASE, damDICE, damSIDES;
    
    int speedD, attrD, hitD, valD, dodgeD, defD, weightD, colorD;
    
    getline(f, str);
    
    if(str.compare("RLG327 OBJECT DESCRIPTION 1")==0)
    {
    }
    else
    {
        return 1;
    }
    
    while(a == 0)
    {
        getline(f, str);
        
        //search for begin monster text
        if(str.find("BEGIN OBJECT") != string::npos)
        {
            dungeonObjects blank;
            objectInstance = blank;
            b = 0;
            nameF = 0;
            tipeF = 0;
            descF = 0;
            colorF = 0;
            speedF = 0;
            attrF = 0;
            hitF = 0;
            damF = 0;
            valF = 0;
            dodgeF = 0;
            defF = 0;
            weightF = 0;
            damSIDES = 0;
            damDICE = 0;
            damBASE = 0;
            speedD = 0;
            attrD = 0;
            hitD = 0;
            valD = 0;
            dodgeD = 0;
            defD = 0;
            weightD = 0;
            colorD = 0;
            while(b==0)
            {

                getline(f, str);
                string temp = str;
                string delimit = " ";
                int pos = temp.find(delimit);
                string firstWord = temp.substr(0, pos);
                
                
                if(firstWord.find("TYPE") != string::npos)
                {
                    if(str.length() == 4 || str.length() == 5) //there is nothing in the field
                    {
                        //nothing included past the field so monster is discarded
                    }
                    else
                    {
                        tipe = str.substr(5);
                        if(tipe.find_first_not_of(' ') == std::string::npos)
                        {
                            break;
                            
                            //empty string so monster is passed
                        }
                        else{
                            string delimit = " ";
                            string temp = tipe;
                            size_t pos = 0;
                            string token;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                if(token.find("WEAPON") == string::npos &&
                                   token.find("OFFHAND") == string::npos &&
                                   token.find("RANGED") == string::npos &&
                                   token.find("ARMOR") == string::npos &&
                                   token.find("HELMET") == string::npos &&
                                   token.find("CLOAK") == string::npos &&
                                   token.find("GLOVES") == string::npos &&
                                   token.find("BOOTS") == string::npos &&
                                   token.find("RING") == string::npos &&
                                   token.find("AMULET") == string::npos &&
                                   token.find("LIGHT") == string::npos &&
                                   token.find("SCROLL") == string::npos &&
                                   token.find("BOOK") == string::npos &&
                                   token.find("FLASK") == string::npos &&
                                   token.find("GOLD") == string::npos &&
                                   token.find("AMMUNITION") == string::npos &&
                                   token.find("FOOD") == string::npos &&
                                   token.find("WAND") == string::npos &&
                                   token.find("CONTAINER") == string::npos)

                                    
                                {
                                    break;
                                }
                                temp.erase(0, pos + delimit.length());
                            }
                            token = temp;
                            if(token.find("WEAPON") == string::npos &&
                               token.find("OFFHAND") == string::npos &&
                               token.find("RANGED") == string::npos &&
                               token.find("ARMOR") == string::npos &&
                               token.find("HELMET") == string::npos &&
                               token.find("CLOAK") == string::npos &&
                               token.find("GLOVES") == string::npos &&
                               token.find("BOOTS") == string::npos &&
                               token.find("RING") == string::npos &&
                               token.find("AMULET") == string::npos &&
                               token.find("LIGHT") == string::npos &&
                               token.find("SCROLL") == string::npos &&
                               token.find("BOOK") == string::npos &&
                               token.find("FLASK") == string::npos &&
                               token.find("GOLD") == string::npos &&
                               token.find("AMMUNITION") == string::npos &&
                               token.find("FOOD") == string::npos &&
                               token.find("WAND") == string::npos &&
                               token.find("CONTAINER") == string::npos) 

                            {
                                break;
                            }
                            

                            tipeF++;
                        }
                    }
                }
                else if(firstWord.find("DESC") != string::npos)
                {
                    
                    
                    descF++;
                    
                    while(str.compare(".") != 0)
                    {
                        getline(f, str);
                        if(str.length() > 77)
                        {
                            cout << "Description text too long on singular line " << endl;
                            cout << endl;
                            descF = 0;
                            break;
                        }
                        objectInstance.push_desc(str);
                    }
              
                    
                    
                }
                else if(firstWord.find("COLOR") != string::npos)
                {

                    if(str.length() == 6 || str.length() == 5) //there is nothing in the field
                    {
                        //nothing included past the field so monster is discarded
                    }
                    else
                    {

                        color = str.substr(6);
                        if(color.find_first_not_of(' ') == std::string::npos)
                        {
                            break;
                            
                            //empty string so monster is passed
                        }
                        else
                        {
                            string delimit = " ";
                            string temp = color;
                            size_t pos = 0;
                            int c = 0;
                            string token;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                if(token.find("RED") == string::npos &&
                                   token.find("BLUE") == string::npos &&
                                   token.find("GREEN") == string::npos &&
                                   token.find("CYAN") == string::npos &&
                                   token.find("MAGENTA") == string::npos &&
                                   token.find("BLACK") == string::npos &&
                                   token.find("WHITE") == string::npos &&
                                   token.find("YELLOW") == string::npos
                                   )
                                {
                                    break;
                                }
                                if(c == 0)
                                {
                                    if(token.find("RED") != string::npos)
                                    {
                                        colorD = RED;
                                    }
                                    else if(token.find("BLUE") != string::npos)
                                    {
                                        colorD = BLUE;
                                    }
                                    else if(token.find("MAGENTA") != string::npos)
                                    {
                                        colorD = MAGENTA;
                                    }
                                    else if(token.find("YELLOW") != string::npos)
                                    {
                                        colorD = YELLOW;
                                    }
                                    else if(token.find("BLACK") != string::npos)
                                    {
                                        colorD = BLACK;
                                    }
                                    else if(token.find("GREEN") != string::npos)
                                    {
                                        colorD = GREEN;
                                    }
                                    else if(token.find("CYAN") != string::npos)
                                    {
                                        colorD = CYAN;
                                    }
                                    else if(token.find("WHITE") != string::npos)
                                    {
                                        colorD = WHITE;
                                    }
                                    c++;
                                }

                                temp.erase(0, pos + delimit.length());
                            }
                            token = temp;
                            if(token.find("RED") == string::npos &&
                               token.find("BLUE") == string::npos &&
                               token.find("GREEN") == string::npos &&
                               token.find("CYAN") == string::npos &&
                               token.find("MAGENTA") == string::npos &&
                               token.find("BLACK") == string::npos &&
                               token.find("WHITE") == string::npos &&
                               token.find("YELLOW") == string::npos
                               )
                            {
                                break;
                            }
                            if(c == 0)
                            {
                                if(token.find("RED") != string::npos)
                                {
                                    colorD = RED;
                                }
                                else if(token.find("BLUE") != string::npos)
                                {
                                    colorD = BLUE;
                                }
                                else if(token.find("MAGENTA") != string::npos)
                                {
                                    colorD = MAGENTA;
                                }
                                else if(token.find("YELLOW") != string::npos)
                                {
                                    colorD = YELLOW;
                                }
                                else if(token.find("BLACK") != string::npos)
                                {
                                    colorD = BLACK;
                                }
                                else if(token.find("GREEN") != string::npos)
                                {
                                    colorD = GREEN;
                                }
                                else if(token.find("CYAN") != string::npos)
                                {
                                    colorD = CYAN;
                                }
                                else if(token.find("WHITE") != string::npos)
                                {
                                    colorD = WHITE;
                                }
                                c++;
                            }

                            
                            colorF++;

                        }
                        
                }
                }
                else if(firstWord.find("SPEED") != string::npos)
                {
                    if(str.length() == 6 || str.length() == 5) //there is nothing in the field
                    {
                        //nothing included past the field so monster is discarded
                    }
                    else
                    {
                        speed = str.substr(6);
                        if(speed.find_first_not_of(' ') == std::string::npos)
                        {
                            break;
                            
                            //empty string so monster is passed
                        }
                        else
                        {
                            string delimit = "+";
                            string temp = speed;
                            size_t pos = 0;
                            int speedBASE;
                            string token;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                speedBASE = atoi(token.c_str());
                                temp.erase(0, pos + delimit.length());
                            }
                            
                            delimit = "d";
                            pos = 0;
                            int speedDICE;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                speedDICE = atoi(token.c_str());
                                temp.erase(0, pos + delimit.length());
                            }
                            
                            token = temp;
                            int speedSIDES = atoi(token.c_str());
                            
                            
                            speedD = rollDice(speedBASE, speedDICE, speedSIDES);
                            
                            speedF++;

                        }
                        
                    }
                }
                else if(firstWord.find("ATTR") != string::npos)
                {
                    if(str.length() == 4 || str.length() == 5) //there is nothing in the field
                    {
                        //nothing included past the field so monster is discarded
                    }
                    else
                    {
                        attr = str.substr(5);
                        if(attr.find_first_not_of(' ') == std::string::npos)
                        {
                            break;
                            
                            //empty string so monster is passed
                        }
                        else
                        {
                            string delimit = "+";
                            string temp = attr;
                            size_t pos = 0;
                            int attrBASE;
                            string token;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                attrBASE = atoi(token.c_str());
                                temp.erase(0, pos + delimit.length());
                            }
                            
                            delimit = "d";
                            pos = 0;
                            int attrDICE;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                attrDICE = atoi(token.c_str());
                                temp.erase(0, pos + delimit.length());
                            }
                            
                            token = temp;
                            int attrSIDES = atoi(token.c_str());
                            
                            attrD = rollDice(attrBASE, attrDICE, attrSIDES);

                            
                            attrF++;
                            
                        }
                        
                    }
                }
                else if(firstWord.find("HIT") != string::npos)
                {
                    if(str.length() == 4 || str.length() == 3) //there is nothing in the field
                    {
                        //nothing included past the field so monster is discarded
                    }
                    else
                    {
                        hit = str.substr(4);
                        if(hit.find_first_not_of(' ') == std::string::npos)
                        {
                            break;
                            
                            //empty string so monster is passed
                        }
                        else
                        {
                            string delimit = "+";
                            string temp = hit;
                            size_t pos = 0;
                            int hitBASE;
                            string token;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                hitBASE = atoi(token.c_str());
                                temp.erase(0, pos + delimit.length());
                            }
                            
                            delimit = "d";
                            pos = 0;
                            int hitDICE;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                hitDICE = atoi(token.c_str());
                                temp.erase(0, pos + delimit.length());
                            }
                            
                            token = temp;
                            int hitSIDES = atoi(token.c_str());
                            
                            hitD = rollDice(hitBASE, hitDICE, hitSIDES);
                            hitF++;
                            
                        }
                        
                    }
                }
                else if(firstWord.find("NAME") != string::npos)
                {
                    if(str.length() == 4 || str.length() == 5) //there is nothing in the field
                    {
                        //nothing included past the field so monster is discarded
                    }
                    else
                    {
                        name = str.substr(5);
                        if(name.find_first_not_of(' ') == std::string::npos)
                        {
                            //empty string so monster is passed
                        }
                        else
                        {
                            nameF++;

                        }
                        
                    }
                }
                else if(firstWord.find("VAL") != string::npos)
                {
                    if(str.length() == 4 || str.length() == 3) //there is nothing in the field
                    {
                        //nothing included past the field so monster is discarded
                    }
                   
                        else
                        {
                            val = str.substr(4);
                            if(val.find_first_not_of(' ') == std::string::npos)
                            {
                                break;
                                
                                //empty string so monster is passed
                            }
                            else
                            {
                                string delimit = "+";
                                string temp = val;
                                size_t pos = 0;
                                int valBASE;
                                string token;
                                while ((pos = temp.find(delimit)) != string::npos) {
                                    token = temp.substr(0, pos);
                                    valBASE = atoi(token.c_str());
                                    temp.erase(0, pos + delimit.length());
                                }
                                
                                delimit = "d";
                                pos = 0;
                                int valDICE;
                                while ((pos = temp.find(delimit)) != string::npos) {
                                    token = temp.substr(0, pos);
                                    valDICE = atoi(token.c_str());
                                    temp.erase(0, pos + delimit.length());
                                }
                                
                                token = temp;
                                int valSIDES = atoi(token.c_str());
                                
                                valD = rollDice(valBASE, valDICE, valSIDES);
                                
                                valF++;
                                
                                
                                
                                
                                
                                
                            }
                            
                        }
                    }
                else if(firstWord.find("DODGE") != string::npos)
                {
                    if(str.length() == 6 || str.length() == 5) //there is nothing in the field
                    {
                        //nothing included past the field so monster is discarded
                    }
                    else
                    {
                        dodge = str.substr(6);
                        if(dodge.find_first_not_of(' ') == std::string::npos)
                        {
                            break;
                            
                            //empty string so monster is passed
                        }
                        else
                        {
                            string delimit = "+";
                            string temp = dodge;
                            size_t pos = 0;
                            int dodgeBASE;
                            string token;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                dodgeBASE = atoi(token.c_str());
                                temp.erase(0, pos + delimit.length());
                            }
                            
                            delimit = "d";
                            pos = 0;
                            int dodgeDICE;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                dodgeDICE = atoi(token.c_str());
                                temp.erase(0, pos + delimit.length());
                            }
                            
                            token = temp;
                            int dodgeSIDES = atoi(token.c_str());
                            
                            dodgeD = rollDice(dodgeBASE, dodgeDICE, dodgeSIDES);
                            
                            dodgeF++;
                            
                        }
                        
                    }
                }
                else if(firstWord.find("DEF") != string::npos)
                {
                    if(str.length() == 4 || str.length() == 3) //there is nothing in the field
                    {
                        //nothing included past the field so monster is discarded
                    }
                    else
                    {
                        def = str.substr(4);
                        if(def.find_first_not_of(' ') == std::string::npos)
                        {
                            break;
                            
                            //empty string so monster is passed
                        }
                        else
                        {
                            string delimit = "+";
                            string temp = def;
                            size_t pos = 0;
                            int defBASE;
                            string token;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                defBASE = atoi(token.c_str());
                                temp.erase(0, pos + delimit.length());
                            }
                            
                            delimit = "d";
                            pos = 0;
                            int defDICE;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                defDICE = atoi(token.c_str());
                                temp.erase(0, pos + delimit.length());
                            }
                            
                            token = temp;
                            int defSIDES = atoi(token.c_str());
                            
                            defD = rollDice(defBASE, defDICE, defSIDES);
                            
                            defF++;
                            
                        }
                        
                    }
                }
                else if(firstWord.find("WEIGHT") != string::npos)
                {
                    if(str.length() == 6 || str.length() == 7) //there is nothing in the field
                    {
                        //nothing included past the field so monster is discarded
                    }
                    else
                    {
                        weight = str.substr(7);
                        if(weight.find_first_not_of(' ') == std::string::npos)
                        {
                            break;
                            
                            //empty string so monster is passed
                        }
                        else
                        {
                            string delimit = "+";
                            string temp = weight;
                            size_t pos = 0;
                            int weightBASE;
                            string token;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                weightBASE = atoi(token.c_str());
                                temp.erase(0, pos + delimit.length());
                            }
                            
                            delimit = "d";
                            pos = 0;
                            int weightDICE;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                weightDICE = atoi(token.c_str());
                                temp.erase(0, pos + delimit.length());
                            }
                            
                            token = temp;
                            int weightSIDES = atoi(token.c_str());
                            
                            weightD = rollDice(weightBASE, weightDICE, weightSIDES);
                            
                            weightF++;
                            
                        }
                        
                    }
                }
                else if(firstWord.find("DAM") != string::npos)
                {
                    if(str.length() == 4 || str.length() == 3) //there is nothing in the field
                    {
                        break;
                        
                        //nothing included past the field so monster is discarded
                    }
                    else
                    {
                        dam = str.substr(4);
                        if(dam.find_first_not_of(' ') == std::string::npos)
                        {
                            break;
                            
                            //empty string so monster is passed
                        }
                        else
                        {
                            string delimit = "+";
                            string temp = dam;
                            size_t pos = 0;
                            string token;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                damBASE = atoi(token.c_str());
                                temp.erase(0, pos + delimit.length());
                            }
                            
                            delimit = "d";
                            pos = 0;
                            while ((pos = temp.find(delimit)) != string::npos) {
                                token = temp.substr(0, pos);
                                damDICE = atoi(token.c_str());
                                temp.erase(0, pos + delimit.length());
                            }
                            
                            token = temp;
                            damSIDES = atoi(token.c_str());
                            
                            
                            damF++;
                            
                        }
                        
                    }
                    
                }
                else if(firstWord.find("END") != string::npos)
                {
                    if(
                       nameF == 1 && tipeF == 1 && descF == 1
                       && colorF == 1 && speedF == 1 && attrF == 1
                       && hitF == 1 && damF == 1 && valF == 1 &&
                       dodgeF == 1 && defF == 1 && weightF == 1
                       )
                    {
                       
                        
                        
                        objectInstance.createObjectInstance(colorD, hitD, valD, defD,dodgeD,
                                                            weightD, speedD, attrD,damDICE,
                                                            damSIDES,damBASE,name, tipe);

                        
                        objectList.push_back(objectInstance);
                        count++;
                        if(count == 20 && loop_ran != 0)
                        {
                            //cout << "Returning now..." << endl;
                            return 0;
                        }

                        
                        
                    }
                    b++;
                    
                }
                
            }
        }
        else if(f.eof())
        {
            
            if(count < 20)
            {
                f.clear();
                f.seekg(0, ios::beg);
                loop_ran++;
            }
            else
            {
            a++;
            }
        }
        
    }
    
    f.close();
    
    return 0;

    
        
    
}



char* monsterFile() {
    char* full_path;
    char* home_directory;
    const char* relative_path = "/.rlg327/monster_desc.txt";
    
    home_directory = getenv("HOME");
    full_path = (char*) malloc(sizeof(char) * (strlen(home_directory) + strlen(relative_path) + 1));
    sprintf(full_path, "%s/.rlg327/monster_desc.txt", home_directory);
    return full_path;
}

char* objectFile() {
    char* full_path;
    char* home_directory;
    const char* relative_path = "/.rlg327/object_desc.txt";
    
    home_directory = getenv("HOME");
    full_path = (char*) malloc(sizeof(char) * (strlen(home_directory) + strlen(relative_path) + 1));
    sprintf(full_path, "%s/.rlg327/object_desc.txt", home_directory);
    return full_path;
}


int rollDice(int base, int dice, int sides)
{
    int totalRoll = 0;
    for(int i = 0; i < dice; i++)
    {
        totalRoll = totalRoll + (rand() % sides + 1); //the dice is rolled dice times and the value
        //is accumulated within the loop;
    }
    
    return (base + totalRoll);
}





