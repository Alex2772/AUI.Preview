//
// Created by alex2 on 6/24/2021.
//

#pragma once

#include <AUI/Preview/Cpp/Parser.h>
#include <AUI/Preview/Model/Project.h>
#include "converter.h"

namespace aui::preview {

    template<>
    struct converter<ass::unset_wrap<int>> {
        static ass::unset_wrap<int> from_vm(const _<ExpressionNode>& n) {
            class NumberVisitor: public UnsetWrapVisitor<int> {

            public:
                void visitNode(const IntegerNode& node) override {
                    mValue = node.getNumber();
                    mIsValid = true;
                }

            } v;
            n->acceptVisitor(v);
            return v.getValue();
        }
    };


    template<>
    struct converter<int>: unset_wrap_converter<int> {};
}