//
// Created by alex2 on 6/24/2021.
//

#pragma once

#include <AUI/Image/AImageLoaderRegistry.h>
#include "converter.h"

namespace aui::preview {

    template<>
    struct converter<_<AImage>> {
        static _<AImage> from_vm(const _<ExpressionNode>& n) {
            /**
             * Parses AImageLoaderRegistry::inst().loadImage(...)
             */

            class ImageVisitor: public INodeVisitor {
            private:
                _<AImage> mValue;

            public:
                void visitNode(const MemberAccessOperatorNode& node) override {
                    INodeVisitor::visitNode(node);

                    node.getRight()->acceptVisitor(*this);
                }

                /**
                 * loadImage or AUrl
                 * @param node
                 */
                void visitNode(const OperatorCallNode& node) override {
                    if (node.getCallee() == "loadImage") {
                        if (node.getArgs().size() == 1) {
                            node.getArgs().first()->acceptVisitor(*this);
                        }
                    } else if (node.getCallee() == "AUrl") {
                        if (node.getArgs().size() == 1) {
                            StringVisitor s;
                            node.getArgs().first()->acceptVisitor(s);
                            if (s.getValue()) {
                                // FIXME AImageLoaderRegistry
                                //mValue = AImageLoaderRegistry::inst().loadImage(ConversionHelper::remapUrl(*s.getValue()));
                            }
                        }
                    }
                }

                const _<AImage>& getValue() const {
                    return mValue;
                }

            };
            ImageVisitor v;
            n->acceptVisitor(v);
            return v.getValue();
        }
    };
}