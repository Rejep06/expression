#include <stdexcept>
#include "../includes/expression.hpp"

// ============
// |Expression|
// ============

template <typename T>
Expression<T>::Expression(std::shared_ptr<ExpressionBase<T>> base_) : base(base_)
{
}

template <typename T>
Expression<T>::Expression(T number) : base(std::make_shared<Value<T>>(number))
{
}

template <typename T>
Expression<T>::Expression(const std::string &variable) : base(std::make_shared<Variable<T>>(variable))
{
}

template <typename T>
Expression<T>::Expression(const Expression<T> &other) : base(other.base)
{
}

template <typename T>
Expression<T> &Expression<T>::operator=(Expression<T> &&other)
{
    if (this != &other)
    {
        base = std::move(other.base); // Перемещаем базовый указатель
    }
    return *this;
}

template <typename T>
Expression<T> Expression<T>::operator+(const Expression<T> &that) const
{
    return Expression<T>(std::make_shared<OpAdd<T>>(*this, that));
}

template <typename T>
Expression<T> &Expression<T>::operator+=(const Expression<T> &other)
{
    *this = *this + other;
    return *this;
}

template <typename T>
Expression<T> Expression<T>::operator*(const Expression<T> &that) const
{
    return Expression<T>(std::make_shared<OpMult<T>>(*this, that));
}

template <typename T>
Expression<T> &Expression<T>::operator*=(const Expression<T> &other)
{
    *this = *this * other;
    return *this;
}

template <typename T>
Expression<T> Expression<T>::operator-(const Expression<T> &that) const
{
    return Expression<T>(std::make_shared<OpSub<T>>(*this, that));
}

template <typename T>
Expression<T> &Expression<T>::operator-=(const Expression<T> &other)
{
    *this = *this - other;
    return *this;
}

template <typename T>
Expression<T> Expression<T>::operator/(const Expression<T> &that) const
{
    return Expression<T>(std::make_shared<OpDiv<T>>(*this, that));
}

template <typename T>
Expression<T> &Expression<T>::operator/=(const Expression<T> &other)
{
    *this = *this / other;
    return *this;
}

template <typename T>
Expression<T> Expression<T>::operator^(const Expression<T> &that) const
{
    return Expression<T>(std::make_shared<OpPow<T>>(*this, that));
}

template <typename T>
Expression<T> &Expression<T>::operator^=(const Expression<T> &other)
{
    *this = *this ^ other;
    return *this;
}

// template <typename T>
// Expression<T> operator""_val(T number)
// {
//     return Expression<T>(std::make_shared<Value<T>>(number));
// }

// template <typename T>
// Expression<T> operator""_var(const char *name)
// {
//     return Expression<T>(std::make_shared<Variable<T>>(std::string(name)));
// }

// template <typename T>
// Expression<T> operator""_var(const char *name, size_t size)
// {
//     if (size == 0)
//     {
//         throw std::invalid_argument("Variable name cannot be empty");
//     }
//     return Expression<T>(std::make_shared<Variable>(std::string(name)));
// }

template <typename T>
T Expression<T>::eval(std::map<std::string, T> context) const
{
    return base->eval(context);
}

template <typename T>
std::string Expression<T>::to_string() const
{
    return base->to_string();
}

template class Expression<long double>;
// =============
// |class Value|
// =============

template <typename T>
Value<T>::Value(T number)
{
    value = number;
}

template <typename T>
T Value<T>::eval(std::map<std::string, T> context) const
{

    (void)context;
    return value;
}

template <typename T>
std::string Value<T>::to_string() const
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

template class Value<long double>;
// template class Value<std::complex<long double>>;
// ================
// |class Variable|
// ================

template <typename T>
Variable<T>::Variable(std::string name_) : name(name_)
{
}

template <typename T>
T Variable<T>::eval(const std::map<std::string, T> context) const
{
    auto iter = context.find(name);
    if (iter == context.end())
    {
        throw std::runtime_error("Variable " + name + " not present in eval context!!!");
    }
    return iter->second;
}

template <typename T>
std::string Variable<T>::to_string() const
{
    return name;
}

template class Variable<long double>;
// template class Variable<std::complex<long double>>;

// ====================
// |class OpAdd|
// ====================

template <typename T>
OpAdd<T>::OpAdd(const Expression<T> &left_, const Expression<T> &right_) : left(left_),
                                                                           right(right_)
{
}

template <typename T>
T OpAdd<T>::eval(std::map<std::string, T> context) const
{
    T value_left = left.eval(context);
    T value_right = right.eval(context);

    return value_left + value_right;
}

template <typename T>
std::string OpAdd<T>::to_string() const
{
    return std::string("(") + left.to_string() +
           std::string(" + ") + right.to_string() +
           std::string(")");
}

