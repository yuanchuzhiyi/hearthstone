//
//  effect_func.cpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/13.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//
#include <map>
#include <vector>
#include <algorithm>
#include <random>
#include "effect_func.hpp"
#include "Player.hpp"
#include "Card.hpp"
#include "battlephase.hpp"
#include "utils.hpp"
#include "game.hpp"
#include "global.hpp"
#include "death.hpp"

using namespace std;
extern map<int,ef> effectfuncs;
extern timepoints timepoint;

void ef_103(Player& mine, Player& enemy, int self[])
{
    cout << "无私英雄去世" << endl;
    map<int, Card>::iterator iter;
    iter = mine.minions.begin();
    int count = 0;
    while(iter != mine.minions.end())
    {
        if(iter -> second.shield == false)
        {
            count++;
        }
        iter++;
    }
    
    if(count == 0) return;
    iter = mine.minions.begin();
    int random = rand() % count + 1;
    while(iter != mine.minions.end())
    {
        if(iter -> second.shield == true)
        {
            iter++;
            
            
            continue;
        }
        if(iter -> second.shield == false)
        {
            random--;
            if(random == 0)
            {
                get_shield(iter -> first, mine, enemy);
                return;
                
            }
        }
        
    }
    
}

void ef_104(Player& mine, Player& enemy, int self[])
{
    cout << "雄斑虎召唤出雌斑虎" << endl;
    Card son;;
    son.setbyid(6);
    Card sons[0];
    sons[0] = son;
    add_son(self[0], sons, 1, mine, enemy);
}


void ef_106(Player& mine, Player& enemy, int self[])
{
    Card card = mine.minions[self[0]];
    bool has_murloc = false;
    map<int, Card>::iterator iter;
    iter = mine.minions.begin();
    while(iter != mine.minions.end())
    {
        if(iter -> second.race == MURLOC && iter -> second.gameid != self[1])
        {
            has_murloc = true;
            break;
        }
        iter++;
    }
    if(!has_murloc)
    {
        
        return;
    }
    
    int targetindex = findgameid(mine, self[2]);
    if(mine.minions[targetindex].race != MURLOC)
    {
        cout << "指定目标不是鱼人，请重新指定目标" << endl;
        mine.handcards.push_back(card);
        mine.minions.erase(self[0]);
        return;
    }
    mine.minions[targetindex].atk += 1;
    mine.minions[targetindex].hp += 1;
    
}


void ef_108(Player& mine, Player& enemy, int self[])
{
    
    cout << "机械袋鼠生儿子" << endl;

    Card son;

    son.setbyname("机械袋鼠宝宝");

    Card sons[1];
    sons[0] = son;
    add_son(self[0], sons, 1,  mine, enemy);
}

void ef_110(Player& mine, Player& enemy, int self[])
{
    cout << "鱼人猎潮者召唤鱼人斥候" << endl;
    Card son;;
    son.setbyid(7);
    Card sons[0];
    sons[0] = son;
    add_son(self[0], sons, 1, mine, enemy);
}

void ef_111(Player& mine, Player& enemy, int self[])
{
    cout << "粗俗的矮劣魔召唤自损2" << endl;
    mine.herohp -= 2;
}


void ef_112(Player& mine, Player& enemy, int self[])
{
    cout << "邪魔仆从死亡" << endl;
    if(mine.minions.empty())
        return;
    int target_index = random_target(mine.minions);
    mine.minions[target_index].atk += self[2];
    
}

/*效果：战斗开始时，随机对敌方一个随从造成等同于我方场上龙属性随从数量的伤害*/
void ef_113(Player& mine, Player& enemy, int self[])
{   cout << "小火龙开喷" << endl;
    if(enemy.minions.empty())
        return;
    
    int target_index = random_target(enemy.minions);
    
    
    cout << "喷到" << target_index << "号随从" << endl;
    
    int damage = 0;
    map<int, Card>::iterator iter;
    iter = mine.minions.begin();
    while(iter != mine.minions.end())
    {
        if(iter ->second.race == DRAGON)
            damage++;
        iter++;
    }
    pure_damage_phase(self[1], enemy.minions[target_index].gameid, mine, enemy, damage);
    judge_death(mine, enemy);
    
}

