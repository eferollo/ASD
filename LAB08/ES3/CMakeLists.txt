cmake_minimum_required(VERSION 3.24)
project(ES3 C)

set(CMAKE_C_STANDARD 17)

add_executable(ES3 main.c TitleSet.c TitleSet.h DailyQuotation.c DailyQuotation.h Title.c Title.h DailyQuotationSet.c DailyQuotationSet.h DateTime.c DateTime.h)
