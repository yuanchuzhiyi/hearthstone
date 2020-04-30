//
//  Card.hpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/13.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//

#ifndef Card_hpp
#define Card_hpp

#include <stdio.h>
#include <iostream>
#include "global.hpp"
using namespace std;


class Card
{
public:
    string name;
    int id;          //随从编号
    int gameid;      //全局游戏id，不会重复
    int level;       //对应酒馆战旗星级1-6
    int atk;         //攻击力
    int hp;          //血量
    int inthewind;   //风怒指示物
    bool dead;       //是否已经死亡
    bool taunt;      //是否具有嘲讽
    bool shield;     //是否有圣盾
    bool poisonous;  //是否剧毒
    bool battlefury; //是否狂战
    bool windfury;   //是否风怒
    bool overkill;   //是不是超杀
    bool deathrattle;//是否有亡语关键字
    bool overkilled; //是否超杀了
    bool attacked;   //是否攻击过，一排最后一个攻击过后清零
    enum races race; //种族
    enum timepoints timepoint[5]; //触发效果节点，最多允许5个节点
    int effectid[5];  //效果id，最多允许5个效果
   
    
    
    Card();
    

    Card(int,int,int,int);
    void setid(int);
    void setlevel(int);
    void setCard(int, int, int, int, bool);
    void settaunt(bool);
    void setbase(int, int);
    void setshield(bool);
    void setpoisonous(bool);
    void seteffect(int[]);
    void settimepoint(enum timepoints[]);
    void setname(string);
    void setbattlefury(bool);
    void setwindfury(bool);
    void setrace(enum races);
    void setdeathrattle(bool);
    void setoverkill(bool);
    void setattacked(bool);
    void setbyname(string);
    void setbyid(int);
    void setgameid();
    bool has_deatheffect();   //是否有亡语效果（不一定带亡语关键字）
    
    




};

#endif /* Card_hpp */
