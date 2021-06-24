//
// Created by alex2 on 6/24/2021.
//

#pragma once

#include "converter.h"

namespace aui::preview {

    template<>
    struct converter<bool> {
        static bool from_vm(const _<ExpressionNode>& n) {
            class BoolVisitor: public INodeVisitor {
            private:
                bool mValue;
                bool mIsValid = false;

            public:
                void visitNode(const BoolNode& node) override {
                    mValue = node.getValue();
                    mIsValid = true;
                }

                [[nodiscard]]
                bool getValue() const {
                    if (mIsValid) {
                        return mValue;
                    }
                    throw AException("not a boolean");
                }
            } v;
            n->acceptVisitor(v);
            return v.getValue();
        }
    };
}