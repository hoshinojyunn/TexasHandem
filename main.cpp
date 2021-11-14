#include <bits/stdc++.h>
#include "Poker.h"
#include "Player.h"
using namespace std;
//// EV = (%W*$W)-(%L*$L)
void Round1(Player&player,Player&opponent,jackPot&pot){  //发手牌阶段
        string judge;
        double rand1=(rand()*1.0)/RAND_MAX;
        base(player.Poker);  //发手牌
        base(opponent.Poker);
        player.display();
        /*游戏开始*/
        /*第一轮 发手牌*/
        if(player.identity=="smallblind"){
            player.make_bet(pot,50);
            cout<<"请做出你的判断,fold,follow,check or raise?";
            cin>>judge;
            if(judge=="fold"){
                cout<<"game over"<<endl;
                //exit(0);
            }else if(judge=="check"){
                player.check();
            }else if(judge=="raise"){
                player.raise(pot,opponent);
            }else if(judge=="follow"){
                player.follow(pot,opponent);
            }
            opponent.make_bet(pot,100);
            opponent.check();
            
        }else{
            opponent.make_bet(pot,50);
            opponent.check();
            player.make_bet(pot,100);
            cout<<"请做出你的判断,fold,follow,check or raise?";
            cin>>judge;
            if(judge=="fold"){
                cout<<"game over"<<endl;
            }else if(judge=="check"){
                player.check();
            }else if(judge=="raise"){
                player.raise(pot,opponent);
            }else if(judge=="follow"&&player.bet<opponent.bet){
                player.follow(pot,opponent);
            }else{
                cout<<"无法做出次行动";
            }
        }
}


// double cal_winRate(Player player,vector<pair<int,char>>River_Card){
//     int win=0;
//     int same=0;
//     int lose=0;
//     double EV;
//     auto copy=River_Card;
//     auto player_River=River_Card;
//     player_River.insert(player_River.cbegin(),player.Poker.cbegin(),player.Poker.cend());
//     // int opponentBet=opponent.getBet();
//     // int playerBet=player.getBet();
//     Player opponent;
//     for(int i=0;i!=10000;++i){  //10000局比赛
//         base(opponent.Poker);
//         River_Card.insert(River_Card.cbegin(),opponent.Poker.cbegin(),opponent.Poker.cend());
//         string judge=compare(player_River,River_Card);
//         if(judge=="bigger"){
//             ++win;
//         }else if(judge=="the same"){
//             ++same;
//         }else{
//             ++lose;
//         }
//         River_Card=copy;
//     }
//     double winRate=win*1.0/10000;
//     double loseRate=lose*1.0/10000;
//     cout<<"胜率是:"<<winRate<<" 输率是:"<<loseRate;
//     // EV=(winRate*(opponent.bet))-(loseRate*bet);
//     // return EV;
//     return winRate;
// }

double cal_RR(double winRate,int bet,jackPot pot){
    double pot_odds=bet/bet+pot.total;
    double RR=winRate/pot_odds;
    return RR;
}
int main(){
    Player opponent(20000);
    Player player(20000);
    jackPot pot;
    opponent.bet=500;
    vector<pair<int,char>>River_Card{};
    RiverCard(River_Card);
    add(River_Card, 0);
    add(River_Card, 0);
    string flag;
    string judge;
    vector<pair<int,char>>Player_arr{};
    vector<pair<int,char>>opponent_arr;
    //cout<<cal_winRate(player,River_Card);
    vector<pair<int,char>>test1_arr{{3,'B'},{4,'B'},{13,'B'},{5,'B'},{11,'B'},{7,'B'},{6,'B'}};
    vector<pair<int,char>>test2_arr{{4,'A'},{3,'A'},{9,'A'},{7,'A'},{5,'A'},{12,'B'},{6,'A'}};
    cout<<same_judge_straight_wh(test1_arr,test2_arr);
    /*构造玩家牌种序列*/
    // Player_arr.insert(Player_arr.cbegin(),River_Card.begin(),River_Card.end());
    // Player_arr.insert(Player_arr.cbegin(),player.Poker.begin(),player.Poker.end());
    // /*构造对手牌种序列*/
    // opponent_arr.insert(opponent_arr.cbegin(),River_Card.begin(),River_Card.end());
    // opponent_arr.insert(opponent_arr.cbegin(),opponent.Poker.begin(),opponent.Poker.end());
    // srand(time(nullptr));
    // cout<<"start the game?yes or no?";
    // cin>>flag;
    // // while(flag=="yes"){
    // //     double rand1=(rand()*1.0)/RAND_MAX;
    // //     Player opponent(rand1,20000);
    // //     Player player(1-rand1,20000);
    // //     base(player.Poker);  //发手牌
    // //     base(opponent.Poker);
    // //     player.display();
    // //     /*游戏开始*/
    // //     /*第一轮 发手牌*/
    // //     if(player.identity=="smallblind"){
    // //         player.make_bet(pot,50);
    // //         cout<<"请做出你的判断,fold,follow,check or raise?";
    // //         cin>>judge;
    // //         if(judge=="fold"){
    // //             cout<<"game over"<<endl;
    // //             cout<<"continue?yes or no?";
    // //             cin>>flag;
    // //             continue;
    // //         }else if(judge=="check"){
    // //             player.check();
    // //         }else if(judge=="raise"){
    // //             player.raise(pot,opponent);
    // //         }else if(judge=="follow"){
    // //             player.follow(pot,opponent);
    // //         }
    // //         opponent.make_bet(pot,100);
    // //         opponent.check();
            
    // //     }else{
    // //         opponent.make_bet(pot,50);
    // //         opponent.check();
    // //         player.make_bet(pot,100);
    // //         cout<<"请做出你的判断,fold,follow,check or raise?";
    // //         cin>>judge;
    // //         if(judge=="fold"){
    // //             cout<<"game over"<<endl;
    // //             cout<<"continue?yes or no?";
    // //             cin>>flag;
    // //             continue;
    // //         }else if(judge=="check"){
    // //             player.check();
    // //         }else if(judge=="raise"){
    // //             player.raise(pot,opponent);
    // //         }else if(judge=="follow"&&player.bet<opponent.bet){
    // //             player.follow(pot,opponent);
    // //         }else{
    // //             cout<<"无法做出次行动";
    // //         }
    // //     }
    // //     /*第一轮结束 第二轮开始*/
        
    // //     vector<pair<int,char>>River_Card{};
    // //     RiverCard(River_Card);  //发河牌
    // //     if(player.identity=="bigblind"){
    // //         cout<<"请做出你的判断,fold,follow,check or raise?";
    // //         cin>>judge;
    // //         if(judge=="fold"){
    // //             cout<<"game over"<<endl;
    // //             cout<<"continue?yes or no?";
    // //             cin>>flag;
    // //             continue;
    // //         }else if(judge=="check"){
    // //             player.check();
    // //         }else if(judge=="raise"){       
    // //             player.raise(pot,opponent);
    // //         }else if(judge=="follow"&&player.bet<opponent.bet){  //赌金少过对面才能跟
    // //             player.follow(pot,opponent);
    // //         }
    // //         auto winRate=cal_winRate(opponent,River_Card);
    // //         auto RR=cal_RR(winRate,)

    // //     }






    //     cout<<"continue?yes or no?";
    //     cin>>flag;
    // }
    cout<<"complete";
    //完成
}
