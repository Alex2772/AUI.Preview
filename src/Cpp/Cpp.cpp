//
// Created by alex2 on 6/12/2021.
//

#include <AUI/IO/FileInputStream.h>
#include "Cpp.h"
#include "Lexer.h"
#include "Parser.h"

_<AST> Cpp::parseCode(const APath& p) {
    Lexer l(_new<FileInputStream>(p));
    Parser parser(l.performLexAnalysis());
    return _new<AST>(parser.parse());
}
