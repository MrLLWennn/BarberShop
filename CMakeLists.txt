cmake_minimum_required(VERSION 3.28)
project(barberShop)

set(CMAKE_CXX_STANDARD 17)

include_directories(./easyX/include)
link_directories(./easyX/lib64)
link_libraries(libeasyx.a)


add_executable(barberShop main.cpp
        Barber.h
        headerFiles.h
        Customer.h
        BarberShop.h
)