//
// Created by alex2 on 6/28/2021.
//

#include <AUI/Autumn/Autumn.h>
#include "Context.h"

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