void ef_202(Player& mine, Player& enemy, int self[])
{
    cout << "金刚刃牙兽召唤" << endl;
    map<int, Card>::iterator iter;
    iter = mine.minions.begin();
    while(iter != mine.minions.end())
    {
        if(iter ->second.race == MECH && iter -> second.gameid != self[1])
            iter -> second.atk += 2;
        iter++;
    }
    
}

void ef_203(Player& mine, Player& enemy, int self[])
{
    cout << "食尸鬼死亡" << endl;
    map<int, Card>::iterator iter;
    
    vector<int> mine_gameids;
    vector<int> enemy_gameids;
    
    iter = enemy.minions.begin();
    while(iter != enemy.minions.end())
    {
        if(find(enemy_gameids.begin(), enemy_gameids.end(), iter -> second.gameid) != enemy_gameids.end())
        {
            iter++;
            continue;
        }
        enemy_gameids.push_back(iter -> second.gameid);
        
        pure_damage_phase(self[1], iter -> second.gameid, mine, enemy, 1);
        judge_death(mine, enemy);
        
        iter = enemy.minions.begin();
        

    }
    
    iter = mine.minions.begin();
    while(iter != mine.minions.end())
    {
        if(find(mine_gameids.begin(), mine_gameids.end(), iter -> second.gameid) != mine_gameids.end())
        {
            iter++;
            continue;
        }
        mine_gameids.push_back(iter -> second.gameid);
        
        pure_damage_phase(self[1], iter -> second.gameid, mine, mine, 1);
        judge_death(mine, enemy);
        
        iter = mine.minions.begin();
        

    }
    

    
    
}

void ef_204(Player& mine, Player& enemy, int self[])
{
    
    cout << "狼外婆生儿子" << endl;

    Card son;
    son.setbase(3, 2);
    son.setrace(BEAST);
    son.setname("大灰狼");
    son.setlevel(1);
    Card sons[1];
    sons[0] = son;
    add_son(self[0], sons, 1,  mine, enemy);
}



/*效果：亡语：使自己的其他随从获得+1/+1*/
void ef_206(Player& mine, Player& enemy, int self[])
{
    cout << "子嗣死亡" << endl;
    map<int, Card>::iterator iter;
    iter = mine.minions.begin();
    while(iter != mine.minions.end())
    {
        iter -> second.atk += 1;
        iter -> second.hp += 1;
        
        iter++;
    }
    
}

/*效果：亡语：随机对一个敌方随从造成4点伤害*/
void ef_208(Player& mine, Player& enemy, int self[])
{   
    cout << "炸弹炸4" << endl;
    if(enemy.minions.empty())
        return;
    
    int target_index = random_target(enemy.minions);
    cout << "炸到" << target_index << "号随从" << endl;
    int damage = 4;
    
    pure_damage_phase(self[1], enemy.minions[target_index].gameid, mine, enemy, damage);

    judge_death(mine, enemy);
    
}


void ef_210(Player& mine, Player& enemy, int self[])
{
    cout << "鱼人领军死亡，buff取消" << endl;
    map<int, Card>::iterator iter;
    iter = mine.minions.begin();
    while(iter != mine.minions.end())
    {
        if(iter -> second.race == MURLOC)
        {
            iter -> second.atk -= 2;
            
        }
        
        
        iter++;
    }
}



void ef_211(Player& mine, Player& enemy, int self[])
{
    cout << "老鼠死亡生儿子" << endl;
    if(self[2] == 0)
        return;
    if(self[2] > 7)
        self[2] = 7;
    Card son;
    son.setbase(1,1);
    son.setlevel(1);
    son.setrace(BEAST);
    son.setname("老鼠");
    Card sons[7];
    for(int i = 0; i < self[2]; i++)
    {
        sons[i] = son;
    }
    add_son(self[0], sons, self[2], mine, enemy);
}


/*效果 ：亡语： 召唤一个2/1的机械 */
void ef_213(Player& mine, Player& enemy, int self[])
{
    
    cout << "麦田生儿子" << endl;

    Card son;

    son.setbyname("损坏的傀儡");
 
    Card sons[1];
    sons[0] = son;
    add_son(self[0], sons, 1,  mine, enemy);
}

