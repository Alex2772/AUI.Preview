cmake_minimum_required(VERSION 3.14.4)

project(AUI.Preview.Library)

aui_module(AUI.Preview.Library)


target_link_libraries(AUI.Preview.Library PRIVATE AUI.Core)
target_link_libraries(AUI.Preview.Library PRIVATE AUI.Views)
target_link_libraries(AUI.Preview.Library PRIVATE AUI.Json)
