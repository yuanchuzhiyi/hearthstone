//
//  global.cpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/13.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//

#include "global.hpp"
#include "Player.hpp"
#include "effect_func.hpp"



int turn;
map<int,ef> effectfuncs;
timepoints timepoint = NONE;
int global_id = 0;
int level_minion_count[] = {14, 17, 19, 16, 15, 11};//每个等级有多少只怪
int level_total_number[] = {18, 15, 13, 11, 9, 6};//不同等级怪的卡池数量
void register_effectfuncs()
{
    void (*p103)(Player&, Player&, int[]) = ef_103;
    effectfuncs[103] = p103;
    
    void (*p104)(Player&, Player&, int[]) = ef_104;
    effectfuncs[104] = p104;
    
    void (*p106)(Player&, Player&, int[]) = ef_106;
    effectfuncs[106] = p106;
    
    void (*p108)(Player&, Player&, int[]) = ef_108;
    effectfuncs[108] = p108;
    
    void (*p110)(Player&, Player&, int[]) = ef_110;
    effectfuncs[110] = p110;
    
    void (*p111)(Player&, Player&, int[]) = ef_111;
    effectfuncs[111] = p111;
    
    void (*p112)(Player&, Player&, int[]) = ef_112;
    effectfuncs[112] = p112;
    
    void (*p113)(Player&, Player&, int[]) = ef_113;
    effectfuncs[113] = p113;
    
    void (*p202)(Player&, Player&, int[]) = ef_202;
    effectfuncs[202] = p202;
    
    void (*p203)(Player&, Player&, int[]) = ef_203;
    effectfuncs[203] = p203;
    
    void (*p204)(Player&, Player&, int[]) = ef_204;
    effectfuncs[204] = p204;
    
    void (*p206)(Player&, Player&, int[]) = ef_206;
    effectfuncs[206] = p206;
    
    void (*p208)(Player&, Player&, int[]) = ef_208;
    effectfuncs[208] = p208;
    
    void (*p210)(Player&, Player&, int[]) = ef_210;
    effectfuncs[210] = p210;
    
    void (*p211)(Player&, Player&, int[]) = ef_211;
    effectfuncs[211] = p211;
    
    void (*p213)(Player&, Player&, int[]) = ef_213;
    effectfuncs[213] = p213;
    
    void (*p214)(Player&, Player&, int[]) = ef_214;
    effectfuncs[214] = p214;
    
    void (*p217)(Player&, Player&, int[]) = ef_217;
    effectfuncs[217] = p217;
    
    void (*p301)(Player&, Player&, int[]) = ef_301;
    effectfuncs[301] = p301;
    
    void (*p303)(Player&, Player&, int[]) = ef_303;
    effectfuncs[303] = p303;
    
    void (*p304)(Player&, Player&, int[]) = ef_304;
    effectfuncs[304] = p304;
    
    void (*p307)(Player&, Player&, int[]) = ef_307;
    effectfuncs[307] = p307;
    
    void (*p309)(Player&, Player&, int[]) = ef_309;
    effectfuncs[309] = p309;
    
    void (*p316)(Player&, Player&, int[]) = ef_316;
    effectfuncs[316] = p316;
    
    void (*p402)(Player&, Player&, int[]) = ef_402;
    effectfuncs[402] = p402;
    
    void (*p406)(Player&, Player&, int[]) = ef_406;
    effectfuncs[406] = p406;
    
    void (*p407)(Player&, Player&, int[]) = ef_407;
    effectfuncs[407] = p407;
    
    void (*p411)(Player&, Player&, int[]) = ef_411;
    effectfuncs[411] = p411;
    
    void (*p504)(Player&, Player&, int[]) = ef_504;
    effectfuncs[504] = p504;
    
    void (*p506)(Player&, Player&, int[]) = ef_506;
    effectfuncs[506] = p506;
    
    void (*p509)(Player&, Player&, int[]) = ef_509;
    effectfuncs[509] = p509;
    
    void (*p512)(Player&, Player&, int[]) = ef_512;
    effectfuncs[512] = p512;
    
    void (*p513)(Player&, Player&, int[]) = ef_513;
    effectfuncs[513] = p513;
    
    void (*p604)(Player&, Player&, int[]) = ef_604;
    effectfuncs[604] = p604;
    
    void (*p605)(Player&, Player&, int[]) = ef_605;
    effectfuncs[605] = p605;
    
    void (*p608)(Player&, Player&, int[]) = ef_608;
    effectfuncs[608] = p608;
    
    void (*p610)(Player&, Player&, int[]) = ef_610;
    effectfuncs[610] = p610;
    
    void (*p777)(Player&, Player&, int[]) = ef_777;
    effectfuncs[777] = p777;
    
    
    /*--------------金色分割线-------------------*/
    
    void (*p2060)(Player&, Player&, int[]) = ef_2060;
    effectfuncs[2060] = p2060;
    
    void (*p2080)(Player&, Player&, int[]) = ef_2080;
    effectfuncs[2080] = p2080;

    void (*p4070)(Player&, Player&, int[]) = ef_4070;
    effectfuncs[4070] = p4070;
    
    void (*p5090)(Player&, Player&, int[]) = ef_5090;
    effectfuncs[5090] = p5090;
    
    void (*p5130)(Player&, Player&, int[]) = ef_5130;
    effectfuncs[5130] = p5130;
}

  
