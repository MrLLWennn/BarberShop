//
// Created by 86198 on 2024/6/8.
//

#ifndef BARBERSHOP_BARBERSHOP_H
#define BARBERSHOP_BARBERSHOP_H


#include"Barber.h"
#include"Customer.h"



namespace myBarberShop
{
    class barber;
    class barberShop
    {
        friend class Barber;
    private:
        //营业时间
        Rank serviceTime;
        //理发师
        vector<barber> barbers;
        //顾客
        vector<queue<Customer>> customers;

    public:
        //文件读入的构造函数
        barberShop() : serviceTime(myBarberShop::DEFAULT_SERVICE_TIME), barbers(myBarberShop::DEFAULT_BARBERS)
        {
            ifstream inputFile;
            inputFile.open("D:\\clion\\数据结构课设\\barberShop\\files\\barbers.txt");

            if (!inputFile.is_open())
            {
                std::cerr << "无法打开文件" << std::endl;
                exit(-1);
            }

            string line;
            int i = 0;
            while(std::getline(inputFile, line))
            {
                stringstream ss(line);
                string item;


                if(std::getline(ss, item, ','))
                {
                    barbers[i].id = std::stoi(item);
                }
                if(std::getline(ss, item, ','))
                {
                    if(item == "1")
                    {
                        barbers[i].level = myBarberShop::barberLevel::FIRST_LEVEL;
                        myBarberShop::bLevel[i] = myBarberShop::barberLevel::FIRST_LEVEL;
                    }
                    else if(item == "2")
                    {
                        barbers[i].level = myBarberShop::barberLevel::SECOND_LEVEL;
                        myBarberShop::bLevel[i] = myBarberShop::barberLevel::SECOND_LEVEL;
                    }
                    else if(item == "3")
                    {
                        barbers[i].level = myBarberShop::barberLevel::THIRD_LEVEL;
                        myBarberShop::bLevel[i] = myBarberShop::barberLevel::THIRD_LEVEL;
                    }
                    else
                    {
                        cerr << "未知理发师等级" << endl;
                    }
                    i++;
                }
            }
            cout << "读入D:\\clion\\数据结构课设\\barberShop\\files\\barbers.txt文件打开成功" << endl;
            inputFile.close();

            //初始化customers
            customers.resize(myBarberShop::DEFAULT_BARBERS);

            for(auto& barber : barbers)
            {
                barber.isFree = true;
                barber.totalRevenue = 0;
                barber.size = 0;
            }

            for(Rank i = 0;i < myBarberShop::DEFAULT_CHAIRS;i++)
            {
                emptyChairs[i] = INT_MAX;
            }
        }


        //自输入的构造函数， 输入营业时间
        explicit barberShop(Rank service_time) : serviceTime(service_time), barbers(myBarberShop::DEFAULT_BARBERS)
        {
            ifstream inputFile;
            inputFile.open("D:\\clion\\数据结构课设\\barberShop\\files\\barbers.txt");

            if (!inputFile.is_open())
            {
                std::cerr << "无法打开文件" << std::endl;
                exit(-1);
            }

            string line;
            int i = 0;
            while(std::getline(inputFile, line))
            {
                stringstream ss(line);
                string item;


                if(std::getline(ss, item, ','))
                {
                    barbers[i].id = std::stoi(item);
                }
                if(std::getline(ss, item, ','))
                {
                    if(item == "1")
                    {
                        barbers[i].level = myBarberShop::barberLevel::FIRST_LEVEL;
                        myBarberShop::bLevel[i] = myBarberShop::barberLevel::FIRST_LEVEL;
                    }
                    else if(item == "2")
                    {
                        barbers[i].level = myBarberShop::barberLevel::SECOND_LEVEL;
                        myBarberShop::bLevel[i] = myBarberShop::barberLevel::SECOND_LEVEL;
                    }
                    else if(item == "3")
                    {
                        barbers[i].level = myBarberShop::barberLevel::THIRD_LEVEL;
                        myBarberShop::bLevel[i] = myBarberShop::barberLevel::THIRD_LEVEL;
                    }
                    else
                    {
                        cerr << "未知理发师等级" << endl;
                    }
                    i++;
                }
            }
            cout << "读入D:\\clion\\数据结构课设\\barberShop\\files\\barbers.txt文件打开成功" << endl;
            inputFile.close();

            //初始化customers
            customers.resize(myBarberShop::DEFAULT_BARBERS);

            for(auto& barber : barbers)
            {
                barber.isFree = true;
                barber.totalRevenue = 0;
                barber.size = 0;
            }
        }

