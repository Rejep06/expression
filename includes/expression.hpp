#ifndef HEADER_GUARD_EXPRESSION_HPP_INCLUDED
#define HEADER_GUARD_EXPRESSION_HPP_INCLUDED
#include <string>
#include <map>
#include <memory>
#include <sstream>
#include <complex>

template <typename T>
class Expression;

template <typename T>
class ExpressionBase
{
public:
    ExpressionBase() = default;
    virtual ~ExpressionBase() = default;

    virtual T eval(std::map<std::string, T> context) const = 0;

    virtual Expression<T> diff(const std::string &by) = 0;

    virtual std::string to_string() const = 0;
};

template <typename T>
class Expression
{
public:
    Expression() = default;
    Expression(T value);
    Expression(const std::string &variable);
    Expression(const Expression<T> &other);
    Expression(std::shared_ptr<ExpressionBase<T>> base_);

    ~Expression() = default;

    // friend Expression operator""_val(T val);
    // friend Expression operator""_var(const char *variable);
    // friend Expression operator""_var(const char *variable, size_t size);

    Expression<T> diff(const std::string &by) const;

    Expression<T> operator-() const;

    Expression<T> &operator=(const Expression<T> &other);
    Expression<T> &operator=(Expression<T> &&other);

    Expression<T> operator+(const Expression<T> &other) const;
    Expression<T> &operator+=(const Expression<T> &other);

    Expression<T> operator-(const Expression<T> &other) const;
    Expression<T> &operator-=(const Expression<T> &other);

    Expression<T> operator*(const Expression<T> &other) const;
    Expression<T> &operator*=(const Expression<T> &other);

    Expression<T> operator/(const Expression<T> &other) const;
    Expression<T> &operator/=(const Expression<T> &other);

    Expression<T> operator^(const Expression<T> &other) const;
    Expression<T> &operator^=(const Expression<T> &other);

    Expression<T> ExprSin() const;
    Expression<T> ExprCos() const;
    Expression<T> ExprLn() const;
    Expression<T> ExprExp() const;

    T eval(std::map<std::string, T> context) const;
    std::string to_string() const;

private:
    std::shared_ptr<ExpressionBase<T>> base;
};

template <typename T>
class Value : public ExpressionBase<T>
{
public:
    Value(T number);

    virtual ~Value() override = default;

    virtual Expression<T> diff(const std::string &by) override;

    virtual T eval(std::map<std::string, T> context) const override;
    virtual std::string to_string() const override;

private:
    T value;
};

template <typename T>
class Variable : public ExpressionBase<T>
{
public:
    Variable(std::string name_);

    virtual ~Variable() override = default;

    virtual Expression<T> diff(const std::string &by) override;

    virtual T eval(std::map<std::string, T> context) const override;
    virtual std::string to_string() const override;

private:
    std::string name;
};

template <typename T>
class Negate : public ExpressionBase<T>
{
public:
    Negate(const Expression<T> &expr_);

    virtual ~Negate() override = default;

    virtual Expression<T> diff(const std::string &by) override;

    virtual T eval(std::map<std::string, T> context) const override;
    virtual std::string to_string() const override;

private:
    Expression<T> expr;
};

template <typename T>
class OpAdd : public ExpressionBase<T>
{
public:
    OpAdd(const Expression<T> &left_, const Expression<T> &right_);

    virtual ~OpAdd() override = default;

    virtual Expression<T> diff(const std::string &by) override;

    virtual T eval(std::map<std::string, T> context) const override;
    virtual std::string to_string() const override;

private:
    Expression<T> left;
    Expression<T> right;
};

template <typename T>
class OpMult : public ExpressionBase<T>
{
public:
    OpMult(const Expression<T> &left_, const Expression<T> &right_);

    virtual ~OpMult() override = default;

    virtual Expression<T> diff(const std::string &by) override;

    virtual T eval(std::map<std::string, T> context) const override;
    virtual std::string to_string() const override;

private:
    Expression<T> left;
    Expression<T> right;
};

template <typename T>
class OpSub : public ExpressionBase<T>
{
public:
    OpSub(const Expression<T> &left_, const Expression<T> &right_);

    virtual ~OpSub() override = default;

    virtual Expression<T> diff(const std::string &by) override;

    virtual T eval(std::map<std::string, T> context) const override;
    virtual std::string to_string() const override;

private:
    Expression<T> left;
    Expression<T> right;
};

template <typename T>
class OpDiv : public ExpressionBase<T>
{
public:
    OpDiv(const Expression<T> &left_, const Expression<T> &right_);

    virtual ~OpDiv() override = default;

    virtual Expression<T> diff(const std::string &by) override;

    virtual T eval(std::map<std::string, T> context) const override;
    virtual std::string to_string() const override;

private:
    Expression<T> left;
    Expression<T> right;
};

template <typename T>
class OpPow : public ExpressionBase<T>
{
public:
    OpPow(const Expression<T> &left_, const Expression<T> &right_);

    virtual ~OpPow() override = default;

    virtual Expression<T> diff(const std::string &by) override;

    virtual T eval(std::map<std::string, T> context) const override;
    virtual std::string to_string() const override;

private:
    Expression<T> left;
    Expression<T> right;
};

template <typename T>
class SinFunc : public ExpressionBase<T>
{
public:
    SinFunc(const Expression<T> &arg_);

    virtual ~SinFunc() override = default;

    virtual Expression<T> diff(const std::string &by) override;

    virtual T eval(std::map<std::string, T> context) const override;
    virtual std::string to_string() const override;

private:
    Expression<T> arg;
};

template <typename T>
class CosFunc : public ExpressionBase<T>
{
public:
    CosFunc(const Expression<T> &arg_);

    virtual ~CosFunc() override = default;

    virtual Expression<T> diff(const std::string &by) override;

    virtual T eval(std::map<std::string, T> context) const override;
    virtual std::string to_string() const override;

private:
    Expression<T> arg;
};

template <typename T>
class LnFunc : public ExpressionBase<T>
{
public:
    LnFunc(const Expression<T> &arg_);

    virtual ~LnFunc() override = default;

    virtual Expression<T> diff(const std::string &by) override;

    virtual T eval(std::map<std::string, T> context) const override;
    virtual std::string to_string() const override;

private:
    Expression<T> arg;
};

template <typename T>
class ExpFunc : public ExpressionBase<T>
{
public:
    ExpFunc(const Expression<T> &arg_);

    virtual ~ExpFunc() override = default;

    virtual Expression<T> diff(const std::string &by) override;

    virtual T eval(std::map<std::string, T> context) const override;
    virtual std::string to_string() const override;

private:
    Expression<T> arg;
};

#endif