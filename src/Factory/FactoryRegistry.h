//
// Created by alex2 on 6/15/2021.
//

#pragma once


#include <AUI/Common/AString.h>
#include <AUI/Common/AMap.h>
#include "IFactory.h"
#include <AUI/Traits/iterators.h>

template<typename F>
class FactoryRegistry {
private:
    AMap<AString, AVector<_unique<IFactory<F>>>> mFactories;


public:
    void registerFactory(IFactory<F>* factory) {
        auto typeName = factory->getTypeName();
        mFactories[typeName] << _unique<IFactory<F>>(factory);
    }

    void registerFactory(const AVector<IFactory<F>*>& factories) {
        for (auto& factory : factories) {
            registerFactory(factory);
        }
    }

    [[nodiscard]]
    const AVector<_unique<IFactory<F>>>& getFactoriesForTypeName(const AString& typeName) {
        return mFactories.at(typeName);
    }

    [[nodiscard]]
    _<F> create(const AString& typeName, const AVector<_<ExpressionNode>>& args) {
        try {
            for (auto& f : aui::reverse_iterator_wrap(mFactories.at(typeName))) {
                try {
                    if (f->isApplicable(args)) {
                        return f->create(args);
                    }
                } catch (...) {

                }
            }
        } catch (...) {}
        return nullptr;
    }
};


