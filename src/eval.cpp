// Copyright 2025 Vladislav Aleinik
#include "../includes/expression.hpp"

#include <iostream>
#include <cstring>

int main()
{
    // if (argc != 5 || std::strcmp(argv[1], "--x") != 0 || std::strcmp(argv[3], "--y") != 0)
    // {
    //     printf("Usage: eval --x <x value> --y <y value>\n");
    //     return EXIT_FAILURE;
    // }

    // long double x = stold(std::string(argv[2]));
    // long double y = stold(std::string(argv[4]));

    std::map<std::string, long double> input_context =
    {
        {"x", 2}, {"y", 3}
    };

    // // Создаём объект выражения на основе механизма синтаксического соответствия.

    Expression<long double> hundred100(100.0), two2(2.0);
    Expression<long double> x("x"), y("y");

    Expression expr1 = hundred100 + x / two2;
    expr1 += y * (x ^ 2);

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

    // printf("EVAL[%s]{x = 1.0, y = 2.0} = %Lf\n", expr1.to_string().c_str(), expr1.eval(context1));
    // printf("EVAL[%s]{x = 2.0, y = 3.0} = %Lf\n", expr1.to_string().c_str(), expr1.eval(context2));

    return EXIT_SUCCESS;
}