//
//  death.cpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/17.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
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
extern map<int,ef> effectfuncs;
extern timepoints timepoint;
using namespace std;

void effect_box(int id, Player& mine, Player& enemy, map<int,Card>& dead, int index)
{
    map<int, Card>::iterator iter;
    iter = dead.find(index);
    int para[2];
    para[0] = index;
    para[1] = 0;
    
    if(iter -> second.name == "邪魔仆从" || iter -> second.name == "瘟疫鼠群")
    {
        para[1] = iter -> second.atk;
        effectfuncs[id](mine, enemy, para);
    }
    
    effectfuncs[id](mine, enemy, para);
}


void after_death(Card dead, Player& mine, Player& enemy, int index)
{
    
    /*回收机器人效果处理*/
    if(dead.race == MECH)
    {
        
        map<int, Card>::iterator iter;
        iter = mine.minions.begin();
        while(iter != mine.minions.end())
        {
            if(iter -> second.name == "回收机器人")
            {
                iter -> second.atk += 2;
                iter -> second.hp += 2;
            }
            
            iter++;
        }
        
    }
    
    if(dead.race == BEAST)
    {
        map<int, Card>::iterator iter;
        iter = mine.minions.begin();
        while(iter != mine.minions.end())
        {
            if(iter -> second.name == "食腐土狼")
            {
                iter -> second.atk += 2;
                iter -> second.hp += 1;
            }
            
            iter++;
        }
    }
    
    if(dead.race == DEMON)
    {
        map<int, Card>::iterator iter;
        iter = mine.minions.begin();
        vector<int> mine_gameids;
        while(iter != mine.minions.end())
        {
            if(iter -> second.name == "灵魂杂耍者" &&
               (find(mine_gameids.begin(), mine_gameids.end(), iter -> second.gameid) == mine_gameids.end()) )
            {
                int target = random_target(enemy.minions);
                cout << "喷子喷到" << target << "号随从" << endl;
                mine_gameids.push_back(iter -> second.gameid);
                pure_damage_phase(iter -> second.gameid, enemy.minions[target].gameid, mine, enemy, 3);
                judge_death(mine, enemy);
                iter = mine.minions.begin();
                continue;
            }
            
            iter++;
        }
        
    }
    
    if(dead.race == MURLOC)
    {
        map<int, Card>::iterator iter;
        iter = mine.minions.begin();
        while(iter != mine.minions.end())
        {
            if(iter -> second.name == "老瞎眼")
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
                iter -> second.atk -=1;
            }
            
            iter++;
        }
    }
    
    if(dead.race == MECH)
    {
        if(mine.deadmechs[0] == 0 || mine.deadmechs[1] == 0)
        {
            if(mine.deadmechs[0] == 0)
            {
                mine.deadmechs[0] = dead.id;
                return;
                
            }
            
            if(mine.deadmechs[1] == 0)
            {
                mine.deadmechs[1] = dead.id;
                return;
            }
                
        }
    }
    

}


