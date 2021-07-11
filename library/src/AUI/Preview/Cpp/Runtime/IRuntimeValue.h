//
// Created by alex2 on 6/28/2021.
//

#pragma once

#include <AUI/Common/AVector.h>
#include <AUI/Preview/Cpp/AST/ExpressionNode.h>

class IRuntimeValue {
public:
    explicit Variable(const _<AObject>& value) : mValue(value) {}

    virtual const _<AObject>& getValue() const = 0;
    virtual void doCall(const AVector<_<ExpressionNode>>& args) = 0;
};


