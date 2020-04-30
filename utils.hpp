//
//  utils.hpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/13.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//

#ifndef utils_hpp
#define utils_hpp

#include <stdio.h>
#include <map>
using namespace std;
class Player;
class Card;

Player &get_currentplayer(bool flag, Player& player1, Player& player2);
Player &get_enemyplayer(bool flag, Player& player1, Player& player2);
bool has_taunt(map<int,Card> minions);
int battle_random_target(map<int, Card> minions);
int random_target(map<int, Card> minions);
void redistribute(int index, Player& player);
int max_level(Player player);
int total_atk(Player player);
int count_point(int winner, Player player1, Player player2);
int findgameid(Player& player, int gameid);
void  common_effect_box(int id, Player& mine, Player& enemy, Card& card, int gameid, int index);
void summon_effect_box(int id, Player& mine, Player& enemy, int gameid1, int gameid2, int index);
#endif /* utils_hpp */



