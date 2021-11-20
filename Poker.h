//
// Created by 47345 on 2021/11/13.
//
#ifndef TEXASHANDEM_POKER_H
#define TEXASHANDEM_POKER_H
#include<iostream>
#include<cstdlib>
#include<vector>
typedef struct {
    int card_point;
    char suit;
    int number;
}Basep,*basepap;

void base(std::vector<std::pair<int,char>>&Poker);//分配底牌
void RiverCard(std::vector<std::pair<int,char>>&River_Card);
void add(std::vector<std::pair<int, char>> &River_Card);
//函数返回桌面上是否有三张或三张以上花色相同的牌
void clearPoker(std::vector<std::pair<int,char>>&playerPoker,std::vector<std::pair<int,char>>&opponentPoker,std::vector<std::pair<int,char>>&River_Card);
void clearPoker(std::vector<std::pair<int,char>>&playerPoker,std::vector<std::pair<int,char>>&opponentPoker);
#endif //TEXASHANDEM_POKER_H
