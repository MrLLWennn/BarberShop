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
    public://Ȩ������Ϊpublic,��Ϊ����ʵ��������˿͵�������Ҫ����,Ҳ������struct
        //�˿�ID
        Rank customerId;
        //�˿�ѡ�����ʦ�ȼ�
        selection select;
        //����ʱ��
        Rank arrivalTime;
        //�������ʱ��
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

        //�ù˿ͱ��η�������ķ���
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
