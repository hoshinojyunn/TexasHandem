//
// Created by 47345 on 2021/11/13.
//
#ifndef PLAYER_H
#define PLAYER_H
#include <bits/stdc++.h>
#include "Poker.h"
#include "judge.h"
using namespace std;
class CardPlayer{
public:
    vector<pair<int,char>>Poker;
    double bonus;//赌注
    string identity;
    explicit CardPlayer(double bonus=20000){
        this->bonus=bonus;
        srand(time(nullptr));
        if((rand()*1.0)/RAND_MAX>0.5){
            identity="bigblind";
        }else{
            identity="smallblind";
        }
        base(Poker);
    }

    void earn(double bet){
        bonus+=bet;
    }//赢家全拿

    void loss(double bet){
        bonus-=bet;
    }//输掉赌注

};
#endif