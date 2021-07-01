//
// Created by alex2 on 6/28/2021.
//

#pragma once


#include <AUI/Common/AString.h>
#include <AUI/Common/AMap.h>
#include <Cpp/AST/INode.h>
#include <Cpp/AST/INodeVisitor.h>
#include "Variable.h"
#include <optional>

namespace Runtime {
    class Context : public INodeVisitor {
    private:
        AMap<AString, Variable> mLocalVariables;
        Variable* mCalleeThis = nullptr;

        bool doThisCall(const OperatorCallNode& call);

    public:

        struct PushLocal {
        private:
            std::optional<Variable> mPreviousValue;
            AString mName;

        public:
            PushLocal(const AString& name, const Variable& v);

            ~PushLocal();
        };

        struct PushThis {
        private:
            Variable* mPreviousValue;

        public:
            PushThis(Variable* mNewValue);
            ~PushThis();
        };

        /**
         * Sets local variable.
         * @param name variable name
         * @param v new value
         * @return previous value, nullptr if was not set
         */
        std::optional<Variable> setLocalVariable(const AString& name, const Variable& v);

        /**
         * Gets local variable
         * @param name variable name
         * @return variable value
         */
        [[nodiscard]] std::optional<Variable> getLocalVariable(const AString& name) const {
            if (auto c = mLocalVariables.contains(name)) {
                return c->second;
            }
            return std::nullopt;
        }

        void visitNode(const AssignmentOperatorNode& node) override;

        /**
         * Executes code block with registered locals and functions.
         * @param codeBlock
         */
        void executeCodeBlock(const AVector<_<INode>>& codeBlock);

        void visitNode(const OperatorCallNode& node) override;

        void visitNode(const MemberAccessOperatorNode& node) override;



        /**
         * The variable member function is called of
         */
        [[nodiscard]] Variable* getCalleeThis() const {
            return mCalleeThis;
        }

        void visitNode(const ARepeatOperatorNode& node) override;
    };
}