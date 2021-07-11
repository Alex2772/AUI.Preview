//
// Created by alex2 on 6/15/2021.
//

#pragma once


#include <AUI/Common/AString.h>
#include <AUI/Common/AMap.h>
#include "IFactory.h"
#include <AUI/Traits/iterators.h>
#include <optional>
#include <AUI/Preview/Cpp/Runtime/Variable.h>

namespace impl {
    template<typename F>
    class FactoryRegistryWithoutCreate {
    protected:
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
    };
}

template<typename F>
class FactoryRegistry: public impl::FactoryRegistryWithoutCreate<F> {
public:
    [[nodiscard]]
    _<F> create(const AString& typeName, const AVector<_<ExpressionNode>>& args) {
        for (auto& f : aui::reverse_iterator_wrap(this->mFactories.at(typeName))) {
            try {
                if (f->isApplicable(args)) {
                    return f->create(args);
                }
            } catch (...) {

            }
        }
        return nullptr;
    }
};



template<>
class FactoryRegistry<AObject>: public impl::FactoryRegistryWithoutCreate<AObject> {
public:
    [[nodiscard]]
    std::optional<Runtime::Variable> create(const AString& typeName, const AVector<_<ExpressionNode>>& args) {
        for (auto& f : aui::reverse_iterator_wrap(this->mFactories.at(typeName))) {
            try {
                if (f->isApplicable(args)) {
                    return Runtime::Variable(f->getType(), f->create(args));
                }
            } catch (...) {

            }
        }
        return std::nullopt;
    }
};


