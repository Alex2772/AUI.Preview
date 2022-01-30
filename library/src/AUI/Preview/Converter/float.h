//
// Created by alex2 on 6/24/2021.
//

#pragma once

#include <AUI/Preview/Cpp/Parser.h>
#include <AUI/Preview/Model/Project.h>
#include "converter.h"

namespace aui::preview {

    template<>
    struct converter<ass::unset_wrap<float>> {
        static ass::unset_wrap<float> from_vm(const _<ExpressionNode>& n) {
            class NumberVisitor: public UnsetWrapVisitor<float> {

            public:
                void visitNode(const FloatNode& node) override {
                    mValue = node.getNumber();
                    mIsValid = true;
                }


            } v;
            n->acceptVisitor(v);
            return v.getValue();
        }
    };


    template<>
    struct converter<float>: unset_wrap_converter<float> {};
}