//
// Created by alex2 on 6/15/2021.
//

#pragma once


#include "IFactory.h"

#include <Converter/converter.h>
#include <tuple>
#include <AUI/Common/SharedPtrTypes.h>
#include <AUI/Reflect/AClass.h>

template<typename T>
class factory: public IFactory {
public:

public:
    _<AObject> create(const AVector<_<ExpressionNode>>& args) override {
        return _new<T>();
    }

    AString getTypeName() override {
        return AClass<T>::name();
    }

    template<typename... Args>
    class with_args : public IFactory {
    private:

        template<unsigned i, typename FArg, typename... FArgs>
        void fill_storage(std::tuple<Args...>& storage, const AVector<_<ExpressionNode>>& args) {
            std::get<i>(storage) = aui::preview::converter<FArg>::from_vm(args.at(i));
            fill_storage<i + 1, FArgs...>(storage, args);
        }

        template<unsigned i>
        void fill_storage(std::tuple<Args...>& storage, const AVector<_<ExpressionNode>>& args) {}

    public:

        AString getTypeName() override {
            return AClass<T>::name();
        }

        _<AObject> create(const AVector<_<ExpressionNode>>& args) override {
            std::tuple<Args...> storage;
            fill_storage<0, Args...>(storage, args);
            //return _new<T>(aui::preview::converter<Args>::from_vm(args[0])...);
            return std::apply([](Args... args) { return (_<AObject>)_new<T>(std::forward<Args>(args)...); }, storage);
        }
    };
};