    public:
        void display(Rank currentTime)
        {
            ofstream outputFile;
            string fileName = "D:\\clion\\数据结构课设\\barberShop\\files\\newResult.txt";
            outputFile.open(fileName, ios::out | ios::app);

            if(!outputFile.is_open())
            {
                cerr << "打开文件: " << fileName << "错误，不能进行写" << endl;
                exit(-1);
            }

            Rank hour = currentTime / 60 + 8;
            Rank minute = currentTime % 60;

            outputFile << endl;
            outputFile << "|-------当前时间 " << hour << ":" << minute << "-------|" <<endl;
            outputFile << "| 理发椅编号 | 理发师级别  | 排队长度  |" << endl;
            outputFile << "|-----------|------------|----------|" << endl;

            for(Rank i = 0;i < barbers.size();i++)
            {
                outputFile << " | " << std::setw(7) << "Num   " << i
                << " | " << std::setw(10) << barbers[i].level
                << " | " << std::setw(8) << barbers[i].size << " | " << endl;
            }

            cout << fileName << "文件打开成功" << endl;
            outputFile.close();
        }


        void draw(Rank currentTime, Widget& widget, Rank count)
        {
            auto newPage = new IMAGE;
            initgraph(800, 600);


            loadimage(newPage, "../image/shop.jpeg", 800, 600);
            putimage(0, 0, newPage);
            getimage(newPage, 0, 0, 800, 600); // 将页面1的内容保存到图片中


            Rank hour = currentTime / 60 + 8;
            Rank minute = currentTime  % 60;


            //显示页面主要画面
            settextstyle(30, 0, _T("宋体"));
            settextcolor(BLACK);
            setbkmode(TRANSPARENT);
            outtextxy(250, 10, _T("My BarberShop Status"));

            string s = "Current Time - ";
            s.append(std::to_string(hour));
            s.append(":");
            if(!(minute / 10))
            {
                s.append("0");
            }
            s.append(std::to_string(minute));
            settextstyle(20, 0, _T("宋体"));
            outtextxy(290, 40, s.c_str());

            outtextxy(150, 70, _T("Barbers"));
            outtextxy(600, 70, _T("Customers"));

            settextstyle(16, 0, _T("宋体"));
            outtextxy(270, 95, _T("Status"));
            outtextxy(330, 95, _T("Total Earnings"));
            outtextxy(510, 95, _T("Queue Size"));
            outtextxy(630, 95, _T("Customer Id"));

            settextstyle(16, 0, _T("宋体"));
            settextcolor(YELLOW);


            //显示当前时间理发馆的状态

            //显示理发师状态
            for(Rank i = 0;i < barbers.size();i++)
            {
                setbkmode(TRANSPARENT);

                Rank x = 120;
                Rank y = 120 + 50 * i;

                string text = "Barber ";
                text.append(std::to_string(barbers[i].id)).append("(Level ").append(std::to_string(barbers[i].level)).append(") : ");
                text.append((barbers[i].isFree ? " Free  " : " Busy  ")).append(std::to_string(barbers[i].totalRevenue));
                outtextxy(x, y, text.c_str());
            }


            //显示理发师的等待队列情况
            for(Rank i = 0;i < customers.size();i++)
            {
                setbkmode(TRANSPARENT);

                Rank x = 550;
                Rank y = 120 + 50 * i;

                string s;
                s.append(std::to_string(barbers[i].size));
                Rank si = barbers[i].size;
                if(si)
                {
                    auto q = customers[i];
                    while(si--)
                    {
                        s.append("         ").append(std::to_string(q.front().customerId));
                        q.pop();
                    }
                }
                outtextxy(x, y, s.c_str());
            }

            //页面增加
            widget.addPage(newPage);

            //增加按键
            auto result = new IMAGE;

            string ss = "../image/page";

            ss.append(std::to_string(count)).append(".jpg");

            saveimage(ss.c_str(), result);

            widget.addPage(result);

            LPCTSTR str ="Next Page";
            auto button1_1 = new Button(400, 550, 200, 40, str, [&]() {
                widget.setCurrentIndex(count + 1); // 点击按钮1时，切换到页面2"开始模拟"
            });
            widget.addButton(count, button1_1); // 将按钮1添加到页面1

            _getch();
            //Sleep(1500);
            closegraph();
        }


