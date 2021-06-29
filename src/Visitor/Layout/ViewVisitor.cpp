//
// Created by alex2 on 6/17/2021.
//

#include <Factory/FactoryRegistry.h>
#include <AUI/Autumn/Autumn.h>
#include <AUI/Logging/ALogger.h>
#include <AUI/View/ALabel.h>
#include <AUI/Util/UIBuildingHelpers.h>
#include "ViewVisitor.h"
#include "Visitor/StringVisitor.h"
#include "ContainerListVisitor.h"
#include "Visitor/Replicator.h"
#include <AUI/Traits/strings.h>
#include <Visitor/Style/RuleVisitor.h>
#include <Visitor/Style/StyleRuleBlockVisitor.h>
#include <Cpp/Runtime/Context.h>

void ViewVisitor::visitNode(const LShiftOperatorNode& node) {
    try {
        StringVisitor c;
        node.getRight()->acceptVisitor(c);
        auto assName = *c.getValue();
        node.getLeft()->acceptVisitor(*this);
        if (mView != nullptr) {
            mView << assName;
        }
    } catch (...) {}
}

void ViewVisitor::visitNode(const MemberAccessOperatorNode& node) {
    node.getLeft()->acceptVisitor(*this);
}

void ViewVisitor::visitNode(const ALetOperatorNode& node) {
    node.getTarget()->acceptVisitor(*this);

    //RuntimeContext::PushLocal it("it", Variable(mView));
}

void ViewVisitor::visitNode(const AssignmentOperatorNode& node) {
    node.getRight()->acceptVisitor(*this);
}

void ViewVisitor::visitNode(const TemplateOperatorCallNode& node) {
    if (node.getCallee() == "_new") {
        assert(mView == nullptr);

        try {
            mView = _cast<AView>(Autumn::get<FactoryRegistry<AObject>>()->create(node.getTemplateArg(), node.getArgs()));
        } catch (...) {

        }
    } else if (node.getCallee() == "_container") {
        assert(mView == nullptr);

        try {
            ContainerListVisitor v;
            v.getContainer()->setLayout(Replicator::layout(node.getTemplateArg()));
            mView = v.getContainer();

            if (node.getArgs().size() == 1) {
                node.getArgs().first()->acceptVisitor(v);
            }
        } catch (...) {

        }
    }
    if (mView == nullptr) {
        ALogger::warn(":{} Replicate error for {}"_as.format(node.getLineNumber(), node.getTemplateArg()));
        mView = _new<ALabel>("<:{} replicate error {}>"_as.format(node.getLineNumber(), node.getTemplateArg()));
    }
}

void ViewVisitor::visitNode(const ExplicitInitializerListCtorNode& node) {
    assert(mView == nullptr);
    _<AViewContainer> view;
    if (node.getClassName() == "Stacked") {
        view = Stacked{};
    } else if (node.getClassName() == "Vertical") {
        view = Vertical{};
    } else if (node.getClassName() == "Horizontal") {
        view = Horizontal{};
    } else {
        return;
    }

    for (auto& x : node.getArgs()) {
        ViewVisitor v;
        x->acceptVisitor(v);
        if (v.getView()) {
            view->addView(v.getView());
        }
    }
    mView = view;
}

void ViewVisitor::visitNode(const AWithStyleOperatorNode& node) {
    INodeVisitor::visitNode(node);
    node.getTarget()->acceptVisitor(*this);
    if (mView) {
        for (auto& i : node.getArgs()) {
            RuleVisitor v;
            i->acceptVisitor(v);
            RuleWithoutSelector r;
            if (auto rule = v.getRule()) {
                r.addDeclaration(rule.get());
                StyleRuleBlockVisitor::ourDeclarationStorage << rule;
                mView->setCustomAss(r);
            }
        }
    }
}
