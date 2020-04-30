//
//  test.cpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/30.
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
#include "test.hpp"
#define TIMES 100
void test_winrate()
{
        std::random_device rd;
        std::mt19937 mt(rd());
    
        Player player1;
        Player player2;
        player1.setname("哥哥");
        player2.setname("弟弟");
        srand((unsigned int)time(0));
        reset_player(player1, player2);
        /*注册效果id对应表*/
        register_effectfuncs();
    
        int player1_win = 0;
        int player2_win = 0;
        int winner = 0;           //1代表player1获胜，2代表player2获胜,0表示平局
        int player1_point_sum = 0;
        int player2_point_sum = 0;
        int loop = 0;
        while(loop < TIMES)
        {
            int point = auto_attack(winner, player1, player2);
    
    
            if(winner == 1)
            {
                player1_point_sum += point;
                player1_win++;
            }
    
            if(winner == 2)
            {
                player2_point_sum += point;
                player2_win++;
            }
    
//            reset_player(player1, player2);
            loop++;
    
        }
        double player1_winrate = (double)player1_win / (double)TIMES;
        double player2_winrate = (double)player2_win / (double)TIMES;
        double tie_rate = 1 - player1_winrate - player2_winrate;
    
        cout << "经过" << TIMES << "次模拟" << endl;
        if(player1_win == 0)
        {
            cout << "玩家1的胜率为0" << endl;
        }
        else
        {
            cout << "玩家1的胜率为" << player1_winrate << "," << "平均打" << player1_point_sum / player1_win++ << "点血" << endl;
        }
    
        if(player2_win == 0)
        {
            cout << "玩家2的胜率为0" << endl;
    
        }
        else
        {
            cout << "玩家2的胜率为" << player2_winrate << "," << "平均打" << player2_point_sum / player2_win++ << "点血" << endl;
        }
    
        cout << "平局概率为" << tie_rate << endl;
}