    public:


        //当天总收入
        double totalRevenue()
        {
            double totalRevenue = 0;
            for (const auto& b : barbers)
                totalRevenue += b.totalRevenue;
            return totalRevenue;
        }


        //不同等级理发师营业额
        void levelRevenue()
        {
            double firstLevel_Revenue = 0;
            double secondLevel_Revenue = 0;
            double thirdLevel_Revenue = 0;
            for (const auto& b : barbers)
            {
                switch (b.level){
                    case  myBarberShop::FIRST_LEVEL:
                        firstLevel_Revenue += b.totalRevenue;
                        break;
                    case  myBarberShop::SECOND_LEVEL:
                        secondLevel_Revenue += b.totalRevenue;
                        break;
                    case  myBarberShop::THIRD_LEVEL:
                        thirdLevel_Revenue += b.totalRevenue;
                        break;
                    default:
                        cout<<"ERROR"<<endl;
                        break;
                }
            }
            cout<<"第一等级的理发师总营业额为："<<firstLevel_Revenue<<"/元"<<endl;
            cout<<"第二等级的理发师总营业额为："<<secondLevel_Revenue<<"/元"<<endl;
            cout<<"第三等级的理发师总营业额为："<<thirdLevel_Revenue<<"/元"<<endl;
        }


    public:

        void run() {
            myBarberShop::Widget widget(800, 600);
            ExMessage msg;

            widget.init();

            BeginBatchDraw(); // 开始批量绘制

            while(true) // 检查是否有消息
            {
                if(peekmessage(&msg))
                {
                    int mouseX = msg.x; // 获取鼠标x坐标
                    int mouseY = msg.y; // 获取鼠标y坐标

                    if (msg.message == WM_LBUTTONDOWN) {
                        // 鼠标左键按下事件
                        if (widget.currentIndex >= 0 && widget.currentIndex < widget.buttons.size()) {
                            for (Button *button: widget.buttons[widget.currentIndex]) {
                                if (button->checkClick(mouseX, mouseY)) {
                                    widget.close();
                                    break;
                                }
                            }
                        }// 处理鼠标点击事件
                        break;
                    } else if (msg.message == WM_MOUSEMOVE) {// 鼠标移动事件
                        widget.mouseMove(mouseX, mouseY); // 处理鼠标移动事件
                    }

                }

                //画主界面
                widget.draw();
                FlushBatchDraw();
                Sleep(10);
            }

            closegraph();
            simulate(widget);


            cleardevice();

            EndBatchDraw();
        }


