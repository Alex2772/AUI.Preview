//
// Created by alex2 on 6/11/2021.
//

#pragma once

#include <AUI/Json/AJson.h>

struct Project {
    AJSON_FIELDS(path)

    APath path;

    [[nodiscard]]
    APath getRoot() const {
        // find src/ folder
        for (auto p = path; !p.empty(); p = p.parent()) {
            if (p.isDirectoryExists() && p.filename() == "src") {
                return p.parent();
            }
        }
        return {};
    }
};


