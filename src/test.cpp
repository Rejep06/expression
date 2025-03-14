#include "../includes/expression.hpp"
#include "../includes/TestSystem.hpp"
#include "../includes/lexer.hpp"
#include "../includes/parser.hpp"
#include "../includes/TestSystem.hpp"
#include <iostream>
#include <iomanip>

using namespace TestSystem;

// TESTS:

bool test_constructor()
{
    Expression<long double> expr1(0);
    Expression<long double> expr2(expr1);
    Expression<long double> expr{"x"};
    std::map<std::string, long double> context =
        {
            {"x", 1}};
    return (expr1.eval(context) == 0 && expr2.eval(context) == 0 && expr.eval(context) == 1);
}

bool test_operations()
{
    Expression<long double> expr1(5);
    Expression<long double> expr2("x");
    std::map<std::string, long double> context =
        {
            {"x", 2}};
    Expression sum = expr1 + expr2;
    Expression mult = expr1 * expr2;
    Expression sub = expr1 - expr2;
    Expression div = expr1 / expr2;
    Expression poww = expr1 ^ expr2;
    return (sum.eval(context) == 7 && mult.eval(context) == 10 && sub.eval(context) == 3 && div.eval(context) == 2.5 && poww.eval(context) == 25);
}

bool test_functions()
{
    Expression<long double> expr("x");
    std::map<std::string, long double> context =
        {
            {"x", 2}};
    Expression e_sin = expr.ExprSin();
    Expression e_cos = expr.ExprCos();
    Expression e_ln = expr.ExprLn();
    Expression e_exp = expr.ExprExp();
    return (std::abs(e_sin.eval(context) - std::sin(2) < 1e-14) &&
            std::abs(e_cos.eval(context) - std::cos(2) < 1e-14) &&
            std::abs(e_ln.eval(context) - std::log(2) < 1e-14) &&
            std::abs(e_exp.eval(context) - std::exp(2) < 1e-14));
}

bool test_parser()
{
    Lexer lexer{"(x + y) * sin(x + 2) * 2 ^ x + 3 * ln(x)"};

    std::map<std::string, long double> context =
        {
            {"x", 2}, {"y", 3}};

    // Создаём парсер для выражения.
    Parser<long double> parser{lexer};

    // Создаём выражение на основе строки.
    Expression expr = parser.parseExpression();

    return (std::abs(expr.eval(context) - (5 * std::sin(4) * 4 + 3 * log(2))) < 1e-14);
}

bool test_diff()
{
    Lexer lexer{"(x + y) * sin(x + 2) * 2 ^ x + 3 * ln(x)"};

    std::map<std::string, long double> context =
        {
            {"x", 2}, {"y", 3}};

    // Создаём парсер для выражения.
    Parser<long double> parser{lexer};

    // Создаём выражение на основе строки.
    Expression expr = parser.parseExpression();

    Expression expr_diff = expr.diff("x");
    // sin(x + 2) * 2 ^ x + (x + y) * (cos(x + 2) * 2 ^ x + sin(x + 2) * 2 ^ x * ln(2)) + 3 / x)

    return (std::abs(expr_diff.eval(context) - (std::sin(4) * 4 + 5 * (std::cos(4) * 4 + std::sin(4) * 4 * std::log(2)) + 3.0 / 2)) < 1e-14);
}

int main()
{
    printf("Start testing...\n");
    run_test("Test Constructor", test_constructor);
    run_test("Test Operations", test_operations);
    run_test("Test Functions", test_functions);
    run_test("Test Parser", test_parser);
    run_test("Test Diff", test_diff);
    // run_test("Test Operator Multiple", test_operator_multipe);
    // run_test("Test Operator Div", test_operator_div);
    // run_test("Test Operator !=", test_operator_notequal);
    // run_test("Test Operator>", test_operator_geater);
    // run_test("Test Operator<", test_operator_less);
    // run_test("Test Literal", test_literal);

    return EXIT_SUCCESS;
}