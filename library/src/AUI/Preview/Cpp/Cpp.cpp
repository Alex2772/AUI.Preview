//
// Created by alex2 on 6/12/2021.
//

#include <AUI/IO/FileInputStream.h>
#include <AUI/IO/StringStream.h>
#include "Cpp.h"
#include "Lexer.h"
#include "Parser.h"

_<AST> Cpp::parseCode(const APath& p) {
    Lexer l(_new<FileInputStream>(p));
    auto parser = _new<Parser>(l.performLexAnalysis());
    Autumn::put(parser);
    return _new<AST>(parser->parse());
}

_<ExpressionNode> Cpp::parseExpression(const AString& text) {
    Lexer l(_new<StringStream>(text));
    auto parser = _new<Parser>(l.performLexAnalysis());
    return _<ExpressionNode>(parser->parseExpression());
}
