#include <bits/stdc++.h>
#include "Poker.h"
#include "Player.h"
using namespace std;
//// EV = (%W*$W)-(%L*$L)



// double cal_EV(vector<pair<int,char>>playerPoker){
//     int win=0;
//     double EV;
//     int opponentBet=opponent.getBet();
//     int playerBet=player.getBet();
//     for(int i=0;i!=10000;++i){  //10000局比赛
//         auto opponentPoker=opponent.takePoker();
//         if(playerPoker.Point>opponentPoker.Point){
//             ++win;
//         }else{
//             continue;
//         }
//     }
//     double winRate=win*1.0/10000;
//     EV=(winRate*(opponentBet+playerBet))-((1-winRate)*(opponentBet-playerBet));
//     return EV;
// }

int main(){
    CardPlayer opponent(20000);
    CardPlayer player(20000);
    vector<pair<int,char>>River_Card{};
    RiverCard(River_Card);
    add(River_Card);
    add(River_Card);
    vector<pair<int,char>>Player_arr{};
    vector<pair<int,char>>opponent_arr;
    vector<pair<int,char>>test_arr{{9,'B'},{9,'A'},{9,'C'},{11,'A'},{10,'B'},{10,'A'},{12,'A'}};
    /*构造玩家牌种序列*/
    Player_arr.insert(Player_arr.cbegin(),River_Card.begin(),River_Card.end());
    Player_arr.insert(Player_arr.cbegin(),player.Poker.begin(),player.Poker.end());
    /*构造对手牌种序列*/
    opponent_arr.insert(opponent_arr.cbegin(),River_Card.begin(),River_Card.end());
    opponent_arr.insert(opponent_arr.cbegin(),opponent.Poker.begin(),opponent.Poker.end());
    if(judge_straight(Player_arr)){
        cout<<"这是顺子"<<endl;
    }else{
        cout<<"No"<<endl;
    }
    if(judge_straight(opponent_arr)){
        cout<<"this straight"<<endl;
    }else{
        cout<<"fuck"<<endl;
    }
    if(judge_same_flush(Player_arr)){
        cout<<"这是同花"<<endl;
    }else{
        cout<<"No"<<endl;
    }
    if(judge_same_flush(opponent_arr)){
        cout<<"this is same flush"<<endl;
    }else{
        cout<<"fuck"<<endl;
    }
    if(judge_pair(test_arr)){
        cout<<"test one pair"<<endl;
    }else{
        cout<<"asndsd"<<endl;
    }
    if(judge_twopair(test_arr)){
        cout<<"test two pair"<<endl;
    }else{
        cout<<"not two pair"<<endl;
    }
    if(judge_straight_wh(test_arr)){
        cout<<"test straiht_wh"<<endl;
    }else{
        cout<<"not straight_wh"<<endl;
    }
    if(judge_straight_w(test_arr)){
        cout<<"test straight_w"<<endl;
    }else{
        cout<<"not straight_w"<<endl;
    }
    if(judge_twopair(test_arr)){
        cout<<"test two_pair"<<endl;
    }else{
        cout<<"not two_pair"<<endl;
    }
    if(judge_Three_beltTwo(test_arr)){
        cout<<"test ThreebeltTwo"<<endl;
    }else{
        cout<<"Not three belt Two"<<endl;
    }
    cout<<"complete";
    //完成
}
