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
        //Ӫҵʱ��
        Rank serviceTime;
        //��ʦ
        vector<barber> barbers;
        //�˿�
        vector<queue<Customer>> customers;

    public:
        //�ļ�����Ĺ��캯��
        barberShop() : serviceTime(myBarberShop::DEFAULT_SERVICE_TIME), barbers(myBarberShop::DEFAULT_BARBERS)
        {
            ifstream inputFile;
            inputFile.open("D:\\clion\\���ݽṹ����\\barberShop\\files\\barbers.txt");

            if (!inputFile.is_open())
            {
                std::cerr << "�޷����ļ�" << std::endl;
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
                        cerr << "δ֪��ʦ�ȼ�" << endl;
                    }
                    i++;
                }
            }
            cout << "����D:\\clion\\���ݽṹ����\\barberShop\\files\\barbers.txt�ļ��򿪳ɹ�" << endl;
            inputFile.close();

            //��ʼ��customers
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


        //������Ĺ��캯���� ����Ӫҵʱ��
        explicit barberShop(Rank service_time) : serviceTime(service_time), barbers(myBarberShop::DEFAULT_BARBERS)
        {
            ifstream inputFile;
            inputFile.open("D:\\clion\\���ݽṹ����\\barberShop\\files\\barbers.txt");

            if (!inputFile.is_open())
            {
                std::cerr << "�޷����ļ�" << std::endl;
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
                        cerr << "δ֪��ʦ�ȼ�" << endl;
                    }
                    i++;
                }
            }
            cout << "����D:\\clion\\���ݽṹ����\\barberShop\\files\\barbers.txt�ļ��򿪳ɹ�" << endl;
            inputFile.close();

            //��ʼ��customers
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
            string fileName = "D:\\clion\\���ݽṹ����\\barberShop\\files\\newResult.txt";
            outputFile.open(fileName, ios::out | ios::app);

            if(!outputFile.is_open())
            {
                cerr << "���ļ�: " << fileName << "���󣬲��ܽ���д" << endl;
                exit(-1);
            }

            Rank hour = currentTime / 60 + 8;
            Rank minute = currentTime % 60;

            outputFile << endl;
            outputFile << "|-------��ǰʱ�� " << hour << ":" << minute << "-------|" <<endl;
            outputFile << "| ���α�� | ��ʦ����  | �Ŷӳ���  |" << endl;
            outputFile << "|-----------|------------|----------|" << endl;

            for(Rank i = 0;i < barbers.size();i++)
            {
                outputFile << " | " << std::setw(7) << "Num   " << i
                << " | " << std::setw(10) << barbers[i].level
                << " | " << std::setw(8) << barbers[i].size << " | " << endl;
            }

            cout << fileName << "�ļ��򿪳ɹ�" << endl;
            outputFile.close();
        }


        void draw(Rank currentTime, Widget& widget, Rank count)
        {
            auto newPage = new IMAGE;
            initgraph(800, 600);


            loadimage(newPage, "../image/shop.jpeg", 800, 600);
            putimage(0, 0, newPage);
            getimage(newPage, 0, 0, 800, 600); // ��ҳ��1�����ݱ��浽ͼƬ��


            Rank hour = currentTime / 60 + 8;
            Rank minute = currentTime  % 60;


            //��ʾҳ����Ҫ����
            settextstyle(30, 0, _T("����"));
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
            settextstyle(20, 0, _T("����"));
            outtextxy(290, 40, s.c_str());

            outtextxy(150, 70, _T("Barbers"));
            outtextxy(600, 70, _T("Customers"));

            settextstyle(16, 0, _T("����"));
            outtextxy(270, 95, _T("Status"));
            outtextxy(330, 95, _T("Total Earnings"));
            outtextxy(510, 95, _T("Queue Size"));
            outtextxy(630, 95, _T("Customer Id"));

            settextstyle(16, 0, _T("����"));
            settextcolor(YELLOW);


            //��ʾ��ǰʱ�����ݵ�״̬

            //��ʾ��ʦ״̬
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


            //��ʾ��ʦ�ĵȴ��������
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

            //ҳ������
            widget.addPage(newPage);

            //���Ӱ���
            auto result = new IMAGE;

            string ss = "../image/page";

            ss.append(std::to_string(count)).append(".jpg");

            saveimage(ss.c_str(), result);

            widget.addPage(result);

            LPCTSTR str ="Next Page";
            auto button1_1 = new Button(400, 550, 200, 40, str, [&]() {
                widget.setCurrentIndex(count + 1); // �����ť1ʱ���л���ҳ��2"��ʼģ��"
            });
            widget.addButton(count, button1_1); // ����ť1��ӵ�ҳ��1

            _getch();
            //Sleep(1500);
            closegraph();
        }


    public:


        //����������
        double totalRevenue()
        {
            double totalRevenue = 0;
            for (const auto& b : barbers)
                totalRevenue += b.totalRevenue;
            return totalRevenue;
        }


        //��ͬ�ȼ���ʦӪҵ��
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
            cout<<"��һ�ȼ�����ʦ��Ӫҵ��Ϊ��"<<firstLevel_Revenue<<"/Ԫ"<<endl;
            cout<<"�ڶ��ȼ�����ʦ��Ӫҵ��Ϊ��"<<secondLevel_Revenue<<"/Ԫ"<<endl;
            cout<<"�����ȼ�����ʦ��Ӫҵ��Ϊ��"<<thirdLevel_Revenue<<"/Ԫ"<<endl;
        }


    public:

        void run() {
            myBarberShop::Widget widget(800, 600);
            ExMessage msg;

            widget.init();

            BeginBatchDraw(); // ��ʼ��������

            while(true) // ����Ƿ�����Ϣ
            {
                if(peekmessage(&msg))
                {
                    int mouseX = msg.x; // ��ȡ���x����
                    int mouseY = msg.y; // ��ȡ���y����

                    if (msg.message == WM_LBUTTONDOWN) {
                        // �����������¼�
                        if (widget.currentIndex >= 0 && widget.currentIndex < widget.buttons.size()) {
                            for (Button *button: widget.buttons[widget.currentIndex]) {
                                if (button->checkClick(mouseX, mouseY)) {
                                    widget.close();
                                    break;
                                }
                            }
                        }// ����������¼�
                        break;
                    } else if (msg.message == WM_MOUSEMOVE) {// ����ƶ��¼�
                        widget.mouseMove(mouseX, mouseY); // ��������ƶ��¼�
                    }

                }

                //��������
                widget.draw();
                FlushBatchDraw();
                Sleep(10);
            }

            closegraph();
            simulate(widget);


            cleardevice();

            EndBatchDraw();
        }


        //��ʼģ��,�õĺ��������������
        void simulate(Widget& widget)
        {

            //��ǰʱ��
            Rank currentTime = 0;
            //�˿����
            Rank customer_id = 0;
            //�ܶ���ʱ��
            Rank customerTotalLastingTime = 0;
            //�˿�����
            Rank totalCustomers = 0;
            //����β����ʱ��
            Rank totalEndingTime = 0;
            //�ȴ����г���
            double queueTotalLength = 0;

            double sum = 0;

            Rank count = 1;


            ofstream outputFile;
            string fileName = "D:\\clion\\���ݽṹ����\\barberShop\\files\\arrivalTime.txt";
            outputFile.open(fileName);
            outputFile << "|    �˿�    |    ����ʱ��    | ѡ�����ʦ�ȼ� |   �������ʱ��   |" << endl;
            outputFile.close();


            while (currentTime < serviceTime) {
                // ��������˿�
                Rank duringTime = myBarberShop::generateRandomNumber(15, 60);
                myBarberShop::selection ss;
                Rank internalTime = myBarberShop::generateRandomNumber(1, 60);
                Customer customer(customer_id++, ss, currentTime + internalTime, duringTime);

                // �ڴ���֮ǰ����
                if (currentTime + internalTime < serviceTime) {
                    // ���ù˿͵���Ϣд���ļ�
                    writeArrivalTime(customer);

                    bool assigned = false;


                    //Ѱ�ҿ�����ʦ
                    for(auto& barber : barbers)
                    {
                        if(barber.isFree && barber.level == customer.select.choseLevel)
                        {
                            assigned = true;
                            //����ʦ��ʼ��
                            barber.isFree = false;
                            //barber.hairCutting();
                            //��¼��ʦ�������Ĺ˿͵��뿪ʱ�䣬��Ϊ��(����ʱ��+����ʱ��)
                            myBarberShop::busyBarber[barber.id] = customer.arrivalTime + customer.durTime;
                            sum += static_cast<double>(customer.durTime);
                            barber.totalRevenue += customer.totalFee();
                            break;
                        }
                    }


                    //���û�з��������Ŀ�����ʦ
                    if(!assigned)
                    {
                        Rank minQueue = 0;
                        //��Ѱ����̶��н���ȴ�
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
                    //����״̬���ж���ʦ�������˿��Ƿ��Ѿ�����
                    if(!barber.isFree)
                    {
                        //�����ǰʱ���Ѿ�������һ���˿͵��뿪ʱ�䣬����Խ�
                        if(currentTime >= busyBarber[barber.id])
                            barber.isFree = true;
                        //�ȴ����в�Ϊ��
                        if(barber.size)
                        {
                            //���µ�ǰʱ���µĵȴ����г���
                            queueTotalLength += barber.size;
                            barber.isFree = false;
                            //�ȴ����еĹ˿ͼ�Ϊ��һ�����Ķ��󣬵�������
                            Customer nextCustomer = customers[barber.id].front();
                            customers[barber.id].pop();
                            barber.size--;
                            //�����ܶ���ʱ��Ϊ����һ�����Ĺ˿͵��뿪ʱ���ȥ
                            if(busyBarber[barber.id] > nextCustomer.arrivalTime)
                                customerTotalLastingTime += busyBarber[barber.id] - nextCustomer.arrivalTime;
                            //�����ǰʱ��ʱ����ʦ��һ�����Ĺ˿��Ѿ��뿪�ˣ���
                            if(currentTime >= busyBarber[barber.id]) {
                                //����ʱ���
                                busyBarber[barber.id] = nextCustomer.arrivalTime + nextCustomer.durTime;
                            }
                        }
                    }
                }

                printStatus(currentTime);

                //��ʾ���������б仯
                display(currentTime);

                //ͼ�λ�
                draw(currentTime, widget,count++);

                //����
                cleardevice();


            }//while(currentTime < 22*60)


            //����whileѭ����������β����ʱ��
            // ��Ϊ�ڴ���ʱ��֮ǰ���룬���ǳ���Ĭ�Ϸ���ʱ�仹�ڷ���ʱ���ڵĹ˿�ʣ��ʱ��
            //����headerFiles�ж����ʱ�������ѭ��ʱ���Ƚ���ʱ��barbe״̬����
            for(auto& barber : barbers)
            {
                //�˳�ģ�����ʱ������æ״̬�ҵȴ�����Ϊ�յ���ʦ
                if(!barber.isFree && barber.size == 0)
                {
                    //�ж�����һλ���Ĺ˿��Ƿ��Ѿ����귢�����귢����״̬��Ϊtrue
                    if(busyBarber[barber.id] <= serviceTime)
                    {
                        barber.isFree = true;
                    }
                    else//�����˿��ڴ���ʱ�仹δ����������Ϊ��β����ʱ��
                    {
                        totalEndingTime += (busyBarber[barber.id] - serviceTime);
                    }
                }
                else if(barber.size)//�����ʱ����ʦ�ĵȴ������Բ�Ϊ��
                {
                    //��ô�������ڵȴ����еĹ˿͵ķ���ʱ��ҲΪ��β����ʱ��
                    while(!customers[barber.id].empty())
                    {
                        totalEndingTime += (customers[barber.id].front().durTime);
                        customers[barber.id].pop();
                    }
                }
            }


            //ͳ������
            // a) һ���ڹ˿��������ڵ�ƽ������ʱ�䣻
            double averageLastingTime = static_cast<double>(customerTotalLastingTime + sum) / totalCustomers;
            cout << "һ���ڹ˿��������ڵ�ƽ������ʱ��: " << averageLastingTime << "/����"<< endl;

            // b) �˿��ŶӵȺ����Ķ��г���ƽ��ֵ��
            cout << "�˿��ŶӵȺ����Ķ��г���ƽ��ֵ: " << queueTotalLength / totalCustomers << "/��" << endl;

            // c) Ӫҵʱ�䵽���������ɷ������β����ʱ�䣻
            cout << "Ӫҵʱ�䵽���������ɷ������β����ʱ��: " << totalEndingTime << "/����" <<endl;

            // d) ͳ��ÿ���Ӫҵ�
            cout << "ÿ���Ӫҵ��: " << totalRevenue() << "/Ԫ"<<endl;

            // e) ͳ��ÿ�첻ͬ������ʦ�Ĵ��ա�
            levelRevenue();

            cout << widget.buttons.size() << endl;
            cout << widget.pages.size() << endl;

            //widget.close();
            EndBatchDraw();
       }


       //���ڴ�ӡ��ǰ��״̬�����ڵ���
        void printStatus(Rank currentTime) {

            Rank hour = currentTime / 60 + 8;
            Rank minute = currentTime % 60;

            cout << "��ǰʱ��Ϊ��" << hour << ":" << minute << endl;

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


        //���˿͵ĵ���ʱ������ļ���
        static void writeArrivalTime(const Customer& customer)
        {
            ofstream outputFile;
            string fileName = "D:\\clion\\���ݽṹ����\\barberShop\\files\\arrivalTime.txt";
            outputFile.open(fileName, ios::out | ios::app);

            if(!outputFile.is_open())
            {
                cerr << "�ļ� �� "  << fileName << "��ʧ��" << endl;
                exit(-1);
            }

            int hour = static_cast<int>(customer.arrivalTime / 60 + 8);

            int minute = static_cast<int>(customer.arrivalTime % 60);

            outputFile<< "|�˿�" << std::setiosflags(ios::left) << std::setfill(' ') << std::setw(8) << customer.customerId
            << "|"  << std::setiosflags(ios::right) << std::setfill('0') << std::setw(2) <<  hour << ":"  << std::setfill('0') << std::setw(2) << minute << "          |"
            << std::setfill(' ') << std::setw(16)  << std::setiosflags(ios::left) << customer.select.choseLevel
            << "|" << std::setiosflags(ios::left) << std::setfill(' ') << std::setw(17) << customer.durTime  << "|" << endl;

            cout << "�ļ�arrivalTime.txtд��ɹ�" <<endl;

            outputFile.close();
        }

    };//! class barberShop


}//! namespace myBarberShop


#endif //BARBERSHOP_BARBERSHOP_H
