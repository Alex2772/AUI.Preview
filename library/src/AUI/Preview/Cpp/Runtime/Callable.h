//
// Created by alex2 on 6/28/2021.
//

#pragma once

#include <functional>
#include <AUI/Common/AVector.h>
#include <AUI/Preview/Cpp/AST/ExpressionNode.h>

namespace Runtime {
    using CallArgs = AVector<_<ExpressionNode>>;
    using Callable = std::function<void(const CallArgs&)>;
}