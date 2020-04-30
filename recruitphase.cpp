//
//  recruitphase.cpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/24.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//
#include <random>
#include "recruitphase.hpp"
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
#include "damagephase.hpp"
#include "summon.hpp"


extern timepoints timepoint;
extern int level_minion_count[];
extern int level_total_number[];
extern int levelup_cost[];



int get_random_level(int max_level)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    int max = 0;
    for(int i = 0; i < max_level; i++)
    {
        max = max + level_total_number[i];
    }
    int seed = mt() % max;
    if(seed >= 0 && seed < level_total_number[0])
    {
        return 1;
    }
    if(seed >= level_total_number[0] && seed < level_total_number[0] + level_total_number[1])
    {
        return 2;
    }
    if(seed >= level_total_number[0] + level_total_number[1] && seed < level_total_number[0] + level_total_number[1] +level_total_number[2])
    {
        return 3;
    }
    if(seed >= level_total_number[0] + level_total_number[1] +level_total_number[2] && seed <
       level_total_number[0] + level_total_number[1] +level_total_number[2] + level_total_number[3])
    {
        return 4;
    }
    if(seed >= level_total_number[0] + level_total_number[1] +level_total_number[2] + level_total_number[3] && seed < level_total_number[0] + level_total_number[1] +level_total_number[2] + level_total_number[3] + level_total_number[4])
    {
        return 5;
    }
    if(seed >= level_total_number[0] + level_total_number[1] +level_total_number[2] + level_total_number[3] + level_total_number[4] && seed < level_total_number[0] + level_total_number[1] +level_total_number[2] + level_total_number[3] + level_total_number[4] + level_total_number[5])
    {
        return 6;
    }
    return -1;
}

void refresh(Player& mine)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    if(timepoint != TURN_START)
    {
        if(mine.coin == 0)
        {
            cout << "没钱了" << endl;
            return;
        }
        else
        {
            mine.coin -= 1;
        }
        
    }
    mine.tavern.clear();
    int level_max[] = {3, 4, 5, 5, 6, 6};
    int level = mine.level;

   
    
    
    for(int i = 0; i < level_max[level - 1]; i++)
    {
        Card card;
        int card_level = get_random_level(level);
        int card_id = card_level * 100 + mt() % level_minion_count[card_level - 1] + 1;
        card.setbyid(card_id);
        mine.tavern.push_back(card);
    }
    printtavern(mine);
}

void buy(Player& mine, int index)
{
    if(index < 1 || index > mine.tavern.size())
    {
        cout << "请输入正确的随从的位置" << endl;
        return;
    }
    if(mine.coin < 3)
    {
        cout << "钱不够！" << endl;
        return;
    }
    mine.coin -= 3;
    Card card;
    list<Card>::iterator iter;
    iter = mine.tavern.begin();
    int loop = index;
    while(iter != mine.tavern.end())
    {
        loop--;
        if(loop == 0)
        {
            
            mine.handcards.push_back(*iter);
            mine.tavern.erase(iter);
            break;
        }
        
        ++iter;
    }
    printhandcards(mine);
    
    
}

void display(Player& mine, int para)
{
    if(para == 1)
    {
        printcurrent(mine);
    }
    else if(para == 2)
    {
        printcurrentall(mine);
    }
    else if(para == 3)
    {
        printplayer(mine);
    }
    else
    {
        cout << "无效的参数！" << endl;
    }
    
}

void levelup(Player& mine)
{
    if(mine.level == 6)
    {
        cout << "已经是最高等级！" << endl;
        return;
    }
    if(mine.coin < mine.levelup_cost[mine.level - 1])
    {
        cout << "升级的钱不够！" << endl;
        return;
    }
    mine.coin -= mine.levelup_cost[mine.level - 1];
    mine.level += 1;
}

void sell(Player& mine, int index)
{
    mine.minions.erase(index);
    mine.coin += 1;
    if(mine.coin > 10)
        mine.coin = 10;
    printminion(mine);
}

void move(Player& mine, int origin, int dest)
{
    
    Card card = mine.minions[origin];
    mine.minions.erase(origin);
    redistribute(dest, mine);
    int insertindex = mine.lower_minion(dest) + 1;
    mine.minions[insertindex] = card;
    printminion(mine);
}

