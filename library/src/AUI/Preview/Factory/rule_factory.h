//
// Created by alex2 on 6/19/2021.
//

#pragma once

#include "IFactory.h"

#include <AUI/Preview/Converter/converter.h>
#include <tuple>
#include <AUI/Common/SharedPtrTypes.h>
#include <AUI/Reflect/AClass.h>
#include <AUI/ASS/ASS.h>
#include <AUI/Preview/Converter/all.h>

template<typename T>
class rule_factory {
public:

    template<typename... Args>
    class with_args : public IFactory<ass::decl::IDeclarationBase> {
    public:
        bool isApplicable(const AVector<_<ExpressionNode>>& args) override {
            return args.size() == sizeof...(Args);
        }

        AString getTypeName() override {
            // substring ass::
            auto name = AClass<T>::name();
            if (name.startsWith("ass::")) {
                return name.mid(5);
            }
            return name;
        }

        _<ass::decl::IDeclarationBase> create(const AVector<_<ExpressionNode>>& args) override {
            aui::preview::call_helper<Args...> h;
            h.feed(args);
            //return _new<T>(aui::preview::converter<Args>::from_vm(args[0])...);
            return (std::apply)([](Args... args) {
                return (_<ass::decl::IDeclarationBase>)_new<ass::decl::Declaration<T>>(T{std::forward<Args>(args)...});
            }, h.storage);
        }
    };

    template<typename FactoryFunction>
    class with_factory_function : public IFactory<ass::decl::IDeclarationBase> {
    private:
        AString mName;
        FactoryFunction mFactoryFunction;

    public:
        with_factory_function(AString name, FactoryFunction factoryFunction) :
            mName(std::move(name)),
            mFactoryFunction(std::move(factoryFunction)) {

        }

        bool isApplicable(const AVector<_<ExpressionNode>>& args) override {
            return args.empty();
        }

        AString getTypeName() override {
            // substring ass::
            auto name = AClass<T>::name() + "::" + mName;
            if (name.startsWith("ass::")) {
                return name.mid(5);
            }
            return name;
        }

        _<ass::decl::IDeclarationBase> create(const AVector<_<ExpressionNode>>& args) override {
            return _new<ass::decl::Declaration<T>>(mFactoryFunction());
        }
    };
    template<typename ConstantValue>
    class with_constant : public IFactory<ass::decl::IDeclarationBase> {
    private:
        AString mName;
        ConstantValue mConstantValue;

    public:
        with_constant(AString name, ConstantValue constantValue) :
            mName(std::move(name)),
            mConstantValue(std::move(constantValue)) {

        }

        bool isApplicable(const AVector<_<ExpressionNode>>& args) override {
            return args.empty();
        }

        AString getTypeName() override {
            // substring ass::
            auto name = AClass<T>::name() + "::" + mName;
            if (name.startsWith("ass::")) {
                return name.mid(5);
            }
            return name;
        }

        _<ass::decl::IDeclarationBase> create(const AVector<_<ExpressionNode>>& args) override {
            return _new<ass::decl::Declaration<T>>(mConstantValue);
        }
    };
};