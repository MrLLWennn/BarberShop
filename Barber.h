//
// Created by 86198 on 2024/6/8.
//

#ifndef BARBERSHOP_BARBER_H
#define BARBERSHOP_BARBER_H


#include"Customer.h"


namespace myBarberShop
{
    class barberShop;
    class Customer;

    class barber
    {
        friend class barberShop;
    private:
        //理发师的编号
        Rank id;
        //理发师等级
        myBarberShop::barberLevel level;
        //理发师是否空闲
        bool isFree;
        //理发师总收入
        double totalRevenue;
        //理发师队列长度
        Rank size;


    public:
        barber(Rank id, myBarberShop::barberLevel level, bool b, double totalRevenue, Rank size) :
        id(id), level(level), isFree(true), totalRevenue(totalRevenue), size(size){}

        barber() = default;


        ~barber() = default;


    public:
        void hairCutting()
        {
            //理发，即判断是否有空椅子
            Rank count = 0;
            while(true)
            {
                for(auto & emptyChair : emptyChairs)
                {
                    if(emptyChair == INT_MAX)
                    {
                        emptyChair = this->id;
                        count++;
                        break;
                    }
                }

                //如果找到空闲椅子，退出
                if(count != myBarberShop::DEFAULT_CHAIRS)
                {
                    break;
                }
                else//否则
                {
                    cout << "当前没有空椅子，请稍等。。。。。" <<endl;
                }
            }
        }

    };//! class barber

}//! namespace myBarberShop



#endif //BARBERSHOP_BARBER_H
