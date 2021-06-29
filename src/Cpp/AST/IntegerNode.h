//
// Created by alex2 on 6/12/2021.
//

#pragma once


#include "ExpressionNode.h"
#include <cstdint>

class IntegerNode: public ExpressionNode {
private:
    int64_t mNumber;

public:
    IntegerNode(int64_t number) : mNumber(number) {}

    int64_t getNumber() const {
        return mNumber;
    }

    void acceptVisitor(INodeVisitor& v) override;
};