void ef_214(Player& mine, Player& enemy, int self[])
{
    
    cout << "小鬼囚徒生儿子" << endl;

    Card son;
    son.setbase(1, 1);
    son.setrace(DEMON);
    son.setname("小鬼");
    son.setlevel(1);
    Card sons[1];
    sons[0] = son;
    add_son(self[0], sons, 1,  mine, enemy);
}

/*效果：攻击前，攻击力翻倍*/
void ef_217(Player& mine, Player& enemy, int self[])
{
    cout << "翻倍龙攻击力翻倍" << endl;
    mine.minions[self[0]].atk = mine.minions[self[0]].atk * 2;
    
    
}

void ef_301(Player& mine, Player& enemy, int self[])
{
    cout << "比斯巨兽生内鬼" << endl;
    Card son;
    son.setbase(3,3);
    son.setrace(NEUTRAL);
    son.setname("内鬼");
    son.setlevel(1);
    Card sons[1];
    sons[0] = son;
    add_son(MAX_MINION, sons, 1, enemy, enemy);
}

/*每当该随从受到伤害，召唤一个1/1的小鬼*/
void ef_303(Player& mine, Player& enemy, int self[])
{
    cout << "鬼父生小鬼" << endl;
    Card son;
    son.setbase(1,1);
    son.setrace(DEMON);
    son.setname("小鬼");
    son.setlevel(1);
    Card sons[1];
    sons[0] = son;
    add_son(self[0], sons, 1, mine, enemy);
}


void ef_304(Player& mine, Player& enemy, int self[])
{
    
    cout << "寄生恶狼生儿子" << endl;

    Card son;
    son.setbase(1, 1);
    son.setrace(BEAST);
    son.setname("蜘蛛");
    son.setlevel(1);
    Card sons[2];
    sons[0] = son;
    sons[1] = son;
    add_son(self[0], sons, 2,  mine, enemy);
}

void ef_307(Player& mine, Player& enemy, int self[])
{
    std::random_device rd;
    std::mt19937 mt(rd());
    cout << "收割机生儿子" << endl;
    int cost2[] = {102,106,107,110,111,114,201,203,204,212,314};
    int size = sizeof(cost2) / sizeof(int);
    int random = mt() % size;
    Card sons[1];
    Card son;
    son.setbyid(cost2[random]);
    sons[0] = son;
    add_son(self[0], sons, 1,  mine, enemy);
}

/*亡语：召唤3个1/1的微型机器人*/
void ef_309(Player& mine, Player& enemy, int self[])
{
    
    cout << "量产恐吓机生儿子" << endl;

    Card son;

    son.setbyname("微型机器人");

    Card sons[3];
    sons[0] = son;
    sons[1] = son;
    sons[2] = son;
    add_son(self[0], sons, 3,  mine, enemy);
}


void ef_316(Player& mine, Player& enemy, int self[])
{
    cout << "青铜龙生儿子" << endl;
    Card son;
    son.setname("青铜守卫");
    son.setid(316);
    son.setlevel(3);
    son.setbase(2, 1);
    son.setshield(true);
    son.setrace(DRAGON);
    Card sons[1];
    sons[0] = son;
    add_son(self[0], sons, 1, mine, enemy);
}

void ef_402(Player& mine, Player& enemy, int self[])
{
    cout << "狮子生儿子" << endl;
    Card son;
    son.setbase(2, 2);
    son.setrace(BEAST);
    son.setlevel(1);
    son.setname("土狼");
    Card sons[2];
    sons[0] = son;
    sons[1] = son;
    add_son(self[0], sons, 2, mine, enemy);
}


void ef_406(Player& mine, Player& enemy, int self[])
{
    cout << "安保生儿子" << endl;
    Card son;
    son.setbase(2,3);
    son.setlevel(1);
    son.setrace(MECH);
    son.settaunt(true);
    son.setname("安保儿子");
    Card sons[1];
    sons[0] = son;
    add_son(self[0], sons, 1, mine, enemy);
    
}

void ef_407(Player& mine, Player& enemy, int self[])
{
    cout << "机械蛋生儿子" << endl;
    Card son;

    son.setbyname("机械暴龙");
    Card sons[1];
    sons[0] = son;
    add_son(self[0], sons, 1, mine, enemy);
    
}


