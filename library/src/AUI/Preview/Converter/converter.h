//
// Created by alex2 on 6/15/2021.
//

#pragma once


#include <AUI/Common/AException.h>
#include <AUI/Preview/Visitor/StringVisitor.h>
#include <AUI/Logging/ALogger.h>
#include <AUI/Logging/ALogger.h>

namespace aui::preview {
    template<typename T>
    struct converter {
        static T from_vm(const _<ExpressionNode>& n) {
            assert(("unimplemented" && 0));
            throw AException("unimplemented");
        }
    };


    /**
     * unset_wrap helper
     */
    template<typename T>
    struct unset_wrap_converter: converter<ass::unset_wrap<T>> {
        static T from_vm(const _<ExpressionNode>& n) {
            ass::unset_wrap<T> v = converter<ass::unset_wrap<T>>::from_vm(n);
            if (v) {
                return *v;
            }
            throw AException(":{} lacks value"_as.format(n->getLineNumber()));
        }
    };
}