//
// Created by alex2 on 6/23/2021.
//

#pragma once

#include "converter.h"

namespace aui::preview {
    template<>
    struct converter<ass::unset_wrap<glm::vec2>> {
    static ass::unset_wrap<glm::vec2> from_vm(const _<ExpressionNode>& n) {
        return {};
    }
};
}