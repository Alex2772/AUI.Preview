//
// Created by alex2 on 6/24/2021.
//

#pragma once

#include "converter.h"

namespace aui::preview {

    template<>
    struct converter<std::nullptr_t> {
        static std::nullptr_t from_vm(const _<ExpressionNode>& n) {
            class NullptrVisitor: public INodeVisitor {
            private:
                bool mIsValid = false;

            public:
                void visitNode(const NullptrNode& node) override {
                    INodeVisitor::visitNode(node);
                    mIsValid = true;
                }

                void visitNode(const ImplicitInitializerListCtorNode& node) override {
                    INodeVisitor::visitNode(node);
                    if (node.getElements().size() == 0) {
                        mIsValid = true;
                    }
                }

                [[nodiscard]]
                std::nullptr_t getValue() const {
                    if (mIsValid) {
                        return nullptr;
                    }
                    throw AException("not a nullptr");
                }
            } v;
            n->acceptVisitor(v);
            return v.getValue();
        }
    };
}