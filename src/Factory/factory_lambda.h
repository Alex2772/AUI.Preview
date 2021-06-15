//
// Created by alex2 on 6/16/2021.
//

#pragma once

template<typename Lambda>
class factory_lambda: public IFactory {
private:
    Lambda mLambda;

public:
    factory_lambda(const Lambda& lambda) : mLambda(lambda) {}

    _<AObject> create(const AVector<_<ExpressionNode>>& args) override {
        return (_<AObject>)mLambda();
    }

    AString getTypeName() override {
        return AClass<decltype(mLambda())::stored_t>::name();
    }
};