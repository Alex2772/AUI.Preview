//
// Created by alex2 on 6/18/2021.
//

#include "StyleRuleBlockVisitor.h"
#include "SelectorVisitor.h"
#include "RuleVisitor.h"

AVector<_<ass::decl::IDeclarationBase>> StyleRuleBlockVisitor::ourDeclarationStorage;

void StyleRuleBlockVisitor::visitNode(const ImplicitInitializerListCtorNode& node) {
    INodeVisitor::visitNode(node);

    // the first element is a selector either implicit initializer list ctor or a single rule
    if (node.getElements().size() >= 2) {
        // selector
        {
            SelectorVisitor v;
            node.getElements().first()->acceptVisitor(v);
            mRule = std::make_unique<Rule>(std::move(v.getSelector()));
        }

        // the other elements are rules
        for (auto i = node.getElements().begin() + 1; i != node.getElements().end(); ++i) {
            RuleVisitor v;
            (*i)->acceptVisitor(v);
            if (auto rule = v.getRule()) {
                mRule->addDeclaration(rule.get());
                ourDeclarationStorage << rule;
            }
        }
    }
}
