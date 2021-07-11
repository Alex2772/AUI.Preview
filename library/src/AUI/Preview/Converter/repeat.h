//
// Created by alex2 on 6/23/2021.
//

#pragma once

#include "enum.h"
#include <AUI/ASS/ASS.h>

namespace aui::preview {
    template<>
    struct converter<ass::unset_wrap<Repeat>>: enum_converter<Repeat> {};
}