//
// Created by alex2 on 6/12/2021.
//

#include <AUI/Logging/ALogger.h>
#include <Cpp/AST/ConstructorDeclarationNode.h>
#include <Cpp/AST/StringNode.h>
#include <Cpp/AST/NumberNode.h>
#include <Cpp/AST/VariableReferenceNode.h>
#include <Cpp/AST/OperatorLiteralNode.h>
#include <Cpp/AST/OperatorCallNode.h>
#include <Cpp/AST/ExplicitInitializerListCtorNode.h>
#include <Cpp/AST/TemplateOperatorCallNode.h>
#include <Cpp/AST/BinaryOperatorNode.h>
#include <Cpp/AST/AUI/ALetOperatorNode.h>
#include <Cpp/AST/ThisNode.h>
#include <Cpp/AST/LambdaNode.h>
#include <Cpp/AST/NullptrNode.h>
#include <Cpp/AST/UnaryOperatorNode.h>
#include <Cpp/AST/ImplicitInitializerListCtorNode.h>
#include <Cpp/AST/AUI/AAsyncOperatorNode.h>
#include <Cpp/AST/TernaryOperatorNode.h>
#include "Parser.h"

template<typename variant, typename type>
struct index_of {
private:
    template<size_t i, size_t... next>
    static constexpr size_t value_impl2(std::index_sequence<i, next...>) {
        if constexpr (std::is_same_v<std::variant_alternative_t<i, variant>, type>) {
            return i;
        } else {
            return value_impl2(std::index_sequence<next...>{});
        }
    }

    static constexpr size_t value_impl() {
        return value_impl2(std::make_index_sequence<std::variant_size_v<variant>>());
    }
public:
    static constexpr size_t value = value_impl();
};

template<typename type>
constexpr size_t got = index_of<AnyToken , type>::value;

AVector<_<INode>> Parser::parse() {
    AVector<_<INode>> nodes;
    for (; mIterator != mTokens.end(); ++mIterator) {
        try {
            // here we should find #includes and function definitions
            switch (mIterator->index()) {
                case got<PreprocessorDirectiveToken>: {
                    break;
                }
                case got<SemicolonToken>: {
                    break;
                }
                case got<KeywordToken>: {
                    if (parseUsing()) break;
                    break;
                }
                case got<IdentifierToken>: {
                    // variable or function definition
                    auto name1 = std::get<IdentifierToken>(*mIterator).value();
                    ++mIterator;
                    switch (mIterator->index()) {
                        case got<DoubleColonToken>:
                            // class constructor definition
                            ++mIterator;

                            switch (mIterator->index()) {
                                case got<IdentifierToken>: {
                                    auto name2 = std::get<IdentifierToken>(*mIterator).value();
                                    ++mIterator;
                                    auto args = parseFunctionDeclarationArgs();
                                    auto initializerList = parseConstructorInitializerList();
                                    auto codeBlock = parseCodeBlock();
                                    nodes << _new<ConstructorDeclarationNode>(name1, name2, args, name1, initializerList, codeBlock);
                                    break;
                                }

                                default:
                                    reportUnexpectedErrorAndSkip("expected name token for constructor definition");
                            }

                            break;

                        case got<IdentifierToken>:
                            // variable or function definition
                            // name1    name2
                            // result_t function_or_class_name
                            auto name2 = std::get<IdentifierToken>(*mIterator).value();
                            ++mIterator;

                            switch (mIterator->index()) {
                                case got<SemicolonToken>:
                                case got<EqualToken>:
                                    // variable definition which we not interested in
                                    skipUntilSemicolon();
                                    break;

                                case got<LParToken>:
                                    // function definition
                                    parseFunctionDeclarationArgs();
                                    break;

                                case got<DoubleColonToken>:
                                    // class constructor definition

                                    break;
                            }

                            break;
                    }

                    break;
                }
                default:
                    reportError("unexpected \"" + getTokenName() + "\"");
            }
        } catch (const AException& ) {}
    }
    return nodes;
}

