#include <string>
#include <stack>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <math.h>
using namespace std;

#define DIVISION_NULL "деление на ноль :("

#define SYNTAX_ERROR_EXIT_BRACKET "не хватает закрывающей скобки : index "

#define SYNTAX_ERROR_UNEXPECTED "не ожиданный символ :  "

#define SYNTAX_ERROR "некорректный ввод, строка содержит недопустимое выражение "

#define RESULT_ERROR "результат вычисления по модулю больше 10 000 000"

#define EXPRESSION_ERROR "пустое выражение"
#define UNEXPECTED_ENDING "неожиданный конец выражения"
#define BIGGER 1e7

#define INFINUM 0.1e-15

#define COUNT_SYMBOL_IN_NUMBER 9 // 12.23 - good; 1.99999956565655 - bad
#define COUNT_SYMBOL_AFTER_POINT 2
#define INCORRECT_NUMBER "введено некорректное число: "
const unordered_map<char, pair<int, function< double(double, double)>>> operators = {
	{
		' ', pair<int, function< double(double, double)>>(0, [](double a, double b) {
	return 0; })
	},

	{
		'+', pair<int, function< double(double, double)>>(1, [](double a, double b) {
		return a + b; })
	},

	{
		'-', pair<int, function< double(double, double)>>(1, [](double a, double b) {
			return a - b; })
	},

	{
		'*', pair<int, function< double(double, double)>>(2, [](double a, double b) {
				return a * b; })
	},

	{
		'/', pair<int, function< double(double, double)>>(2, [](double a, double b) {
					if (b < INFINUM && b > -INFINUM)
					{
						throw runtime_error(DIVISION_NULL);
					}
					return a / b; })
	},

};

class ExpressionParser {

private:
	class Operator
	{
	public:
		int priority;
		char op;
		Operator();
		Operator(char);
	};

	class OperatorWithValue
	{
	public:
		Operator op;
		double value;
		OperatorWithValue();
		OperatorWithValue(const Operator&, double);
		int GetPriority();
		bool IsNull();
	};

	string expr;
	string result;
	size_t index;
	stack <OperatorWithValue> stck;

	bool IsRightNumberInString(string& doubleTypeNumber);
	bool IsNumber(char&);
	bool IsOperator(char&);
	void RemoveSpace();
	template <class T>
	string ToString(T);
	double ToDouble(string);
	double RoundDouble(double);
	string ReadNumber();
	double Calculate(double, double, Operator&);
	double GetValue();
	double ParseExpr();
public:
	ExpressionParser(const std::string&);
	double Result();
};
