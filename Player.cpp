//
// Created by 47345 on 2021/11/13.
//
#include <bits/stdc++.h>
#include "Poker.h"
using namespace std;
class CardPlayer{
public:
    multimap<int,char>Poker;
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
int main(){
    CardPlayer opponent(20000);
    CardPlayer player(20000);
    multimap<int,char>River_Card;
    RiverCard(River_Card);
    multimap<int,char>Player_arr;
    multimap<int,char>opponent_arr;
    /*构造玩家牌种序列*/
    Player_arr.insert(River_Card.begin(),River_Card.end());
    Player_arr.insert(player.Poker.begin(),player.Poker.end());
    /*构造对手牌种序列*/
    opponent_arr.insert(River_Card.begin(),River_Card.end());
    opponent_arr.insert(opponent.Poker.begin(),opponent.Poker.end());
    cout<<"complete";
    //完成
}