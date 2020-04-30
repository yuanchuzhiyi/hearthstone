//
//  damagephase.cpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/17.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//


#include <iostream>
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
#include "damagephase.hpp"

extern map<int,ef> effectfuncs;
extern timepoints timepoint;

/*
 index可变不安全函数
 */
void after_damage(int gameid1, int gameid2, Player& mine, Player& enemy, int damage)
{
    int index1 = findgameid(mine, gameid1);
    if(index1 == 0)
    {
        cout << "造成伤害的随从已经死亡" << endl;
        return;
    }
    int index2 = findgameid(enemy, gameid2);
    if(index2 == 0)
    {
        cout << "受到伤害的随从已经死亡" << endl;
        return;
    }

    if(damage > 0)
    {
        for(int i = 0;i < 5; i++)
        {
            if(enemy.minions[index2].timepoint[i] == AFTER_DAMAGE)
            {
                int id = enemy.minions[index2].effectid[i];
                common_effect_box(id, enemy, mine, enemy.minions[index2], gameid2, index2);
            }
        }
    }
}


/*
 战斗阶段：mine的gameid1给enemy的gameid2造成伤害
 index可变不安全函数
 */
void damage_phase(int gameid1, int gameid2, Player& mine, Player& enemy, int damage)
{
    int index1 = findgameid(mine, gameid1);
    if(index1 == 0)
    {
//        cout << "造成伤害的随从已经死亡" << endl;
        return;
    }
    int index2 = findgameid(enemy, gameid2);
    if(index2 == 0 )
    {
        cout << "受到伤害的随从已经死亡" << endl;
        return;
    }
    if(mine.minions[index1].battlefury == false)
    {
        pure_damage_phase(gameid1, gameid2, mine, enemy, damage);
        return;
    }
    
    if(mine.minions[index1].battlefury == true)
    {

        map<int, Card>::iterator iter;
        iter = enemy.minions.find(index2);

        /*目标在最左边*/
        if(iter == enemy.minions.begin())
        {
            iter++;
            if(iter != enemy.minions.end())
            {
                pure_damage_phase(gameid1, iter -> second.gameid, mine, enemy, damage);
                return;
            }

        }

        /*目标在最右边*/
        map<int, Card>::iterator temp;
        iter = enemy.minions.find(index2);
        temp = ++iter;
        if(temp == enemy.minions.end())
        {
            if(iter != enemy.minions.begin())
            {
                iter--;
                pure_damage_phase(gameid1, iter -> second.gameid, mine, enemy, damage);
                return;
            }
        }


        /*目标在中间*/
        iter = enemy.minions.find(index2);
        map<int, Card>::iterator left;
        map<int, Card>::iterator right;
        iter--;
        left = iter;
        iter++;iter++;
        right = iter;
        pure_damage_phase(gameid1, left -> second.gameid, mine, enemy, damage);
        pure_damage_phase(gameid1, right -> second.gameid, mine, enemy, damage);
        return;

    }
    

    
}

/*
 index可变不安全函数
 mine的gameid1给enemy的gameid2造成伤害
 */
void pure_damage_phase(int gameid1, int gameid2, Player& mine, Player& enemy, int damage)
{
    int index1 = findgameid(mine, gameid1);
    if(index1 == 0)
    {
//        cout << "造成伤害的随从已经死亡" << endl;
//        return;
    }
    int index2 = findgameid(enemy, gameid2);
    if(index2 == 0 )
    {
        cout << "受到伤害的随从已经死亡" << endl;
        return;
    }
        

    if(enemy.minions[index2].shield)
    {
        damage = 0;
        lose_shield(index2, enemy, mine);
    }
    
    enemy.minions[index2].hp = enemy.minions[index2].hp - damage;
    if(enemy.minions[index2].hp <= 0)
    {
        enemy.minions[index2].dead = true;
    }
    
//    if(findgameid(mine, gameid1) != 0)
//    {
//        if(mine.minions[index1].overkill == true)
//        {
//            if(enemy.minions[index2].hp < 0)
//            {
//                mine.minions[index1].overkilled = true;
//            }
//        }
//    }
    
    
    after_damage(gameid1, gameid2, mine, enemy, damage);//不安全函数
    

    


    
    
    
    
}