        //开始模拟,用的函数都在这里调用
        void simulate(Widget& widget)
        {

            //当前时间
            Rank currentTime = 0;
            //顾客序号
            Rank customer_id = 0;
            //总逗留时间
            Rank customerTotalLastingTime = 0;
            //顾客总数
            Rank totalCustomers = 0;
            //总收尾工作时间
            Rank totalEndingTime = 0;
            //等待队列长度
            double queueTotalLength = 0;

            double sum = 0;

            Rank count = 1;


            ofstream outputFile;
            string fileName = "D:\\clion\\数据结构课设\\barberShop\\files\\arrivalTime.txt";
            outputFile.open(fileName);
            outputFile << "|    顾客    |    到达时间    | 选择的理发师等级 |   所需服务时间   |" << endl;
            outputFile.close();


            while (currentTime < serviceTime) {
                // 生成随机顾客
                Rank duringTime = myBarberShop::generateRandomNumber(15, 60);
                myBarberShop::selection ss;
                Rank internalTime = myBarberShop::generateRandomNumber(1, 60);
                Customer customer(customer_id++, ss, currentTime + internalTime, duringTime);

                // 在打烊之前进门
                if (currentTime + internalTime < serviceTime) {
                    // 将该顾客的信息写进文件
                    writeArrivalTime(customer);

                    bool assigned = false;


                    //寻找空闲理发师
                    for(auto& barber : barbers)
                    {
                        if(barber.isFree && barber.level == customer.select.choseLevel)
                        {
                            assigned = true;
                            //该理发师开始理发
                            barber.isFree = false;
                            //barber.hairCutting();
                            //记录理发师正在理发的顾客的离开时间，即为：(到达时间+服务时间)
                            myBarberShop::busyBarber[barber.id] = customer.arrivalTime + customer.durTime;
                            sum += static_cast<double>(customer.durTime);
                            barber.totalRevenue += customer.totalFee();
                            break;
                        }
                    }


                    //如果没有符合条件的空闲理发师
                    if(!assigned)
                    {
                        Rank minQueue = 0;
                        //则寻找最短队列进入等待
                        for(auto& barber : barbers)
                        {
                            if(barber.level == customer.select.choseLevel
                            && customers[minQueue].size() >= customers[barber.id].size())
                            {
                                minQueue = barber.id;
                            }
                        }


                        customers[minQueue].push(customer);
                        barbers[minQueue].totalRevenue += customer.totalFee();
                        barbers[minQueue].size++;

                        sum += static_cast<double>(customer.durTime);
                    }

                    totalCustomers++;
                    currentTime+=internalTime;
                }
                else
                {
                    break;
                }



                for(auto& barber : barbers)
                {
                    //更新状态，判断理发师正在理发顾客是否已经结束
                    if(!barber.isFree)
                    {
                        //如果当前时间已经超过上一个顾客的离开时间，则可以将
                        if(currentTime >= busyBarber[barber.id])
                            barber.isFree = true;
                        //等待队列不为空
                        if(barber.size)
                        {
                            //更新当前时间下的等待队列长度
                            queueTotalLength += barber.size;
                            barber.isFree = false;
                            //等待队列的顾客即为下一个理发的对象，弹出队列
                            Customer nextCustomer = customers[barber.id].front();
                            customers[barber.id].pop();
                            barber.size--;
                            //更新总逗留时间为：上一个理发的顾客的离开时间减去
                            if(busyBarber[barber.id] > nextCustomer.arrivalTime)
                                customerTotalLastingTime += busyBarber[barber.id] - nextCustomer.arrivalTime;
                            //如果当前时间时，理发师上一个理发的顾客已经离开了，则
                            if(currentTime >= busyBarber[barber.id]) {
                                //更新时间表
                                busyBarber[barber.id] = nextCustomer.arrivalTime + nextCustomer.durTime;
                            }
                        }
                    }
                }

                printStatus(currentTime);

                //显示迭代过程中变化
                display(currentTime);

                //图形化
                draw(currentTime, widget,count++);

                //清屏
                cleardevice();


            }//while(currentTime < 22*60)


            //结束while循环，计算收尾工作时间
            // 即为在打烊时间之前进入，但是超过默认服务时间还在服务时间内的顾客剩余时间
            //由在headerFiles中定义的时间表，结束循环时，先将此时的barbe状态更新
            for(auto& barber : barbers)
            {
                //退出模拟过程时还处于忙状态且等待队列为空的理发师
                if(!barber.isFree && barber.size == 0)
                {
                    //判断其上一位理发的顾客是否已经理完发，理完发则将其状态置为true
                    if(busyBarber[barber.id] <= serviceTime)
                    {
                        barber.isFree = true;
                    }
                    else//如果其顾客在打烊时间还未理发结束，即为收尾工作时间
                    {
                        totalEndingTime += (busyBarber[barber.id] - serviceTime);
                    }
                }
                else if(barber.size)//如果此时该理发师的等待队列仍不为空
                {
                    //那么，所有在等待队列的顾客的服务时间也为收尾工作时间
                    while(!customers[barber.id].empty())
                    {
                        totalEndingTime += (customers[barber.id].front().durTime);
                        customers[barber.id].pop();
                    }
                }
            }


            //统计数据
            // a) 一天内顾客在理发馆内的平均逗留时间；
            double averageLastingTime = static_cast<double>(customerTotalLastingTime + sum) / totalCustomers;
            cout << "一天内顾客在理发馆内的平均逗留时间: " << averageLastingTime << "/分钟"<< endl;

            // b) 顾客排队等候理发的队列长度平均值；
            cout << "顾客排队等候理发的队列长度平均值: " << queueTotalLength / totalCustomers << "/人" << endl;

            // c) 营业时间到点后仍需完成服务的收尾工作时间；
            cout << "营业时间到点后仍需完成服务的收尾工作时间: " << totalEndingTime << "/分钟" <<endl;

            // d) 统计每天的营业额；
            cout << "每天的营业额: " << totalRevenue() << "/元"<<endl;

            // e) 统计每天不同级别理发师的创收。
            levelRevenue();

            cout << widget.buttons.size() << endl;
            cout << widget.pages.size() << endl;

            //widget.close();
            EndBatchDraw();
       }


