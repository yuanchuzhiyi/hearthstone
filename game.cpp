//
//  game.cpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/13.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//


#include <iostream>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <vector>
#include "effect_func.hpp"
#include "Player.hpp"
#include "Card.hpp"
#include "battlephase.hpp"
#include "set.hpp"
#include "print.hpp"
#include "game.hpp"
#include "utils.hpp"
#include "global.hpp"
#include "death.hpp"

#define TIMES 1

using namespace std;
extern map<int,ef> effectfuncs;
extern timepoints timepoint;
extern int global_id;
void before_battle(Player& current_player, Player& enemy_player)
{
     map<int, Card>::iterator iter;

     iter = current_player.minions.begin();
     while(iter != current_player.minions.end())
     {
         for(int i = 0; i < 5; i++)
         {
             if(iter -> second.timepoint[i] == BEFORE_BATTLE)
             {
                 int id = iter -> second.effectid[i];

                 common_effect_box(id, current_player, enemy_player, iter -> second, iter -> second.gameid, iter -> first);
             }
             
         }
         
         iter++;
     }
    
     iter = enemy_player.minions.begin();
     while(iter != enemy_player.minions.end())
     {
         for(int i = 0; i < 5; i++)
         {
             if(iter -> second.timepoint[i] == BEFORE_BATTLE)
             {
                 int id = iter -> second.effectid[i];

                 common_effect_box(id, enemy_player, current_player, iter -> second, iter -> second.gameid, iter -> first);
             }
                 
         }
         iter++;
     }
}


/*
 index不变安全函数
 */

void get_shield(int index, Player& mine, Player& enemy)  //mine的index号随从获得圣盾
{
    mine.minions[index].setshield(true);
}

/*
 index不变安全函数
 */
void lose_shield(int index, Player& mine, Player& enemy)  //mine的index号随从失去圣盾
{
    mine.minions[index].setshield(false);
    map<int, Card>::iterator iter;
    
    iter = mine.minions.begin();
    while(iter != mine.minions.end())
    {
        if(iter -> second.name == "鲭鱼圣者" && (iter -> first != index) )
        {
            get_shield(iter -> first, mine, enemy);
            cout << "鲭鱼圣者补盾" << endl;
        }
        iter++;
    }
        
    

        
       
    iter = mine.minions.begin();
    while(iter != mine.minions.end())
    {
        if(iter -> second.name == "龙人执行者")
        {
            iter -> second.atk += 2;
            iter -> second.hp += 2;
            cout << "龙人执行者+2/+2" << endl;
        }
        
        if(iter -> second.name == "金色龙人执行者")
        {
            iter -> second.atk += 4;
            iter -> second.hp += 4;
            cout << "龙人执行者+4/+4" << endl;
        }
        
        iter++;
    }
    
    
    iter = mine.minions.begin();
    while(iter != mine.minions.end())
    {
        if(iter -> second.name == "浴火者伯瓦尔")
        {
            iter -> second.atk += 2;
            cout << "伯瓦尔+2" << endl;
        }
        if(iter -> second.name == "金色浴火者伯瓦尔")
        {
            iter -> second.atk += 4;
            cout << "伯瓦尔+4" << endl;
        }
        
        iter++;
    }
    
    
    
}

