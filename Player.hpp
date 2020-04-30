//
//  Player.hpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/13.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <list>
using namespace std;

class Card;

class Player
{
public:
    string name;
    int herohp;
    int level;
    int coin;
    int levelup_cost[5];
    list <Card> tavern;
    list <Card> handcards;
    map <int,Card> minions;
    int deadmechs[2];
    Player();
    
    vector<int>gameids;
    void setminions(map <int,Card>);
    void setname(string);
    bool has_minion(string);   //该玩家场上是否存在某个随从，按名字搜索
    bool has_minion(int);      //该玩家场上是否存在某个随从，按id搜索
    int lower_minion(int);   //返回key值小于等于某个index的随从index
    int upper_minion(int);    //返回key值大于某个index的随从index
};
#endif /* Player_hpp */
