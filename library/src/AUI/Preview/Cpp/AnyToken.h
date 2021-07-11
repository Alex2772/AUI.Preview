//
// Created by alex2 on 6/12/2021.
//

#pragma once

#include <variant>
#include <AUI/Preview/Cpp/Token/IToken.h>
#include <AUI/Preview/Cpp/Token/IdentifierToken.h>
#include <AUI/Preview/Cpp/Token/IntegerToken.h>
#include <AUI/Preview/Cpp/Token/ColonToken.h>
#include <AUI/Preview/Cpp/Token/BracketsToken.h>
#include <AUI/Preview/Cpp/Token/StringToken.h>
#include <AUI/Preview/Cpp/Token/CommaToken.h>
#include <AUI/Preview/Cpp/Token/LShiftToken.h>
#include <AUI/Preview/Cpp/Token/RShiftToken.h>
#include <AUI/Preview/Cpp/Token/PlusToken.h>
#include <AUI/Preview/Cpp/Token/MinusToken.h>
#include <AUI/Preview/Cpp/Token/AsteriskToken.h>
#include <AUI/Preview/Cpp/Token/DivideToken.h>
#include <AUI/Preview/Cpp/Token/PointerFieldAccessToken.h>
#include <AUI/Preview/Cpp/Token/FieldAccessToken.h>
#include <AUI/Preview/Cpp/Token/LogicalNotToken.h>
#include <AUI/Preview/Cpp/Token/AmpersandToken.h>
#include <AUI/Preview/Cpp/Token/EqualToken.h>
#include <AUI/Preview/Cpp/Token/TernaryToken.h>
#include <AUI/Preview/Cpp/Token/PreprocessorDirectiveToken.h>
#include <AUI/Preview/Cpp/Token/SemicolonToken.h>
#include <AUI/Preview/Cpp/Token/DoubleColonToken.h>
#include <AUI/Preview/Cpp/Token/KeywordToken.h>
#include <AUI/Preview/Cpp/Token/BitwiseOrToken.h>
#include <AUI/Preview/Cpp/Token/LogicalOrToken.h>
#include <AUI/Preview/Cpp/Token/LogicalAndToken.h>
#include <AUI/Preview/Cpp/Token/ModToken.h>
#include <AUI/Preview/Cpp/Token/NotEqualToken.h>
#include <AUI/Preview/Cpp/Token/DoubleEqualToken.h>
#include <AUI/Preview/Cpp/Token/FloatToken.h>

using AnyToken = std::variant<IdentifierToken,
                              IntegerToken,
                              ColonToken,
                              LParToken,
                              RParToken,
                              LCurlyBracketToken,
                              RCurlyBracketToken,
                              LSquareBracketToken,
                              RSquareBracketToken,
                              LAngleBracketToken,
                              RAngleBracketToken,
                              StringToken,
                              CommaToken,
                              LShiftToken,
                              RShiftToken,
                              PlusToken,
                              MinusToken,
                              AsteriskToken,
                              DivideToken,
                              PointerFieldAccessToken,
                              FieldAccessToken,
                              LogicalNotToken,
                              AmpersandToken,
                              EqualToken,
                              TernaryToken,
                              PreprocessorDirectiveToken,
                              SemicolonToken,
                              DoubleColonToken,
                              KeywordToken,
                              BitwiseOrToken,
                              LogicalAndToken,
                              LogicalOrToken,
                              ModToken,
                              DoubleEqualToken,
                              NotEqualToken,
                              FloatToken>;