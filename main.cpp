#include"BarberShop.h"


using namespace myBarberShop;


int main()
{
    Rank time;

    cout << "请输入营业时间: ";
    cin >> time;
    myBarberShop::barberShop myShop(time);
    myShop.run();
    return 0;
}