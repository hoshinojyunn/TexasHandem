//
// Created by 47345 on 2021/11/13.
//

#ifndef TEXASHANDEM_JUDGE_POINT_H
#define TEXASHANDEM_JUDGE_POINT_H
#include <bits/stdc++.h>

bool judge_straight(const std::vector<std::pair<int,char>>&arr) //判顺子
{     //参数:手牌与河牌组成的牌组
    auto it=arr;
    sort(it.begin(), it.end());
    for(auto & i : it){
        i.second='#';
    }
    it.erase(unique(it.begin(),it.end()),it.end());
    for(auto i=0;i+4<it.size();++i){
        if((it[i+4].first-it[i].first)==4){
            return true;
        }else{
            continue;
        }
    }
    return false;
}
bool judge_same_flush(const std::vector<std::pair<int,char>>&arr) //判同花
{
    std::map<char,int>count;
    for(const auto & i : arr){
        count[i.second]+=1;
        if(count[i.second]==5){
            return true;
        }
    }
    return false;
}
bool judge_two();


bool Three_belt_two(const std::vector<std::pair<int,char>>&arr){

}
#endif //TEXASHANDEM_JUDGE_POINT_H