AVector<_<VariableDeclarationNode>> Parser::parseFunctionDeclarationArgs() {
    expect<LParToken>();
    AVector<_<VariableDeclarationNode>> result;
    ++mIterator;
    for (; mIterator != mTokens.end();) {
        switch (mIterator->index()) {
            case got<RParToken>:
                ++mIterator;
                return result;

            case got<CommaToken>:
                // next arg
                ++mIterator;
                break;

            case got<KeywordToken>:
            case got<IdentifierToken>:
                result << parseVariableDeclaration();
                break;

            default:
                reportUnexpectedErrorAndSkip("expected identifier, comma or right parenthesis");
                throw AException{};
        }
    }
}
AVector<_<ExpressionNode>> Parser::parseCallArgs() {
    expect<LParToken>();
    AVector<_<ExpressionNode>> result;
    ++mIterator;
    for (; mIterator != mTokens.end();) {
        switch (mIterator->index()) {
            case got<RParToken>:
                ++mIterator;
                return result;

            case got<CommaToken>:
                // next arg
                ++mIterator;
                break;

            default:
                result << parseExpression();
        }
    }

    reportUnexpectedEof();
    throw AException{};
}
AVector<_<ExpressionNode>> Parser::parseCurlyBracketsArgs() {
    expect<LCurlyBracketToken>();
    AVector<_<ExpressionNode>> result;
    ++mIterator;
    for (; mIterator != mTokens.end();) {
        switch (mIterator->index()) {
            case got<RCurlyBracketToken>:
                ++mIterator;
                return result;

            case got<CommaToken>:
                // next arg
                ++mIterator;
                break;

            default:
                result << parseExpression();
        }
    }

    reportUnexpectedEof();
    throw AException{};
}

AVector<_<INode>> Parser::parseCodeBlock() {
    AVector<_<INode>> result;
    expect<LCurlyBracketToken>();
    ++mIterator;
    for (; mIterator != mTokens.end();) {
        switch (mIterator->index()) {
            case got<IdentifierToken>: {
                // variable declaration, variable assignment or function call
                result << parseExpression();
                break;
            }

            case got<SemicolonToken>:
                ++mIterator;
                break;

            case got<RCurlyBracketToken>:
                ++mIterator;
                return result;

            case got<KeywordToken>: {
                // TODO place for for, while, goto
                auto t = std::get<KeywordToken>(*mIterator).getType();
                ++mIterator;
                switch (t) {
                    case KeywordToken::RETURN:
                        result << _new<ReturnOperatorNode>(parseExpression());
                        break;

                    default:
                        result << parseExpression();
                }

                break;
            }

            default:
                reportUnexpectedErrorAndSkip("code block expects identifier or semicolon");
                throw AException{};
        }
    }


    reportUnexpectedEof();
    return result;
}

_<ExpressionNode> Parser::parseExpression() {
    _<ExpressionNode> result = nullptr;
    for (; mIterator != mTokens.end(); ) {
        switch (mIterator->index()) {
            case got<KeywordToken>: {
                auto keyword = std::get<KeywordToken>(*mIterator);
                switch (keyword.getType()) {
                    case KeywordToken::THIS:
                        result = _new<ThisNode>();
                        ++mIterator;
                        break;

                    case KeywordToken::NULLPTR:
                        result = _new<NullptrNode>();
                        ++mIterator;
                        break;

                    case KeywordToken::AUTO:
                        result = parseVariableDeclaration();
                        break;

                    case KeywordToken::TRUE:
                        result = _new<VariableReferenceNode>("true");
                        ++mIterator;
                        break;

                    case KeywordToken::FALSE:
                        result = _new<VariableReferenceNode>("false");
                        ++mIterator;
                        break;

                    default:
                        reportError("only auto, this, true, false and nullptr keywords are allowed in an expression");
                        throw AException{};
                }
                break;
            }
            case got<TernaryToken>: { // ternary operator
                result = parseTernary(result);
                break;
            }
            case got<IdentifierToken>: {
                auto name1 = std::get<IdentifierToken>(*mIterator).value();
                if (result == nullptr) {
                    if (name1 == "async") {
                        // AUI async syntax
                        ++mIterator;
                        auto codeBlock = parseCodeBlock();
                        result = _new<AAsyncOperatorNode>(codeBlock);
                    } else {
                        // variable reference
                        result = parseIdentifier();
                    }
                } else {
                    if (name1 == "let") {
                        // AUI let syntax
                        ++mIterator;
                        auto codeBlock = parseCodeBlock();
                        return _new<ALetOperatorNode>(result, codeBlock);
                    } else {
                        // operator literal
                        result = _new<OperatorLiteralNode>(name1, result);
                        ++mIterator;
                    }
                }
                break;
            }

            case got<DoubleColonToken>:
            case got<PointerFieldAccessToken>:
            case got<FieldAccessToken>: {
                // variable access or method call
                ++mIterator;
                if (result == nullptr) {
                    reportError("field access requires object");
                    throw AException{};
                }

                result = _new<MemberAccessOperatorNode>(result, parseMemberAccess());

                break;
            }

            case got<StringToken>:
                result = _new<StringNode>(std::get<StringToken>(*mIterator).value());
                ++mIterator;
                break;

            case got<NumberToken>:
                result = _new<NumberNode>(std::get<NumberToken>(*mIterator).value());
                ++mIterator;
                break;

            case got<LShiftToken>:
                ++mIterator;
                return _new<LShiftOperatorNode>(result, parseExpression());

            case got<RShiftToken>:
                ++mIterator;
                return _new<RShiftOperatorNode>(result, parseExpression());

            case got<LSquareBracketToken>: {
                // lambda
                result = parseLambda();
                break;
            }

            case got<EqualToken>: {
                ++mIterator;
                return _new<AssignmentOperatorNode>(result, parseExpression());
            }

            case got<LogicalNotToken>: {
                ++mIterator;
                if (result != nullptr) {
                    reportError("logical not is not a binary operator");
                    throw AException{};
                }
                result = _new<LogicalNotOperatorNode>(parseExpression());
                break;
            }

            case got<AsteriskToken>: { // pointer dereference
                ++mIterator;
                result = _new<PointerDereferenceOperatorNode>(parseExpression());
                break;
            }

            case got<AmpersandToken>: { // variable pointer creation
                ++mIterator;
                result = _new<PointerCreationOperatorNode>(parseExpression());
                break;
            }

            case got<LCurlyBracketToken>: { // implicit initializer list initialization
                result = _new<ImplicitInitializerListCtorNode>(parseCurlyBracketsArgs());
                break;
            }

            default:
                 if (result == nullptr) {
                    reportUnexpectedErrorAndSkip("not an expression");
                    throw AException{};
                }
                return result;

        }
    }
    return result;
}