void ef_411(Player& mine, Player& enemy, int self[])
{
    cout << "攻城恶魔死亡，buff取消" << endl;
    map<int, Card>::iterator iter;
    iter = mine.minions.begin();
    while(iter != mine.minions.end())
    {
        if(iter -> second.race == DEMON)
        {
            iter -> second.atk -= 1;
            
        }
        
        
        iter++;
    }
}


/*虚空领主*/
void ef_504(Player& mine, Player& enemy, int self[])
{
    cout << "939生儿子" << endl;
    Card son;
    son.setbase(1,3);
    son.setrace(DEMON);
    son.settaunt(true);
    son.setlevel(1);
    son.setname("小蓝胖");
    Card sons[3];
    sons[0] = son;
    sons[1] = son;
    sons[2] = son;
    add_son(self[0], sons, 3,  mine, enemy);
    
}

void ef_506(Player& mine, Player& enemy, int self[])
{
    std::random_device rd;
    std::mt19937 mt(rd());
    cout << "伐木机生儿子" << endl;
    int legends[] = {201, 301, 313, 314, 509, 511, 512, 513, 601, 602, 603};
    int size = sizeof(legends) / sizeof(int);
    int random = mt() % size;
    Card son;
    son.setbyid(legends[random]);
    Card sons[1];
    sons[0] = son;
    add_son(self[0], sons, 1,  mine, enemy);
    
}

void ef_509(Player& mine, Player& enemy, int self[])
{
    cout << "狼爹+4/+4" << endl;
    map<int, Card>::iterator iter;
    iter = mine.minions.begin();
    while(iter != mine.minions.end())
    {
        if(iter -> second.race == BEAST)
        {
            iter -> second.atk += 4;
            iter -> second.hp += 4;
        }
        
        
        iter++;
    }
    
}

/*二王隐藏亡语*/
void ef_512(Player& mine, Player& enemy, int self[])
{
    cout << "二王死亡，buff取消" << endl;
    map<int, Card>::iterator iter;
    iter = mine.minions.begin();
    while(iter != mine.minions.end())
    {
        if(iter -> second.race == DEMON)
        {
            iter -> second.atk -= 2;
            iter -> second.hp -= 2;
            if(iter -> second.hp <= 0)
                iter -> second.hp = 1;
        }
        
        
        iter++;
    }
}

void ef_513(Player& mine, Player& enemy, int self[])
{
    cout << "鱼人国王死亡" << endl;
    map<int, Card>::iterator iter;
    iter = mine.minions.begin();
    while(iter != mine.minions.end())
    {
        if(iter -> second.race == MURLOC)
        {
            iter -> second.atk += 2;
            iter -> second.hp += 2;
        }
        
        
        iter++;
    }
}

void ef_604(Player& mine, Player& enemy, int self[])
{

    Card sons[2];
    cout << "坎格尔生儿子" << endl;
    if(mine.deadmechs[0] == 0)
        return;
    else if(mine.deadmechs[1] == 0)
    {
        Card sons[1];
        Card son;
        son.setbyid(mine.deadmechs[0]);
        sons[0] = son;
        cout << "坎格尔生了" << son.name<< endl;
        add_son(self[0], sons, 1,  mine, enemy);
    }
    
    else
    {
        Card sons[2];
        Card son1;
        son1.setbyid(mine.deadmechs[0]);
        Card son2;
        son2.setbyid(mine.deadmechs[1]);
        sons[0] = son1;
        sons[1] = son2;
        cout << "坎格尔生了" << son1.name << "和" << son2.name << endl;
        add_son(self[0], sons, 2, mine, enemy);
    }
    
    
    
    
}

void ef_605(Player& mine, Player& enemy, int self[])
{
    std::random_device rd;
    std::mt19937 mt(rd());
    cout << "大蛇生儿子" << endl;
    int deathrattles[] = {103, 108, 112, 203, 204, 206, 208, 211, 213, 214, 301, 304, 307, 309, 402, 407, 504, 506, 509, 513, 604, 608};
    int size = sizeof(deathrattles) / sizeof(int);
    int random1 = mt() % size;
    int random2 = mt() % size;
    Card son1;
    Card son2;
    son1.setbyid(deathrattles[random1]);
    son2.setbyid(deathrattles[random2]);
    cout << "大蛇生了" << son1.name << "和" << son2.name << endl;
    Card sons[2];
    sons[0] = son1;
    sons[1] = son2;
    add_son(self[0], sons, 2,  mine, enemy);
}

