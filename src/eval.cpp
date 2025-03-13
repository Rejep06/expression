#include "../includes/expression.hpp"
#include "../includes/parser.hpp"
#include "../includes/lexer.hpp"

#include <iostream>
#include <cstring>

int main()
{

    std::map<std::string, long double> input_context =
    {
        {"x", 2}, {"y", 3}
    };

    // // Создаём объект выражения на основе механизма синтаксического соответствия.

    Expression<long double> hundred100(100.0), two2(2.0);
    Expression<long double> x("x"), y("y");

    Expression expr1 = hundred100 + x / two2;
    expr1 += y * (x ^ 2);

    expr1 = expr1.ExprSin();

    // Задаём контексты для вычисления выражений.
    std::map<std::string, long double> context1 =
    {
        {"x", 1.0}, {"y", 2.0}
    };

    std::map<std::string, long double> context2 =
    {
        {"x", 2.0}, {"y", 3.0}
    };

    // Вычисляем выражение в различных контекстах.
    printf("EVAL[%s] = %Lf\n", expr1.to_string().c_str(), expr1.eval(input_context));

    printf("EVAL[%s]{x = 1.0, y = 2.0} = %Lf\n", expr1.to_string().c_str(), expr1.eval(context1));
    printf("EVAL[%s]{x = 2.0, y = 3.0} = %Lf\n", expr1.to_string().c_str(), expr1.eval(context2));


    Lexer lexer{"(x + y) * sin(x + 2) * 2 ^ x + 3 * ln(x)"};

    // Создаём парсер для выражения.
    Parser<long double> parser{lexer};

    // Создаём выражение на основе строки.
    Expression expr = parser.parseExpression();

    // Вычисляем выражение, созданное на основе строки, в разных контекстах.
    printf("EVAL[%s]{x = 1.0, y = 2.0} = %Lf\n", expr.to_string().c_str(), expr.eval(context1));
    printf("EVAL[%s]{x = 2.0, y = 3.0} = %Lf\n", expr.to_string().c_str(), expr.eval(context2));

    return EXIT_SUCCESS;
}