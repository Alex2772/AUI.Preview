cmake_minimum_required(VERSION 3.14.4)

project(aui.preview.library)

aui_module(aui.preview.library)


aui_link(aui.preview.library PUBLIC aui.core aui.views aui.json)

aui_enable_tests(aui.preview.library)