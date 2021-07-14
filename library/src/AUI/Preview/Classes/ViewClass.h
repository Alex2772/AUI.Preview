//
// Created by alex2 on 6/28/2021.
//

#pragma once

#include "ClassDescriptor.h"
#include <AUI/Preview/Cpp/Runtime/Class.h>
#include <AUI/View/AView.h>
#include <AUI/View/AButton.h>

template<>
struct class_descriptor<AView>: Runtime::Class<AView>, Runtime::IClass {
public:
    class_descriptor();
    ~class_descriptor() override = default;
};

template<typename T>
struct view_class_descriptor: class_descriptor<AView>, Runtime::Class<T> {
public:
    view_class_descriptor() = default;
    ~view_class_descriptor() override = default;
};


template <>
struct class_descriptor<AButton>: view_class_descriptor<AButton> {};

template <>
struct class_descriptor<ALabel>: view_class_descriptor<ALabel> {};

