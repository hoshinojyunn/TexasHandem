#ifndef JACKPOT_H
#define JACKPOT_H
class jackPot{
public:
    int total;
    jackPot(){
        total=0;
    }
    void display(){
        std::cout<<"目前奖池金额:"<<total<<std::endl;
    }
};
#endif