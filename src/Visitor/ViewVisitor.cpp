//
// Created by alex2 on 6/17/2021.
//

#include <Factory/FactoryRegistry.h>
#include <AUI/Autumn/Autumn.h>
#include <AUI/Logging/ALogger.h>
#include <AUI/View/ALabel.h>
#include <AUI/Util/UIBuildingHelpers.h>
#include "ViewVisitor.h"
#include "StringVisitor.h"
#include "ContainerListVisitor.h"
#include "Replicator.h"
#include <AUI/Traits/strings.h>

void ViewVisitor::visitNode(const LShiftOperatorNode& node) {
    try {
        StringVisitor c;
        node.getRight()->acceptVisitor(c);
        auto assName = c.getString();
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
}

void ViewVisitor::visitNode(const AssignmentOperatorNode& node) {
    node.getRight()->acceptVisitor(*this);
}

void ViewVisitor::visitNode(const TemplateOperatorCallNode& node) {
    if (node.getCallee() == "_new") {
        assert(mView == nullptr);

        try {
            mView = _cast<AView>(Autumn::get<FactoryRegistry>()->create(node.getTemplateArg(), node.getArgs()));
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
