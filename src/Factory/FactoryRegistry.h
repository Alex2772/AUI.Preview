//
// Created by alex2 on 6/15/2021.
//

#pragma once


#include <AUI/Common/AString.h>
#include <AUI/Common/AMap.h>
#include "IFactory.h"

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
};