       //用于打印当前的状态，便于调试
        void printStatus(Rank currentTime) {

            Rank hour = currentTime / 60 + 8;
            Rank minute = currentTime % 60;

            cout << "当前时间为：" << hour << ":" << minute << endl;

            std::cout << "Current status of the barber shop:" << std::endl;
            for (const auto &barber : barbers) {
                std::cout << "Barber " << barber.id << " (Level " << barber.level << "): " << (barber.isFree ? "Free" : "Busy") << " " << barber.totalRevenue <<endl;
            }
            for (int i = 0; i < customers.size(); ++i) {
                std::cout << "Queue for Barber " << i << ": " << customers[i].size() << " customers" << std::endl;
            }

            for(Rank i = 0;i < DEFAULT_BARBERS;i++)
            {
                cout << busyBarber[i] << " ";
            }
            cout << endl;
        }


        //将顾客的到达时间读入文件中
        static void writeArrivalTime(const Customer& customer)
        {
            ofstream outputFile;
            string fileName = "D:\\clion\\数据结构课设\\barberShop\\files\\arrivalTime.txt";
            outputFile.open(fileName, ios::out | ios::app);

            if(!outputFile.is_open())
            {
                cerr << "文件 ： "  << fileName << "打开失败" << endl;
                exit(-1);
            }

            int hour = static_cast<int>(customer.arrivalTime / 60 + 8);

            int minute = static_cast<int>(customer.arrivalTime % 60);

            outputFile<< "|顾客" << std::setiosflags(ios::left) << std::setfill(' ') << std::setw(8) << customer.customerId
            << "|"  << std::setiosflags(ios::right) << std::setfill('0') << std::setw(2) <<  hour << ":"  << std::setfill('0') << std::setw(2) << minute << "          |"
            << std::setfill(' ') << std::setw(16)  << std::setiosflags(ios::left) << customer.select.choseLevel
            << "|" << std::setiosflags(ios::left) << std::setfill(' ') << std::setw(17) << customer.durTime  << "|" << endl;

            cout << "文件arrivalTime.txt写入成功" <<endl;

            outputFile.close();
        }

    };//! class barberShop


}//! namespace myBarberShop


#endif //BARBERSHOP_BARBERSHOP_H
