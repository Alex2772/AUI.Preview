//
// Created by alex2 on 6/30/2021.
//

#pragma once

#include <AUI/Preview/Cpp/Runtime/Class.h>
#include <AUI/Preview/Cpp/Runtime/IClass.h>

template<class T>
struct class_descriptor: Runtime::Class<AObject>, Runtime::IClass {

};