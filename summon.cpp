//
//  summon.cpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/24.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//

#include "summon.hpp"
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


/*
 @index:随从放置后的位置
 */
void add_minion(Card& card, Player& mine, int index, int target)
{
    int gameid1 = card.gameid;
    int gameid2 = -1;
    if(target > 0 && target <= mine.minions.size())
    {
        gameid2 = mine.minions[target].gameid;
    }
    
    size_t minion_size = mine.minions.size();
    if(minion_size == MAX_MINION)
    {
        cout << "场上没有空位放置随从了！" << endl;
        return;
    }
    Player enemy;

    redistribute(index, mine);
    index = mine.lower_minion(index) + 1;
//    printplayer(mine);
    mine.minions[index] = card;
    /*处理战吼效果*/
    for(int i = 0; i < 5; i++)
    {
        if(card.timepoint[i] == BATTLECRY)
        {
            int id = card.effectid[i];
            summon_effect_box(id, mine, enemy, gameid1, gameid2, index);
        }
    }
    //judge_death(<#Player &mine#>, <#Player &enemy#>)
    index = findgameid(mine, gameid1);
    if(index != 0)
    {
        judge_son(index, mine.minions[index], mine, enemy);
    }
    
    
    
    
    
    
    
}

/*
 
 @hand_index :在手牌中的位置
 @field_index: 召唤到场上的位置
 @target: 如果有战吼效果目标的话， 指向目标随从的位置
 */

void summon(Player& mine, int handpos, int field_index, int target_index)
{
    Card card;
    list<Card>::iterator iter;
    iter = mine.handcards.begin();
    
    int count = handpos;
    while(iter != mine.handcards.end())
    {
        count--;
        if(count == 0)
        {
            card = *iter;
            mine.handcards.erase(iter);
            break;
        }
        ++iter;
    }
    
    add_minion(card, mine, field_index, target_index);
//    printminion(mine);
}

