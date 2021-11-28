//
// Created by 47345 on 2021/11/28.
//

#ifndef TEXASHANDEM_GAME_H
#define TEXASHANDEM_GAME_H

#include "Player.h"
#include "Poker.h"
class Game {
public:
    bool ending=false;
    void Round1(Player&player,Player&opponent,jackPot&pot);
    void Round2(Player&player,Player&opponent,jackPot&pot);
    void Round3(Player&player,Player&opponent,jackPot&pot);
    void Round_final(Player&player,Player&opponent,jackPot&pot);
};


#endif //TEXASHANDEM_GAME_H
