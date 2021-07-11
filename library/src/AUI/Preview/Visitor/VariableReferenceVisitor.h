//
// Created by alex2 on 7/3/2021.
//

#pragma once

#include <AUI/Preview/Cpp/AST/INodeVisitor.h>
#include <optional>

class VariableReferenceVisitor : public INodeVisitor {
private:
    std::optional<AString> mName;

public:
    void visitNode(const VariableReferenceNode& node) override;

    const std::optional<AString>& getName() const {
        return mName;
    }
};