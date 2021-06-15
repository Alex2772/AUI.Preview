//
// Created by alex2 on 6/12/2021.
//

#pragma once

class INodeVisitor;

class INode {
public:
    virtual ~INode() = default;

    virtual void acceptVisitor(INodeVisitor* v) = 0;
};
