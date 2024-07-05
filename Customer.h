//
// Created by 86198 on 2024/6/8.
//

#ifndef BARBERSHOP_CUSTOMER_H
#define BARBERSHOP_CUSTOMER_H


#include"headerFiles.h"


namespace myBarberShop
{




    class Customer
    {
    public://权限设置为public,因为按照实际情况，顾客的需求需要公开,也可以用struct
        //顾客ID
        Rank customerId;
        //顾客选择的理发师等级
        selection select;
        //到达时间
        Rank arrivalTime;
        //所需服务时间
        Rank durTime;
    public:

        explicit Customer(Rank id, selection s, Rank arrival, Rank d) : customerId(id), select(s), arrivalTime(arrival), durTime(d)
        {}

        ~Customer() = default;

        bool operator==(Customer& c) const
        {
            return this->customerId == c.customerId;
        }


        bool operator!=(Customer& c) const
        {
            return !operator==(c);
        }


    public:

        //该顾客本次服务所需的费用
        [[nodiscard("no use return")]]double totalFee() const noexcept
        {
            switch(this->select.choseLevel)
            {
                case myBarberShop::FIRST_LEVEL:
                    return this->durTime * fees[1];
                case myBarberShop::SECOND_LEVEL:
                    return this->durTime * fees[2];
                case myBarberShop::THIRD_LEVEL:
                    return this->durTime * fees[3];
            }
        }


    };//! class Customer

}//! namespace myBarberShop



#endif //BARBERSHOP_CUSTOMER_H