//红衣
void ef_608(Player& mine, Player& enemy, int self[])
{
    cout << "红衣死亡" << endl;
    map<int, Card>::iterator iter;
    iter = mine.minions.begin();
    while(iter != mine.minions.end())
    {
        if(iter -> second.race == DRAGON)
        {
            get_shield(iter -> first, mine, enemy);
        }
        
        
        iter++;
    }
    
}
    
void ef_610(Player& mine, Player& enemy, int self[])
{
    std::random_device rd;
    std::mt19937 mt(rd());
    cout << "鬼妈生儿子" << endl;
    int demons[] = {111,112,209,214,303,401,411,504,508};
    int size = sizeof(demons) / sizeof(int);
    int random = mt() % size;
    Card sons[1];
    Card son;
    son.setbyid(demons[random]);
    son.settaunt(true);
    sons[0] = son;
    add_son(self[0], sons, 1, mine, enemy);
    
}


void ef_777(Player& mine, Player& enemy, int self[])
{
    std::random_device rd;
    std::mt19937 mt(rd());
    Card son1;
    Card son2;
    
    while(son1.name == "unknown")
    {
        int random1 = mt() % 600 + 100;
        son1.setbyid(random1);
    }
    while(son2.name == "unknown")
    {
        int random2 = mt() % 600 + 100;
        son2.setbyid(random2);
    }
    
    cout << "777生儿子" << endl;
    cout << "777生了" << son1.name << "和" << son2.name << endl;
    Card sons[2];
    sons[0] = son1;
    sons[1] = son2;
    add_son(self[0], sons, 2,  mine, enemy);
}



/*----------------------------------------金色分割线---------------------------------------*/

void ef_2060(Player& mine, Player& enemy, int self[])
{
    cout << "子嗣死亡" << endl;
    map<int, Card>::iterator iter;
    iter = mine.minions.begin();
    while(iter != mine.minions.end())
    {
        iter -> second.atk += 2;
        iter -> second.hp += 2;
        
        iter++;
    }
    
}

void ef_2080(Player& mine, Player& enemy, int self[])
{
    cout << "炸弹炸4" << endl;
    size_t minion_size = enemy.minions.size();
    if(minion_size == 0)
        return;
    
    int target_index = random_target(enemy.minions);
    cout << "炸到" << target_index << "号随从" << endl;
    int damage = 4;
    
    pure_damage_phase(self[1], enemy.minions[target_index].gameid, mine, enemy, damage);

    judge_death(mine, enemy);
    
    
    target_index = random_target(enemy.minions);
    cout << "炸到" << target_index << "号随从" << endl;
    damage = 4;
    
    pure_damage_phase(self[1], enemy.minions[target_index].gameid, mine, enemy, damage);

    judge_death(mine, enemy);
    
    
}



void ef_4070(Player& mine, Player& enemy, int self[])
{
    cout << "机械蛋生儿子" << endl;
    Card son;
    son.setbase(16,16);
    son.setlevel(4);
    son.setrace(MECH);
    son.setname("机械暴龙");
    Card sons[1];
    sons[0] = son;
    add_son(self[0], sons, 1, mine, enemy);
    
}

void ef_5090(Player& mine, Player& enemy, int self[])
{
    cout << "狼爹+8/+8" << endl;
    map<int, Card>::iterator iter;
    iter = mine.minions.begin();
    while(iter != mine.minions.end())
    {
        if(iter -> second.race == BEAST)
        {
            iter -> second.atk += 8;
            iter -> second.hp += 8;
        }
        
        
        iter++;
    }
    
}



void ef_5130(Player& mine, Player& enemy, int self[])
{
    cout << "鱼人国王死亡" << endl;
    map<int, Card>::iterator iter;
    iter = mine.minions.begin();
    while(iter != mine.minions.end())
    {
        if(iter -> second.race == MURLOC)
        {
            iter -> second.atk += 4;
            iter -> second.hp += 4;
        }
        
        
        iter++;
    }
}