// =====================
// |class OpMult|
// =====================

template <typename T>
OpMult<T>::OpMult(const Expression<T> &left_, const Expression<T> &right_) : left(left_),
                                                                             right(right_)
{
}

template <typename T>
T OpMult<T>::eval(std::map<std::string, T> context) const
{
    T value_left = left.eval(context);
    T value_right = right.eval(context);

    return value_left * value_right;
}

template <typename T>
std::string OpMult<T>::to_string() const
{
    return std::string("(") + left.to_string() +
           std::string(" * ") + right.to_string() +
           std::string(")");
}

// =====================
// |class OpSub|
// =====================

template <typename T>
OpSub<T>::OpSub(const Expression<T> &left_, const Expression<T> &right_) : left(left_),
                                                                           right(right_)
{
}

template <typename T>
T OpSub<T>::eval(std::map<std::string, T> context) const
{
    T value_left = left.eval(context);
    T value_right = right.eval(context);

    return value_left - value_right;
}

template <typename T>
std::string OpSub<T>::to_string() const
{
    return std::string("(") + left.to_string() +
           std::string(" - ") + right.to_string() +
           std::string(")");
}

// =====================
// |class OpDiv|
// =====================

template <typename T>
OpDiv<T>::OpDiv(const Expression<T> &left_, const Expression<T> &right_) : left(left_),
                                                                           right(right_)
{
}

template <typename T>
T OpDiv<T>::eval(std::map<std::string, T> context) const
{
    T value_left = left.eval(context);
    T value_right = right.eval(context);

    return value_left / value_right;
}

template <typename T>
std::string OpDiv<T>::to_string() const
{
    return std::string("(") + left.to_string() +
           std::string(" / ") + right.to_string() +
           std::string(")");
}

// =====================
// |class OpPow|
// =====================

template <typename T>
OpPow<T>::OpPow(const Expression<T> &left_, const Expression<T> &right_) : left(left_),
                                                                           right(right_)
{
}

template <typename T>
T OpPow<T>::eval(std::map<std::string, T> context) const
{
    T value_left = left.eval(context);
    T value_right = right.eval(context);

    return std::pow(value_left, value_right);
}

template <typename T>
std::string OpPow<T>::to_string() const
{
    return std::string("(") + left.to_string() +
           std::string(" ^ ") + right.to_string() +
           std::string(")");
}

// =====================
// |class SinFunc|
// =====================

template <typename T>
SinFunc<T>::SinFunc(const Expression<T> &arg_) : arg(arg_)
{
}

template <typename T>
T SinFunc<T>::eval(std::map<std::string, T> context) const
{
    T value_arg = arg.eval(context);

    return std::sin(arg);
}

template <typename T>
std::string SinFunc<T>::to_string() const
{
    return std::string("sin(") + arg.to_string() +
           std::string(")");
}

// =====================
// |class CosFunc|
// =====================

template <typename T>
CosFunc<T>::CosFunc(const Expression<T> &arg_) : arg(arg_)
{
}

template <typename T>
T CosFunc<T>::eval(std::map<std::string, T> context) const
{
    T value_arg = arg.eval(context);

    return std::cos(arg);
}

template <typename T>
std::string CosFunc<T>::to_string() const
{
    return std::string("cos(") + arg.to_string() +
           std::string(")");
}

// =====================
// |class LnFunc|
// =====================

template <typename T>
LnFunc<T>::LnFunc(const Expression<T> &arg_) : arg(arg_)
{
}

template <typename T>
T LnFunc<T>::eval(std::map<std::string, T> context) const
{
    T arg_value = arg->resolve();
    if (arg_value <= 0.0L)
        throw std::runtime_error("Ln of negative value in LnFunc::resolve");
    return std::log(arg_value);
};

// template <>
// std::complex<long double> LnFunc<std::complex<long double>>::eval(std::map<std::string, complex<long double>> context) const {
// 	throw std::runtime_error(
// 		"Logarithm of complex numbers is not supported in this implementation"
// 	);
// }

template <typename T>
std::string LnFunc<T>::to_string() const
{
    return std::string("ln(") + arg.to_string() +
           std::string(")");
}

// =====================
// |class ExpFunc|
// =====================

template <typename T>
ExpFunc<T>::ExpFunc(const Expression<T> &arg_) : arg(arg_)
{
}

template <typename T>
T ExpFunc<T>::eval(std::map<std::string, T> context) const
{
    T value_arg = arg.eval(context);

    return std::exp(arg);
}

template <typename T>
std::string ExpFunc<T>::to_string() const
{
    return std::string("sin(") + arg.to_string() +
           std::string(")");
}
