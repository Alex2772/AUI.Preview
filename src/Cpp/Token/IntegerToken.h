//
// Created by alex2 on 6/12/2021.
//

#pragma once


#include <cstdint>
#include "IToken.h"

/**
 * Token describing some integer constant
 */
class IntegerToken: public IToken {
private:
    int64_t mNumber;

public:
    IntegerToken(int64_t number): mNumber(number) {}

    const char* getName() override;

    [[nodiscard]]
    int64_t value() const {
        return mNumber;
    }
};

