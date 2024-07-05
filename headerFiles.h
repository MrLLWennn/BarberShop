//
// Created by 86198 on 2024/6/8.
//

#ifndef BARBERSHOP_HEADERFILES_H
#define BARBERSHOP_HEADERFILES_H
#pragma once

#define _stprintf
#define _CRT_SECURE_NO_WARNINGS


#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
#include<ctime>
#include<cstring>
#include<sstream>
#include<iomanip>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<random>
#include<windows.h>
#include<graphics.h>
#include<functional>
#include<conio.h>


namespace myBarberShop
{
    using Rank = unsigned int;

    using std::queue;
    using std::vector;
    using std::string;
    using std::wstring;
    using std::function;
    using std::ofstream;
    using std::ifstream;
    using std::stringstream;
    using std::ios;
    using std::cout;
    using std::cin;
    using std::cerr;
    using std::endl;


    template<typename eleType>
    struct QNode
    {
        using Node = QNode<eleType>;
        eleType data;
        Node* next;

        explicit QNode(const eleType& elem = 0, Node* n = nullptr) : data(elem), next(n){}

        void setData(const eleType& elem)
        {
            this->data = elem;
        }
    };


    template<typename eleType>
    class myQueue
    {
        using Node = QNode<eleType>;
    private:
        //队列大小
        Rank _size;
        //队首指针,出队
        Node* _front;
        //队尾指针，入队
        Node* _rear;
    public:
        myQueue() : _size(0), _front(nullptr), _rear(nullptr){}

        ~myQueue()
        {
            while(_front)
            {
                Node* node = _front;
                _front = _front->next;
                delete node;
            }
            this->size = 0;
        }

    public:
        Node& front()
        {
            return &this->_front;
        }

        [[nodiscard("no use return")]] size_t size() const noexcept
        {
            return this->_size;
        }

        [[nodiscard("no use return")]] bool empty() const noexcept
        {
            return this->_size == 0;
        }

    public:
        void pop() {
            if (empty()) {
                cerr << "ERROR! Empty Queue" << endl;
            } else {
                Node *temp = _front;
                _front = _front->next;
                delete temp;
                if (_front == nullptr) {
                    _rear = nullptr;
                }
            }
        }


        void push(const eleType& elem)
        {
            if(empty())
            {
                _front = _rear = new myQueue<eleType>(elem);
            }
            else
            {
                Node* node = new Node(elem);
                _rear->next = node;
                _rear = node;
            }
            this->_size++;
        }
    };



    //默认理发店总的椅子数为8把
    const Rank DEFAULT_CHAIRS = 8;
    //默认理发师人数
    const Rank DEFAULT_BARBERS = 8;


    //时间单位均默认为分钟

    //默认理发店营业时间：14小时，即为22点打烊
    const Rank DEFAULT_SERVICE_TIME = 14*60;

    //不同等级的理发师收费/分钟,等级从1开始到3，则该数组只有1-3号数据有效
    const double fees[4] = {0, 1, 1.5,2};


     //理发师等级
     enum barberLevel{
        FIRST_LEVEL = 1,//一级理发师
        SECOND_LEVEL = 2,//二级理发师
        THIRD_LEVEL = 3//三级理发师
    };



     //加入的顾客状态（GONE：离开（表示加入成功）；WAITING：等待中；HAIRCUTTING：理发中）
     using customerStatus = enum{GONE, WAITING, HAIRCUTTING};


     //全局barbers数组，方便获取其对应编号的barberLevel
     barberLevel bLevel[DEFAULT_BARBERS];


    //椅子判空数组（当理发师使用对应秩的椅子时，即变为占用）
    Rank emptyChairs[myBarberShop::DEFAULT_CHAIRS];


