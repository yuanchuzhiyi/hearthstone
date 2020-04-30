//
//  global.hpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/13.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//

#ifndef global_hpp
#define global_hpp
#include <map>
#include <stdio.h>
using namespace std;
#define MAX_MINION 7

class Player;

typedef void (*ef)(Player&, Player&, int self[]);
enum timepoints {NONE,BEFORE_BATTLE,BEFORE_ATTACK,IN_ATTACK,DAMAGE_PHASE,AFTER_DAMAGE,AFTER_ATTACK,DEATH_PHASE,AFTER_DEATH,GAME_OVER,
    TURN_START,TURN_OVER,BATTLECRY,RECRUIT, OTHERS};

enum races {MECH,BEAST,MURLOC,DRAGON,DEMON,PIRATE,TOTEM,ELEMENT,ALL,NEUTRAL};

void register_effectfuncs();

#endif /* global_hpp */
