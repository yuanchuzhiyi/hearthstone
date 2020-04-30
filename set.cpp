//
//  set.cpp
//  jiuguanzhanqi
//
//  Created by Mr.zhu on 2020/4/13.
//  Copyright © 2020 Mr.zhu. All rights reserved.
//

#include "set.hpp"
#include "Card.hpp"
#include "Player.hpp"
#include "global.hpp"
#include <map>
extern map<int,ef> effectfuncs;
extern timepoints timepoint;
void reset_player(Player& player1, Player& player2)
{
    map <int,Card> map1;
    map <int,Card> map2;
    
    Card a1;
    Card a2;
    Card a3;
    Card a4;
    Card a5;
    Card a6;
    Card a7;
    Card b1;
    Card b2;
    Card b3;
    Card b4;
    Card b5;
    Card b6;
    Card b7;
    
    a1.setbyname("777");
    a2.setbyname("777");
    a3.setbyname("777");
    a4.setbyname("777");
    a5.setbyname("777");
    a6.setbyname("777");
    a7.setbyname("777");
    b1.setbyname("777");
    b2.setbyname("777");
    b3.setbyname("777");
    b4.setbyname("777");
    b5.setbyname("777");
    b6.setbyname("777");
    b7.setbyname("777");
    
//    a1.setbase(6, 3);
//    a2.setbase(7, 7);
//    a3.setbase(4, 3);
//    a4.setbase(8, 7);
//    a5.setbase(6, 5);
//    a6.setbase(5, 7);
//    a7.setbase(1, 7);
//
//    b1.settaunt(true);
//    b1.setbase(6, 3);
//    b2.setbase(7, 8);
//    b3.setbase(2, 4);
//    b4.setbase(2, 1);
//    b5.setbase(3, 4);
//    b6.setbase(2, 4);
//    b7.setbase(3, 3);
    
    
    map1[1] = a1;
    map1[2] = a2;
    map1[3] = a3;
    map1[4] = a4;
    map1[5] = a5;
    map1[6] = a6;
    map1[7] = a7;
    map2[1] = b1;
    map2[2] = b2;
    map2[3] = b3;
    map2[4] = b4;
    map2[5] = b5;
    map2[6] = b6;
    map2[7] = b7;
    
    
    player1.setminions(map1);
    player2.setminions(map2);

}


