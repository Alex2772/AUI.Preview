//
// Created by alex2 on 6/15/2021.
//

#pragma once

#include <Cpp/AST/ExpressionNode.h>
#include <AUI/Common/SharedPtrTypes.h>
#include <AUI/Common/AVector.h>


template<typename F>
class IFactory {
public:
    virtual _<F> create(const AVector<_<ExpressionNode>>& args) = 0;
    virtual bool isApplicable(const AVector<_<ExpressionNode>>& args) = 0;
    virtual AString getTypeName() = 0;
};