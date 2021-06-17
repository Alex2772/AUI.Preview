//
// Created by alex2 on 6/15/2021.
//

#include <AUI/View/AViewContainer.h>
#include <AUI/Util/UIBuildingHelpers.h>
#include <Factory/FactoryRegistry.h>
#include "LayoutVisitor.h"
#include "Replicator.h"
#include "ViewVisitor.h"


void LayoutVisitor::visitNode(const ConstructorDeclarationNode& node) {
    for (auto& n : node.getCode()) {
        n->acceptVisitor(this);
    }
}

void LayoutVisitor::visitNode(const OperatorCallNode& node) {
    if (node.getCallee() == "setContents") {
        for (auto& x : node.getArgs()) {
            ViewVisitor uiBuilder;
            x->acceptVisitor(&uiBuilder);
            if (auto container = _cast<AViewContainer>(uiBuilder.getView())) {
                mContainer->setContents(container);
            }
        }
    } else if (node.getCallee() == "setLayout") {
        if (node.getArgs().size() == 1) {
            class NewVisitor: public INodeVisitor {
            private:
                TemplateOperatorCallNode const* mNode = nullptr;
            public:
                void visitNode(const TemplateOperatorCallNode& node) override {
                    mNode = &node;
                }

                [[nodiscard]] const TemplateOperatorCallNode* getNode() const {
                    return mNode;
                }
            } v;
            node.getArgs().first()->acceptVisitor(&v);
            if (v.getNode()) {
                if (v.getNode()->getArgs().empty() && v.getNode()->getCallee() == "_new") {
                    auto layoutName = v.getNode()->getTemplateArg();
                    mContainer->setLayout(Replicator::layout(layoutName));
                }
            }
        }
    } else if (node.getCallee() == "addView") {
        if (node.getArgs().size() == 1) {
            ViewVisitor v;
            node.getArgs().first()->acceptVisitor(&v);
            if (v.getView()) {
                mContainer->addView(v.getView());
            }
        }
    }
}

LayoutVisitor::LayoutVisitor() {
    mContainer = _new<ViewContainer>();
}