void judge_son(int index, Card& card, Player& mine, Player& enemy)    //mine场上多了一个card随从,编号为index
{
    if(card.race == MECH)
    {

        map<int, Card>::iterator iter;
        iter = mine.minions.begin();
        while(iter != mine.minions.end())
        {
             if(iter -> second.name == "偏折机器人")
             {
                 iter -> second.atk += 1;
                 if(iter -> second.shield == false)
                 {
                     get_shield(iter -> first, mine, enemy);
                     cout << "偏折机器人补盾" << endl;
                 }

             }
             iter++;
         }
        
    }
    
    if(card.race == MURLOC)
    {
        
        map<int, Card>::iterator iter;
        iter = mine.minions.begin();
        while(iter != mine.minions.end())
        {
             if(iter -> second.name == "鱼人招潮者")
             {
                 iter -> second.atk += 1;

             }
             iter++;
         }
        
        
        
        iter = mine.minions.begin();
        while(iter != mine.minions.end())
        {
             if(iter -> second.name == "鱼人领军")
             {
                 card.atk += 2;

             }
             iter++;
         }
        
        
        
        iter = mine.minions.begin();
        while(iter != mine.minions.end())
        {
            if(iter -> second.name == "老瞎眼" && iter -> first != index)
            {
                iter -> second.atk -=1;
            }
            iter++;
        }
        iter = enemy.minions.begin();
        while(iter != enemy.minions.end())
        {
            if(iter -> second.name == "老瞎眼")
            {
                iter ->second.atk -= 1;
            }
            iter++;
        }
        
        
    }
        
    
    if(card.race == BEAST)
    {
        
        map<int, Card>::iterator iter;
        iter = mine.minions.begin();
        while(iter != mine.minions.end())
        {
             if(iter -> second.name == "熊妈妈" && (iter -> first != index))
             {
                 card.atk += 5;
                 card.hp += 5;

             }
             if(iter -> second.name == "族群领袖")
             {
                 card.atk += 3;
             }
             iter++;
         }
        
    }
    
        
    if(card.race == DEMON)
    {
        map<int, Card>::iterator iter;
        iter = mine.minions.begin();
        while(iter != mine.minions.end())
        {
             if(iter -> second.name == "玛尔加尼斯" && (iter -> first != index))
             {
                 card.atk += 2;
                 card.hp += 2;

             }
             iter++;
         }
        
        iter = mine.minions.begin();
        while(iter != mine.minions.end())
        {
             if(iter -> second.name == "攻城恶魔" && (iter -> first != index))
             {
                 card.atk += 1;
                

             }
             iter++;
         }
        
        
    }

        
}

/*
 @father:父随从index
 @son_num:数组元素个数
 @return: -1失败
 */
    
