#include <bits/stdc++.h>
#include "Poker.h"
#include "Player.h"
#include "judge.h"
using namespace std;
//// EV = (%W*$W)-(%L*$L)
bool cmp(const pair<string,int>p1,const pair<string,int>p2){
    return p1.second<p2.second;
}
void deliver(const vector<pair<int, char>> &playerRiver, vector<pair<int, char>> &Poker)
{ //  模拟分配
    int paper_num[14][5];
    memset(paper_num, 0, sizeof(paper_num));

    for (auto i = 0; i != playerRiver.size(); ++i)
    { //模拟发对手牌时 排除已经出现的牌 即自己手牌加上河牌
        if (playerRiver[i].second == 'A')
        {
            paper_num[playerRiver[i].first][1] = 1;
        }
        else if (playerRiver[i].second == 'B')
        {
            paper_num[playerRiver[i].first][2] = 1;
        }
        else if (playerRiver[i].second == 'C')
        {
            paper_num[playerRiver[i].first][3] = 1;
        }
        else if (playerRiver[i].second == 'D')
        {
            paper_num[playerRiver[i].first][4] = 1;
        }
    }
    srand(time(nullptr));
    for (int i = 0; i < 2; i++)
    {
        int num = 0; //单张纸牌大小
        num = (rand() % 14);
        int NUM = (rand() % 4); //花色
        if (num)
        {
            if (NUM == 0 && paper_num[num][1] == 0)
            {
                Poker.emplace_back(std::make_pair(num, 'A'));
                paper_num[num][1] = 1;
            }
            else if (NUM == 1 && paper_num[num][2] == 0)
            {
                Poker.emplace_back(std::make_pair(num, 'B'));
                paper_num[num][2] = 1;
            }
            else if (NUM == 2 && paper_num[num][3] == 0)
            {
                Poker.emplace_back(std::make_pair(num, 'C'));
                paper_num[num][3] = 1;
            }
            else if (NUM == 3 && paper_num[num][4] == 0)
            {
                Poker.emplace_back(std::make_pair(num, 'D'));
                paper_num[num][4] = 1;
            }
            else
                i--;
        }
        else
            i--;
    }
}
double cal_winRate(Player player, vector<pair<int, char>> River_Card)
{
    int win = 0;
    int same = 0;
    int lose = 0;
    double EV;
    auto copy = River_Card;
    auto player_River = River_Card;
    player_River.insert(player_River.cbegin(), player.Poker.cbegin(), player.Poker.cend());
    // int opponentBet=opponent.getBet();
    // int playerBet=player.getBet();
    int count = 10000;
    while (count--)
    { //10000局比赛
        vector<pair<int, char>> opponentPoker;
        deliver(player_River, opponentPoker);
        River_Card.insert(River_Card.cbegin(), opponentPoker.cbegin(), opponentPoker.cend());
        string judge = compare(player_River, River_Card);
        if (judge == "bigger")
        {
            ++win;
        }
        else if (judge == "the same")
        {
            ++same;
        }
        else
        {
            ++lose;
        }
        River_Card = copy;
    }
    double winRate = (win+(same/2)) * 1.0 / 10000;
    double loseRate = (lose+(same/2)) * 1.0 / 10000;
    //cout << "winRate is:" << winRate << " loseRate is:" << loseRate;
    // EV=(winRate*(opponent.bet+()))-(loseRate*bet);
    // return EV;
    return winRate;
}

double cal_RR(double winRate, int bet, const jackPot&pot)
{
    double pot_odds = bet*1.0 / (bet + pot.total);
    double RR = winRate*1.0 / pot_odds;
    return RR;
}
void show_bet(const Player&player,const Player&opponent){
    cout<<"now the bet: yours:"<<player.bet<<" opponent's:"<<opponent.bet<<endl;
}

