#include "../includes/expression.hpp"
#include "../includes/parser.hpp"
#include "../includes/lexer.hpp"

#include <iostream>
#include <cstring>
#include <iomanip>

int main(int argc, char *argv[])
{
    std::map<std::string, long double> params;
    std::string eval_expr;
    std::string diff_expr;
    std::string diff_by;
    bool is_eval = false;
    bool is_diff = false;
    bool parsing_params = false;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "--eval" && i + 1 < argc)
        {
            eval_expr = argv[++i];
            is_eval = true;
            parsing_params = true;
        }
        else if (arg == "--diff" && i + 1 < argc)
        {
            diff_expr = argv[++i];
            is_diff = true;
        }
        else if (is_diff && arg == "--by" && i + 1 < argc)
        {
            diff_by = argv[++i];
        }
        else if (parsing_params && arg.find('=') != std::string::npos)
        {
            size_t pos = arg.find('=');
            std::string key = arg.substr(0, pos);
            int value = std::stold(arg.substr(pos + 1));
            params[key] = value;
        }
    }

    if (!is_eval && !is_diff)
    {
        std::cerr << "Error: You cannot use both --eval and --diff flags at the same time." << std::endl;
        return 1;
    }

    if (is_eval)
    {
        Lexer lexer{eval_expr};
        Parser<long double> parser{lexer};
        Expression expr = parser.parseExpression();
        std::cout << expr.eval(params) << std::endl;
    }
    else if (is_diff)
    {
        Lexer lexer{diff_expr};
        Parser<long double> parser{lexer};
        Expression expr = parser.parseExpression();
        std::cout << expr.diff(diff_by).to_string() << std::endl;
    }

    return 0;
}

// int main()
// {
//     std::complex<long double> x_(1, 0), y_(1, 1);

//     std::map<std::string, std::complex<long double>> input_context =
//         {
//             {"x", x_}, {"y", y_}};

//     std::complex<long double> a(3.0, 4.0);
//     std::complex<long double> b(1.0, 2.0);
//     Expression<std::complex<long double>> a_(a), b_(2.0);
//     Expression<std::complex<long double>> x("x"), y("y");
//     Expression<std::complex<long double>> two(2);

//     Expression expr1 = a_ + x / b_;
//     expr1 += y * (x ^ two);

//     expr1 = expr1.ExprLn();

//     // printf("EVAL[%s] = %Lf\n", expr1.to_string().c_str(), expr1.eval(input_context));

//     // Задаём контексты для вычисления выражений.
//     std::map<std::string, long double> context1 =
//         {
//             {"x", 1.0}, {"y", 2.0}};

//     std::map<std::string, long double> context2 =
//         {
//             {"x", 2.0}, {"y", 3.0}};

//     std::cout << std::fixed << std::setprecision(20) << "EVAL[" << expr1.to_string() << "] = " << expr1.eval(input_context) << std::endl;

//     // expr1 = expr1.diff("x");

//     // printf("EVAL[%s]{x = 1.0, y = 2.0} = %Lf\n", expr1.to_string().c_str(), expr1.eval(context1));
//     // printf("EVAL[%s]{x = 2.0, y = 3.0} = %Lf\n", expr1.to_string().c_str(), expr1.eval(context2));

//     // Expression<long double> hundred100(100.0), two2(2.0);
//     // Expression<long double> x("x"), y("y");

//     // std::map<std::string, long double> input_context =
//     // {
//     //     {"x", 2}, {"y", 3}
//     // };

//     // Expression expr1 = hundred100 + x / two2;
//     // expr1 += y * (x ^ 2);

//     // expr1 = expr1.ExprSin();

//     // // Задаём контексты для вычисления выражений.
//     // std::map<std::string, long double> context1 =
//     // {
//     //     {"x", 1.0}, {"y", 2.0}
//     // };

//     // std::map<std::string, long double> context2 =
//     // {
//     //     {"x", 2.0}, {"y", 3.0}
//     // };

//     // // Вычисляем выражение в различных контекстах.
//     // printf("EVAL[%s] = %Lf\n", expr1.to_string().c_str(), expr1.eval(input_context));

//     // expr1 = expr1.diff("x");

//     // printf("EVAL[%s]{x = 1.0, y = 2.0} = %Lf\n", expr1.to_string().c_str(), expr1.eval(context1));
//     // printf("EVAL[%s]{x = 2.0, y = 3.0} = %Lf\n", expr1.to_string().c_str(), expr1.eval(context2));

//     // Lexer lexer{"(x + y) * sin(x + 2) * 2 ^ x + 3 * ln(x)"};

//     // // Создаём парсер для выражения.
//     // Parser<long double> parser{lexer};

//     // // Создаём выражение на основе строки.
//     // Expression expr = parser.parseExpression();

//     // // Вычисляем выражение, созданное на основе строки, в разных контекстах.
//     // printf("EVAL[%s]{x = 1.0, y = 2.0} = %Lf\n", expr.to_string().c_str(), expr.eval(context1));
//     // printf("EVAL[%s]{x = 2.0, y = 3.0} = %Lf\n", expr.to_string().c_str(), expr.eval(context2));

//     return EXIT_SUCCESS;
// }