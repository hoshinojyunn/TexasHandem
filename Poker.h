//
// Created by 47345 on 2021/11/13.
//
#ifndef TEXASHANDEM_POKER_H
#define TEXASHANDEM_POKER_H
#include<iostream>
#include<cstdlib>
const int N=13;
const int M=4;
const int R=0;
const int E=1;
using namespace std;
int paper_num[N+1][M+1]={};
typedef struct {
    int card_point;
    char suit;
    int number;
}Basep,*basepap;

void base(multimap<int,char>&Poker){//分配底牌
    srand(time(nullptr));
    for(int i=0;i<2;i++){
        int num=0;               //单张纸牌大小
        num=(rand()%14);
        int NUM=(rand()%4);      //花色
        if(num){
            if(NUM==0 && paper_num[num][1]==R ){
                Poker.insert({num,'A'});
                paper_num[num][1]=E;
            }
            else if(NUM==1 && paper_num[num][2]==R ){
                Poker.insert(make_pair(num,'B'));
                paper_num [num][2]=E;
            }
            else if(NUM==2 && paper_num[num][3]==R ){
                Poker.insert({num,'C'});
                paper_num [num][3]=E;
            }
            else if(NUM==3 && paper_num[num][4]==R ){
                Poker.insert({num,'D'});
                paper_num [num][4]=E;
            }
            else i--;
        }
        else i--;
    }
}
void RiverCard(multimap<int,char>&River_Card){
    srand(time(nullptr));
    for(int i=0;i<3;i++){  //发三张
        int num=0;               //单张纸牌大小
        num=(rand()%14);
        int NUM=(rand()%4);      //花色
        if(num){
            if(NUM==0 && paper_num[num][1]==R ){
                River_Card.insert({num,'A'});
                paper_num[num][1]=E;
            }
            else if(NUM==1 && paper_num[num][2]==R ){
                River_Card.insert(make_pair(num,'B'));
                paper_num [num][2]=E;
            }
            else if(NUM==2 && paper_num[num][3]==R ){
                River_Card.insert({num,'C'});
                paper_num [num][3]=E;
            }
            else if(NUM==3 && paper_num[num][4]==R ){
                River_Card.insert({num,'D'});
                paper_num [num][4]=E;
            }
            else i--;
        }
        else i--;
    }
}
void add(multimap<int,char>&River_Card){
    srand(time(nullptr));
    for(int i=0;i<1;i++){  //加一张河牌
        int num=0;               //单张纸牌大小
        num=(rand()%14);
        int NUM=(rand()%4);      //花色
        if(num){
            if(NUM==0 && paper_num[num][1]==R ){
                River_Card.insert({num,'A'});
                paper_num[num][1]=E;
            }
            else if(NUM==1 && paper_num[num][2]==R ){
                River_Card.insert(make_pair(num,'B'));
                paper_num [num][2]=E;
            }
            else if(NUM==2 && paper_num[num][3]==R ){
                River_Card.insert({num,'C'});
                paper_num [num][3]=E;
            }
            else if(NUM==3 && paper_num[num][4]==R ){
                River_Card.insert({num,'D'});
                paper_num [num][4]=E;
            }
            else i--;
        }
        else i--;
    }
}
//函数返回桌面上是否有三张或三张以上花色相同的牌
int whea(basepap z,int n){
    int count1=0;
    int count2=0;
    int count3=0;
    int count4=0;
    for(int i=1;i<=n;i++){
        if(z[i].suit=='A' ) count1++;
        else if(z[i].suit=='B' ) count2++;
        else if(z[i].suit=='C' ) count3++;
        else if(z[i].suit=='D')  count4++;
    }
    if(count1>=3) return 1;
    else if(count2>=3) return 2;
    else if(count3>=3) return 3;
    else if(count4>=3) return 4;
    else return 0;
}
//int scord(pap h,basepap z,int &m,int n){     //n为河牌数
//    if(h[1].suit == h[2].suit && whea(z,5) ){
//        for(int )
//    }
//}
#endif //TEXASHANDEM_POKER_H