int add_son(int father, Card sons[], int son_num, Player& mine, Player& enemy)
{
    if(mine.minions.size() == MAX_MINION)
        return 0;
    
    if(son_num > MAX_MINION)
    {
        cout << "儿子太多了" << endl;
        return -1;
    }
    redistribute(father, mine);
//    int upper = mine.upper_minion(father);
    int lower = mine.lower_minion(father);
    
    
    size_t minion_size = mine.minions.size();
    
    int add_max = (int)(MAX_MINION - minion_size);
    if(son_num > add_max)
        son_num = add_max;
    
    int start = lower + 1;
    for(int i = 0; i < son_num; i++)
    {
        if(mine.minions.find(start) != mine.minions.end())
        {
            cout << "重分布出错，这个位置不该有随从" << endl;
            return -1;
        }
        
        if(!mine.has_minion("卡德加"))
        {
            mine.minions[start] = sons[i];
            judge_son(start, mine.minions[start], mine, enemy);
            start++;
        }
        
        if(mine.has_minion("卡德加"))
        {
            
            map<int, Card>::iterator iter;
            iter = mine.minions.begin();
            while(iter != mine.minions.end())
            {
                if(iter -> second.name == "卡德加" && find(mine.gameids.begin(),mine.gameids.end(),iter -> second.gameid)
                   != mine.gameids.end())
                {
                    mine.gameids.push_back(iter -> second.gameid);
                    Card kasons[2];
                    kasons[0] = sons[i];
                    kasons[1] = sons[i];
                    add_son(father, kasons, 2, mine, enemy);
                }
                iter++;
            }
            

            
        }
//        if(mine.has_minion("金色卡德加"))
//        {
//
//            Card kasons[3];
//            kasons[0] = sons[i];
//            kasons[1] = sons[i];
//            kasons[2] = sons[i];
//            add_son(father, kasons, 3, mine, enemy);
//        }
        
        
        
    }

    
    
    
    return 1;
    
    
    
    
}



    
/*在所有之前，查看有没有二王之类的buff*/
void above_all(Player& player1, Player& player2)
{
    map<int, Card>::iterator iter;
    
    iter = player1.minions.begin();
    while(iter != player1.minions.end())
    {
        if(iter -> second.name == "玛尔加尼斯")
        {
            map<int, Card>::iterator other;
            other = player1.minions.begin();
            while(other != player1.minions.end())
            {
                if( (other -> first != iter -> first) && (other ->second.race == DEMON) )
                {
                    other -> second.atk += 2;
                    other -> second.hp +=2;
                }
                other++;
            }
        }
        
        iter++;
    }
    
    
    iter = player1.minions.begin();
    while(iter != player1.minions.end())
    {
        if(iter -> second.name == "攻城恶魔")
        {
            map<int, Card>::iterator other;
            other = player1.minions.begin();
            while(other != player1.minions.end())
            {
                if( (other -> first != iter -> first) && (other ->second.race == DEMON) )
                {
                    other -> second.atk += 1;
                    
                }
                other++;
            }
        }
        
        iter++;
    }
    
    
    iter = player1.minions.begin();
    while(iter != player1.minions.end())
    {
        if(iter -> second.name == "鱼人领军")
        {
            map<int, Card>::iterator other;
            other = player1.minions.begin();
            while(other != player1.minions.end())
            {
                if( (other -> first != iter -> first) && (other ->second.race == MURLOC) )
                {
                    other -> second.atk += 2;
                    
                }
                other++;
            }
        }
        
        iter++;
    }
    
    
    
   iter = player1.minions.begin();
   while(iter != player1.minions.end())
   {
       if(iter -> second.name == "老瞎眼")
       {
           
           int count = 0;
           map<int, Card>::iterator count_iter;
           count_iter = player1.minions.begin();
           while(count_iter != player1.minions.end())
           {
               if(count_iter -> second.race == MURLOC && (count_iter ->first != iter -> first))
               {
                   count++;
               }
               count_iter++;
           }
           count_iter = player2.minions.begin();
           while(count_iter != player2.minions.end())
           {
               if(count_iter -> second.race == MURLOC)
               {
                   count++;
               }
               count_iter++;
           }
           
           iter -> second.atk += count;
       }
       iter++;
   }
    
    
    
    
    
    /*----------------------------------------------------------------------------------------------*/
    
    
    iter = player2.minions.begin();
    while(iter != player2.minions.end())     //找到所有二王
    {
        if(iter -> second.name == "玛尔加尼斯")
        {
            map<int, Card>::iterator other;
            other = player2.minions.begin();
            while(other != player2.minions.end())
            {
                if( (other -> first != iter -> first) && (other ->second.race == DEMON) )//排除自己
                {
                    other -> second.atk += 2;
                    other -> second.hp +=2;
                }
                
                other++;
            }
        }
        
        iter++;
    }
    
    
    iter = player2.minions.begin();
    while(iter != player2.minions.end())
    {
        if(iter -> second.name == "攻城恶魔")
        {
            map<int, Card>::iterator other;
            other = player2.minions.begin();
            while(other != player2.minions.end())
            {
                if( (other -> first != iter -> first) && (other ->second.race == DEMON) )
                {
                    other -> second.atk += 2;
                    
                }
                other++;
            }
        }
        
        iter++;
    }
    
    
    
    iter = player2.minions.begin();
    while(iter != player2.minions.end())
    {
        if(iter -> second.name == "鱼人领军")
        {
            map<int, Card>::iterator other;
            other = player2.minions.begin();
            while(other != player2.minions.end())
            {
                if( (other -> first != iter -> first) && (other ->second.race == MURLOC) )
                {
                    other -> second.atk += 2;
                    
                }
                other++;
            }
        }
        
        iter++;
    }
    
    
    
    iter = player2.minions.begin();
    while(iter != player2.minions.end())
    {
        if(iter -> second.name == "老瞎眼")
        {
            
            int count = 0;
            map<int, Card>::iterator count_iter;
            count_iter = player2.minions.begin();
            while(count_iter != player2.minions.end())
            {
                if(count_iter -> second.race == MURLOC && (count_iter ->first != iter -> first))
                {
                    count++;
                }
                count_iter++;
            }
            count_iter = player1.minions.begin();
            while(count_iter != player1.minions.end())
            {
                if(count_iter -> second.race == MURLOC)
                {
                    count++;
                }
                count_iter++;
            }
            
            iter -> second.atk += count;
        }
        
        iter++;
    }
    
    

    
   
    
}


