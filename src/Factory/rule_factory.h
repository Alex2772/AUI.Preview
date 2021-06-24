//
// Created by alex2 on 6/19/2021.
//

#pragma once

#include "IFactory.h"

#include <Converter/converter.h>
#include <tuple>
#include <AUI/Common/SharedPtrTypes.h>
#include <AUI/Reflect/AClass.h>
#include <AUI/ASS/ASS.h>

template<typename T>
class rule_factory {
public:

    template<typename... Args>
    class with_args : public IFactory<ass::decl::IDeclarationBase> {
    private:

        template<unsigned i, typename FArg, typename... FArgs>
        void fill_storage(std::tuple<Args...>& storage, const AVector<_<ExpressionNode>>& args) {
            std::get<i>(storage) = aui::preview::converter<FArg>::from_vm(args.at(i));
            fill_storage<i + 1, FArgs...>(storage, args);
        }

        template<unsigned i>
        void fill_storage(std::tuple<Args...>& storage, const AVector<_<ExpressionNode>>& args) {}

    public:
        bool isApplicable(const AVector<_<ExpressionNode>>& args) override {
            return args.size() == sizeof...(Args);
        }

        AString getTypeName() override {
            // substring ass::
            return AClass<T>::name().mid(5);
        }

        _<ass::decl::IDeclarationBase> create(const AVector<_<ExpressionNode>>& args) override {
            std::tuple<Args...> storage;
            fill_storage<0, Args...>(storage, args);
            //return _new<T>(aui::preview::converter<Args>::from_vm(args[0])...);
            return (std::apply)([](Args... args) {
                return (_<ass::decl::IDeclarationBase>)_new<ass::decl::Declaration<T>>(T{std::forward<Args>(args)...});
            }, storage);
        }
    };
};