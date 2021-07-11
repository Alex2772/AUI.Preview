//
// Created by alex2 on 6/24/2021.
//

#pragma once

#include <AUI/Preview/Cpp/Runtime/Context.h>
#include "converter.h"

namespace aui::preview {

    template<typename T>
    struct converter<_<T>> {
        static _<T> from_vm(const _<ExpressionNode>& n) {
            class Visitor: public INodeVisitor {
            private:
                bool mIsValid = false;
                _<T> mValue;

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

                void visitNode(const VariableReferenceNode& node) override {
                    INodeVisitor::visitNode(node);
                    auto variable = Autumn::get<Runtime::Context>()->getLocalVariable(node.getVariableName());
                    if (variable) {
                        if (variable->getValue() == nullptr) {
                            mIsValid = true;
                        } else {
                            mValue = _cast<T>(variable->getValue());
                            if (!mValue) {
                                throw AException("invalid type");
                            }
                            mIsValid = true;
                        }
                    }
                }

                [[nodiscard]]
                _<T> getValue() const {
                    if (mIsValid) {
                        return mValue;
                    }
                    throw AException("not a shared_ptr value");
                }
            } v;
            n->acceptVisitor(v);
            return v.getValue();
        }
    };
}