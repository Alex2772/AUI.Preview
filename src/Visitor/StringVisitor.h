//
// Created by alex2 on 6/15/2021.
//

#pragma once


#include <Cpp/AST/INodeVisitor.h>
#include <AUI/Common/AException.h>

class StringVisitor: public INodeVisitor {
private:
    AString mText;
    bool mValid = false;

public:
    void visitNode(const StringNode& node) override;


    [[nodiscard]]
    const AString& getString() const {
        if (!mValid) {
            throw AException("not a string");
        }
        return mText;
    }
};


