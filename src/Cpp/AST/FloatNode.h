#pragma once

#include "ExpressionNode.h"
#include <cstdint>

class FloatNode: public ExpressionNode {
private:
    double mNumber;

public:
    FloatNode(double number) : mNumber(number) {}

    double getNumber() const {
        return mNumber;
    }

    void acceptVisitor(INodeVisitor& v) override;
};
