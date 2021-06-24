//
// Created by alex2 on 6/15/2021.
//

#pragma once


#include <Converter/converter.h>
#include <tuple>
#include <AUI/Common/SharedPtrTypes.h>
#include <AUI/Reflect/AClass.h>

using IObjectFactory = IFactory<AObject>;

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

    template<typename... Args>
    class with_args : public IObjectFactory {
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
            return AClass<T>::name();
        }

        _<AObject> create(const AVector<_<ExpressionNode>>& args) override {
            std::tuple<Args...> storage;
            fill_storage<0, Args...>(storage, args);
            //return _new<T>(aui::preview::converter<Args>::from_vm(args[0])...);
            return (std::apply)([](Args... args) { return (_<AObject>)_new<T>(std::forward<Args>(args)...); }, storage);
        }
    };
};