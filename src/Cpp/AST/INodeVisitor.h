//
// Created by alex2 on 6/15/2021.
//

#pragma once

#include "ConstructorDeclarationNode.h"
#include "BinaryOperatorNode.h"
#include "ExplicitInitializerListCtorNode.h"
#include "ImplicitInitializerListCtorNode.h"
#include "FunctionDeclarationNode.h"
#include "LambdaNode.h"
#include "MethodDeclarationNode.h"
#include "NullptrNode.h"
#include "NumberNode.h"
#include "OperatorCallNode.h"
#include "OperatorLiteralNode.h"
#include "StringNode.h"
#include "TemplateOperatorCallNode.h"
#include "TernaryOperatorNode.h"
#include "ThisNode.h"
#include "UnaryOperatorNode.h"
#include "VariableDeclarationNode.h"
#include "VariableReferenceNode.h"
#include "AUI/AAsyncOperatorNode.h"
#include "AUI/ALetOperatorNode.h"

class INodeVisitor {
public:
    virtual void visitNode(const ConstructorDeclarationNode& node) {};
    virtual void visitNode(const LShiftOperatorNode& node) {};
    virtual void visitNode(const RShiftOperatorNode& node) {};
    virtual void visitNode(const MemberAccessOperatorNode& node) {};
    virtual void visitNode(const AssignmentOperatorNode& node) {};
    virtual void visitNode(const ExplicitInitializerListCtorNode& node) {};
    virtual void visitNode(const ImplicitInitializerListCtorNode& node) {};
    virtual void visitNode(const FunctionDeclarationNode& node) {};
    virtual void visitNode(const LambdaNode& node) {};
    virtual void visitNode(const MethodDeclarationNode& node) {};
    virtual void visitNode(const NullptrNode& node) {};
    virtual void visitNode(const NumberNode& node) {};
    virtual void visitNode(const OperatorCallNode& node) {};
    virtual void visitNode(const OperatorLiteralNode& node) {};
    virtual void visitNode(const StringNode& node) {};
    virtual void visitNode(const TemplateOperatorCallNode& node) {};
    virtual void visitNode(const TernaryOperatorNode& node) {};
    virtual void visitNode(const ThisNode& node) {};
    virtual void visitNode(const ReturnOperatorNode& node) {};
    virtual void visitNode(const LogicalNotOperatorNode& node) {};
    virtual void visitNode(const PointerDereferenceOperatorNode& node) {};
    virtual void visitNode(const PointerCreationOperatorNode& node) {};
    virtual void visitNode(const VariableDeclarationNode& node) {};
    virtual void visitNode(const VariableReferenceNode& node) {};
    virtual void visitNode(const AAsyncOperatorNode& node) {};
    virtual void visitNode(const ALetOperatorNode& node) {};
};