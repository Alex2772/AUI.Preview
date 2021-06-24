//
// Created by alex2 on 6/23/2021.
//

#pragma once

#include "converter.h"

namespace aui::preview {
    template<>
    struct converter<ass::unset_wrap<AColor>> {
        static ass::unset_wrap<AColor> from_vm(const _<ExpressionNode>& n) {
            class ColorVisitor: public UnsetWrapVisitor<AColor> {
            public:
                void visitNode(const OperatorLiteralNode& node) override {
                    bool isAlpha = false;
                    if (node.getLiteralName() == "_rgb") {

                    } else if (node.getLiteralName() == "_argb") {
                        isAlpha = true;
                    } else {
                        throw AException("invalid literal for AColor: {}"_as.format(node.getLiteralName()));
                    }

                    class NumberVisitor: public INodeVisitor {
                    private:
                        unsigned mNumber;
                        bool mIsValid = false;

                    public:
                        void visitNode(const NumberNode& node) override {
                            mNumber = node.getNumber();
                            mIsValid = true;
                        }

                        [[nodiscard]]
                        unsigned int getNumber() const {
                            if (mIsValid) {
                                return mNumber;
                            }
                            throw AException("a color literal is applicable only to integers");
                        }
                    } v;
                    node.getChild()->acceptVisitor(v);

                    unsigned colorValue = v.getNumber();
                    if (isAlpha) {
                        mValue = operator ""_argb(colorValue);
                    } else {
                        mValue = operator ""_rgb(colorValue);
                    }
                    mIsValid = true;
                }
            } v;
            n->acceptVisitor(v);
            return v.getValue();
        }
    };

    template<>
    struct converter<AColor>: unset_wrap_converter<AColor> {};
}