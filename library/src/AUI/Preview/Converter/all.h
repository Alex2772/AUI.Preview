//
// Created by alex2 on 6/23/2021.
//

#pragma once

#include "converter.h"
#include "color.h"
#include "enum.h"
#include "metric.h"
#include "repeat.h"
#include "sizing.h"
#include "string.h"
#include "image.h"
#include "vec2.h"
#include "bool.h"
#include "int.h"
#include "nullptr.h"
#include "object.h"

namespace aui::preview {

    template<typename... Args>
    struct call_helper {
        std::tuple<Args...> storage;

    private:
        template<unsigned i, typename FArg, typename... FArgs>
        void fill_storage(const AVector<_<ExpressionNode>>& args) {
            std::get<i>(storage) = aui::preview::converter<FArg>::from_vm(args.at(i));
            fill_storage<i + 1, FArgs...>(args);
        }

        template<unsigned i>
        void fill_storage(const AVector<_<ExpressionNode>>& args) {}

    public:
        void feed(const AVector<_<ExpressionNode>>& args) {
            fill_storage<0, Args...>(args);
        }
    };
}