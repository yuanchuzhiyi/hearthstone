//
//  print.hpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/13.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//

#ifndef print_hpp
#define print_hpp

#include <stdio.h>
#include <map>
using namespace std;
class Player;
class Card;

#endif /* print_hpp */

void printplayer(Player player);
//void printboth(Player current_player, Player enemy_player);
void printeasy(Player current_player, Player enemy_player);
void printinfo(Player current_player, Player enemy_player);
void printcurrent(Player mine);
void printcurrentall(Player mine);
void printminion(Player mine);
void printtavern(Player mine);
void printhandcards(Player mine);
