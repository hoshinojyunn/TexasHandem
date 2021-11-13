#include <bits/stdc++.h>
#include "Poker.h"
using namespace std;
//// EV = (%W*$W)-(%L*$L)



double cal_EV(playerPoker){
    int win=0;
    double EV;
    int opponentBet=opponent.getBet();
    int playerBet=player.getBet();
    for(int i=0;i!=10000;++i){  //10000局比赛
        auto opponentPoker=opponent.takePoker();
        if(playerPoker.Point>opponentPoker.Point){
            ++win;
        }else{
            continue;
        }
    }
    double winRate=win*1.0/10000;
    EV=(winRate*(opponentBet+playerBet))-((1-winRate)*(opponentBet-playerBet));
    return EV;
}

int main() {
   /*start*/
   Player player;
   playerPoker p_Poker=player.takePoker();
   while(!game.end()) {
       if(cal_EV(p_Poker)>0){
           player.follow();
       }else{
           player.giveUp();
       }
       continue;
   }
}
