#include "../includes/parser.hpp"

#include <stdexcept>

template <typename T>
Parser<T>::Parser(Lexer &lexer) : lexer_(lexer),
                                  currentToken_(),
                                  previousToken_()
{
    // Производим считывание первой лексемы.
    advance();
}

template <typename T>
void Parser<T>::advance()
{
    // Считываем следующую лексему.
    previousToken_ = currentToken_;
    currentToken_ = lexer_.getNextToken();
#ifndef NDEBUG
    std::cout << currentToken_.lexeme << std::endl;
#endif
}

template <typename T>
void Parser<T>::expect(std::set<TokenType> types)
{
    if (!types.contains(currentToken_.type))
    {
        // Выбрасываем сообщение об ошибке.
        throw std::runtime_error(
            "Got unexpected token \"" + currentToken_.lexeme +
            "\" of type " + std::to_string(currentToken_.type));
    }

    // В случае успеха переходим к следующей лексеме.
    advance();
}

template <typename T>
bool Parser<T>::match(TokenType type)
{
    if (currentToken_.type == type)
    {
        advance();
        return true;
    }

    return false;
}

template <typename T>
Expression<T> Parser<T>::parseExpression()
{
    Expression expr = parseExpr();

    expect({TOK_EOF});

    return expr;
}

template <typename T>
Expression<T> Parser<T>::parseExpr()
{
#ifndef NDEBUG
    std::cout << "Expr" << std::endl;
#endif
    Expression expr = parseTerm();

    while (currentToken_.type == TOK_PLUS || currentToken_.type == TOK_SUB)
    {
        // Считываем символ '+' или '-' в обязательном порядке.
        advance();
        Token curToken = currentToken_;
        // Считываем следующее слагаемое в выражении.
        Expression term = parseTerm();

        // Обновляем выражение для суммы или вычитание.
        if (curToken.type == TOK_SUB)
            expr -= term;
        else
            expr += term;
    }

    return expr;
}

template <typename T>
Expression<T> Parser<T>::parseTerm()
{
#ifndef NDEBUG
    std::cout << "Term" << std::endl;
#endif
    Expression term = parseFactor();

    while (currentToken_.type == TOK_MULTIPLY || currentToken_.type == TOK_DIV)
    {
        // Считываем символ '*' или '/' в обязательном порядке.
        advance();

        Token curToken = currentToken_;
        // Считываем следующий множитель в выражении.
        Expression factor = parseFactor();

        // Обновляем выражение для произведения и деление.
        if (curToken.type == TOK_DIV)
            term /= factor;
        else
            term *= factor;
    }

    return term;
}

template <typename T>
Expression<T> Parser<T>::parseFactor()
{
#ifndef NDEBUG
    std::cout << "Factor" << std::endl;
#endif
    Expression<T> expr;
    if (match(TOK_BRACKET_LEFT))
    {
        
        expr = parseExpr();

        expect({TOK_BRACKET_RIGHT});
    }
    else if (match(TOK_FUNCTION))
    {
        Token curToken = previousToken_;
        Expression<T> expr_ = parseExpr();
        if (curToken.lexeme == "sin(")
        {
            expr = expr_.ExprSin();
        }
        else if (curToken.lexeme == "cos(")
        {
            expr = expr_.ExprCos();
        }
        else if (curToken.lexeme == "ln(")
        {
            expr = expr_.ExprLn();
        }
        else if (curToken.lexeme == "exp(")
        {
            expr = expr_.ExprExp();
        }
        expect({TOK_BRACKET_RIGHT});
    }
    else if (match(TOK_VALUE))
    {
        expr = Expression<T>(std::stold(previousToken_.lexeme));
    }
    else if (match(TOK_VARIABLE))
    {
        expr = Expression<T>(previousToken_.lexeme);
    }
    else
    {
        throw std::runtime_error(
            "Got unexpected token \"" + currentToken_.lexeme +
            "\" of type " + std::to_string(currentToken_.type));
    }

    if (match(TOK_POW))
    {
        Expression<T> pow_expr = parseFactor();

        expr ^= pow_expr;
    }
    // std::cout<<expr.to_string();

    return expr;
}

template class Parser<long double>;
