#include"BarberShop.h"


using namespace myBarberShop;


int main()
{
    Rank time;

    cout << "������Ӫҵʱ��: ";
    cin >> time;
    myBarberShop::barberShop myShop(time);
    myShop.run();
    return 0;
}