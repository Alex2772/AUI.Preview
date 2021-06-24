//
// Created by alex2 on 6/23/2021.
//

#pragma once

#include "converter.h"
#include <type_traits>
#include <AUI/Reflect/AEnumerate.h>
#include <AUI/Reflect/AClass.h>

namespace aui::preview {
    template<typename enum_t>
    struct enum_converter {
        static_assert(std::is_enum_v<enum_t>, "please use enum for enum_converter");
        static ass::unset_wrap<enum_t> from_vm(const _<ExpressionNode>& n) {

            class EnumVisitor: public INodeVisitor {
            private:
                AString mEnumValue;
                bool mIsValue = false;

            public:
                void visitNode(const StaticMemberAccessOperatorNode& node) override {
                    INodeVisitor::visitNode(node);


                    class IdentifierVisitor: public INodeVisitor {
                    private:
                        bool mIsValid = false;
                        AString mValue;

                    public:
                        void visitNode(const VariableReferenceNode& node) override {
                            mIsValid = true;
                            mValue = node.getVariableName();
                        }

                        [[nodiscard]]
                        const AString& getValue() const {
                            if (mIsValid) {
                                return mValue;
                            }
                            throw AException("not an identifier");
                        }
                    } v;

                    node.getLeft()->acceptVisitor(v);
                    const auto& enumName = v.getValue();
                    if (enumName != AClass<enum_t>::nameWithoutNamespace()) {
                        throw AException();
                    }
                    node.getRight()->acceptVisitor(v);
                    mEnumValue = v.getValue();
                    mIsValue = true;
                }

                [[nodiscard]]
                const AString& getEnumValue() const {
                    if (mIsValue) {
                        return mEnumValue;
                    }
                    throw AException("invalid enum");
                }
            } v;
            n->acceptVisitor(v);
            auto enumName = v.getEnumValue();
            if (auto c = AEnumerate<enum_t>::all().contains(enumName)) {
                return c->second;
            }
            throw AException("enum {} does not have value {}"_as.format(AClass<enum_t>::name(), enumName));
        }
    };
}