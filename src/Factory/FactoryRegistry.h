//
// Created by alex2 on 6/15/2021.
//

#pragma once


#include <AUI/Common/AString.h>
#include <AUI/Common/AMap.h>
#include "IFactory.h"
#include <AUI/Traits/iterators.h>

class FactoryRegistry {
private:
    AMap<AString, AVector<_unique<IFactory>>> mFactories;


public:
    void registerFactory(IFactory* factory);

    void registerFactory(const AVector<IFactory*>& factories) {
        for (auto& factory : factories) {
            registerFactory(factory);
        }
    }

    [[nodiscard]]
    const AVector<_unique<IFactory>>& getFactoriesForTypeName(const AString& typeName) {
        return mFactories.at(typeName);
    }

    [[nodiscard]]
    _<AObject> create(const AString& typeName, const AVector<_<ExpressionNode>>& args) {
        for (auto& f : aui::reverse_iterator_wrap(mFactories.at(typeName))) {
            try {
                return f->create(args);
            } catch (...) {

            }
        }
        return nullptr;
    }
};