void recruit(Player& mine)
{
    timepoint = TURN_START;
    //turn_start_phase();
    refresh(mine);
    printcurrent(mine);
    while(1)
    {   timepoint = RECRUIT;
        cout << "请输入下一步动作" << endl;
        string funcname;
        cin >> funcname;

        if(funcname == "refresh" || funcname == "r")
        {
            refresh(mine);
        }
        if(funcname == "freeze")
        {
            //freze();
        }
        if(funcname == "levelup")
        {
            levelup(mine);
        }
        if(funcname == "buy" || funcname == "b")
        {
            int index;
            cin >> index;
            if(!(index > 0 && index <= mine.tavern.size()))
            {
                cout << "请输入正确的位置！" << endl;
            }
            buy(mine, index);
            
        }
        if(funcname == "sell" || funcname == "s")
        {
            int pos; // 1到MAX_MINION
            int index = -1;
            cin >> pos;
            if(!(pos > 0 && pos <= mine.minions.size()))
            {
                cout << "请输入正确的位置！" << endl;
                continue;
            }
            map<int, Card>::iterator iter;
            iter = mine.minions.begin();
            while(iter != mine.minions.end())
            {
                pos--;
                if(pos == 0)
                {
                    index = iter -> first;
                    break;
                }
                iter++;
            }
            
            sell(mine, index);
          
        }
        if(funcname == "move")
        {
            int originpos;
            int destpos;
            int origin = -1;
            int dest = -1;
            cin >> originpos;
            cin >> destpos;  //放在哪个随从后面 0-size
            if((originpos < 1 || originpos > mine.minions.size()) || (destpos < 0 || destpos > mine.minions.size()) )
            {
                cout << "请输入正确的位置！" << endl;
            }
            map<int, Card>::iterator iter;
            iter = mine.minions.begin();
            while(iter != mine.minions.end())
            {
                originpos--;
                if(originpos == 0)
                {
                    origin = iter -> first;
                    break;
                }
                ++iter;
            }
            if(destpos == 0)
            {
                dest = 0;
            }
            else
            {
                iter = mine.minions.begin();
                while(iter != mine.minions.end())
                {
                    destpos--;
                    if(destpos == 0)
                    {
                        dest = iter -> first;
                        break;
                    }
                    
                    ++iter;
                }
            }
            
            
            move(mine, origin, dest);
        }
        if(funcname == "display" || funcname == "d" || funcname == "l")
        {
            if(funcname == "l")
            {
                display(mine, 1);
            }
            else
            {
                int para;
                cin >> para;
                display(mine, para);
            }
            
            
        }
        if(funcname == "call" || funcname == "c")
        {
            int handpos;
            int resultpos;
            int targetpos;
            map<int, Card>::iterator iter;
            cin >> handpos;   //手牌
            cin >> resultpos;   //放在哪个位置后面0-7
            cin >> targetpos;   //目标
            int field_index = -1;
            int target_index = -1;
            if(mine.minions.size() == MAX_MINION)
            {
                cout << "场上没有位置放置随从了" << endl;
                continue;
            }
            if(handpos < 1 || handpos > mine.handcards.size())
            {
                cout << "手牌上没有这个位置的随从" << endl;
                continue;
            }
            
            if(resultpos < 0 || resultpos > mine.minions.size())
            {
                cout << "放置的位置不对" << endl;
                continue;
            }
            if(targetpos > mine.minions.size() || targetpos < 0)
            {
                cout << "效果对象位置不对，如果没有效果用0替代" << endl;
                continue;
                
            }
            if(resultpos == 0)
            {
                field_index = 0;
            }
            else
            {
                iter = mine.minions.begin();
                while(iter != mine.minions.end())
                {
                    resultpos--;
                    
                    if(resultpos == 0)
                    {
                        field_index = iter -> first;
                        break;
                    }
                    
                    iter++;
                }
                
            }
            
            if(targetpos <= 0 && targetpos > mine.minions.size())
            {
                target_index = -1;
            }
            
            else
            {
                iter = mine.minions.begin();
                while(iter != mine.minions.end())
                {
                    targetpos--;
                    if(targetpos == 0)
                    {
                        target_index = iter -> first;
                        break;
                    }
                    iter++;
                }
            }
            
            
//            printplayer(mine);
            summon(mine, handpos, field_index, target_index);
            printminion(mine);
        }
        
        if(funcname == "help")
        {
            //helpinfo();
        }
        if(funcname == "end" || funcname == "e" || funcname == "e")
        {
            break;
        }
        

        
        
    }
    
    timepoint = TURN_OVER;
        
        
    //turn_over_phase();
}
