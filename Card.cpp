//
//  Card.cpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/13.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//

#include "Card.hpp"

extern map<int,ef> effectfuncs;
extern timepoints timepoint;
extern int global_id;
Card::Card()
{
    this -> name = "unknown";
    this -> id = 0;
    this -> level = 0;
    this -> atk = 0;
    this -> hp = 0;
    
    this -> inthewind = 0;             //0:还未攻击。  1:攻击了一次    2:攻击了2次
    this -> dead = false;
    this -> taunt = false;
    this -> shield = false;
    this -> poisonous = false;
    this -> battlefury = false;
    this -> attacked = false;
    this -> race = NEUTRAL;
    this -> deathrattle = false;
    this -> windfury = false;
    this -> overkill = false;
    this -> overkilled = false;
    this -> gameid = ++global_id;
    memset(timepoint,0,sizeof(timepoint));
    memset(effectid,0,sizeof(effectid));
    
//    cout << "卡片构造函数" << endl;
    
    
}



Card::Card(int id, int level, int atk, int hp)
{
     this -> id = id;
     this -> level = level;
     this -> atk = atk;
     this -> hp = hp;

     this -> gameid = ++global_id;
}

void Card::setCard(int id, int level, int atk, int hp, bool dead)
{
     this -> id = id;
     this -> level = level;
     this -> atk = atk;
     this -> hp = hp;
     this -> dead = false;
}

void Card::settaunt(bool taunt)
{
    this -> taunt = taunt;
}

void Card::setshield(bool shield)
{
    this -> shield = shield;
}

void Card::setbase(int atk, int hp)
{
    this -> atk = atk;
    this -> hp = hp;
}

void Card::setpoisonous(bool posionous)
{
    this ->poisonous = posionous;
}

void Card::setbattlefury(bool battlefury)
{
    this ->battlefury = battlefury;
}

void Card::seteffect(int p[])
{
    
    for(int i = 0; i < 5; i++)
    {
        effectid[i] = p[i];
    }
}

void Card::settimepoint(enum timepoints t[])
{

    for(int i = 0; i < 5; i++)
    {
        timepoint[i] = t[i];
    }
}

void Card::setname(string name)
{
    this -> name = name;
}

void Card::setrace(enum races race)
{
    this -> race = race;
}

void Card::setattacked(bool attacked)
{
    this -> attacked = attacked;
}


void Card::setid(int id)
{
    this -> id = id;
}

void Card::setlevel(int level)
{
    this -> level = level;
}

void Card::setwindfury(bool windfury)
{
    this -> windfury = windfury;
}

void Card::setoverkill(bool overkill)
{
    this -> overkill = overkill;
}

void Card::setdeathrattle(bool deathrattle)
{
    this -> deathrattle = deathrattle;
}

void Card::setgameid()
{
    this -> gameid = ++global_id;
}

/*是否有亡语效果（不一定带亡语关键字）*/
bool Card::has_deatheffect()
{
    for(int i = 0; i < 5; i++)
    {
        if(timepoint[i] == DEATH_PHASE)
        {
            return true;
        }
    }
    return false;
}














