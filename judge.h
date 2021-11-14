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
        ++count[i.first];
        if(count[i.first]==5){
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
bool judge_Three(const std::vector<std::pair<int,char>>&arr){  //判三张
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
    int count2=0;   //记录对子个数
    for(int i=0;i!=arr.size();++i){
        ++count[arr[i].first];
    }
    for(auto it=count.begin();it!=count.end();++it){
        if(count[it->first]>=pow(2,1)&&count[it->first]<pow(2,2)){
            count2+=1;
        }else if(count[it->first]==pow(2,2)){
            count2+=2;
        }
    }
    if(count2>=2){
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
bool judge_straight_royal(const std::vector<std::pair<int,char>>&arr) //判皇家同花顺 
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
bool judge_Four(const std::vector<std::pair<int,char>>&arr){  //判四张
    std::map<int,int>count;  //第一个int表示牌点 第二个int表示出现的次数
    for(int i=0;i!=arr.size();++i){
        ++count[arr[i].first];
        if(count[arr[i].first]==4){
            return true;
        }
    }
    return false;
}
bool judge_Three_beltTwo(const std::vector<std::pair<int,char>>&arr){  //判三带二
    std::map<int,int>count;  //第一个int表示牌点 第二个int表示出现的次数
    int count3=0;
    int count2=0;
    for(int i=0;i!=arr.size();++i){
        ++count[arr[i].first];
    }
    for(auto it=count.begin();it!=count.end();++it){
        if(count[it->first]==3||count[it->first]==4){
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
bool judge_single(const std::vector<std::pair<int,char>>&arr) //判gao
{     //参数:手牌与河牌组成的牌组
    auto it=arr;
    auto hi=arr;
    sort(it.begin(), it.end());
    for(auto & i : it){
        i.second='#';
    }
    it.erase(unique(it.begin(),it.end()),it.end());
    for(auto i=0;i+4<it.size();++i){
        if((it[i+4].first-it[i].first)==4){
            return false;
        }else{
            continue;
        }
    }
    int count1=0,count2=0,count3=0,count4=0;
    int count=0;
    for(int i=0;i<it.size();i++){
     if(hi[i].second=='A') {
      count1++;
      if(count1>=5) {
   count=1;  
   }
  }
  else if(hi[i].second=='B') {
      count2++;
      if(count2>=5) {
   count=2;  
   } 
  }
  else if(hi[i].second=='C') {
   count3++;
      if(count3>=5) {
   count=3;  
   }
  }
  else if(hi[i].second=='D') {
   count4++;
      if(count4>=5) {
   count=4;  
   }
  } 
 }
 if(count!=0) return false;
 for(int i=0;i<hi.size();i++){
  for(int j=i+1;j<hi.size();j++){
  if(hi[i].first==hi[j].first)
  return false;   
  }
 }
    return true;
}
std::string same_judge_ThreeBeltTwo(const std::vector<std::pair<int,char>>&yourPoker,const std::vector<std::pair<int,char>>&opponentPoker){
    std::map<int,int>your_count;
    std::map<int,int>opponent_count;
    int yourThree=0,opponentThree=0;  //记录自身与对手三条的牌点
    for(const auto&i:yourPoker){
        ++your_count[i.first];
        if(your_count[i.first]>=3&&i.first>yourThree){
            yourThree=i.first;      //若一种牌超过三张 且大于之前记录的三条点数 更新
        }
    }
    for(const auto&i:opponentPoker){
        ++opponent_count[i.first];
        if(opponent_count[i.first]>=3&&i.first>opponentThree){
            opponentThree=i.first;
        }
    }
    if(yourThree>opponentThree){
        return "bigger";
    }else if(yourThree<opponentThree){
        return "smaller";
    }else{
        return "the same";
    }
}
std::string same_judge_sameFlush(const std::vector<std::pair<int,char>>&yourPoker,const std::vector<std::pair<int,char>>&opponentPoker){
    std::map<char,int>your_count;
    std::map<char,int>opponent_count;
    char your_Decor,opponent_Decor;  //记录同花的花色
    int your_point=0,opponent_point=0;  //记录同花牌中的最大点数
    for(const auto & i : yourPoker){
        ++your_count[i.second];
        if(your_count[i.second]>=5){
            your_Decor=i.second;
        }
    }
    for(const auto&i:opponentPoker){
        ++opponent_count[i.second];
        if(opponent_count[i.second]>=5){
            opponent_Decor=i.second;
        }
    }
    if(your_Decor>opponent_Decor){
        return "bigger";
    }else if(your_Decor<opponent_Decor){
        return "smaller";
    }else{    //若花色相同 比较最大牌的点数
        for(const auto&i:yourPoker){
            if(i.second==your_Decor&&i.first>your_point){
                your_point=i.first;
            }
        }
        for(const auto&i:opponentPoker){
            if(i.second==opponent_Decor&&i.first>opponent_point){
                opponent_point=i.first;
            }
        }
        if(your_point>opponent_point){
            return "bigger";
        }else if(your_point<opponent_point){
            return "smaller";
        }else{
            return "the same";
        }
    }
}
std::string same_judge_straight(const std::vector<std::pair<int,char>>&yourPoker,const std::vector<std::pair<int,char>>&opponentPoker){
    auto your_it=yourPoker;
    int your_point=0,opponent_point=0;  //记录顺子最大牌点
    sort(your_it.begin(), your_it.end());
    for(auto & i : your_it){
        i.second='#';
    }
    your_it.erase(unique(your_it.begin(),your_it.end()),your_it.end());
    for(auto i=0;i+4<your_it.size();++i){
        if((your_it[i+4].first-your_it[i].first)==4&&your_it[i+4].first>your_point){
            your_point=your_it[i+4].first;   //更新最大点数
        }else{
            continue;
        }
    }
    auto opponent_it=opponentPoker;
    sort(opponent_it.begin(), opponent_it.end());
    for(auto & i : opponent_it){
        i.second='#';
    }
    opponent_it.erase(unique(opponent_it.begin(),opponent_it.end()),opponent_it.end());
    for(auto i=0;i+4<opponent_it.size();++i){
        if((opponent_it[i+4].first-opponent_it[i].first)==4&&opponent_it[i+4].first>opponent_point){
            opponent_point=opponent_it[i+4].first;   //更新最大点数
        }else{
            continue;
        }
    }
    if(your_point>opponent_point){
        return "bigger";
    }else if(your_point<opponent_point){
        return "smaller";
    }else{
        return "the same";
    }
}
std::string same_judge_straight_royal(const std::vector<std::pair<int,char>>&yourPoker,const std::vector<std::pair<int,char>>&opponentPoker){  //皇家同花顺 
 for(int i=0;i<yourPoker.size();i++){
  for(int j=0;j<opponentPoker.size();j++){
   if(yourPoker[i].first==13&&opponentPoker[j].first==13&&yourPoker[i].second>opponentPoker[j].second){
        return "bigger";
   }else if(yourPoker[i].first==13&&opponentPoker[j].first==13&&yourPoker[i].second==opponentPoker[j].second){
        return "the same";
   }else if(yourPoker[i].first==13&&opponentPoker[j].first==13&&yourPoker[i].second<opponentPoker[j].second){
        return "smaller";
   }
  }
 }
    //return "wrong";
}


void maxl(const std::vector<std::pair<int,char>>&arr,char &hua,int &mmax){
 auto it=arr;
    int coun[5]={0};
    int count=0;
    for(int i=0;i<it.size();i++){
          if(it[i].second=='A') {
      coun[1]++;
      if(coun[1]>=5) {
   count=1;
   hua='A';
   }
  }
  else if(it[i].second=='B') {
      coun[2]++;
      if(coun[2]>=5) {
   count=2;
   hua='B'; 
   } 
  }
  else if(it[i].second=='C') {
   coun[3]++;
      if(coun[3]>=5) {
   count=3;
   hua='C';  
   }
  }
  else if(it[i].second=='D') {
   coun[4]++;
      if(coun[4]>=5) {
   count=4; 
   hua='D'; 
   }
  } 
 }
 mmax=0;
 if(coun[count]==5){
  for(int i=0;i<it.size();i++){
   if(it[i].second==hua&&it[i].first>mmax) mmax=it[i].first;
  }
 }
 else if(coun[count]==6){
  int a1=0;
  for(int i=0;i<it.size();i++){
   if(it[i].second==hua&&it[i].first>mmax) mmax=it[i].first;
  }
  for(int i=0;i<it.size();i++){
   if(it[i].second==hua&&it[i].first>a1&&it[i].first!=mmax) a1=it[i].first;
  }
  if((mmax-a1)!=1) mmax=a1;
 }
 else if(coun[count]==7){
  int a1=0,a2=0;
  for(int i=0;i<it.size();i++){
   if(it[i].second==hua&&it[i].first>mmax) mmax=it[i].first;
  }
  for(int i=0;i<it.size();i++){
   if(it[i].second==hua&&it[i].first>a1&&it[i].first!=mmax) a1=it[i].first;
  }
  for(int i=0;i<it.size();i++){
   if(it[i].second==hua&&it[i].first>a2&&it[i].first!=mmax&&it[i].first!=a1) a2=it[i].first;
  }
  if((mmax-a1)!=1&&(a1-a2)==1) mmax=a1;
  else if((mmax-a1)!=1&&(a1-a2)!=1) mmax=a2;
 }
 return;
}
std::string same_judge_straight_wh(const std::vector<std::pair<int,char>>&yourPoker,const std::vector<std::pair<int,char>>&opponentPoker){  //同花顺
    char hua1='#',hua2='#';
    int mma1=0,mma2=0;
    maxl(yourPoker,hua1,mma1);
    maxl(opponentPoker,hua2,mma2);
    if(mma1>mma2){
     return "bigger";
 }
 else if(mma1==mma2){
  if(hua1>hua2) return "bigger";
  else if(hua1==hua2) return "the same";
  else return "smaller";
 }
 else return "smaller";
}
std::string same_judge_Four(const std::vector<std::pair<int,char>>&arr,const std::vector<std::pair<int,char>>&ar){  //判四张
    std::map<int,int>count;  //第一个int表示牌点 第二个int表示出现的次数
    int a1=0,a2=0;
    for(int i=0;i!=arr.size();++i){
        ++count[arr[i].first];
        if(count[arr[i].first]==4){
            a1=arr[i].first;
        }
    }
    std::map<int,int>coun;
    for(int i=0;i!=ar.size();++i){
        ++coun[ar[i].first];
        if(coun[ar[i].first]==4){
            a2=ar[i].first;
        }
    }
    if(a1>a2)return "bigger";
    else return "smaller";
}

// std::string compare(const std::vector<std::pair<int,char>>&yourPoker,const std::vector<std::pair<int,char>>&opponentPoker){
//     int yourFlag,opponentFlag;  //牌型大小 从1-10
//     string result;
//     /*判断自身牌型*/
//     if(judge_single(yourPoker))
//         yourFlag=1;
//     if(judge_pair(yourPoker))
//         yourFlag=2;
//     if(judge_twopair(yourPoker))
//         yourFlag=3;
//     if(judge_Three(yourPoker))
//         yourFlag=4;
//     if(judge_straight(yourPoker))
//         yourFlag=5;
//     if(judge_same_flush(yourPoker))
//         yourFlag=6;
//     if(judge_Three_beltTwo(yourPoker))
//         yourFlag=7;
//     if(judge_Four(yourPoker))
//         yourFlag=8;
//     if(judge_straight_wh(yourPoker))
//         yourFlag=9;
//     if(judge_straight_royal(yourPoker))
//         yourFlag=10;
//     /*判对手牌型*/
//     if(judge_single(opponentPoker))
//         opponentFlag=1;
//     if(judge_pair(opponentPoker))
//         opponentFlag=2;
//     if(judge_twopair(opponentPoker))
//         opponentFlag=3;
//     if(judge_Three(opponentPoker))
//         opponentFlag=4;
//     if(judge_straight(opponentPoker))
//         opponentFlag=5;
//     if(judge_same_flush(opponentPoker))
//         opponentFlag=6;
//     if(judge_Three_beltTwo(opponentPoker))
//         opponentFlag=7;
//     if(judge_Four(opponentPoker))
//         opponentFlag=8;
//     if(judge_straight_wh(opponentPoker))
//         opponentFlag=9;
//     if(judge_straight_royal(opponentPoker))
//         opponentFlag=10;
//     /*比较大小*/
//     if(yourFlag>opponentFlag){
//         return "bigger";
//     }else if(yourFlag<opponentFlag){
//         return "smaller";
//     }else{   //牌型相同的情况
//         switch(yourFlag){
//             case 1:
//             case 2:
//             case 3:
//             case 4:
//             case 5:
//                 result=same_judge_straight(yourPoker,opponentPoker);
//                 return result;
//             case 6:
//                 result=same_judge_sameFlush(yourPoker,opponentPoker);
//                 return result;
//             case 7:
//                 result=same_judge_ThreeBeltTwo(yourPoker,opponentPoker);
//                 return result;
//             case 8:
//             case 9:
//             case 10:
//         }
//     }
// }
#endif //TEXASHANDEM_JUDGE_H
