//
// Created by alex2 on 6/15/2021.
//

#pragma once


#include <AUI/Common/AException.h>
#include <Visitor/StringVisitor.h>

namespace aui::preview {
    template<typename T>
    struct converter {
        static T from_vm(const _<ExpressionNode>& n) {
            throw AException("unimplemented");
        }
    };


    template<>
    struct converter<AString> {
        static AString from_vm(const _<ExpressionNode>& n) {
            StringVisitor v;
            n->acceptVisitor(&v);
            return v.getString();
        }
    };
}