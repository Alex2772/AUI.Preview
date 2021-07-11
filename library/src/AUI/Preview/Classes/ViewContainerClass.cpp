//
// Created by alex2 on 6/29/2021.
//

#include <AUI/Preview/Visitor/Layout/ViewVisitor.h>
#include <AUI/Preview/Visitor/Layout/LayoutVisitor.h>
#include <AUI/Preview/Visitor/Replicator.h>
#include "ViewContainerClass.h"


class_descriptor<AViewContainer>::class_descriptor() {
    registerFunction("setContents", [](const Runtime::CallArgs& args) {
        for (auto& x : args) {
            ViewVisitor uiBuilder;
            x->acceptVisitor(uiBuilder);
            if (auto container = _cast<AViewContainer>(uiBuilder.getView())) {
                //((LayoutVisitor::ViewContainer*)Class<AViewContainer>::runtimeThis())->setContents(container);
            }
        }
    });
    registerFunction("setLayout", [](const Runtime::CallArgs& args) {
        if (args.size() == 1) {
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
            args.first()->acceptVisitor(v);
            if (v.getNode()) {
                if (v.getNode()->getArgs().empty() && v.getNode()->getCallee() == "_new") {
                    auto layoutName = v.getNode()->getTemplateArg();
                    Class<AViewContainer>::runtimeThis()->setLayout(Replicator::layout(layoutName));
                }
            }
        }
    });
    registerFunction("addView", [](const Runtime::CallArgs& args) {
        if (args.size() == 1) {
            ViewVisitor v;
            args.first()->acceptVisitor(v);
            if (v.getView()) {
                Class<AViewContainer>::runtimeThis()->addView(v.getView());
            }
        }
    });
}