   //实现生成随机数的函数
   //指定需要生成的随机数的范围[start, end]
    Rank generateRandomNumber(Rank start, Rank end)
    {
        // 使用随机设备作为种子
        std::random_device rd;
        // 使用 Mersenne Twister 算法作为随机数引擎
        std::mt19937 gen(rd());
        // 定义随机数分布
        std::uniform_int_distribution<Rank> dis(start, end);

        // 生成随机数
        return dis(gen);
    }


    //当前理发师结束上一个顾客服务的时间表
    Rank busyBarber[DEFAULT_BARBERS];


    //生成随机枚举值
    barberLevel randomBarberLevel()
    {
        // 使用随机设备作为种子
        std::random_device rd;
        // 使用 Mersenne Twister 算法作为随机数引擎
        std::mt19937 gen(rd());
        // 定义随机数分布，范围在 0 到 2 之间
        std::uniform_int_distribution<> dis(1, 3);

        return static_cast<barberLevel>(dis(gen));
    }


    struct selection
    {
        //选择的理发师id

        myBarberShop::barberLevel choseLevel;

        selection()
        {
            Rank level = myBarberShop::randomBarberLevel();
            switch(level)
            {
                case 1:
                    this->choseLevel = barberLevel::FIRST_LEVEL;
                    break;
                case 2:
                    this->choseLevel = barberLevel::SECOND_LEVEL;
                    break;
                case 3:
                    this->choseLevel = barberLevel::THIRD_LEVEL;
                    break;
                default:
                    cout << "error" << endl;
                    break;
            }
        }
    };


    class Button
    {
    private:
        int x; // 按钮左上角x坐标
        int y; // 按钮左上角y坐标
        int width; // 按钮宽度
        int height; // 按钮高度
        float scale; // 缩放比例，用于实现鼠标悬停效果
        bool isMouseOver; // 表示鼠标是否在按钮上方
        LPCTSTR text; // 按钮文本
        function<void()> onClick; // 点击按钮触发的函数

    public:

        Button(int x, int y, int width, int height, LPCTSTR text, const function<void()>& onClick)
                : x(x), y(y), width(width), height(height), text(text), onClick(onClick), scale(1.0f), isMouseOver(false)
        {
        }

        // 检查鼠标是否在按钮上方
        void checkMouseOver(int mouseX, int mouseY)
        {
            isMouseOver = (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);

            if (isMouseOver) {
                scale = 0.9f; // 鼠标悬停时缩放按钮
            }
            else {
                scale = 1.0f; // 恢复按钮原始大小
            }
        }

        // 检查鼠标点击是否在按钮内，并执行函数
        bool checkClick(int mouseX, int mouseY)
        {
            if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
            {
                onClick(); // 执行按钮点击时的函数
                isMouseOver = false;
                scale = 1.0f;
                return true;
            }
            return false;
        }

        // 绘制按钮
        void draw()
        {
            int scaledWidth = width * scale; // 缩放后的按钮宽度
            int scaledHeight = height * scale; // 缩放后的按钮高度
            int scaledX = x + (width - scaledWidth) / 2; // 缩放后的按钮x坐标
            int scaledY = y + (height - scaledHeight) / 2; // 缩放后的按钮y坐标

            if (isMouseOver)
            {
                setlinecolor(RGB(0, 120, 215)); // 鼠标悬停时按钮边框颜色
                setfillcolor(RGB(229, 241, 251)); // 鼠标悬停时按钮填充颜色

            }
            else
            {
                setlinecolor(RGB(173, 173, 173)); // 按钮边框颜色
                setfillcolor(RGB(225, 225, 225)); // 按钮填充颜色
            }

            fillrectangle(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight); // 绘制按钮
            settextcolor(BLACK); // 设置文本颜色为黑色
            setbkmode(TRANSPARENT); // 设置文本背景透明
            settextstyle(20 * scale, 5, _T("宋体")); // 设置文本大小和字体
            //居中显示按钮文本
            int textX = scaledX + (scaledWidth - textwidth(text)) / 2; // 计算文本在按钮中央的x坐标
            int textY = scaledY + (scaledHeight - textheight(_T("宋体"))) / 2; // 计算文本在按钮中央的y坐标
            outtextxy(textX, textY, text); // 在按钮上绘制文本
        }
    };

// 定义Widget类，表示一个简单的图形用户界面
    class Widget {
    public:
        int width; // 宽度
        int height; // 高度
        int currentIndex; // 当前页面索引
        vector<IMAGE *> pages; // 存储所有页面的图片指针
        vector<vector<Button *>> buttons; // 存储每个页面上的按钮