void deal_death(Player& mine, Player& enemy)
{
    map<int, Card>::iterator iter;
    
    /*先进行所有死亡结算*/
    map<int, Card> enemy_temp;
    if(!enemy.minions.empty())
    {
        iter = enemy.minions.begin();
        while(iter != enemy.minions.end())
        {
            if(iter -> second.dead == true)
            {
                if( !( iter ->second.has_deatheffect() ) )
                {
                    
                    int index = iter -> first;
                    Card dead = iter -> second;
                    
                    enemy.minions.erase(iter -> first);
                    
                    
                    after_death(dead, enemy, mine, index);
                    
                    /*清除后iter变成野指针，需要重置重新扫描*/
                    if(!enemy.minions.empty())
                    {
                        iter = enemy.minions.begin();
                        continue;
                    }
                    break;
                    
                }
                    
                else
                {
                    enemy_temp[iter -> first] = iter -> second;
                    
                    int index = iter -> first;
                    Card dead = iter -> second;
                    
                    enemy.minions.erase(iter -> first);
                    
                    after_death(dead, enemy, mine, index);
                    
                    
                    if(!enemy.minions.empty())
                    {
                        iter = enemy.minions.begin();
                        continue;
                    }
                    break;
                    
                }
            }
            iter++;
        }
        
    }
    
    map<int, Card> mine_temp;
    if(!mine.minions.empty())
    {
        iter = mine.minions.begin();
        while(iter != mine.minions.end())
        {
            if(iter -> second.dead == true)
            {
                if( !( iter ->second.has_deatheffect() ) )
                {
                    int index = iter -> first;
                    Card dead = iter -> second;
                    
                    mine.minions.erase(iter -> first);
                    
                    after_death(dead, mine, enemy, index);
                    
                    if(!mine.minions.empty())
                    {
                        iter = mine.minions.begin();
                        continue;
                    }
                    break;
                }
                    
                else
                {
                    mine_temp[iter -> first] = iter -> second;
                    
                    int index = iter -> first;
                    Card dead = iter -> second;
                    
                    mine.minions.erase(iter -> first);
                    
                    after_death(dead, mine, enemy, index);
                    
                    if(!mine.minions.empty())
                    {
                        iter = mine.minions.begin();
                        continue;
                    }
                    break;
                    
                }
            }
            iter++;
        }
        
    }
    
    /*再进行亡语触发*/
    iter = enemy_temp.begin();        //先敌方
    while(iter != enemy_temp.end())
    {
        for(int i = 0; i < 5; i++)
        {
            if(iter -> second.timepoint[i] == DEATH_PHASE)
            {
                int id = iter -> second.effectid[i];
                
                if(!enemy.has_minion("瑞文戴尔男爵") )
                    common_effect_box(id, enemy, mine, iter -> second, iter -> second.gameid, iter -> first);
                if(enemy.has_minion("瑞文戴尔男爵"))
                {
                    if(iter -> second.deathrattle == true)
                    {
                        common_effect_box(id, enemy, mine, iter -> second, iter -> second.gameid, iter -> first);
                        common_effect_box(id, enemy, mine, iter -> second, iter -> second.gameid, iter -> first);
                    }
                    else
                    {
                        common_effect_box(id, enemy, mine, iter -> second, iter -> second.gameid, iter -> first);
                    }
                        
                    
                }
                if(enemy.has_minion("金色瑞文戴尔男爵"))
                {
                    if(iter -> second.deathrattle == true)
                    {
                        common_effect_box(id, enemy, mine, iter -> second, iter -> second.gameid, iter -> first);
                        common_effect_box(id, enemy, mine, iter -> second, iter -> second.gameid, iter -> first);
                        common_effect_box(id, enemy, mine, iter -> second, iter -> second.gameid, iter -> first);
                    }
                    else
                    {
                        common_effect_box(id, enemy, mine, iter -> second, iter -> second.gameid, iter -> first);
                    }
                       
                    
                }

            }
                
            
        }
        iter++;
            
    }
    
    iter = mine_temp.begin();        //再我方
    while(iter != mine_temp.end())
    {
          for(int i = 0; i < 5; i++)
           {
               if(iter -> second.timepoint[i] == DEATH_PHASE)
               {
                    int id = iter -> second.effectid[i];

                    if(!mine.has_minion("瑞文戴尔男爵"))
                        common_effect_box(id, mine, enemy, iter -> second, iter -> second.gameid, iter -> first);
                    if(mine.has_minion("瑞文戴尔男爵") )
                    {
                        if(iter -> second.deathrattle == true)
                        {
                            common_effect_box(id, mine, enemy, iter -> second, iter -> second.gameid, iter -> first);
                            common_effect_box(id, mine, enemy, iter -> second, iter -> second.gameid, iter -> first);
                        }
                        else
                        {
                            common_effect_box(id, mine, enemy, iter -> second, iter -> second.gameid, iter -> first);
                        }
                    }
                    if(mine.has_minion("金色瑞文戴尔男爵"))
                    {
                        
                        if(iter -> second.deathrattle == true)
                        {
                            common_effect_box(id, mine, enemy, iter -> second, iter -> second.gameid, iter -> first);
                            common_effect_box(id, mine, enemy, iter -> second, iter -> second.gameid, iter -> first);
                            common_effect_box(id, mine, enemy, iter -> second, iter -> second.gameid, iter -> first);
                        }
                        else
                        {
                            common_effect_box(id, mine, enemy, iter -> second, iter -> second.gameid, iter -> first);
                        }
                    }

                 
               }
                   
               
           }
        iter++;
    }
        
    
    
}


void judge_death(Player& mine, Player& enemy)
{
    map<int, Card>::iterator iter;
    iter = enemy.minions.begin();
    while(iter != enemy.minions.end())
    {
        if(iter -> second.dead == true)
        {
            deal_death(mine,enemy);
            break;
            
        }
        iter++;
    }
    
    iter = mine.minions.begin();
    while(iter != mine.minions.end())
    {
        if(iter -> second.dead == true)
        {
            
            deal_death(mine,enemy);
            break;
            
        }
        iter++;
    }
    
}
