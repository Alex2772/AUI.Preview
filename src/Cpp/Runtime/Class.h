//
// Created by alex2 on 6/28/2021.
//

#pragma once

#include <AUI/Autumn/Autumn.h>
#include "IClass.h"
#include "Context.h"
#include "Converter/all.h"
#include <AUI/Logging/ALogger.h>

namespace Runtime {

    template<typename T>
    class Class {
    private:

    protected:

        static T* runtimeThis() {
            AObject* obj = Autumn::get<Context>()->getCalleeThis()->getValue().get();
            if (!obj) {
                throw AException("this callee is null");
            }
            T* calleeObject = dynamic_cast<T*>(obj);
            if (!calleeObject) {
                throw AException("this callee is not a {}"_as.format(AClass<T>::name()));
            }
            return calleeObject;
        }

        template<typename... Args>
        Callable member(void(T::*member)(Args...)) {
            return [member](const CallArgs& args) {
                aui::preview::call_helper<std::decay_t<Args>...> h;
                h.feed(args);
                (std::apply)([&](Args&&... args) {(runtimeThis()->*member)(std::forward<Args>(args)...);}, h.storage);
            };
        }

    };

}
