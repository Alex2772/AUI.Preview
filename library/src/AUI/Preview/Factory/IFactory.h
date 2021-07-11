//
// Created by alex2 on 6/15/2021.
//

#pragma once

#include <AUI/Preview/Cpp/AST/ExpressionNode.h>
#include <AUI/Common/SharedPtrTypes.h>
#include <AUI/Common/AVector.h>
#include <AUI/Preview/Cpp/Runtime/IType.h>

template<typename F>
class IFactory {
public:
    virtual _<F> create(const AVector<_<ExpressionNode>>& args) = 0;
    virtual bool isApplicable(const AVector<_<ExpressionNode>>& args) = 0;
    virtual AString getTypeName() = 0;
};

template<>
class IFactory<AObject> {
public:
    virtual _<AObject> create(const AVector<_<ExpressionNode>>& args) = 0;
    virtual bool isApplicable(const AVector<_<ExpressionNode>>& args) = 0;
    virtual AString getTypeName() = 0;
    virtual Runtime::IType& getType() = 0;
};

using IObjectFactory = IFactory<AObject>;