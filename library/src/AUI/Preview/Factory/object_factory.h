//
// Created by alex2 on 6/15/2021.
//

#pragma once


#include <AUI/Preview/Converter/converter.h>
#include <tuple>
#include <AUI/Common/SharedPtrTypes.h>
#include <AUI/Reflect/AClass.h>
#include <AUI/Preview/Converter/all.h>
#include <AUI/Preview/Cpp/Runtime/IType.h>
#include <AUI/Preview/Classes/GetClassDescriptor.h>


template<typename T>
class object_factory: public IObjectFactory {
public:

public:
    _<AObject> create(const AVector<_<ExpressionNode>>& args) override {
        return _new<T>();
    }

    AString getTypeName() override {
        return AClass<T>::name();
    }

    bool isApplicable(const AVector<_<ExpressionNode>>& args) override {
        return args.empty();
    }

    Runtime::IType& getType() override {
        return get_class_descriptor<T>();
    }

    template<typename... Args>
    class with_args : public IObjectFactory {
    public:

        bool isApplicable(const AVector<_<ExpressionNode>>& args) override {
            return args.size() == sizeof...(Args);
        }

        AString getTypeName() override {
            return AClass<T>::name();
        }

        Runtime::IType& getType() override {
            return get_class_descriptor<T>();
        }

        _<AObject> create(const AVector<_<ExpressionNode>>& args) override {
            aui::preview::call_helper<Args...> h;
            h.feed(args);

            //return _new<T>(aui::preview::converter<Args>::from_vm(args[0])...);
            return (std::apply)([](Args... args) { return (_<AObject>)_new<T>(std::forward<Args>(args)...); }, h.storage);
        }
    };
};