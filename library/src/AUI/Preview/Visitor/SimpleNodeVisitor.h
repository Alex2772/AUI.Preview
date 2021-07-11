//
// Created by alex2772 on 7/8/21.
//

#pragma once

#include <AUI/Preview/Cpp/AST/INodeVisitor.h>

template<typename node_t>
class SimpleNodeVisitor: public INodeVisitor {
private:
    const node_t* mNode = nullptr;

public:
    void visitNode(const node_t& node) override {
        INodeVisitor::visitNode(node);
        mNode = &node;
    }

    [[nodiscard]]
    const node_t* getNode() const {
        return mNode;
    }
};
