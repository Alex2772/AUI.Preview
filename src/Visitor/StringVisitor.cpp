//
// Created by alex2 on 6/15/2021.
//

#include "StringVisitor.h"

void StringVisitor::visitNode(const StringNode& node) {
    mText = node.getString();
    mValid = true;
}
