//
//  main.cpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/12.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//

#include <iostream>
#include <map>
#include <random>
#include <cstdlib>
#include <ctime>
#include "Player.hpp"
#include "Card.hpp"
#include "set.hpp"
#include "print.hpp"
#include "global.hpp"
#include "game.hpp"
#include "recruitphase.hpp"
#define TIMES 100
using namespace std;

extern int turn;

int init_player(Player& player)
{
//    Card c106;
//    c106.setbyid(106);
//    player.tavern.push_back(c106);
//    player.handcards.push_back(c106);
//    Card c107;
//    c107.setbyid(107);
//    player.handcards.push_back(c107);
//    Card c101;
//    c101.setbyid(101);
//    player.minions[2] = c101;
//    Card c202;
//    c202.setbyid(202);
//    player.minions[3] = c202;
//    player.minions[4] = c202;
//    player.minions[5] = c202;
    player.coin = 3;
    player.level = 1;
    return 0;
}



int main(int argc, const char * argv[]) {
    

    int winner = -1;
    Player player1;
    player1.setname("哥哥");
    init_player(player1);
    Player player2;
    player2.setname("弟弟");
    init_player(player2);
    
    register_effectfuncs();
    while(player1.herohp > 0 && player2.herohp > 0)
    {
        int point;
        turn++;
        player1.coin = turn + 2;
        if(player1.coin > 10)
        {
            player1.coin = 10;
        }
        player2.coin = turn + 2;
        if(player2.coin > 10)
        {
            player2.coin = 10;
        }
        player1.levelup_cost[player1.level - 1] -= 1;
        if(player1.levelup_cost[player1.level - 1] < 0)
        {
            player1.levelup_cost[player1.level - 1] = 0;
        }
        if(player2.levelup_cost[player2.level - 1] < 0)
        {
            player2.levelup_cost[player2.level - 1] = 0;
        }
        cout << player1.name << "招募阶段" << endl;
        recruit(player1);
        cout << player2.name << "招募阶段" << endl;
        recruit(player2);
        point = auto_attack(winner, player1, player2);
        if(winner == 1)
        {
            player2.herohp = player2.herohp - point;
            if(player2.herohp < 0)
            {
                cout << player2.name << "淘汰" << endl;
                break;
            }
            
            
        }
        if(winner == 2)
        {
            player1.herohp = player1.herohp - point;
            if(player1.herohp < 0)
            {
                cout << player1.name << "淘汰" << endl;
                break;
            }
            
        }
        
    }
    
    
    

    
    
    return 0;
}
