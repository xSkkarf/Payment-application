cmake_minimum_required(VERSION 3.22)
project(Payment_application C)

set(CMAKE_C_STANDARD 99)

add_executable(Payment_application main.c App/App.c App/App.h Card/Card.c Card/Card.h Terminal/Terminal.c Terminal/Terminal.h Server/Server.h Server/Server.c)
