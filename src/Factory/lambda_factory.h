//
// Created by alex2 on 6/20/2021.
//

#pragma once

#include "object_factory.h"

template<typename Lambda>
class factory_lambda: public IObjectFactory {
private:
    Lambda mLambda;

public:
    factory_lambda(const Lambda& lambda) : mLambda(lambda) {}

    _<AObject> create(const AVector<_<ExpressionNode>>& args) override {
        return (_<AObject>)mLambda();
    }

    bool isApplicable(const AVector<_<ExpressionNode>>& args) override {
        return true;
    }

    AString getTypeName() override {
        return AClass<typename decltype(mLambda())::stored_t>::name();
    }
};