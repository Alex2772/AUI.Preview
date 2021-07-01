//
// Created by alex2 on 6/23/2021.
//

#pragma once

#include "converter.h"
#include <optional>

namespace aui::preview {
    template<unsigned S, typename T>
    struct converter<ass::unset_wrap<glm::vec<S, T>>> {
        using vec_t = glm::vec<S, T>;
        static ass::unset_wrap<vec_t> from_vm(const _<ExpressionNode>& n) {
            class VecVisitor: public INodeVisitor {
            private:
                std::optional<vec_t> mValue;

            public:
                void visitNode(const ImplicitInitializerListCtorNode& node) override {
                    INodeVisitor::visitNode(node);
                    try {
                        if (node.getElements().size() == S) {
                            vec_t v;
                            for (unsigned i = 0; i < S; ++i) {
                                v[i] = aui::preview::converter<T>::from_vm(node.getElements()[i]);
                            }
                            mValue = v;
                        }
                    } catch (...) {}
                }
                const std::optional<vec_t>& getValue() const {
                    return mValue;
                }
            } v;

            n->acceptVisitor(v);
            if (v.getValue()) {
                return *v.getValue();
            }
            return {};
        }
    };


    template<unsigned S, typename T>
    struct converter<glm::vec<S, T>>: unset_wrap_converter<glm::vec<S, T>> {};
}