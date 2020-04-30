//
//  damagephase.hpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/17.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//

#ifndef damagephase_hpp
#define damagephase_hpp

#include <stdio.h>

class Player;

void damage_phase(int index1, int index2, Player& current_player, Player& enemy_player, int damage);
void pure_damage_phase(int index1, int index2, Player& current_player, Player& enemy_player, int damage);

#endif /* damagephase_hpp */
