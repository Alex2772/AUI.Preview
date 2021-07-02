//
// Created by alex2 on 6/19/2021.
//

#include <AUI/Common/AException.h>
#include <AUI/Logging/ALogger.h>
#include <AUI/Autumn/Autumn.h>
#include <Factory/FactoryRegistry.h>
#include "RuleVisitor.h"
#include <AUI/ASS/ASS.h>

void RuleVisitor::visitNode(const ExplicitInitializerListCtorNode& node) {
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
                errors.push_back({typeid(*f.get()).name(), e.getMessage()});
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