void show_River(const vector<pair<int,char>>&Poker){
    for(int i=0;i!=Poker.size();++i){
            if(Poker[i].second=='A'){
                std::cout<<"diamond ";  //方块
            }else if(Poker[i].second=='B'){
                std::cout<<"club ";   //梅花
            }else if(Poker[i].second=='C'){
                std::cout<<"heart ";   //红桃
            }else if(Poker[i].second=='D'){
                std::cout<<"spade ";   //黑桃
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
        cout<<endl;
}
string machine_judge(int RR)
{
    string judge;
    srand(time(nullptr));
    if (RR < 0.8)
    {
        double jud = (rand()%100) * 1.0 / 101;
        if (jud < 0.95)
        {
            judge="fold";
        }
        else
        {
            judge="raise";
        }
    }
    else if (0.8 <= RR && RR < 1.0)
    {
        double jud = (rand()%100) * 1.0 / 101;
        if (jud < 0.8)
        {
            judge="fold";
        }
        else if (jud >= 0.8 && jud < 0.85)
        {
            judge="follow";
        }
        else
        {
            judge="raise";
        }
    }
    else if (RR >= 1.0 && RR < 1.3)
    {
        double jud = (rand()%100) * 1.0 / 101;
        if (jud > 0.6)
        {
            judge="follow";
        }
        else
        {
            judge="raise";
        }
    }
    else if (RR >= 1.3)
    {
        double jud = (rand()%100) * 1.0 / 101;
        if (jud < 0.3)
        {
            judge="follow";
        }
        else
        {
            judge="raise";
        }
    }
    return judge;
}
string machine_make_plan(const Player&opponent,const Player&player,vector<pair<int,char>>River_Card,const jackPot&pot){
    auto winRate = cal_winRate(opponent, River_Card);
    auto RR = cal_RR(winRate, player.bet - opponent.bet, pot);
    int count1=500;
    map<string,int>count;
    map<string,int>judge;
    while(count1--){
        auto machine_plan=machine_judge(RR);
        if(machine_plan=="fold"){
            ++count["fold"];
        }else if(machine_plan=="check"){
            ++count["check"];
        }else if(machine_plan=="follow"){
            ++count["follow"];
        }else if(machine_plan=="raise"){
            ++count["raise"];
        }
    }
    auto i=max_element(count.begin(),count.end(),cmp);    //做出最佳决定
    return i->first;
}

void Round1(Player &player, Player &opponent, jackPot &pot) //游戏流程设计
{ //发手牌阶段
    string flag;
    srand(time(nullptr));
    cout << "start the game?yes or no?"<<endl;
//    vector<pair<int,char>>player_River;
//    vector<pair<int,char>>opponent_River;
    cin>>flag;
Label:    while (flag=="yes")
    {
        vector<pair<int,char>>player_River;
        vector<pair<int,char>>opponent_River;
        if((rand()%100)*1.0/101>=0.5){
            player.identity="bigblind";
            opponent.identity="smallblind";
        }else{
            player.identity="smallblind";
            opponent.identity="bigblind";
        }
        //double rand1 = (rand() * 1.0) / RAND_MAX;
        base(player.Poker); //发手牌
        base(opponent.Poker);
        /*游戏开始*/
        /*第一轮 发手牌*/
        cout<<"\n\n";
        player.display();
        cout << "\n\nRound1" << endl;
        if(player.identity=="smallblind"){
            player.make_bet(pot,50);
            opponent.make_bet(pot,100);
        }else{
            player.make_bet(pot,100);
            opponent.make_bet(pot,50);
        }
        
        if (player.identity == "smallblind")
        {
            show_bet(player,opponent);
            auto plan = player.make_plan(pot, opponent);
            while (plan == "invalid")
            {
                //clearPoker(player.Poker,opponent.Poker);
                cout << "you can't make this plan.make again." << endl;
                plan=player.make_plan(pot,opponent);
            }
            if (plan == "yes")
            {
                clearPoker(player.Poker,opponent.Poker);
                continue;
            }
            else if (plan == "no")
            {
                clearPoker(player.Poker,opponent.Poker);
                break;
            }
            opponent.check();
            cout << "opponent check" << endl;
        }
        else
        {
            opponent.check();
            cout << "opponent check" << endl;
            show_bet(player,opponent);
            auto plan = player.make_plan(pot, opponent);
            while (plan == "invalid")
            {
                //clearPoker(player.Poker,opponent.Poker);
                cout << "you can't make this plan.make again." << endl;
                plan=player.make_plan(pot,opponent);
            }
            if (plan == "yes")
            {
                clearPoker(player.Poker,opponent.Poker);
                continue;
            }
            else if (plan == "no")
            {
                clearPoker(player.Poker,opponent.Poker);
                break;
            }
        }
        /*第一轮结束 第二轮开始*/
        cout << "\n\nRound2" << endl;
        vector<pair<int, char>> River_Card{};
        RiverCard(River_Card); //发河牌
        show_River(River_Card);
        if (player.identity == "bigblind")
        { //玩家是大盲 则先做决定
            show_bet(player,opponent);
            auto plan = player.make_plan(pot, opponent);
            while (plan == "invalid")
            {
                //clearPoker(player.Poker,opponent.Poker);
                cout << "you can't make this plan.make again." << endl;
                plan=player.make_plan(pot,opponent);
            }
            if (plan == "yes")
            {
                clearPoker(player.Poker,opponent.Poker,River_Card);
                continue;
            }
            else if (plan == "no")
            {
                clearPoker(player.Poker,opponent.Poker,River_Card);
                break;
            }
            /*玩家決定結束*/
            if (opponent.bet < player.bet)
            {
                auto machine_plan=machine_make_plan(opponent,player,River_Card,pot);
                if(machine_plan=="fold"){
                    opponent.fold(pot,player);
                    cout<<"opponent fold"<<endl;
                    clearPoker(player.Poker,opponent.Poker,River_Card);
                    cout<<"game over.continue?yes or no?";
                    cin>>flag;
                    if(flag=="yes"){
                        continue;
                    }else{
                        break;
                    }
                }else if(machine_plan=="follow"&&opponent.bonus>=player.bet-opponent.bet){
                    opponent.follow(pot,player);
                    cout<<"opponent follow"<<endl;
                }else if(machine_plan=="raise"&&opponent.bonus>=player.bet){
                    opponent.raise(pot,player);
                    cout<<"opponent raise"<<endl;
                }else if(machine_plan=="check"){
                    opponent.check();
                    cout<<"opponent check"<<endl;
                }else{
                    opponent.allin(pot);
                    cout<<"opponent all in"<<endl;
                }
                // if(machine_plan=="invalid"){  //表示已經跟不起也加不起了 那麽就及時止損 fold
                //     opponent.check();
                // }
            }
            else
            { //如果自己赌金比对方大则直接check 没必要加赌注
                opponent.check();
                cout << "opponent check" << endl;
            }
        }
        else
        { //玩家是小盲
           if (opponent.bet < player.bet)
            {
                auto machine_plan=machine_make_plan(opponent,player,River_Card,pot);
                if(machine_plan=="fold"){
                    opponent.fold(pot,player);
                    cout<<"opponent fold"<<endl;
                    clearPoker(player.Poker,opponent.Poker,River_Card);
                    cout<<"game over.continue?yes or no?";
                    cin>>flag;
                    if(flag=="yes"){
                        continue;
                    }else{
                        break;
                    }
                }else if(machine_plan=="follow"&&opponent.bonus>=player.bet-opponent.bet){
                    opponent.follow(pot,player);
                    cout<<"opponent follow"<<endl;
                }else if(machine_plan=="raise"&&opponent.bonus>=player.bet){
                    opponent.raise(pot,player);
                    cout<<"opponent raise"<<endl;
                }else if(machine_plan=="check"){
                    opponent.check();
                    cout<<"opponent check"<<endl;
                }else{
                    opponent.allin(pot);
                    cout<<"opponent all in"<<endl;
                }
                // if(machine_plan=="invalid"){  //表示已經跟不起也加不起了 那麽就及時止損 fold
                //     opponent.check();
                // }
            }
            else
            { //如果自己赌金比对方大则直接check 没必要加赌注
                opponent.check();
                cout << "opponent check" << endl;
            }
            /*玩家后做决定*/
            show_bet(player,opponent);
            auto plan = player.make_plan(pot, opponent);
            while (plan == "invalid")
            {
                //clearPoker(player.Poker,opponent.Poker);
                cout << "you can't make this plan.make again." << endl;
                plan=player.make_plan(pot,opponent);
            }
            if (plan == "yes")
            {
                clearPoker(player.Poker,opponent.Poker,River_Card);
                continue;
            }
            else if (plan == "no")
            {
                clearPoker(player.Poker,opponent.Poker,River_Card);
                break;
            }



        }
        /*第二轮结束 第三轮开始*/
        cout<<"\n\nRound3"<<endl;
        add(River_Card);
        show_River(River_Card);
        if(player.identity=="bigblind"){  //玩家是大盲
            show_bet(player,opponent);
            auto plan = player.make_plan(pot, opponent);
            while (plan == "invalid")
            {
                //clearPoker(player.Poker,opponent.Poker);
                cout << "you can't make this plan.make again." << endl;
                plan=player.make_plan(pot,opponent);
            }
            if (plan == "yes")
            {
                clearPoker(player.Poker,opponent.Poker,River_Card);
                continue;
            }
            else if (plan == "no")
            {
                clearPoker(player.Poker,opponent.Poker,River_Card);
                break;
            }
            if (opponent.bet < player.bet)
            {
                auto machine_plan=machine_make_plan(opponent,player,River_Card,pot);
                if(machine_plan=="fold"){
                    opponent.fold(pot,player);
                    cout<<"opponent fold"<<endl;
                    clearPoker(player.Poker,opponent.Poker,River_Card);
                    cout<<"game over.continue?yes or no?";
                    cin>>flag;
                    if(flag=="yes"){
                        continue;
                    }else{
                        break;
                    }
                }else if(machine_plan=="follow"&&opponent.bonus>=player.bet-opponent.bet){
                    opponent.follow(pot,player);
                    cout<<"opponent follow"<<endl;
                }else if(machine_plan=="raise"&&opponent.bonus>=player.bet){
                    opponent.raise(pot,player);
                    cout<<"opponent raise"<<endl;
                }else if(machine_plan=="check"){
                    opponent.check();
                    cout<<"opponent check"<<endl;
                }else{
                    opponent.allin(pot);
                    cout<<"opponent all in"<<endl;
                }
                // if(machine_plan=="invalid"){  //表示已經跟不起也加不起了 那麽就及時止損 fold
                //     opponent.check();
                // }
            }
            else
            { //如果自己赌金比对方大则直接check 没必要加赌注
                opponent.check();
                cout << "opponent check" << endl;
            }
        }else{
            //玩家是小盲
            if (opponent.bet < player.bet)
            {
                auto machine_plan=machine_make_plan(opponent,player,River_Card,pot);
                if(machine_plan=="fold"){
                    opponent.fold(pot,player);
                    cout<<"opponent fold"<<endl;
                    clearPoker(player.Poker,opponent.Poker,River_Card);
                    cout<<"game over.continue?yes or no?";
                    cin>>flag;
                    if(flag=="yes"){
                        continue;
                    }else{
                        break;
                    }
                }else if(machine_plan=="follow"&&opponent.bonus>=player.bet-opponent.bet){
                    opponent.follow(pot,player);
                    cout<<"opponent follow"<<endl;
                }else if(machine_plan=="raise"&&opponent.bonus>=player.bet){
                    opponent.raise(pot,player);
                    cout<<"opponent raise"<<endl;
                }else if(machine_plan=="check"){
                    opponent.check();
                    cout<<"opponent check"<<endl;
                }else{
                    opponent.allin(pot);
                    cout<<"opponent all in"<<endl;
                }
                // if(machine_plan=="invalid"){  //表示已經跟不起也加不起了 那麽就及時止損 fold
                //     opponent.check();
                // }
            }
            else
            { //如果自己赌金比对方大则直接check 没必要加赌注
                opponent.check();
                cout << "opponent check" << endl;
            }
            /*玩家后做决定*/
            show_bet(player,opponent);
            auto plan = player.make_plan(pot, opponent);
            while (plan == "invalid")
            {
                //clearPoker(player.Poker,opponent.Poker);
                cout << "you can't make this plan.make again." << endl;
                plan=player.make_plan(pot,opponent);
            }
            if (plan == "yes")
            {
                clearPoker(player.Poker,opponent.Poker,River_Card);
                continue;
            }
            else if (plan == "no")
            {
                clearPoker(player.Poker,opponent.Poker,River_Card);
                break;
            }
        }
        /*第三轮结束 最后一轮开始*/
        cout<<"\n\nRound final"<<endl;
        add(River_Card);
        show_River(River_Card);
        player_River.insert(player_River.begin(),player.Poker.begin(),player.Poker.end());
        player_River.insert(player_River.begin(),River_Card.begin(),River_Card.end());
        /*玩家牌河构造完成*/
        opponent_River.insert(opponent_River.begin(),opponent.Poker.begin(),opponent.Poker.end());
        opponent_River.insert(opponent_River.begin(),River_Card.begin(),River_Card.end());
        /*电脑牌河构造完成*/
        //Player pri_plan_player;  //记录上一个做出行动的人
        if(player.identity=="bigblind"){  //玩家是大盲
            show_bet(player,opponent);
            auto plan = player.make_plan(pot, opponent);
            //pri_plan_player=player;  //记录
            while (plan == "invalid")
            {
                //clearPoker(player.Poker,opponent.Poker);
                cout << "you can't make this plan.make again." << endl;
                plan=player.make_plan(pot,opponent);
            }
            if (plan == "yes")
            {
                clearPoker(player.Poker,opponent.Poker,River_Card);
                continue;
            }
            else if (plan == "no")
            {
                clearPoker(player.Poker,opponent.Poker,River_Card);
                break;
            }
            if (opponent.bet < player.bet)
            {
                auto machine_plan=machine_make_plan(opponent,player,River_Card,pot);
                if(machine_plan=="fold"){
                    opponent.fold(pot,player);
                    cout<<"opponent fold"<<endl;
                    clearPoker(player.Poker,opponent.Poker,River_Card);
                    cout<<"game over.continue?yes or no?";
                    cin>>flag;
                    if(flag=="yes"){
                        continue;
                    }else{
                        break;
                    }
                }else if(machine_plan=="follow"&&opponent.bonus>=player.bet-opponent.bet){
                    opponent.follow(pot,player);
                    cout<<"opponent follow"<<endl;
                }else if(machine_plan=="raise"&&opponent.bonus>=player.bet){
                    opponent.raise(pot,player);
                    cout<<"opponent raise"<<endl;
                }else if(machine_plan=="check"){
                    opponent.check();
                    cout<<"opponent check"<<endl;
                }else{
                    opponent.allin(pot);
                    cout<<"opponent all in"<<endl;
                }
                // if(machine_plan=="invalid"){  //表示已經跟不起也加不起了 那麽就及時止損 fold
                //     opponent.check();
                // }
            }
            else
            { //如果自己赌金比对方大则直接check 没必要加赌注
                opponent.check();
                cout << "opponent check" << endl;
            }
            if(player.bet==opponent.bet){
                string your_judge;
                cout<<"Would you wanna raise again?yes or no?";
                cin>>your_judge;
                if(your_judge=="yes"&&player.bonus>opponent.bet){
                    player.raise(pot,opponent);
                }else{
                    //cout<<"you can't do that.arrange check"<<endl;
                    player.check();
                }
            }
            while(player.bet!=opponent.bet){  //最后一轮必须判断二者赌注是否相等 不相等必须做出行动
                if(player.bonus==0&&player.bet<opponent.bet){  //做无筹码情况判断
                    pot.total-=opponent.bet-player.bet;
                    opponent.bonus+=opponent.bet-player.bet;
                    opponent.bet=player.bet;
                }else if(opponent.bonus==0&&opponent.bet<player.bet){
                    pot.total-=player.bet-opponent.bet;
                    player.bonus+=player.bet-opponent.bet;
                    player.bet=opponent.bet;
                }
                show_bet(player,opponent);
                if(player.bet<opponent.bet){
                    cout<<"your bet is less than opponent.fold,raise or follow?";
                    auto plan=player.make_plan(pot,opponent);
                    while(plan=="invalid"){
                        cout<<"you can't make this plan.make again."<<endl;
                        plan=player.make_plan(pot,opponent);
                    }
                    if(plan=="yes"){
                        clearPoker(player.Poker,opponent.Poker,River_Card);
                        goto Label;
                    }else if(plan=="no"){
                        exit(0);
                    }
                }else if(player.bet>opponent.bet){  //机器做决定
                   auto machine_plan=machine_make_plan(opponent,player,River_Card,pot);
                   if(machine_plan=="fold"){
                    opponent.fold(pot,player);
                    clearPoker(player.Poker,opponent.Poker,River_Card);
                    cout<<"opponent fold"<<endl;
                    cout<<"game over.continue?yes or no?";
                    cin>>flag;
                    if(flag=="yes"){
                        goto Label;
                    }else{
                        exit(0);
                    }
                }else if(machine_plan=="follow"&&opponent.bonus>=player.bet-opponent.bet){
                    opponent.follow(pot,player);
                    cout<<"opponent follow"<<endl;
                }else if(machine_plan=="raise"&&opponent.bonus>=player.bet){
                    opponent.raise(pot,player);
                    cout<<"opponent raise"<<endl;
                }else{
                    cout<<"opponent all in."<<endl;
                    opponent.allin(pot);
                    }
                }
                if(player.bet==opponent.bet&&(player.bonus!=0&&opponent.bonus!=0)){
                string you_raise;
                show_bet(player,opponent);
                cout<<"Would you wanna raise again?yes or no?";
                cin>>you_raise;
                if(you_raise=="yes"&&player.bonus>=opponent.bet){
                    player.raise(pot,opponent);
                }else if(you_raise=="yes"&&player.bonus<opponent.bet){
                    cout<<"you can't raise.arrange all in"<<endl;
                    player.allin(pot);
                }else{
                    player.check();
                }
                }
            }//while over      compare start
            cout<<"start to compare!"<<endl;
            cout<<"yours Poker:";
            show_River(player.Poker);
            cout<<"opponent's Poker:";
            show_River(opponent.Poker);
            string result=compare(player_River,opponent_River);  //确定后 开始开牌比较
            if(result=="bigger"){
                cout<<"you win!"<<endl;
                opponent.fold(pot,player);  //玩家赢效果相当于对方弃牌
                clearPoker(player.Poker,opponent.Poker,River_Card);
            }else if(result=="smaller"){
                cout<<"you lose..."<<endl;
                player.fold(pot,opponent);
                clearPoker(player.Poker,opponent.Poker,River_Card);
            }else{
                cout<<"the same point with opponent."<<endl;
                player.bonus+=pot.total/2;
                opponent.bonus+=pot.total/2;
                player.bet=0;
                opponent.bet=0;
                pot.total=0;
                clearPoker(player.Poker,opponent.Poker,River_Card);
            }


        }else{  //玩家为小盲
            if (opponent.bet < player.bet)
            {
                auto machine_plan=machine_make_plan(opponent,player,River_Card,pot);
                if(machine_plan=="fold"){
                    opponent.fold(pot,player);
                    clearPoker(player.Poker,opponent.Poker,River_Card);
                    cout<<"opponent fold"<<endl;
                    cout<<"game over.continue?yes or no?";
                    cin>>flag;
                    if(flag=="yes"){
                        continue;
                    }else{
                        break;
                    }
                }else if(machine_plan=="follow"&&opponent.bonus>=player.bet-opponent.bet){
                    opponent.follow(pot,player);
                    cout<<"opponent follow"<<endl;
                }else if(machine_plan=="raise"&&opponent.bonus>=player.bet){
                    opponent.raise(pot,player);
                    cout<<"opponent raise"<<endl;
                }else if(machine_plan=="check"){
                    opponent.check();
                    cout<<"opponent check"<<endl;
                }else{
                    opponent.allin(pot);
                    cout<<"opponent all in"<<endl;
                }
            }
            else
            { //如果自己赌金比对方大则直接check 没必要加赌注
                opponent.check();
                cout << "opponent check" << endl;
            }
            /*玩家后做决定*/
            show_bet(player,opponent);
            auto plan = player.make_plan(pot, opponent);
            //pri_plan_player=player;  //记录
            while (plan == "invalid")
            {
                //clearPoker(player.Poker,opponent.Poker,River_Card);
                cout << "you can't make this plan.make again." << endl;
                plan=player.make_plan(pot,opponent);
            }
            if (plan == "yes")
            {
                clearPoker(player.Poker,opponent.Poker,River_Card);
                continue;
            }
            else if (plan == "no")
            {
                clearPoker(player.Poker,opponent.Poker,River_Card);
                break;
            }
            if(player.bet==opponent.bet){
                string your_judge;
                cout<<"Would you wanna raise again?yes or no?";
                cin>>your_judge;
                if(your_judge=="yes"&&player.bonus>opponent.bet){
                    player.raise(pot,opponent);
                }else{
                    cout<<"you can't do that.arrange check"<<endl;
                    player.check();
                }
            }
            while(player.bet!=opponent.bet){  //最后一轮必须判断二者赌注是否相等 不相等必须做出行动
                if(player.bonus==0&&player.bet<opponent.bet){  //做无筹码情况判断
                    pot.total-=opponent.bet-player.bet;
                    opponent.bonus+=opponent.bet-player.bet;
                    opponent.bet=player.bet;
                }else if(opponent.bonus==0&&opponent.bet<player.bet){
                    pot.total-=player.bet-opponent.bet;
                    player.bonus+=player.bet-opponent.bet;
                    player.bet=opponent.bet;
                }
                show_bet(player,opponent);
                if(player.bet<opponent.bet){
                    cout<<"your bet is less than opponent.fold,raise or follow?";
                    auto plan=player.make_plan(pot,opponent);
                    while(plan=="invalid"){
                        cout<<"you can't make this plan.make again."<<endl;
                        plan=player.make_plan(pot,opponent);
                    }
                    if(plan=="yes"){
                        clearPoker(player.Poker,opponent.Poker,River_Card);
                        goto Label;
                    }else if(plan=="no"){
                        exit(0);
                    }
                }else if(player.bet>opponent.bet){  //机器做决定
                   auto machine_plan=machine_make_plan(opponent,player,River_Card,pot);
                   if(machine_plan=="fold"){
                    opponent.fold(pot,player);
                    clearPoker(player.Poker,opponent.Poker,River_Card);
                    cout<<"opponent fold"<<endl;
                    cout<<"game over.continue?yes or no?";
                    cin>>flag;
                    if(flag=="yes"){
                        goto Label;
                    }else{
                        exit(0);
                    }
                }else if(machine_plan=="follow"&&opponent.bonus>=player.bet-opponent.bet){
                    opponent.follow(pot,player);
                    cout<<"opponent follow"<<endl;
                }else if(machine_plan=="raise"&&opponent.bonus>=player.bet){
                    opponent.raise(pot,player);
                    cout<<"opponent raise"<<endl;
                }else{
                    cout<<"opponent all in."<<endl;
                    opponent.allin(pot);
                    }
                }
                if(player.bet==opponent.bet&&(player.bonus!=0&&opponent.bonus!=0)){
                string you_raise;
                show_bet(player,opponent);
                cout<<"Would you wanna raise again?yes or no?";
                cin>>you_raise;
                if(you_raise=="yes"&&player.bonus>=opponent.bet){
                    player.raise(pot,opponent);
                }else if(you_raise=="yes"&&player.bonus<opponent.bet){
                    cout<<"you can't raise.arrange all in"<<endl;
                    player.allin(pot);
                }else{
                    player.check();
                }
                }
            }//while over
            cout<<"start to compare!"<<endl;
            cout<<"yours Poker:";
            show_River(player.Poker);
            cout<<"opponent's Poker:";
            show_River(opponent.Poker);
            string result=compare(player_River,opponent_River);  //确定后 开始开牌比较
            if(result=="bigger"){
                cout<<"you win!"<<endl;
                opponent.fold(pot,player);  //玩家赢效果相当于对方弃牌
                clearPoker(player.Poker,opponent.Poker,River_Card);
            }else if(result=="smaller"){
                cout<<"you lose..."<<endl;
                player.fold(pot,opponent);
                clearPoker(player.Poker,opponent.Poker,River_Card);
            }else{
                cout<<"the same point with opponent."<<endl;
                player.bonus+=pot.total/2;
                opponent.bonus+=pot.total/2;
                player.bet=0;
                opponent.bet=0;
                pot.total=0;
                clearPoker(player.Poker,opponent.Poker,River_Card);
            }
        }

        cout << "continue?yes or no?";
        cin >> flag;
    }
}
int main()
{
    srand(time(nullptr));
    double rand1 = (rand()%100) * 1.0 / 101;
    Player opponent;
    Player player;
    jackPot pot;
    Round1(player,opponent,pot);
    //cout<<cal_winRate(player,River_Card);
    // vector<pair<int, char>> test1_arr{{5, 'D'}, {7, 'A'}, {12, 'B'}, {2, 'C'}, {11, 'A'}, {3, 'C'}, {8, 'D'}};
    // vector<pair<int, char>> test2_arr{{4, 'D'}, {12, 'D'}, {12, 'B'}, {2, 'C'}, {11, 'A'}, {3, 'C'}, {8, 'D'}};
    // show_River(test1_arr);
    // show_River(test2_arr);
    // cout << compare(test1_arr, test2_arr);
    cout << "complete";
    //完成
}
