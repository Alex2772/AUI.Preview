//
// Created by alex2 on 6/17/2021.
//

#include "StyleVisitor.h"
#include "StyleRuleBlockVisitor.h"

void StyleVisitor::visitNode(const StructClassDefinition& node) {
    for (auto& n : node.getNodes()) {
        n->acceptVisitor(*this);
    }
}

void StyleVisitor::visitNode(const ConstructorDeclarationNode& node) {
    for(auto& line : node.getCode()) {
        line->acceptVisitor(*this);
    }
}

void StyleVisitor::visitNode(const MemberAccessOperatorNode& node) {
    node.getRight()->acceptVisitor(*this);
}

void StyleVisitor::visitNode(const OperatorCallNode& node) {
    if (node.getArgs().size() == 1) {
        node.getArgs().first()->acceptVisitor(*this);
    }
}

void StyleVisitor::visitNode(const ImplicitInitializerListCtorNode& node) {
    INodeVisitor::visitNode(node);
    for (auto& block : node.getElements()) {
        StyleRuleBlockVisitor v;
        block->acceptVisitor(v);
    }
}
