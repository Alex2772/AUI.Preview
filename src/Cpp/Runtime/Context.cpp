//
// Created by alex2 on 6/28/2021.
//

#include <AUI/Autumn/Autumn.h>
#include <AUI/Logging/ALogger.h>
#include "Context.h"
#include <Cpp/Runtime/Class.h>
#include <Factory/FactoryRegistry.h>
#include <Visitor/VariableReferenceVisitor.h>

using namespace Runtime;

std::optional<Variable> Context::setLocalVariable(const AString& name, const Variable& v) {
    if (auto c = mLocalVariables.contains(name)) {
        Variable previous = c->second;
        c->second = v;
        return previous;
    }
    mLocalVariables.insert_or_assign(name, v);
    return std::nullopt;
}

void Context::executeCodeBlock(const AVector<_<INode>>& codeBlock) {
    for (auto& x : codeBlock) {
        x->acceptVisitor(*this);
    }
}

void Context::visitNode(const OperatorCallNode& node) {
    // check for thiscall
    if (mCalleeThis) {
        doThisCall(node);
    }
}

void Context::visitNode(const MemberAccessOperatorNode& node) {
    INodeVisitor::visitNode(node);

    Variable* variable;
    {
        class VariableVisitor : public INodeVisitor {
        private:
            std::optional<AString> mName;

        public:
            void visitNode(const VariableReferenceNode& node) override {
                INodeVisitor::visitNode(node);
                mName = node.getVariableName();
            }

            const std::optional<AString>& getName() const {
                return mName;
            }
        } v;

        node.getLeft()->acceptVisitor(v);

        if (!v.getName()) {
            ALogger::warn(":{} invalid token to the left of member access"_as.format(node.getLineNumber()));
            return;
        }
        if (auto c = mLocalVariables.contains(*v.getName())) {
            variable = &c->second;
        } else {
            ALogger::warn(":{} undeclared variable '{}'"_as.format(node.getLineNumber(), *v.getName()));
            return;
        }
    }

    {
        class AccessVisitor : public INodeVisitor {
        private:
            std::optional<OperatorCallNode> mCall;

        public:
            void visitNode(const OperatorCallNode& node) override {
                INodeVisitor::visitNode(node);
                mCall = node;
            }

            const std::optional<OperatorCallNode>& getCall() const {
                return mCall;
            }
        } v;
        node.getRight()->acceptVisitor(v);



        if (auto call = v.getCall()) {
            PushThis t(variable);
            doThisCall(*call);
        }
    }
}

bool Context::doThisCall(const OperatorCallNode& call) {
    try {
        auto callee = mCalleeThis->getType()->asClass()->getFunction(call.getCallee());
        try {
            callee(call.getArgs());
            return true;
        } catch (const AException& e) {
            ALogger::warn(":{} failed to call {}::{}: {}"_as.format(call.getLineNumber(),
                                                                    typeid(*mCalleeThis->getType()->asClass()).name(),
                                                                    call.getCallee(),
                                                                    e.getMessage()));
        }
    } catch (...) {
        ALogger::warn(":{} class '{}' doesn't have member function '{}'"_as.format(call.getLineNumber(),
                                                                                   typeid(*mCalleeThis->getType()->asClass()).name(),
                                                                                   call.getCallee()));
    }
    return false;
}

void Context::visitNode(const AssignmentOperatorNode& node) {
    AString variableName;
    {
        VariableReferenceVisitor v;
        node.getLeft()->acceptVisitor(v);
        if (v.getName()) {
            variableName = *v.getName();
        } else {
            ALogger::warn(":{} invalid assignment"_as.format(node.getLineNumber()));
            return;
        }
    }
    class ExpressionVisitor: public INodeVisitor {
    private:
        std::optional<Variable> result;

    public:
        void visitNode(const TemplateOperatorCallNode& node) override {
            INodeVisitor::visitNode(node);
            try {
                result = Autumn::get<FactoryRegistry<AObject>>()->create(node.getTemplateArg(), node.getArgs());
            } catch (const AException& e) {
                ALogger::warn(":{} {}"_as.format(node.getLineNumber(), e.getMessage()));
            }
        }

        const std::optional<Variable>& getResult() const {
            return result;
        }
    } v;
    node.getRight()->acceptVisitor(v);
    if (auto r = v.getResult()) {
        mLocalVariables[variableName] = *r;
    } else {
        ALogger::warn(":{} invalid rvalue"_as.format(node.getLineNumber()));
    }
}

void Context::visitNode(const ARepeatOperatorNode& node) {
    INodeVisitor::visitNode(node);
    for (unsigned i = 0; i < node.getTimes(); ++i) {
        executeCodeBlock(node.getCode());
    }
}

Context::PushLocal::PushLocal(const AString& name, const Variable& v):
        mPreviousValue(Autumn::get<Context>()->setLocalVariable(name, v)),
        mName(name)
{

}

Context::PushLocal::~PushLocal() {
    auto c = Autumn::get<Context>();
    if (mPreviousValue) {
        c->setLocalVariable(mName, *mPreviousValue);
    } else {
        auto it = c->mLocalVariables.find(mName);
        if (it != c->mLocalVariables.end()) {
            c->mLocalVariables.erase(it);
        }
    }
}

Context::PushThis::PushThis(Variable* mNewValue) : mPreviousValue(Autumn::get<Context>()->mCalleeThis) {
    Autumn::get<Context>()->mCalleeThis = mNewValue;
}

Context::PushThis::~PushThis() {
    Autumn::get<Context>()->mCalleeThis = mPreviousValue;
}
