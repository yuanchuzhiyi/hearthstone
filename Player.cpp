//
//  Player.cpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/13.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//

#include "Player.hpp"
#include "Card.hpp"
#include "global.hpp"

extern map<int,ef> effectfuncs;
extern timepoints timepoint;
Player::Player()
{
    name = "unknown";
    level = 1;
    herohp = 40;
    coin = 3;
    levelup_cost[0] = 6;
    levelup_cost[1] = 7;
    levelup_cost[2] = 9;
    levelup_cost[3] = 10;
    levelup_cost[4] = 12;

    deadmechs[0] = 0;
    deadmechs[1] = 0;
}
void Player::setminions(map <int,Card> minions)
{
    this -> minions = minions;
}


void Player::setname(string name)
{
    this -> name = name;
}

bool Player::has_minion(string name)
{
    map<int, Card>::iterator iter;
    iter = minions.begin();
    while(iter != minions.end())
    {
        if(iter -> second.name == name)
        {
            return true;
        }
        
        iter++;
    }
    
    return false;
}

bool Player::has_minion(int id)
{
    map<int, Card>::iterator iter;
    iter = minions.begin();
    while(iter != minions.end())
    {
        if(iter -> second.id == id)
        {
            return true;
        }
        
        iter++;
    }
    
    return false;
}

/*
 
@return: 没有更小的元素返回0
 */
int Player::lower_minion(int index)
{
    map<int, Card>::iterator iter;
    while(index >= 1)
    {
        if(minions.find(index) != minions.end())
        {
            return index;
        }
        else
        {
            index--;
        }
    }
    
    return 0;
}

/*
 
@return: 没有更大的元素返回MAX_MINION + 1
 */
int Player::upper_minion(int index)
{
    
    map<int, Card>::iterator iter;
    iter = minions.find(index);
    if(iter != minions.end())
    {
        iter++;
        if(iter == minions.end())
        {
            return MAX_MINION + 1;
        }
        else
        {
            return iter -> first;
        }
    }
    while(index < MAX_MINION + 1)
    {
        if(minions.find(index) != minions.end())
        {
            return index;
        }
        else
        {
            index++;
        }
    }
    
    return -1;
}
