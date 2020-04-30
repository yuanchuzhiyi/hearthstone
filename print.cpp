//
//  print.cpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/13.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//

#include "print.hpp"
#include "Card.hpp"
#include "Player.hpp"
#include "global.hpp"
extern map<int,ef> effectfuncs;
extern timepoints timepoint;


void printplayer(Player player)
{
    cout << player.name << "的阵容" << endl;
    map<int, Card>::iterator iter;
    
    for(int i = 1; i <= MAX_MINION; i++)
    {
        iter = player.minions.begin();
        iter = player.minions.find(i);
        if(iter != player.minions.end())
        {
            cout << i << "号" << iter->second.atk << ' ' << iter->second.hp << ' ' << iter->second.name << endl;
        }
        else
        {
            cout << i << "号" << ' ' << "空" << endl;
        }
    }
    
    
}




void printeasy(Player current_player, Player enemy_player)
{
    cout << "1号" << ' ' << ' ' << ' ' <<
    "2号" << ' ' << ' ' << ' ' <<
    "3号" << ' ' << ' ' << ' ' <<
    "4号" << ' ' << ' ' << ' ' <<
    "5号" << ' ' << ' ' << ' ' <<
    "6号" << ' ' << ' ' << ' ' <<
    "7号" << endl;
    
    map<int, Card>::iterator iter1;
    map<int, Card>::iterator iter2;
    
    for(int i = 1; i <= MAX_MINION; i++)
    {
        iter1 = current_player.minions.begin();
        iter1 = current_player.minions.find(i);
        if(iter1 != current_player.minions.end())
        {
            cout << iter1->second.atk << ' ' << iter1->second.hp << "--";
        }
        else if(iter1 == current_player.minions.end())
        {
            cout << "空位" << "--";
        }

    }
    
    cout << endl;
    for(int i = 1; i <= MAX_MINION; i++)
    {
        iter2 = enemy_player.minions.begin();
        iter2 = enemy_player.minions.find(i);
        if(iter2 != enemy_player.minions.end())
        {
            cout << iter2->second.atk << ' ' << iter2->second.hp << "--";
        }
        else if(iter2 == enemy_player.minions.end())
        {
            cout << "空位" << "--";
        }

    }
    
    
    

    cout << endl;
}

void printinfo(Player current_player, Player enemy_player)
{
//    printeasy(current_player, enemy_player);
    
    printplayer(current_player);
    printplayer(enemy_player);
}



void printcurrent(Player mine)
{
    int no = 0;
    cout << "等级:" << mine.level << ' ' << "金币:" << mine.coin << ' ' << "升级需要金币:" << mine.levelup_cost[mine.level - 1] << endl;
    cout << "酒馆:";
    no = 1;
    list<Card>::iterator iter1;
    iter1 = mine.tavern.begin();
    while(iter1 != mine.tavern.end())
    {
        cout << no << (*iter1).name << ' ';
        iter1++;
        no++;
    }
    cout << endl;
    
    cout << "场上:";
    no = 1;
    map<int, Card>::iterator iter2;
    iter2 = mine.minions.begin();
    while(iter2 != mine.minions.end())
    {
        cout << no << iter2 -> second.name << ' ';
        no++;
        iter2++;
    }
    cout << endl;
    
    cout << "手牌:";
    no = 1;
    list<Card>::iterator iter3;
    iter3 = mine.handcards.begin();
    while(iter3 != mine.handcards.end())
    {
        cout << no << (*iter3).name << ' ';
        no++;
        iter3++;
    }
    cout << endl;
  
    
}

void printcurrentall(Player mine)
{
    cout << "等级:" << mine.level << ' ' <<  "金币:" << mine.coin << endl;
    cout << "酒馆:";
    list<Card>::iterator iter1;
    iter1 = mine.tavern.begin();
    while(iter1 != mine.tavern.end())
    {
        cout << (*iter1).name << ' ';
        iter1++;
    }
    cout << endl;
    
    printplayer(mine);
    
    cout << "手牌:";
    
    list<Card>::iterator iter3;
    iter3 = mine.handcards.begin();
    while(iter3 != mine.handcards.end())
    {
        cout << (*iter3).name << ' ';
        iter3++;
    }
    cout << endl;
  
    
}

void printminion(Player mine)
{
    int no = 0;
    cout << "场上:";
    no = 1;
    map<int, Card>::iterator iter2;
    iter2 = mine.minions.begin();
    while(iter2 != mine.minions.end())
    {
        cout << no << iter2 -> second.name << ' ';
        no++;
        iter2++;
    }
    cout << endl;
}

void printtavern(Player mine)
{
    int no = 0;
    cout << "酒馆:";
    no = 1;
    list<Card>::iterator iter1;
    iter1 = mine.tavern.begin();
    while(iter1 != mine.tavern.end())
    {
        cout << no << (*iter1).name << ' ';
        iter1++;
        no++;
    }
    cout << endl;
}

void printhandcards(Player mine)
{
    int no = 0;
    cout << "手牌:";
    no = 1;
    list<Card>::iterator iter3;
    iter3 = mine.handcards.begin();
    while(iter3 != mine.handcards.end())
    {
        cout << no << (*iter3).name << ' ';
        no++;
        iter3++;
    }
    cout << endl;
}
