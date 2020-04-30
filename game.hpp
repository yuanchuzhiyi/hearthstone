//
//  game.hpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/13.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//

#ifndef game_hpp
#define game_hpp

#include <stdio.h>

class Player;

int auto_attack(int& winner, Player player1, Player player2);
void get_shield(int index, Player& mine, Player& enemy);
void lose_shield(int index, Player& mine, Player& enemy);
void judge_son(int index, Card& card, Player& mine, Player& enemy);
int add_son(int father, Card sons[], int son_num, Player& mine, Player& enemy);
#endif /* game_hpp */
