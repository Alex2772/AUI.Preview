//
// Created by alex2 on 6/12/2021.
//

#pragma once

#include <variant>
#include <Cpp/Token/IToken.h>
#include <Cpp/Token/IdentifierToken.h>
#include <Cpp/Token/NumberToken.h>
#include <Cpp/Token/ColonToken.h>
#include <Cpp/Token/BracketsToken.h>
#include <Cpp/Token/StringToken.h>
#include <Cpp/Token/CommaToken.h>
#include <Cpp/Token/LShiftToken.h>
#include <Cpp/Token/RShiftToken.h>
#include <Cpp/Token/PlusToken.h>
#include <Cpp/Token/MinusToken.h>
#include <Cpp/Token/AsteriskToken.h>
#include <Cpp/Token/DivideToken.h>
#include <Cpp/Token/PointerFieldAccessToken.h>
#include <Cpp/Token/FieldAccessToken.h>
#include <Cpp/Token/LogicalNotToken.h>
#include <Cpp/Token/AmpersandToken.h>
#include <Cpp/Token/EqualToken.h>
#include <Cpp/Token/TernaryToken.h>
#include <Cpp/Token/PreprocessorDirectiveToken.h>
#include <Cpp/Token/SemicolonToken.h>
#include <Cpp/Token/DoubleColonToken.h>
#include <Cpp/Token/KeywordToken.h>
#include <Cpp/Token/BitwiseOrToken.h>
#include <Cpp/Token/LogicalOrToken.h>
#include <Cpp/Token/LogicalAndToken.h>
#include <Cpp/Token/ModToken.h>
#include <Cpp/Token/NotEqualToken.h>
#include <Cpp/Token/DoubleEqualToken.h>

using AnyToken = std::variant<IdentifierToken,
                              NumberToken,
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
                              NotEqualToken>;