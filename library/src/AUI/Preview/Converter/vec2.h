//
// Created by alex2 on 6/23/2021.
//

#pragma once

#include "converter.h"
#include <optional>
#include <glm/glm.hpp>

namespace aui::preview {
    template<glm::length_t S, typename T, glm::qualifier Q>
    struct converter<ass::unset_wrap<glm::vec<S, T, Q>>> {
        using vec_t = glm::vec<S, T, Q>;
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


    template<glm::length_t S, typename T, glm::qualifier Q>
    struct converter<glm::vec<S, T, Q>>: unset_wrap_converter<glm::vec<S, T, Q>> {};
}