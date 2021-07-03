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
#include <Classes/Class.h>
#include <Util/ICustomViewName.h>
#include <Visitor/VariableReferenceVisitor.h>

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

    using namespace Runtime;
    Variable v(get_class_descriptor<AView>(), mView);
    Context::PushLocal it("it", v);
    Autumn::get<Context>()->executeCodeBlock(node.getCode());
}

void ViewVisitor::visitNode(const AssignmentOperatorNode& node) {
    node.getRight()->acceptVisitor(*this);
    VariableReferenceVisitor v;
    node.getLeft()->acceptVisitor(v);
    if (v.getName()) {
        if (mVariable) {
            Autumn::get<Runtime::Context>()->setLocalVariable(*v.getName(), *mVariable);
        }
    }
}

class ReplicateError: public ALabel, public ICustomViewName {
public:
    ReplicateError(const AString& text) : ALabel(text) {

    }

    ~ReplicateError() override {

    }

    bool consumesClick(const glm::ivec2& pos) override {
        return false;
    }

    AString getCustomViewName() override {
        return getText();
    }
};

void ViewVisitor::visitNode(const TemplateOperatorCallNode& node) {
    if (node.getCallee() == "_new") {
        assert(mView == nullptr);

        try {
            mVariable = Autumn::get<FactoryRegistry<AObject>>()->create(node.getTemplateArg(), node.getArgs());
            mView = _cast<AView>(mVariable->getValue());
        } catch (...) {

        }
    } else if (node.getCallee() == "_container") {
        assert(mView == nullptr);

        try {
            ContainerListVisitor v;
            v.getContainer()->setLayout(Replicator::layout(node.getTemplateArg()));
            mView = v.getContainer();

            mVariable = Runtime::Variable(get_class_descriptor<AViewContainer>(), mView);

            if (node.getArgs().size() == 1) {
                node.getArgs().first()->acceptVisitor(v);
            }
        } catch (...) {

        }
    }
    if (mView == nullptr) {
        ALogger::warn(":{} Replicate error for {}"_as.format(node.getLineNumber(), node.getTemplateArg()));
        mView = _new<ReplicateError>("<:{} {}>"_as.format(node.getLineNumber(), node.getTemplateArg()));
        mView->setCustomAss(TextAlign::CENTER);
        mView << "preview_" + node.getTemplateArg();
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
    mVariable = Runtime::Variable(get_class_descriptor<AViewContainer>(), view);
}

void ViewVisitor::visitNode(const AWithStyleOperatorNode& node) {
    INodeVisitor::visitNode(node);
    node.getTarget()->acceptVisitor(*this);
    if (mView) {
        Replicator::setCustomAss(mView.get(), node.getArgs());
    }
}

void ViewVisitor::visitNode(const VariableReferenceNode& node) {
    INodeVisitor::visitNode(node);
    auto var = Autumn::get<Runtime::Context>()->getLocalVariable(node.getVariableName());
    if (var) {
        if (auto view = _cast<AView>(var->getValue())) {
            mView = view;
            mVariable = var;
        } else {
            ALogger::warn(":{} variable '{}' is not an AView"_as.format(node.getLineNumber(), node.getVariableName()));
        }
    } else {
        ALogger::warn(":{} undefined variable '{}'"_as.format(node.getLineNumber(), node.getVariableName()));
    }
}