_<ExpressionNode> Parser::parseTernary(const _<ExpressionNode>& condition) {
    expect<TernaryToken>();
    ++mIterator;
    auto onTrue = parseExpression();
    expect<ColonToken>();
    ++mIterator;
    auto onFalse = parseExpression();

    return _new<TernaryOperatorNode>(condition, onTrue, onFalse);
}

AVector<_<INode>> Parser::parseConstructorInitializerList() {
    if (!std::holds_alternative<ColonToken>(*mIterator)) {
        return {};
    }
    ++mIterator;
    AVector<_<INode>> result;

    for (; mIterator != mTokens.end();) {
        switch (mIterator->index()) {
            case got<IdentifierToken>: {
                auto fieldName = std::get<IdentifierToken>(*mIterator);
                ++mIterator;
                auto args = parseCallArgs();
                result << _new<OperatorCallNode>(fieldName.value(), args);
                break;
            }
            case got<CommaToken>:
                ++mIterator;
                break;

            default:
                return result;
        }
    }

    reportUnexpectedEof();
    throw AException{};
}

_<VariableDeclarationNode> Parser::parseVariableDeclaration() {
    bool isConst = false, isStatic = false, isReference = false;
    AString typeName, variableName;
    int pointer = 0;

    // find type
    [&]{
        for (; mIterator != mTokens.end(); ++mIterator) {
            switch (mIterator->index()) {
                case got<KeywordToken>: {
                    switch (std::get<KeywordToken>(*mIterator).getType()) {
                        case KeywordToken::CONST:
                            isConst = true;
                            break;

                        case KeywordToken::STATIC:
                            isStatic = true;
                            break;

                        case KeywordToken::UNSIGNED:
                            typeName = "unsigned";
                            ++mIterator;
                            return;
                        case KeywordToken::AUTO:
                            typeName = "auto";
                            ++mIterator;
                            return;
                    }

                    break;
                }
                case got<IdentifierToken>: {
                    auto name = std::get<IdentifierToken>(*mIterator);
                    typeName = name.value();
                    ++mIterator;

                    if (mIterator->index() == got<LAngleBracketToken>) {
                        // template
                        ++mIterator;
                        switch (mIterator->index()) {
                            case got<IdentifierToken>:
                                typeName += "<" + std::get<IdentifierToken>(*mIterator).value() + ">";
                                ++mIterator;
                                expect<RAngleBracketToken>();
                                break;

                            case got<RAngleBracketToken>: // diamond <>
                                break;

                            default:
                                reportUnexpectedErrorAndSkip("expected identifier or right angle bracket");
                        }
                        ++mIterator;
                    }

                    return;
                }

                default:
                    reportUnexpectedErrorAndSkip("expected identifier token");
                    throw AException{};
            }
        }
    }();

    // find name, pointer and reference modifiers
    for (; mIterator != mTokens.end(); ++mIterator) {
        switch (mIterator->index()) {
            case got<IdentifierToken>: {
                if (!variableName.empty()) {
                    reportUnexpectedErrorAndSkip("expected asterisk, ampersand or end of the variable definition");
                }
                variableName = std::get<IdentifierToken>(*mIterator).value();
                break;
            }

            case got<AsteriskToken>: { // pointer
                if (variableName.empty()) {
                    ++pointer;
                    break;
                }

                reportUnexpectedErrorAndSkip("expected end of the variable definition");
                throw AException{};
            }

            case got<AmpersandToken>: // reference
                if (variableName.empty()) {
                    isReference = true;
                    break;
                }

            default:
                if (variableName.empty()) {
                    reportUnexpectedErrorAndSkip("expected variable name");
                    throw AException{};
                }

                return _new<VariableDeclarationNode>(isConst, isStatic, typeName, variableName, pointer, isReference);
        }
    }

    reportUnexpectedEof();
    throw AException{};
}

