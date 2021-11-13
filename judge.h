//
// Created by 47345 on 2021/11/13.
//

#ifndef TEXASHANDEM_JUDGE_H
#define TEXASHANDEM_JUDGE_H
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
bool judge_pair(const std::vector<std::pair<int,char>>&arr){  //判对子
    std::map<int,int>count;  //第一个int表示牌点 第二个int表示出现的次数
    for(int i=0;i!=arr.size();++i){
        ++count[arr[i].first];
        if(count[arr[i].first]==2){
            return true;
        }
    }
    return false;
}
bool judge_Three(const std::vector<std::pair<int,char>>&arr){
    std::map<int,int>count;  //第一个int表示牌点 第二个int表示出现的次数
    for(int i=0;i!=arr.size();++i){
        ++count[arr[i].first];
        if(count[arr[i].first]==3){
            return true;
        }
    }
    return false;
} 
bool judge_twopair(const std::vector<std::pair<int,char>>&arr){ //判两对
    std::map<int,int>count;  //第一个int表示牌点 第二个int表示出现的次数
    int count1=0;   //记录对子个数
    for(int i=0;i!=arr.size();++i){
        ++count[arr[i].first];
        if(count[arr[i].first]==2){
            ++count1;
        }
    }
    if(count1>=2){
        return true;
    }else{
        return false;
    }
} 
bool judge_straight_wh(const std::vector<std::pair<int,char>>&arr) //判同花顺 
{     //参数:手牌与河牌组成的牌组
    auto it=arr;
    int count1=0,count2=0,count3=0,count4=0;
    int count=0;
    int mll[5][8]={0};
    for(int i=0;i<it.size();i++){
     if(it[i].second=='A') {
      count1++;
      mll[1][count1]=it[i].first;
      if(count1>=5) {
   count=1;  
   }
  }
  else if(it[i].second=='B') {
      count2++;
      mll[2][count1]=it[i].first;
      if(count2>=5) {
   count=2;  
   } 
  }
  else if(it[i].second=='C') {
   count3++;
   mll[3][count1]=it[i].first;
      if(count3>=5) {
   count=3;  
   }
  }
  else if(it[i].second=='D') {
   count4++;
   mll[4][count1]=it[i].first;
      if(count4>=5) {
   count=4;  
   }
  } 
 }
 if(count==0) return false;
    
 for(int i=1;i<=6;i++){
  for(int j=1;j<=7-i;j++)
  if(mll[count][j]>mll[count][j+1]){
   int mol=mll[count][j];
   mll[count][j]=mll[count][j+1];
   mll[count][j+1]=mol;
  }
 }
 for(int i=1;i+4<=7;++i){
        if((mll[count][i+4]-mll[count][i])==4&&mll[count][i]!=0){
            return true;
        }else{
            continue;
        }
    }
    return false;
}
bool judge_straight_w(const std::vector<std::pair<int,char>>&arr) //判皇家同花顺 
{     //参数:手牌与河牌组成的牌组
    auto it=arr;
    int count1=0,count2=0,count3=0,count4=0;
    int count=0;
    int mll[5][8]={0};
    for(int i=0;i<it.size();i++){
     if(it[i].second=='A') {
      count1++;
      mll[1][count1]=it[i].first;
      if(count1>=5) {
   count=1;  
   }
  }
  else if(it[i].second=='B') {
      count2++;
      mll[2][count1]=it[i].first;
      if(count2>=5) {
   count=2;  
   } 
  }
  else if(it[i].second=='C') {
   count3++;
   mll[3][count1]=it[i].first;
      if(count3>=5) {
   count=3;  
   }
  }
  else if(it[i].second=='D') {
   count4++;
   mll[4][count1]=it[i].first;
      if(count4>=5) {
   count=4;  
   }
  } 
 }
 if(count==0) return false;
    
 for(int i=1;i<=6;i++){
  for(int j=1;j<=7-i;j++)
  if(mll[count][j]>mll[count][j+1]){
   int mol=mll[count][j];
   mll[count][j]=mll[count][j+1];
   mll[count][j+1]=mol;
  }
 }
 for(int i=1;i+4<=7;++i){
        if((mll[count][i+4]-mll[count][i])==4&&mll[count][i]!=0&&mll[count][i+4]==13){
            return true;
        }else{
            continue;
        }
    }
    return false;
}
bool judge_Four(const std::vector<std::pair<int,char>>&arr){
    std::map<int,int>count;  //第一个int表示牌点 第二个int表示出现的次数
    for(int i=0;i!=arr.size();++i){
        ++count[arr[i].first];
        if(count[arr[i].first]==4){
            return true;
        }
    }
    return false;
}
bool judge_Three_beltTwo(const std::vector<std::pair<int,char>>&arr){
    std::map<int,int>count;  //第一个int表示牌点 第二个int表示出现的次数
    int count3=0;
    int count2=0;
    for(int i=0;i!=arr.size();++i){
        ++count[arr[i].first];
    }
    for(auto it=count.begin();it!=count.end();++it){
        if(count[it->first]==3){
            ++count3;
        }
    }
    if(count3==2){
        return true;
    }else{
        for(auto it=count.begin();it!=count.end();++it){
        if(count[it->first]==2){
            ++count2;
            } 
        }
    }
    if(count3==1&&count2>=1){
        return true;
    }else{
        return false;
    }
}
#endif //TEXASHANDEM_JUDGE_H