void Card::setbyname(string name)
{
    if(name == "损坏的傀儡")
    {
        setname("损坏的傀儡");
        setid(1);
        setrace(MECH);
        setlevel(1);
        setbase(1, 1);
    }
    if(name == "微型机器人")
    {
        setname("微型机器人");
        setid(2);
        setrace(MECH);
        setlevel(1);
        setbase(1, 1);
    }
    if(name == "机械暴龙")
    {
        setname("机械暴龙");
        setid(3);
        setrace(MECH);
        setlevel(1);
        setbase(8, 8);
    }
    
    if(name == "机械袋鼠宝宝")
    {
        setname("机械袋鼠宝宝");
        setid(4);
        setrace(MECH);
        setlevel(1);
        setbase(1, 1);
    }
    if(name == "安保儿子")
    {
        setname("安保儿子");
        setid(5);
        setrace(MECH);
        setlevel(1);
        setbase(2, 3);
        settaunt(true);
    }
    if(name == "雌斑虎")
    {
        setname("雌斑虎");
        setid(6);
        setrace(MECH);
        setlevel(1);
        setbase(1, 1);
    }
    
    if(name == "鱼人斥候")
    {
        setname("鱼人斥候");
        setid(7);
        setrace(MURLOC);
        setlevel(1);
        setbase(1, 1);
    }

    if(name =="鱼人招潮者")
    {
        setid(101);
        setname("鱼人招潮者");
        setlevel(1);
        setrace(MURLOC);
        setbase(1, 2);
    }
    if(name == "恐狼前锋")                   //to be done
    {
        setname("恐狼前锋");
        setid(102);
        setlevel(1);
        setbase(2, 2);
        setrace(BEAST);
    }
    if(name == "无私的英雄")
    {
        setname("无私的英雄");
        setid(103);
        setlevel(1);
        setrace(NEUTRAL);
        setbase(2, 1);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {103,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name =="雄斑虎")
    {
        setid(104);
        setname("雄斑虎");
        setlevel(1);
        setrace(BEAST);
        setbase(1, 1);
        timepoints t[5] = {BATTLECRY,NONE,NONE,NONE,NONE};
        int e[5] = {104,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "正义保护者")
    {
        setname("正义保护者");
        setid(105);
        setlevel(1);
        setrace(NEUTRAL);
        setbase(1, 1);
        settaunt(true);
        setshield(true);
    }
    if(name == "石塘猎人")
    {
        setname("石塘猎人");
        setid(106);
        setlevel(1);
        setrace(MURLOC);
        setbase(2, 3);
        timepoints t[5] = {BATTLECRY,NONE,NONE,NONE,NONE};
        int e[5] = {106,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "微型战斗机甲")
    {
        setname("微型战斗机甲");
        setid(107);
        setlevel(1);
        setrace(MECH);
        setbase(1, 2);
    }
    
    if(name == "机械袋鼠")
    {
        setname("机械袋鼠");
        setid(108);
        setlevel(1);
        setrace(MECH);
        setbase(1, 1);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {108,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "愤怒编织者")
    {
        setname("愤怒编织者");
        setid(109);
        setlevel(1);
        setrace(NEUTRAL);
        setbase(1,1);
    }
    if(name == "鱼人猎潮者")
    {
        setname("鱼人猎潮者");
        setid(110);
        setlevel(1);
        setrace(MURLOC);
        setbase(2, 1);
        timepoints t[5] = {BATTLECRY,NONE,NONE,NONE,NONE};
        int e[5] = {110,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "粗俗的矮劣魔")
    {
        setname("粗俗的矮劣魔");
        setid(111);
        setlevel(1);
        setrace(DEMON);
        setbase(2,4);
        settaunt(true);
        timepoints t[5] = {BATTLECRY,NONE,NONE,NONE,NONE};
        int e[5] = {111,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "邪魔仆从")
    {
        setname("邪魔仆从");
        setid(112);
        setlevel(1);
        setrace(DEMON);
        setbase(2,1);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {112,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "红色雏龙")
    {
        setid(113);
        setname("红色雏龙");
        setrace(DRAGON);
        setbase(1,2);
        setlevel(1);
        timepoints t[5] = {BEFORE_BATTLE,NONE,NONE,NONE,NONE};
        int e[5] = {113,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "龙人军官")
    {
        setid(114);
        setname("龙人军官");
        setlevel(1);
        setrace(DRAGON);
        setbase(2,3);
        settaunt(true);
    }
    if(name == "老瞎眼")
    {
        setname("老瞎眼");
        setid(201);
        setlevel(2);
        setbase(2, 4);
        setrace(MURLOC);
    }
    if(name == "金刚刃牙兽")
    {
        setname("金刚刃牙兽");
        setid(202);
        setlevel(2);
        setbase(3, 3);
        setrace(MECH);
        timepoints t[5] = {BATTLECRY,NONE,NONE,NONE,NONE};
        int e[5] = {202,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "蹒跚的食尸鬼")
    {
        setname("蹒跚的食尸鬼");
        setid(203);
        setlevel(2);
        setbase(1, 3);
        setrace(NEUTRAL);
        settaunt(true);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {203,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "慈祥的外婆")
    {
        setname("慈祥的外婆");
        setid(204);
        setlevel(2);
        setbase(1, 1);
        setrace(BEAST);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {204,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "机械动物管理员")
    {
        setname("机械动物管理员");
        setid(205);
        setlevel(2);
        setrace(MECH);
        setbase(3,3);
    }
    if(name == "恩佐斯的子嗣")
    {
        setname("恩佐斯的子嗣");
        setid(206);
        setlevel(2);
        setbase(2, 2);
        setrace(NEUTRAL);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {206,0,0,0,0};
        settimepoint(t);
        seteffect(e);
        
    }
    if(name == "蹦蹦兔")
    {
        setname("蹦蹦兔");
        setid(207);
        setlevel(2);
        setrace(MECH);
        setbase(1,1);
    }
    
    if(name == "爆爆机器人")
    {
        setname("爆爆机器人");
        setid(208);
        setlevel(2);
        setbase(2, 2);
        setrace(MECH);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {208,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    
    if(name == "纳斯雷兹姆监工")
    {
        setname("纳斯雷兹姆监工");
        setid(209);
        setlevel(2);
        setrace(DEMON);
        setbase(2,3);
    }
    
    if(name == "鱼人领军")
    {
        setname("鱼人领军");
        setid(210);
        setlevel(2);
        setrace(MURLOC);
        setbase(3,3);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {210,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "瘟疫鼠群")
    {
        setname("瘟疫鼠群");
        setid(211);
        setlevel(2);
        setrace(BEAST);
        setbase(2, 2);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {211,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    
    if(name == "食腐土狼")
    {
        setname("食腐土狼");
        setid(212);
        setlevel(2);
        setrace(BEAST);
        setbase(2, 2);
    }
    if(name == "麦田傀儡")
    {
        setname("麦田傀儡");
        setid(213);
        setlevel(2);
        setbase(2, 3);
        setrace(MECH);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {213,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    
    if(name == "小鬼囚徒")
    {
        setname("小鬼囚徒");
        setid(214);
        setlevel(2);
        setrace(DEMON);
        setbase(3, 3);
        settaunt(true);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {214,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "蜡烛骑士托瓦格尔")         //to be done
    {
        setname("蜡烛骑士托瓦格尔");
        setid(215);
        setlevel(2);
        setrace(NEUTRAL);
        setbase(1, 2);
    }
    if(name == "时间管理者")
    {
        setname("时间管理者");
        setid(216);
        setrace(DRAGON);
        setlevel(2);
        setbase(3, 4);
    }
    if(name == "雕文护卫者")
    {
        setname("雕文护卫者");
        setid(217);
        setlevel(2);
        setbase(2, 4);
        setrace(DRAGON);
        timepoints t[5] = {BEFORE_ATTACK,NONE,NONE,NONE,NONE};
        int e[5] = {217,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    
    if(name == "比斯巨兽")
    {
        setname("比斯巨兽");
        setid(301);
        setlevel(3);
        setbase(9,7);
        setrace(BEAST);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {301,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    
    if(name == "人气选手")
    {
        setname("人气选手");
        setid(302);
        setlevel(3);
        setbase(4, 4);
        setrace(NEUTRAL);
        
    }
    
    if(name == "小鬼首领")
    {
        setname("小鬼首领");
        setid(303);
        setlevel(3);
        setbase(2, 4);
        setrace(DEMON);
        timepoints t[5] = {AFTER_DAMAGE,NONE,NONE,NONE,NONE};
        int e[5] = {303,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    
    if(name == "寄生恶狼")
    {
        setname("寄生恶狼");
        setid(304);
        setlevel(3);
        setbase(3, 3);
        setrace(BEAST);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {304,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "魔瘾结晶者")
    {
        setname("魔瘾结晶者");
        setid(305);
        setlevel(3);
        setbase(5, 4);
        setrace(NEUTRAL);
    }
    
    if(name == "寒光先知")
    {
        setname("寒光先知");
        setid(306);
        setlevel(3);
        setbase(2, 3);
        setrace(MURLOC);
    }
    
    if(name == "载人收割机")
    {
        setname("载人收割机");
        setid(307);
        setlevel(3);
        setbase(4, 3);
        setrace(MECH);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {307,0,0,0,0};
        settimepoint(t);
        seteffect(e);
        
    }
    
    if(name == "族群领袖")
    {
        setname("族群领袖");
        setid(308);
        setlevel(3);
        setbase(3, 3);
        setrace(NEUTRAL);
    }
    if(name == "量产型恐吓机")
    {
        setname("量产型恐吓机");
        setid(309);
        setlevel(3);
        setbase(3, 1);
        setrace(MECH);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {309,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "灵魂杂耍者")
    {
        setname("灵魂杂耍者");
        setid(310);
        setlevel(3);
        setbase(3, 3);
        setrace(NEUTRAL);
    }
    if(name == "驯兽师")
    {
        setname("驯兽师");
        setid(311);
        setlevel(3);
        setbase(4, 3);
        setrace(NEUTRAL);
    }
    if(name == "废旧螺栓机甲")
    {
        setname("废旧螺栓机甲");
        setid(312);
        setlevel(3);
        setbase(2, 5);
        setrace(NEUTRAL);
    }
    if(name == "百变泽鲁斯")
    {
        setname("百变泽鲁斯");
        setid(313);
        setlevel(3);
        setbase(1, 1);
        setrace(NEUTRAL);
    }
    
    if(name == "卡德加")                    //to be done
    {
        setname("卡德加");
        setid(314);
        setlevel(3);
        setbase(2, 2);
        setrace(NEUTRAL);
    }
    if(name == "急饿巨龙")
    {
        setname("急饿巨龙");
        setid(315);
        setlevel(3);
        setbase(4, 4);
        setrace(DRAGON);
    }
    
    if(name == "青铜守卫")
    {
        setname("青铜守卫");
        setid(316);
        setlevel(3);
        setbase(2, 1);
        setshield(true);
        setrace(DRAGON);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {316,0,0,0,0};
        settimepoint(t);
        seteffect(e);
        
    }
    if(name == "暮光使者")
    {
        setname("暮光使者");
        setid(317);
        setlevel(3);
        setbase(4, 4);
        setrace(DRAGON);
        settaunt(true);
    }
    
    if(name == "邪鳍导航员")
    {
        setname("邪鳍导航员");
        setid(318);
        setlevel(3);
        setbase(4, 4);
        setrace(MURLOC);
    }
    
    
    if(name == "偏折机器人")
    {
        setname("偏折机器人");
        setrace(MECH);
        setid(319);
        setlevel(3);
        setbase(3, 2);
        setshield(true);
        
    }
    if(name == "漂浮观察者")
    {
        setname("漂浮观察者");
        setid(401);
        setlevel(4);
        setbase(4, 4);
        setrace(DEMON);
    }
    
    if(name == "长鬃草原狮")
    {
        setname("长鬃草原狮");
        setid(402);
        setlevel(4);
        setbase(6, 5);
        setrace(BEAST);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {402,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "展览馆法师")
    {
        setname("展览馆法师");
        setid(403);
        setlevel(4);
        setbase(4, 4);
        setrace(NEUTRAL);
        
    }
    if(name == "浴火者伯瓦尔")
    {
        setname("浴火者伯瓦尔");
        setid(404);
        setlevel(4);
        setbase(1, 7);
        setrace(NEUTRAL);
        setshield(true);
    }
    if(name == "吵吵模组")
    {
        setname("吵吵模组");
        setid(405);
        setlevel(4);
        setbase(2, 4);
        setrace(MECH);
        settaunt(true);
        setshield(true);
    }
    if(name == "安保巡游者")
    {
        setname("安保巡游者");
        setid(406);
        setlevel(4);
        setbase(2, 6);
        setrace(MECH);
        timepoints t[5] = {AFTER_DAMAGE,NONE,NONE,NONE,NONE};
        int e[5] = {406,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "机械蛋")
    {
        setname("机械蛋");
        setid(407);
        setlevel(4);
        setbase(0, 8);
        setrace(MECH);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {407,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "阿古斯防御者")
    {
        setname("阿古斯防御者");
        setid(408);
        setlevel(4);
        setrace(NEUTRAL);
        setbase(2, 3);
    }
    if(name == "兔妖教头")
    {
        setname("兔妖教头");
        setid(409);
        setlevel(4);
        setrace(NEUTRAL);
        setbase(4, 5);
    }
    if(name == "钢铁武道家")
    {
        setname("钢铁武道家");
        setid(410);
        setlevel(4);
        setrace(MECH);
        setbase(2, 2);
    }
    if(name == "攻城恶魔")
    {
        setname("攻城恶魔");
        setid(411);
        setrace(DEMON);
        setbase(5, 8);
        setlevel(4);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {411,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "洞穴多头蛇")
    {
        setname("洞穴多头蛇");
        setid(412);
        setrace(BEAST);
        setlevel(4);
        setbase(2, 4);
        setbattlefury(true);
    }
    if(name == "深蓝刃鳞龙人")
    {
        setname("深蓝刃鳞龙人");
        setid(413);
        setlevel(4);
        setrace(DRAGON);
        setbase(5, 5);
    }
    if(name == "毒鳍鱼人")
    {
        setname("毒鳍鱼人");
        setid(414);
        setlevel(4);
        setrace(MURLOC);
        setbase(1, 2);
    }
    if(name == "火焰传令官")                     //to be done
    {
        setname("火焰传令官");
        setid(415);
        setlevel(4);
        setrace(DRAGON);
        setbase(5, 6);
    }
    if(name == "龙人执行者")
    {
        setname("龙人执行者");
        setid(416);
        setlevel(4);
        setbase(3, 6);
        setrace(DRAGON);
        
    }
    if(name == "回收机器人")
    {
        setname("回收机器人");
        setid(501);
        setlevel(5);
        setbase(1,5);
        setrace(MECH);
    }
    if(name == "瑞文戴尔男爵")
    {
        setname("瑞文戴尔男爵");
        setid(502);
        setlevel(5);
        setbase(1, 7);
        setrace(NEUTRAL);
    }
    if(name == "硬壳清道夫")
    {
        setname("硬壳清道夫");
        setid(503);
        setlevel(5);
        setbase(2, 3);
        setrace(NEUTRAL);
    }
    if(name == "虚空领主")
    {
        setname("虚空领主");
        setid(504);
        setlevel(5);
        setbase(3,9);
        setrace(DEMON);
        settaunt(true);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {504,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "铁皮恐角龙")
    {
        setname("铁皮恐角龙");
        setid(505);
        setlevel(5);
        setrace(BEAST);
        setbase(7,7);
        setoverkill(true);
        
    }
    
    if(name == "斯尼德的伐木机")
    {
        setname("斯尼德的伐木机");
        setid(506);
        setlevel(5);
        setbase(5, 7);
        setrace(MECH);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {506,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "光牙执行者")
    {
        setname("光牙执行者");
        setid(507);
        setlevel(5);
        setbase(2, 2);
        setrace(NEUTRAL);
    }
    if(name == "安尼赫兰战场军官")
    {
        setname("安尼赫兰战场军官");
        setid(508);
        setlevel(5);
        setbase(3,1);
        setrace(DEMON);
    }
    if(name == "巨狼戈德林")
    {
        setname("巨狼戈德林");
        setid(509);
        setlevel(5);
        setbase(4, 4);
        setrace(BEAST);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {509,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    
    if(name == "蛮鱼斥候")
    {
        setname("蛮鱼斥候");
        setid(510);
        setlevel(5);
        setbase(3, 2);
        setrace(MURLOC);
    }
    if(name == "布莱恩-铜须")
    {
        setname("布莱恩-铜须");
        setid(511);
        setlevel(5);
        setbase(2, 4);
        setrace(NEUTRAL);
    }
    if(name == "玛尔加尼斯")
    {
        setname("玛尔加尼斯");
        setid(512);
        setlevel(5);
        setbase(9,7);
        setrace(DEMON);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {512,0,0,0,0};
        settimepoint(t);
        seteffect(e);
        
    }
    if(name == "拜戈尔格国王")
    {
        setname("拜戈尔格国王");
        setid(513);
        setlevel(5);
        setbase(6, 3);
        setrace(MURLOC);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {513,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "狂野的拉佐格尔")
    {
        setname("狂野的拉佐格尔");
        setid(514);
        setlevel(5);
        setbase(2, 4);
        setrace(DRAGON);
    }
    
    if(name == "姆诺兹多")
    {
        setname("姆诺兹多");
        setid(515);
        setlevel(5);
        setbase(5, 5);
        setrace(DRAGON);
    }
    
    if(name == "死神4000型")
    {
        setname("死神4000型");
        setid(601);
        setlevel(6);
        setbase(6, 9);
        setrace(MECH);
        setbattlefury(true);
    }
    
    if(name == "迈克斯纳")
    {
        setname("迈克斯纳");
        setid(602);
        setlevel(6);
        setbase(2,8);
        setrace(BEAST);
        setpoisonous(true);
    }
    if(name == "扎普-斯里维克")
    {
        setname("扎普-斯里维克");
        setid(603);
        setlevel(6);
        setbase(7, 9);
        setrace(NEUTRAL);
        setwindfury(true);
        
    }
    
    if(name == "坎格尔的学徒")
    {
        setname("坎格尔的学徒");
        setid(604);
        setlevel(6);
        setbase(3, 6);
        setrace(NEUTRAL);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {604,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    
    if(name == "阴森巨蟒")
    {
        setname("阴森巨蟒");
        setid(605);
        setlevel(6);
        setbase(7, 7);
        setrace(BEAST);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {605,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "熊妈妈")
    {
        setname("熊妈妈");
        setid(606);
        setlevel(6);
        setbase(5, 5);
        setrace(BEAST);
    }
    if(name == "温顺的巨壳龙")
    {
        setname("温顺的巨壳龙");
        setid(607);
        setlevel(6);
        setbase(5,4);
        setrace(BEAST);
    }
    
    if(name == "红衣纳迪娜")
    {
        setname("红衣纳迪娜");
        setid(608);
        setlevel(6);
        setbase(7, 4);
        setrace(NEUTRAL);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {608,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    if(name == "奥术守护者卡雷苟斯")
    {
        setid(609);
        setname("奥术守护者卡雷苟斯");
        setlevel(6);
        setbase(4,12);
        setrace(DRAGON);
    }
    if(name == "小鬼妈妈")
    {
        setname("小鬼妈妈");
        setid(610);
        setlevel(6);
        setbase(6, 10);
        setrace(DEMON);
        timepoints t[5] = {AFTER_DAMAGE,NONE,NONE,NONE,NONE};
        int e[5] = {610,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    
    if(name == "鲭鱼圣者")
    {
        setname("鲭鱼圣者");
        setid(611);
        setlevel(6);
        setbase(8, 4);
        setrace(MURLOC);
    }
    
    if(name == "777")
    {
        setname("777");
        setid(777);
        setlevel(7);
        setbase(7, 7);
        setrace(ALL);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {777,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    
    /*------------------------------------金色分割线------------------------*/
    if(name == "金色恩佐斯的子嗣")
    {
        setname("金色恩佐斯的子嗣");
        setid(2060);
        setlevel(2);
        setbase(2, 2);
        setrace(NEUTRAL);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {2060,0,0,0,0};
        settimepoint(t);
        seteffect(e);
        
    }
    
    if(name == "爆爆机器人")
    {
        setname("金色爆爆机器人");
        setid(2080);
        setlevel(2);
        setbase(4, 4);
        setrace(MECH);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {2080,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    
    if(name == "金色浴火者伯瓦尔")
    {
        setname("金色浴火者伯瓦尔");
        setid(4040);
        setlevel(4);
        setbase(2, 14);
        setrace(NEUTRAL);
        setshield(true);
    }
    
    if(name == "金色机械蛋")
    {
        setname("金色机械蛋");
        setid(4070);
        setlevel(4);
        setbase(0, 16);
        setrace(MECH);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {4070,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    
    
    if(name == "金色龙人执行者")
    {
        setname("金色龙人执行者");
        setid(4160);
        setlevel(4);
        setbase(6, 12);
        setrace(DRAGON);
        
    }
    
    
    if(name == "金色巨狼戈德林")
    {
        setname("金色巨狼戈德林");
        setid(5090);
        setlevel(5);
        setbase(8, 8);
        setrace(BEAST);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {5090,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    
    if(name == "金色拜戈尔格国王")
    {
        setname("金色拜戈尔格国王");
        setid(5130);
        setlevel(5);
        setbase(12, 4);
        setrace(MURLOC);
        setdeathrattle(true);
        timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
        int e[5] = {5130,0,0,0,0};
        settimepoint(t);
        seteffect(e);
    }
    
    if(name == "金色瑞文戴尔男爵")
    {
        setname("金色瑞文戴尔男爵");
        setid(5020);
        setlevel(5);
        setbase(2, 14);
        setrace(NEUTRAL);
    }
    
    
    setgameid();
    
    
    
}





































































void Card::setbyid(int id)
{
    if(id == 1)
    {
        setname("损坏的傀儡");
        setid(1);
        setrace(MECH);
        setlevel(1);
        setbase(1, 1);
    }
    if(id == 2)
    {
        setname("微型机器人");
        setid(2);
        setrace(MECH);
        setlevel(1);
        setbase(1, 1);
    }
    if(id == 3)
    {
        setname("机械暴龙");
        setid(3);
        setrace(MECH);
        setlevel(1);
        setbase(8, 8);
    }
    
    if(id == 4)
    {
        setname("机械袋鼠宝宝");
        setid(4);
        setrace(MECH);
        setlevel(1);
        setbase(1, 1);
    }
    if(id == 5)
    {
        setname("安保儿子");
        setid(5);
        setrace(MECH);
        setlevel(1);
        setbase(2, 3);
        settaunt(true);
    }
    
    if(id == 6)
    {
        setname("雌斑虎");
        setid(6);
        setrace(MECH);
        setlevel(1);
        setbase(1, 1);
    }
    
    if(id == 7)
    {
        setname("鱼人斥候");
        setid(7);
        setrace(MURLOC);
        setlevel(1);
        setbase(1, 1);
    }
    
    if(id == 101)
     {
         setid(101);
         setname("鱼人招潮者");
         setlevel(1);
         setrace(MURLOC);
         setbase(1, 2);
     }
    if(id == 102)                   //to be done
     {
         setname("恐狼前锋");
         setid(102);
         setlevel(1);
         setbase(2, 2);
         setrace(BEAST);
     }
     if(id == 103)
     {
         setname("无私的英雄");
         setid(103);
         setlevel(1);
         setrace(NEUTRAL);
         setbase(2, 1);
         setdeathrattle(true);
         timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
         int e[5] = {103,0,0,0,0};
         settimepoint(t);
         seteffect(e);
     }
     if(id == 104)
     {
         setid(104);
         setname("雄斑虎");
         setlevel(1);
         setrace(BEAST);
         setbase(1, 1);
         timepoints t[5] = {BATTLECRY,NONE,NONE,NONE,NONE};
         int e[5] = {104,0,0,0,0};
         settimepoint(t);
         seteffect(e);
     }
     if(id == 105)
     {
         setname("正义保护者");
         setid(105);
         setlevel(1);
         setrace(NEUTRAL);
         setbase(1, 1);
         settaunt(true);
         setshield(true);
     }
     if(id == 106)
     {
         setname("石塘猎人");
         setid(106);
         setlevel(1);
         setrace(MURLOC);
         setbase(2, 3);
         timepoints t[5] = {BATTLECRY,NONE,NONE,NONE,NONE};
         int e[5] = {106,0,0,0,0};
         settimepoint(t);
         seteffect(e);
     }
     if(id == 107)
     {
         setname("微型战斗机甲");
         setid(107);
         setlevel(1);
         setrace(MECH);
         setbase(1, 2);
     }
     
     if(id == 108)
     {
         setname("机械袋鼠");
         setid(108);
         setlevel(1);
         setrace(MECH);
         setbase(1, 1);
         timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
         int e[5] = {108,0,0,0,0};
         settimepoint(t);
         seteffect(e);
     }
     if(id == 109)
     {
         setname("愤怒编织者");
         setid(109);
         setlevel(1);
         setrace(NEUTRAL);
         setbase(1,1);
     }
     if(id == 110)
     {
         setname("鱼人猎潮者");
         setid(110);
         setlevel(1);
         setrace(MURLOC);
         setbase(2, 1);
         timepoints t[5] = {BATTLECRY,NONE,NONE,NONE,NONE};
         int e[5] = {110,0,0,0,0};
         settimepoint(t);
         seteffect(e);
     }
     if(id == 111)
     {
         setname("粗俗的矮劣魔");
         setid(111);
         setlevel(1);
         setrace(DEMON);
         setbase(2,4);
         settaunt(true);
         timepoints t[5] = {BATTLECRY,NONE,NONE,NONE,NONE};
         int e[5] = {111,0,0,0,0};
         settimepoint(t);
         seteffect(e);
     }
     if(id == 112)
     {
         setname("邪魔仆从");
         setid(112);
         setlevel(1);
         setrace(DEMON);
         setbase(2,1);
         timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
         int e[5] = {112,0,0,0,0};
         settimepoint(t);
         seteffect(e);
     }
     if(id == 113)
     {
         setid(113);
         setname("红色雏龙");
         setrace(DRAGON);
         setbase(1,2);
         setlevel(1);
         timepoints t[5] = {BEFORE_BATTLE,NONE,NONE,NONE,NONE};
         int e[5] = {113,0,0,0,0};
         settimepoint(t);
         seteffect(e);
     }
     if(id == 114)
     {
         setid(114);
         setname("龙人军官");
         setlevel(1);
         setrace(DRAGON);
         setbase(2,3);
         settaunt(true);
     }
    if(id == 201)
       {
           setname("老瞎眼");
           setid(201);
           setlevel(2);
           setbase(2, 4);
           setrace(MURLOC);
       }
       if(id == 202)
       {
           setname("金刚刃牙兽");
           setid(202);
           setlevel(2);
           setbase(3, 3);
           setrace(MECH);
           timepoints t[5] = {BATTLECRY,NONE,NONE,NONE,NONE};
           int e[5] = {202,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       if(id == 203)
       {
           setname("蹒跚的食尸鬼");
           setid(203);
           setlevel(2);
           setbase(1, 3);
           setrace(NEUTRAL);
           settaunt(true);
           setdeathrattle(true);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {203,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       if(id == 204)
       {
           setname("慈祥的外婆");
           setid(204);
           setlevel(2);
           setbase(1, 1);
           setrace(BEAST);
           setdeathrattle(true);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {204,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       if(id == 205)
       {
           setname("机械动物管理员");
           setid(205);
           setlevel(2);
           setrace(MECH);
           setbase(3,3);
       }
       if(id == 206)
       {
           setname("恩佐斯的子嗣");
           setid(206);
           setlevel(2);
           setbase(2, 2);
           setrace(NEUTRAL);
           setdeathrattle(true);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {206,0,0,0,0};
           settimepoint(t);
           seteffect(e);
           
       }
       if(id == 207)
       {
           setname("蹦蹦兔");
           setid(207);
           setlevel(2);
           setrace(MECH);
           setbase(1,1);
       }
       
       if(id == 208)
       {
           setname("爆爆机器人");
           setid(208);
           setlevel(2);
           setbase(2, 2);
           setrace(MECH);
           setdeathrattle(true);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {208,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       
       if(id == 209)
       {
           setname("纳斯雷兹姆监工");
           setid(209);
           setlevel(2);
           setrace(DEMON);
           setbase(2,3);
       }
       
       if(id == 210)
       {
           setname("鱼人领军");
           setid(210);
           setlevel(2);
           setrace(MURLOC);
           setbase(3,3);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {210,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       if(id == 211)
       {
           setname("瘟疫鼠群");
           setid(211);
           setlevel(2);
           setrace(BEAST);
           setbase(2, 2);
           setdeathrattle(true);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {211,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       
       if(id == 212)
       {
           setname("食腐土狼");
           setid(212);
           setlevel(2);
           setrace(BEAST);
           setbase(2, 2);
       }
       if(id == 213)
       {
           setname("麦田傀儡");
           setid(213);
           setlevel(2);
           setbase(2, 3);
           setrace(MECH);
           setdeathrattle(true);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {213,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       
       if(id == 214)
       {
           setname("小鬼囚徒");
           setid(214);
           setlevel(2);
           setrace(DEMON);
           setbase(3, 3);
           settaunt(true);
           setdeathrattle(true);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {214,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       if(id == 215)         //to be done
       {
           setname("蜡烛骑士托瓦格尔");
           setid(215);
           setlevel(2);
           setrace(NEUTRAL);
           setbase(1, 2);
       }
       if(id == 216)
       {
           setname("时间管理者");
           setid(216);
           setrace(DRAGON);
           setlevel(2);
           setbase(3, 4);
       }
       if(id == 217)
       {
           setname("雕文护卫者");
           setid(217);
           setlevel(2);
           setbase(2, 4);
           setrace(DRAGON);
           timepoints t[5] = {BEFORE_ATTACK,NONE,NONE,NONE,NONE};
           int e[5] = {217,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       
       if(id == 301)
       {
           setname("比斯巨兽");
           setid(301);
           setlevel(3);
           setbase(9,7);
           setrace(BEAST);
           setdeathrattle(true);
           timepoints t[5] = {BEFORE_ATTACK,NONE,NONE,NONE,NONE};
           int e[5] = {301,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       
       if(id == 302)
       {
           setname("人气选手");
           setid(302);
           setlevel(3);
           setbase(4, 4);
           setrace(NEUTRAL);
           
       }
       
       if(id == 303)
       {
           setname("小鬼首领");
           setid(303);
           setlevel(3);
           setbase(2, 4);
           setrace(DEMON);
           timepoints t[5] = {DAMAGE_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {303,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       
       if(id == 304)
       {
           setname("寄生恶狼");
           setid(304);
           setlevel(3);
           setbase(3, 3);
           setrace(BEAST);
           setdeathrattle(true);
           timepoints t[5] = {DAMAGE_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {304,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       if(id == 305)
       {
           setname("魔瘾结晶者");
           setid(305);
           setlevel(3);
           setbase(5, 4);
           setrace(NEUTRAL);
       }
       
       if(id == 306)
       {
           setname("寒光先知");
           setid(306);
           setlevel(3);
           setbase(2, 3);
           setrace(MURLOC);
       }
       
       if(id == 307)
       {
           setname("载人收割机");
           setid(307);
           setlevel(3);
           setbase(4, 3);
           setrace(MECH);
           setdeathrattle(true);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {307,0,0,0,0};
           settimepoint(t);
           seteffect(e);
           
       }
       
       if(id == 308)
       {
           setname("族群领袖");
           setid(308);
           setlevel(3);
           setbase(3, 3);
           setrace(NEUTRAL);
       }
       if(id == 309)
       {
           setname("量产型恐吓机");
           setid(309);
           setlevel(3);
           setbase(3, 1);
           setrace(MECH);
           setdeathrattle(true);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {309,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       if(id == 310)
       {
           setname("灵魂杂耍者");
           setid(310);
           setlevel(3);
           setbase(3, 3);
           setrace(NEUTRAL);
       }
       if(id == 311)
       {
           setname("驯兽师");
           setid(311);
           setlevel(3);
           setbase(4, 3);
           setrace(NEUTRAL);
       }
       if(id == 312)
       {
           setname("废旧螺栓机甲");
           setid(312);
           setlevel(3);
           setbase(2, 5);
           setrace(NEUTRAL);
       }
       if(id == 313)
       {
           setname("百变泽鲁斯");
           setid(313);
           setlevel(3);
           setbase(1, 1);
           setrace(NEUTRAL);
       }
       
       if(id == 314)                    //to be done
       {
           setname("卡德加");
           setid(314);
           setlevel(3);
           setbase(2, 2);
           setrace(NEUTRAL);
       }
       if(id == 315)
       {
           setname("急饿巨龙");
           setid(315);
           setlevel(3);
           setbase(4, 4);
           setrace(DRAGON);
       }
       
       if(id == 316)
       {
           setname("青铜守卫");
           setid(316);
           setlevel(3);
           setbase(2, 1);
           setshield(true);
           setrace(DRAGON);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {316,0,0,0,0};
           settimepoint(t);
           seteffect(e);
           
       }
       if(id == 317)
       {
           setname("暮光使者");
           setid(317);
           setlevel(3);
           setbase(4, 4);
           setrace(DRAGON);
           settaunt(true);
       }
       
       if(id == 318)
       {
           setname("邪鳍导航员");
           setid(318);
           setlevel(3);
           setbase(4, 4);
           setrace(MURLOC);
       }
       
       
       if(id == 319)
       {
           setname("偏折机器人");
           setrace(MECH);
           setid(319);
           setlevel(3);
           setbase(3, 2);
           setshield(true);
           
       }
       if(id == 401)
       {
           setname("漂浮观察者");
           setid(401);
           setlevel(4);
           setbase(4, 4);
           setrace(DEMON);
       }
       
       if(id == 402)
       {
           setname("长鬃草原狮");
           setid(402);
           setlevel(4);
           setbase(6, 5);
           setrace(BEAST);
           setdeathrattle(true);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {402,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       if(id == 403)
       {
           setname("展览馆法师");
           setid(403);
           setlevel(4);
           setbase(4, 4);
           setrace(NEUTRAL);
           
       }
       if(id == 404)
       {
           setname("浴火者伯瓦尔");
           setid(404);
           setlevel(4);
           setbase(1, 7);
           setrace(NEUTRAL);
       }
       if(id == 405)
       {
           setname("吵吵模组");
           setid(405);
           setlevel(4);
           setbase(2, 4);
           setrace(MECH);
           settaunt(true);
           setshield(true);
       }
       if(id == 406)
       {
           setname("安保巡游者");
           setid(406);
           setlevel(4);
           setbase(2, 6);
           setrace(MECH);
           timepoints t[5] = {DAMAGE_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {406,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       if(id == 407)
       {
           setname("机械蛋");
           setid(407);
           setlevel(4);
           setbase(0, 8);
           setrace(MECH);
           setdeathrattle(true);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {407,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       if(id == 408)
       {
           setname("阿古斯防御者");
           setid(408);
           setlevel(4);
           setrace(NEUTRAL);
           setbase(2, 3);
       }
       if(id == 409)
       {
           setname("兔妖教头");
           setid(409);
           setlevel(4);
           setrace(NEUTRAL);
           setbase(4, 5);
       }
       if(id == 410)
       {
           setname("钢铁武道家");
           setid(410);
           setlevel(4);
           setrace(MECH);
           setbase(2, 2);
       }
       if(id == 411)
       {
           setname("攻城恶魔");
           setid(411);
           setrace(DEMON);
           setbase(5, 8);
           setlevel(4);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {411,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       if(id == 412)
       {
           setname("洞穴多头蛇");
           setid(412);
           setrace(BEAST);
           setlevel(4);
           setbase(2, 4);
           setbattlefury(true);
       }
       if(id == 413)
       {
           setname("深蓝刃鳞龙人");
           setid(413);
           setlevel(4);
           setrace(DRAGON);
           setbase(5, 5);
       }
       if(id == 414)
       {
           setname("毒鳍鱼人");
           setid(414);
           setlevel(4);
           setrace(MURLOC);
           setbase(1, 2);
       }
       if(id == 415)    //to be done
       {
           setname("火焰传令官");
           setid(415);
           setlevel(4);
           setrace(DRAGON);
           setbase(5, 6);
       }
       if(id == 416)
       {
           setname("龙人执行者");
           setid(416);
           setlevel(4);
           setbase(3, 6);
           setrace(DRAGON);
           
       }
       if(id == 501)
       {
           setname("回收机器人");
           setid(501);
           setlevel(5);
           setbase(1,5);
           setrace(MECH);
       }
       if(id == 502)
       {
           setname("瑞文戴尔男爵");
           setid(502);
           setlevel(5);
           setbase(1, 7);
           setrace(NEUTRAL);
       }
       if(id == 503)
       {
           setname("硬壳清道夫");
           setid(503);
           setlevel(5);
           setbase(2, 3);
           setrace(NEUTRAL);
       }
       if(id == 504)
       {
           setname("虚空领主");
           setid(504);
           setlevel(5);
           setbase(3,9);
           setrace(DEMON);
           settaunt(true);
           setdeathrattle(true);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {504,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       if(id == 505)
       {
           setname("铁皮恐角龙");
           setid(505);
           setlevel(5);
           setrace(BEAST);
           setbase(7,7);
           setoverkill(true);
           
       }
       
       if(id == 506)
       {
           setname("斯尼德的伐木机");
           setid(506);
           setlevel(5);
           setbase(5, 7);
           setrace(MECH);
           setdeathrattle(true);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {506,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       if(id == 507)
       {
           setname("光牙执行者");
           setid(507);
           setlevel(5);
           setbase(2, 2);
           setrace(NEUTRAL);
       }
       if(id == 508)
       {
           setname("安尼赫兰战场军官");
           setid(508);
           setlevel(5);
           setbase(3,1);
           setrace(DEMON);
       }
       if(id == 509)
       {
           setname("巨狼戈德林");
           setid(509);
           setlevel(5);
           setbase(4, 4);
           setrace(BEAST);
           setdeathrattle(true);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {509,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       
       if(id == 510)
       {
           setname("蛮鱼斥候");
           setid(510);
           setlevel(5);
           setbase(3, 2);
           setrace(MURLOC);
       }
       if(id == 511)
       {
           setname("布莱恩-铜须");
           setid(511);
           setlevel(5);
           setbase(2, 4);
           setrace(NEUTRAL);
       }
       if(id == 512)
       {
           setname("玛尔加尼斯");
           setid(512);
           setlevel(5);
           setbase(9,7);
           setrace(DEMON);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {512,0,0,0,0};
           settimepoint(t);
           seteffect(e);
           
       }
       if(id == 513)
       {
           setname("拜戈尔格国王");
           setid(513);
           setlevel(5);
           setbase(6, 3);
           setrace(MURLOC);
           setdeathrattle(true);
       }
       if(id == 514)
       {
           setname("狂野的拉佐格尔");
           setid(514);
           setlevel(5);
           setbase(2, 4);
           setrace(DRAGON);
       }
       
       if(id == 515)
       {
           setname("姆诺兹多");
           setid(515);
           setlevel(5);
           setbase(5, 5);
           setrace(DRAGON);
       }
       
       if(id == 601)
       {
           setname("死神4000型");
           setid(601);
           setlevel(6);
           setbase(6, 9);
           setrace(MECH);
           setbattlefury(true);
       }
       
       if(id == 602)
       {
           setname("迈克斯纳");
           setid(602);
           setlevel(6);
           setbase(2,8);
           setrace(BEAST);
           setpoisonous(true);
       }
       if(id == 603)
       {
           setname("扎普-斯里维克");
           setid(603);
           setlevel(6);
           setbase(7, 9);
           setrace(NEUTRAL);
           setwindfury(true);
           
       }
       
       if(id == 604)
       {
           setname("坎格尔的学徒");
           setid(604);
           setlevel(6);
           setbase(3, 6);
           setrace(NEUTRAL);
           setdeathrattle(true);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {604,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       
       if(id == 605)
       {
           setname("阴森巨蟒");
           setid(605);
           setlevel(6);
           setbase(7, 7);
           setrace(BEAST);
           setdeathrattle(true);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {605,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       if(id == 606)
       {
           setname("熊妈妈");
           setid(606);
           setlevel(6);
           setbase(5, 5);
           setrace(BEAST);
       }
       if(id == 607)
       {
           setname("温顺的巨壳龙");
           setid(607);
           setlevel(6);
           setbase(5,4);
           setrace(BEAST);
       }
       
       if(id == 608)
       {
           setname("红衣纳迪娜");
           setid(608);
           setlevel(6);
           setbase(7, 4);
           setrace(NEUTRAL);
           setdeathrattle(true);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {608,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       if(id == 609)
       {
           setid(609);
           setname("奥术守护者卡雷苟斯");
           setlevel(6);
           setbase(4,12);
           setrace(DRAGON);
       }
       if(id == 610)
       {
           setname("小鬼妈妈");
           setid(610);
           setlevel(6);
           setbase(6, 10);
           setrace(DEMON);
           timepoints t[5] = {DAMAGE_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {610,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
       
       if(id == 611)
       {
           setname("鲭鱼圣者");
           setid(611);
           setlevel(6);
           setbase(8, 4);
           setrace(MURLOC);
       }
    
        
       if(id == 777)
       {
           setname("777");
           setid(777);
           setlevel(7);
           setbase(7, 7);
           setrace(ALL);
           setdeathrattle(true);
           timepoints t[5] = {DEATH_PHASE,NONE,NONE,NONE,NONE};
           int e[5] = {777,0,0,0,0};
           settimepoint(t);
           seteffect(e);
       }
    
    
    /*-----------------------------------金色分割线---------------------------------------*/
    
    
    
    
    
    
    
    
    setgameid();
}
