//
// Created by alex2 on 6/18/2021.
//

#include <AUI/Logging/ALogger.h>
#include "StyleRuleBlockVisitor.h"
#include "SelectorVisitor.h"
#include "DeclarationVisitor.h"
#include "MyDeclarationWrapper.h"

// TODO remove this because it produces memory leak
AVector<_<ass::decl::IDeclarationBase>> StyleRuleBlockVisitor::ourDeclarationStorage;

void StyleRuleBlockVisitor::visitNode(const ImplicitInitializerListCtorNode& node) {
    INodeVisitor::visitNode(node);

    // the first element is a selector either implicit initializer list ctor or a single rule
    if (node.getElements().size() >= 2) {
        // selector
        try {
            SelectorVisitor v;
            node.getElements().first()->acceptVisitor(v);
            mRule = std::make_unique<Rule>(std::move(v.getSelector()));
        } catch (const AException& e) {
            ALogger::warn(e.getMessage());
            return;
        }

        // the other elements are declarations
        for (auto i = node.getElements().begin() + 1; i != node.getElements().end(); ++i) {
            DeclarationVisitor v;
            (*i)->acceptVisitor(v);
            if (auto rule = v.getDeclaration()) {
                auto wrapper = _new<MyDeclarationWrapper>(rule.get(), v.getNode());
                mRule->addDeclaration(wrapper.get());
                ourDeclarationStorage << wrapper;
                ourDeclarationStorage << rule;
            }
        }
    }
}
