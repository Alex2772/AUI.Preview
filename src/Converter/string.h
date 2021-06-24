//
// Created by alex2 on 6/24/2021.
//

#pragma once

#include <Cpp/Parser.h>
#include <Model/Project.h>
#include "converter.h"

namespace aui::preview {

    template<>
    struct converter<ass::unset_wrap<AString>> {
        static ass::unset_wrap<AString> from_vm(const _<ExpressionNode>& n) {
            StringVisitor v;
            n->acceptVisitor(v);
            auto str = *v.getValue();
            if (str.startsWith(':')) {
                // url; replace it
                auto projectRoot = Autumn::get<Project>()->getRoot();
                return "file://"_as + projectRoot["assets"][AString(str.begin() + 1, str.end())];
            }
            return str;
        }
    };


    template<>
    struct converter<AString>: unset_wrap_converter<AString> {};
}