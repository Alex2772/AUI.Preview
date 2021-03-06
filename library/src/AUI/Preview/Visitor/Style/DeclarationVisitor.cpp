//
// Created by alex2 on 6/19/2021.
//

#include <AUI/Common/AException.h>
#include <AUI/Logging/ALogger.h>
#include <AUI/Autumn/Autumn.h>
#include <AUI/Preview/Factory/FactoryRegistry.h>
#include "DeclarationVisitor.h"
#include <AUI/ASS/ASS.h>
#include <AUI/Reflect/AReflect.h>

void DeclarationVisitor::visitNode(const ExplicitInitializerListCtorNode& node) {
    mNode = _new<ExplicitInitializerListCtorNode>(node);
    const AVector<_unique<IFactory<ass::decl::IDeclarationBase>>>* factories = nullptr;
    AVector<std::pair<AString, AString>> errors;
    try {
        auto name = node.getClassName();
        //ALogger::info(":{} visited {}"_as.format(node.getLineNumber(), name));
        factories = &Autumn::get<FactoryRegistry<ass::decl::IDeclarationBase>>()->getFactoriesForTypeName(name);

        for (auto& f : aui::reverse_iterator_wrap(*factories)) {
            try {
                if (f->isApplicable(node.getArgs())) {
                    mRule = f->create(node.getArgs());
                    break;
                }
            } catch (const AException& e) {
                errors.push_back({AReflect::name(f.get()), e.getMessage()});
            }
        }
    } catch (...) {}
    if (mRule == nullptr) {
        auto msg = ":{} failed to replicate rule {}: {}"_as.format(node.getLineNumber(), node.getClassName(),
                                                                   factories == nullptr || factories->empty()
                                                                   ? "unknown rule"
                                                                   : "no applicable candidate");
        ALogger::warn(msg);

        for (auto& f : errors) {
            ALogger::warn("note: candidate {} dropped by SFINAE with reason: {}"_as.format(f.first, f.second));
        }
    }
}

void DeclarationVisitor::visitNode(const StaticMemberAccessOperatorNode& node) {
    mNode = _new<StaticMemberAccessOperatorNode>(node);
    const AVector<_unique<IFactory<ass::decl::IDeclarationBase>>>* factories = nullptr;
    AVector<std::pair<AString, AString>> errors;
    try {

        auto left = assume<VariableReferenceNode>(node.getLeft());
        auto right = assume<VariableReferenceNode>(node.getRight());
        auto name = left->getVariableName() + "::" + right->getVariableName();
        factories = &Autumn::get<FactoryRegistry<ass::decl::IDeclarationBase>>()->getFactoriesForTypeName(name);

        for (auto& f : aui::reverse_iterator_wrap(*factories)) {
            try {
                if (f->isApplicable({})) {
                    mRule = f->create({});
                    break;
                }
            } catch (const AException& e) {
                errors.push_back({AReflect::name(f.get()), e.getMessage()});
            }
        }
    } catch (...) {}
    if (mRule == nullptr) {
        auto msg = ":{} failed to replicate rule: {}"_as.format(node.getLineNumber(),
                                                                   factories == nullptr || factories->empty()
                                                                   ? "unknown rule"
                                                                   : "no applicable candidate");
        ALogger::warn(msg);

        for (auto& f : errors) {
            ALogger::warn("note: candidate {} dropped by SFINAE with reason: {}"_as.format(f.first, f.second));
        }
    }
}

