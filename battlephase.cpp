//
//  battlephase.cpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/13.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//
#include <map>
#include "battlephase.hpp"
#include "Player.hpp"
#include "Card.hpp"
#include "utils.hpp"
#include "game.hpp"
#include "global.hpp"
#include "death.hpp"
#include "damagephase.hpp"

extern map<int,ef> effectfuncs;
extern timepoints timepoint;



/*
 @last:上一个攻击者index
 @return：下一个攻击者index
 */
int next_attack(Player current_player, Player enemy_player)
{
    if(current_player.minions.empty())
        return -1;
    bool nobody_attacked = true;
    
    map<int, Card>::iterator iter;
    iter = current_player.minions.begin();
    while(iter != current_player.minions.end())
    {
        if(iter ->second.attacked == true)
        {
            nobody_attacked = false;
            break;
        }
        iter++;
        
    }
    
    
    if(nobody_attacked == true)
    {
        iter = current_player.minions.begin();
        return iter -> first;
    }
    
    iter = current_player.minions.end();
    iter--;
    while(iter != current_player.minions.begin())
    {
        if(iter -> second.attacked == false)
        {
            iter--;
            continue;
        }
        
        break;
    }
    
    if(iter == current_player.minions.begin())
    {
        if(iter -> second.attacked == true)
        {
            iter++;
            if(iter == current_player.minions.end())
            {    iter = current_player.minions.begin();
                 return iter -> first;
            }
            return iter -> first;
        }
        else
        {
            return iter -> first;
        }
    }
    
    iter++;
    if(iter == current_player.minions.end())
    {
          iter = current_player.minions.begin();
        
         return iter -> first;
    }
    return iter -> first;
    

}

void before_attack(Player& current_player, Player& enemy_player, int mine)
{
    map<int, Card>::iterator iter;
    iter = current_player.minions.begin();
    while(iter != current_player.minions.end())
    {
        for(int i = 0; i < 5; i++)
         {
             if(iter -> second.timepoint[i] == BEFORE_ATTACK && iter -> first == mine)
             {
                 int id = iter -> second.effectid[i];

                 common_effect_box(id, current_player, enemy_player, iter -> second, iter -> second.gameid, iter -> first);
             }
                 
         }
         iter++;
    }
    
}

void battle(int index1, int index2, Player& current_player, Player& enemy_player) //index1攻击index2
{
    
    int gameid1 = current_player.minions[index1].gameid;
    int gameid2 = enemy_player.minions[index2].gameid;
    
    int damage1 = current_player.minions[index1].poisonous?  9999 : current_player.minions[index1].atk;
    
    damage_phase(gameid1, gameid2, current_player, enemy_player, damage1);
    
    int damage2 = enemy_player.minions[index2].poisonous?  9999 : enemy_player.minions[index2].atk;
    
    pure_damage_phase(gameid2, gameid1, enemy_player, current_player, damage2);
    
    int new_index1 = findgameid(current_player, gameid1);
    
    if(new_index1)
    {
        current_player.minions[new_index1].setattacked(true);
        
        if(current_player.minions[new_index1].windfury == true)
        {
            current_player.minions[new_index1].inthewind++;
            if(current_player.minions[new_index1].inthewind >= 2)
            {
                current_player.minions[new_index1].inthewind = 0;
            }
            
        }
        
        //超杀
        if(current_player.minions[new_index1].overkilled == true)
        {
            if(current_player.minions[new_index1].name == "铁皮恐角龙")
            {
                Card son;
                son.setname("铁皮小恐龙");
                son.setlevel(1);
                son.setbase(5,5);
                son.setrace(BEAST);
                Card sons[1];
                sons[0] = son;
                add_son(new_index1, sons, 1, current_player, enemy_player);
            }
            
        }
    }
    

    
    judge_death(current_player, enemy_player);
    

    
    if(current_player.minions.empty())
        return;
    /*一轮攻击过后重头开始重新攻击*/
    map<int, Card>::iterator iter;
    iter = current_player.minions.end();
    iter--;
    if(iter -> second.attacked == true)   //最后一个也攻击过了
    {
        iter = current_player.minions.begin();
        while(iter != current_player.minions.end())
        {
            iter -> second.attacked = false;
            iter++;
        }
    }

    
}
