//
// Created by alex2 on 6/12/2021.
//

#pragma once


#include <AUI/Util/ATokenizer.h>
#include "AnyToken.h"

class Lexer {
private:
    ATokenizer mTokenizer;

    void reportError(const AString& text);

public:
    explicit Lexer(const _<IInputStream>& is): mTokenizer(is) {}


    AVector<AnyToken> performLexAnalysis();
};