int judge_winner(int& winner, int hero1_level, int hero2_level, Player player1, Player player2)
{

    
    if(player1.minions.empty() && player2.minions.empty())
    {
        cout << "平局" << endl;
        timepoint = GAME_OVER;
        winner = 0;
        global_id = 0;
        return 0;
    }
    
    if(player2.minions.empty())
    {
        
        timepoint = GAME_OVER;
        winner = 1;
        global_id = 0;
        int total_point = count_point(winner, player1, player2) + hero1_level;
        cout << "player1获胜" << "打了" << total_point << "点血" << endl;
        return total_point;
    
    }
    if(player1.minions.empty())
    {
        
        timepoint = GAME_OVER;
        winner = 2;
        global_id = 0;
        int total_point = count_point(winner, player1, player2) + hero2_level;
        cout << "player2获胜" << "打了" << total_point<< "点血" << endl;
        return total_point;
    }
    
    if(total_atk(player1) == 0 && total_atk(player2) == 0)
    {
        cout << "平局" << endl;
        timepoint = GAME_OVER;
        winner = 0;
        global_id = 0;
        return 0;
    }
    
    return -1;
    
}




    
int auto_attack(int& winner, Player player1, Player player2)
{
    cout << "进入自动战斗！" << endl;
    cout << "双方初始阵容为" << endl;

    srand((unsigned int)time(0));
    int count = 0;     //最大互相攻击次数限制器
    
    int player1_maxlevel = max_level(player1);
    int player2_maxlevel = max_level(player2);
    int point = 0;
    point = judge_winner(winner, player1_maxlevel, player2_maxlevel, player1, player2);
    if(point >= 0)
    {
        return point;
    }
    
    above_all(player1, player2);   //pos不变函数
    
    
    printplayer(player1);
    printplayer(player2);
    

    timepoint = BEFORE_BATTLE;

    before_battle(player1, player2);
    
    cout << "开局效果处理完毕后阵容为" << endl;
    printinfo(player1, player2);
    
    timepoint = NONE;
    
    point = judge_winner(winner, player1_maxlevel, player2_maxlevel, player1, player2);
    if(point >= 0)
    {
        return point;
    }
    
    
    
    cout<< "--------------------" << endl;
    
    bool flag = true;
    while(1)
    {
        timepoint = BEFORE_BATTLE;
        cout << "before_attack开始时阵容！！！" << endl;
        
        Player& current_player = get_currentplayer(flag, player1, player2);
        Player& enemy_player = get_enemyplayer(flag, player1, player2);
        
        printinfo(current_player, enemy_player);
       
        /*判断当前攻击次序,谁攻击谁*/
         
        int mine = next_attack(current_player, enemy_player);
        if(mine == 0)
        {
            cout << "出错" << endl;
            return -1;
            
        }
        int target = battle_random_target(enemy_player.minions);
        before_attack(current_player, enemy_player, mine);

        
        cout << mine << "号随从攻击" << target << "号随从" << endl;
        
        
        battle(mine, target, current_player, enemy_player);
        
        
        /*风怒处理*/
        map<int, Card>::iterator iter;
        iter = current_player.minions.begin();
        while(iter != current_player.minions.end())
        {
            if(iter -> second.inthewind == 1)
            {
                int target = battle_random_target(enemy_player.minions);
                cout << iter -> first << "号随从攻击" << target << "号随从" << endl;
                battle(iter -> first, target, current_player, enemy_player);
                break;
            }
            iter++;
                
        }
        
        
        
        if(current_player.minions.find(0) != current_player.minions.end() || enemy_player.minions.find(0) != enemy_player.minions.end())
        {
            cout << "出错" << endl;
            return -1 ;
        }
        
        printinfo(current_player, enemy_player);


        cout << endl;
        cout << endl;
        flag = !flag; //更换选手


        //如果一方空场，则跳出循环
        
        if((current_player.minions.size() == 0) || (enemy_player.minions.size() == 0)
           || (total_atk(current_player) == 0 && total_atk(enemy_player) == 0) )
        {
            break;
        }
        count++;
        if(count >= 100)
        {
            cout << "循环次数过多，可能有bug" << endl;
            break;
            
        }

    }
    
    
    
    player1_maxlevel = player1.level;
    player2_maxlevel = player2.level;
    point = judge_winner(winner, player1_maxlevel, player2_maxlevel, player1, player2);
    if(point >= 0)
    {
        return point;
    }
    return -1;
    
    
    
    
}