        // 添加一个页面
        void addPage(IMAGE *page) {
            pages.push_back(page);
            buttons.push_back({});
        }

        // 在指定页面上添加一个按钮
        void addButton(int index, Button *button) {
            if (index >= 0 && index < buttons.size()) {
                buttons[index].push_back(button);
            }
        }

        // 设置当前显示的页面索引
        void setCurrentIndex(int index) {
            if (index >= 0 && index < pages.size()) {
                currentIndex = index;
            }
        }

        // 处理鼠标点击事件
        void mouseClick(int mouseX, int mouseY) {
            if (currentIndex >= 0 && currentIndex < buttons.size()) {
                for (Button *button: buttons[currentIndex]) {
                    if (button->checkClick(mouseX, mouseY)) {
                        break;
                    }
                }
            }
        }

        // 处理鼠标移动事件
        void mouseMove(int mouseX, int mouseY) {
            if (currentIndex >= 0 && currentIndex < buttons.size()) {
                for (Button *button: buttons[currentIndex]) {
                    button->checkMouseOver(mouseX, mouseY);
                }
            }
        }

        // 绘制当前页面的内容
        void draw() {
            if (currentIndex >= 0 && currentIndex < pages.size()) {
                putimage(0, 0, pages[currentIndex]); // 在窗口中绘制当前页面的图片

                if (currentIndex >= 0 && currentIndex < buttons.size()) {
                    for (Button *button: buttons[currentIndex]) {
                        button->draw(); // 绘制当前页面上的所有按钮
                    }
                }
            }
        }

    public:
        Widget(int width, int height)
                : width(width), height(height), currentIndex(-1) {
        }


        ~Widget()  = default;


        void init()
        {
            auto image1 = new IMAGE;
            initgraph(800, 600);

            loadimage(image1, "..\\image\\main.jpg", 800, 600);
            putimage(0, 0, image1);
            getimage(image1, 0, 0, width, height); // 将页面1的内容保存到图片中

            addPage(image1);

            LPCTSTR str ="Begin simulating";
            auto button1_1 = new Button(400, 500, 200, 50, str, [&]() {
                setCurrentIndex(1); // 点击按钮1时，切换到页面2"开始模拟"
            });
            addButton(0, button1_1); // 将按钮1添加到页面1

            //将初始化页面置为第一页
            setCurrentIndex(0);

        }

        // 运行，进入消息循环
        void run()
        {
            ExMessage msg;

            BeginBatchDraw(); // 开始批量绘制

            while (true)
            {
                if (peekmessage(&msg)) // 检查是否有消息
                {
                    int mouseX = msg.x; // 获取鼠标x坐标
                    int mouseY = msg.y; // 获取鼠标y坐标

                    switch (msg.message)
                    {
                        case WM_LBUTTONDOWN: // 鼠标左键按下事件
                            mouseClick(mouseX, mouseY); // 处理鼠标点击事件
                            break;
                        case WM_MOUSEMOVE: // 鼠标移动事件
                            mouseMove(mouseX, mouseY); // 处理鼠标移动事件
                            break;
                    }
                }

                draw(); // 绘制当前页面内容
                FlushBatchDraw(); // 将缓冲区内容显示在屏幕上
                Sleep(10);
            }

            EndBatchDraw(); // 结束批量绘制
        }

        // 关闭
        static void close()
        {
            closegraph(); // 关闭图形环境
        }


    };


}


#endif //BARBERSHOP_HEADERFILES_H
