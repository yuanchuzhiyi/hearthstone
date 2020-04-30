//
//  battlephase.hpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/13.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//

#ifndef battlephase_hpp
#define battlephase_hpp

#include <stdio.h>

class Player;



void damage_phase(int index1, int index2, Player& current_player, Player& enemy_player, int damage);
void pure_damage_phase(int index1, int index2, Player& current_player, Player& enemy_player, int damage);
void battle(int index1, int index2, Player& current_player, Player& enemy_player);
int next_attack(Player current_player, Player enemy_player);
void before_attack(Player& current_player, Player& enemy_player, int mine);
#endif /* battlephase_hpp */
