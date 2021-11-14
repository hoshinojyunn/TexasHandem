//
// Created by 47345 on 2021/11/13.
//
#ifndef PLAYER_H
#define PLAYER_H
#include <bits/stdc++.h>
#include "Poker.h"
#include "judge.h"
#include "jackPot.h"
class Player{
public:
    std::vector<std::pair<int,char>>Poker;
    double bonus{};//赌注
    int bet{};   //当前进度所下的赌注
    std::string identity;
    Player()=default;
    explicit Player(double rand,double bonus=20000){
        bet=0;
        this->bonus=bonus;
        if(rand>0.5){
            identity="bigblind";
        }else{
            identity="smallblind";
        }
        //base(Poker);
    }
    void make_bet(jackPot&pot,int bet){  //下赌注
        bonus-=bet;
        this->bet+=bet;
        pot.total+=bet;
    }
    int follow(jackPot&pot,Player opponent){  //跟注
        int follow_bet=opponent.bet-bet;  //跟注需要加的钱
        bonus-=follow_bet;
        bet=opponent.bet;
        pot.total+=follow_bet;
        return follow_bet;
    }
    int raise(jackPot&pot,Player opponent){  //加注
        int fill_bet=opponent.bet*2-bet;
        bonus-=fill_bet;
        bet=bet+opponent.bet*2;
        pot.total+=fill_bet;
        return fill_bet;
    }
    void display(){  //显示当前信息
        std::cout<<"当前总金额:"<<bonus<<std::endl;
        std::cout<<"当前已下赌注:"<<bet<<std::endl;
        std::cout<<"身份:"<<identity<<std::endl;
        std::cout<<"你的手牌: ";
        for(int i=0;i!=Poker.size();++i){
            if(Poker[i].second=='A'){
                std::cout<<"方块";
            }else if(Poker[i].second=='B'){
                std::cout<<"梅花";
            }else if(Poker[i].second=='C'){
                std::cout<<"红桃";
            }else if(Poker[i].second=='D'){
                std::cout<<"黑桃";
            }
            if(Poker[i].first<=9){
                std::cout<<Poker[i].first+1;
            }else if(Poker[i].first==10){
                std::cout<<"J";
            }else if(Poker[i].first==11){
                std::cout<<"Q";
            }else if(Poker[i].first==12){
                std::cout<<"K";
            }else if(Poker[i].first==13){
                std::cout<<"A";
            }
            std::cout<<" ";
        }
    }
    void fold(jackPot&pot,Player&opponent){  //弃牌  直接结束本轮游戏
        opponent.bonus+=pot.total;
        opponent.bet=0;
        this->bet=0;
    }



    void check(){   //check 过牌 什么也不做
        return;
    }

};
#endif