void Parser::skipUntilSemicolon() {
    for (; mIterator != mTokens.end(); ++mIterator) {
        if (std::holds_alternative<SemicolonToken>(*mIterator)) {
            return;
        }
    }
}

bool Parser::parseUsing() {
    auto& nameToken = std::get<KeywordToken>(*mIterator);
    if (nameToken.getType() == KeywordToken::USING) {
        // using definition, skip it
        skipUntilSemicolon();
        return true;
    }
    return false;
}

void Parser::reportUnexpectedErrorAndSkip(const AString& string) {
    reportError(string + ", got "_as + getTokenName());
    skipUntilSemicolon();
}

AString Parser::getTokenName() {
    AString name;
    std::visit([&](auto&& arg) {
        name = arg.getName();
    }, *mIterator);
    return name;
}

void Parser::reportUnexpectedEof() {
    reportError("unexpected end of file");
    skipUntilSemicolon();
}

void Parser::reportError(const AString& message) {
    unsigned lineNumber;
    std::visit([&](auto&& x) {
        lineNumber = x.getLineNumber();
    }, *mIterator);


    ALogger::err(":" + AString::number(lineNumber) + " " + message);
}

_<ExpressionNode> Parser::parseMemberAccess() {
    switch (mIterator->index()) {
        case got<IdentifierToken>: {
            return parseIdentifier();
        }

        default:
            reportUnexpectedErrorAndSkip("expected identifier");
            throw AException{};
    }
    return nullptr;
}

_<ExpressionNode> Parser::parseLambda() {
    expect<LSquareBracketToken>();

    // skip everything until ]
    for (; mIterator->index() != got<RSquareBracketToken>; ++mIterator);
    ++mIterator;

    AVector<_<VariableDeclarationNode>> args;

    switch (mIterator->index()) {
        case got<LParToken>: {// lambda argument list
            args = parseFunctionDeclarationArgs();
            break;
        }

        case got<LCurlyBracketToken>:
            break;

        default:
            reportUnexpectedErrorAndSkip("expected left parenthesis or left curly bracket in lambda declaration");
    }
    auto code = parseCodeBlock();

    return _new<LambdaNode>(args, code);
}

_<ExpressionNode> Parser::parseIdentifier() {
    auto name1 = std::get<IdentifierToken>(*mIterator).value();
    ++mIterator;
    _<ExpressionNode> result;
    switch (mIterator->index()) {
        case got<LCurlyBracketToken>: {
            // initializer list object initialization
            result = _new<ExplicitInitializerListCtorNode>(name1, parseCurlyBracketsArgs());
            break;
        }

        case got<LAngleBracketToken>: {
            // template argument
            ++mIterator;
            auto templateArgument = expect<IdentifierToken>().value();
            ++mIterator;
            expect<RAngleBracketToken>();
            ++mIterator;
            auto callArgs = parseCallArgs();
            result = _new<TemplateOperatorCallNode>(name1, callArgs, templateArgument);
            break;
        } // fallthrough
        case got<LParToken>: {
            auto callArgs = parseCallArgs();
            result = _new<OperatorCallNode>(name1, callArgs);
            break;
        }

        default:
            result = _new<VariableReferenceNode>(name1);
            break;
    }
    return result;
}
