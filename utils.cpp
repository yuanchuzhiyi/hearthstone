//
//  utils.cpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/13.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//
#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>
#include <random>
#include "effect_func.hpp"
#include "Player.hpp"
#include "Card.hpp"
#include "battlephase.hpp"
#include "set.hpp"
#include "print.hpp"
#include "utils.hpp"
#include "global.hpp"

extern map<int,ef> effectfuncs;
extern timepoints timepoint;


Player &get_currentplayer(bool flag, Player& player1, Player& player2)
{
    if(flag)
        return player1;
    else
        return player2;
}

Player &get_enemyplayer(bool flag, Player& player1, Player& player2)
{
    if(flag)
        return player2;
    else
        return player1;
}


int findgameid(Player& player, int gameid)
{
    map<int, Card>::iterator iter;
    iter = player.minions.begin();
    while(iter != player.minions.end())
    {
        if((iter -> second).gameid == gameid)
            return iter -> first;
        iter++;
    }
    
    return 0;
}


bool has_taunt(map<int,Card> minions)
{
    map<int, Card>::iterator iter;
    iter = minions.begin();
    while(iter != minions.end())
    {
        if((iter -> second).taunt)
            return true;
        iter++;
    }
    
    return false;
}


/*
 @return -1 表示没有随从
 */
int random_target(map<int, Card> minions)
{

    std::random_device rd;
    std::mt19937 mt(rd());
    size_t minion_size = minions.size();
    if(minion_size == 0)
        return -1;
    
//    int random = rand() % minion_size + 1;
    int random = mt() % minion_size + 1;
    map<int, Card>::iterator iter;
    iter = minions.begin();
    for(int i = 1; i < random; i++)
    {
        iter++;
    }
    return iter -> first;
        
}

int battle_random_target(map<int, Card> minions)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    
    size_t minion_size = minions.size();
    if(minion_size == 0)
        return -1;
    bool taunt = has_taunt(minions);
    if(!taunt)
    {
//        int random = rand() % minion_size + 1;
        int random = mt() % minion_size + 1;
        map<int, Card>::iterator iter;
        iter = minions.begin();
        for(int i = 1; i < random; i++)
        {
            iter++;
        }
        return iter -> first;
        
        
    }
    
    else    //有嘲讽
    {

        map<int, Card>::iterator iter;
        iter = minions.begin();
        int count = 0;
        while(iter != minions.end())
        {
            if(iter -> second.taunt == true)
            {
                count++;
            }
            iter++;
        }
        
        if(count == 0) return -1;
        iter = minions.begin();
        int random = rand() % count + 1;
        while(iter != minions.end())
        {
            if(iter -> second.taunt == false)
            {
                iter++;
                
                
                continue;
            }
            if(iter -> second.taunt == true)
            {
                random--;
                if(random == 0)
                {
                    
                    return iter -> first;
                    
                }
            }
            
        }
       
    }
    return -1;
}



int count_point(int winner, Player player1, Player player2)
{
    if(winner == 0)
    {
        return 0;
    }
    
    if(winner == 2)
    {
        int point = 0;
        map<int, Card>::iterator iter;
        iter = player2.minions.begin();
        while(iter != player2.minions.end())
        {
            point = point + iter -> second.level;
            iter++;
        }
        
        return point;
    
    }
    
    if(winner == 1)
    {
        int point = 0;
        map<int, Card>::iterator iter;
        iter = player1.minions.begin();
        while(iter != player1.minions.end())
        {
            point = point + iter -> second.level;
            iter++;
        }
        
        return point;
    }
    
    
    return -1;
    
}



/*小于等于index的全部往左靠，大于index的往右靠*/
void redistribute(int index, Player& player)
{
    if(player.minions.empty())
        return;
    cout << "redistribute" << endl;
    map<int, Card>::iterator iter;
    map<int, Card> after;
    int i;
    
    iter = player.minions.begin();
    if(index != 0)
    {
        i = 1;
        while( (iter -> first <= index) && i <= index)
        {
             
            after[i] = iter -> second;
            iter++;
            i++;
            if(iter == player.minions.end())
            {
                break;
            }
        }
    }

    
    iter = player.minions.end();
    iter--;
    i = MAX_MINION;
    while(iter -> first > index && i > index)
    {
        
        after[i] = iter -> second;
        i--;
        if(iter != player.minions.begin())
        {
            iter--;
        }
        else
            break;
    }
    player.minions.clear();
    
    player.minions = after;

    

    
    
    
}

int max_level(Player player)
{
    map<int, Card>::iterator iter;
    iter = player.minions.begin();
    int max_level = 0;
    while(iter != player.minions.end())
    {
        if(iter -> second.level > max_level)
        {
            max_level = iter -> second.level;
        }
        
        iter++;
    }
    
    return max_level;
}


int total_atk(Player player)
{
    map<int, Card>::iterator iter;
    iter = player.minions.begin();
    int total_atk = 0;
    while(iter != player.minions.end())
    {
        total_atk += iter -> second.atk;

        iter++;
    }
    
    return total_atk;
}

/*
 @id :效果编号
 @card: 发效果的卡片信息
 @gameid:发效果的卡片gameid
 @index:发效果的卡片位置信息，如果已经死亡就是原位置信息
 */
void  common_effect_box(int id, Player& mine, Player& enemy, Card& card, int gameid, int index)
{
    
    
    int para[3];
    para[0] = index;
    para[1] = gameid;
    para[2] = card.atk;
    

    effectfuncs[id](mine, enemy, para);
}

/*
 @id:效果编号
 @gameid1: 发动效果的gameid
 @gameid2: 目标随从的gameid
 @index: 发动效果的随从位置
 
 
 
 */
void summon_effect_box(int id, Player& mine, Player& enemy, int gameid1, int gameid2, int index)
{
    int para[3];
    para[0] = index;
    para[1] = gameid1;
    para[2] = gameid2;
    

    effectfuncs[id](mine, enemy, para);
}







