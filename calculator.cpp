
#include "calculator.h"

extern const unordered_map<char, pair<int, function< double(double, double)>>> operators;

ExpressionParser::Operator::Operator() {
	this->op = ' ';
	this->priority = 0;
}
ExpressionParser::Operator::Operator(char ch) {
	this->op = ch;
	auto it = operators.find(ch);
	this->priority = it != operators.end() ? it->second.first : 0;
}

ExpressionParser::OperatorWithValue::OperatorWithValue():op() {
	this->value = 0;
}
ExpressionParser::OperatorWithValue::OperatorWithValue(const Operator& op, double value) {
	this->op = op;
	this->value = value;
}
int ExpressionParser::OperatorWithValue::GetPriority() {
	return this->op.priority;
}
bool ExpressionParser::OperatorWithValue::IsNull() {
	return this->op.priority == 0;
}

bool ExpressionParser::IsRightNumberInString(string& doubleTypeNumber)
{
	int size = doubleTypeNumber.size();
	int indexPoint = doubleTypeNumber.find('.');

	if (size <= COUNT_SYMBOL_IN_NUMBER)
	{
		if (indexPoint == -1)
		{
			return true;
		}
		if (size - indexPoint - 1 <= COUNT_SYMBOL_AFTER_POINT)
		{
			return true;
		}
	}
	return false;
}

bool ExpressionParser::IsNumber(char& ch) {
	return ch >= '0' && ch <= '9';
}
bool ExpressionParser::IsOperator(char& ch) {
	auto it = operators.find(ch);
	return it != operators.end() ? true : false;
}
void ExpressionParser::RemoveSpace() {
	while (isspace(this->expr[index]) != 0)
		index++;
}

template <class T>
string ExpressionParser::ToString(T number) {
	std::ostringstream oss;
	oss << number;
	return oss.str();
}
double ExpressionParser::ToDouble(string str) {
	double number = 0.0;
	std::istringstream iss(str);
	iss >> number;
	return number;
}
double ExpressionParser::RoundDouble(double number)
{
	if (number < 0.05 && number > -0.05)
	{
		return 0;
	}
	return roundf(number * 100) / 100;
}
string ExpressionParser::ReadNumber()
{
	string number = "";
	char nextCh = this->expr[index];
	while (IsNumber(nextCh) == true || nextCh == '.' || nextCh == ',')
	{
		if (nextCh == ',')
		{
			number += '.';
		}
		else
		{
			number += nextCh;
		}
		nextCh = this->expr[++index];
	}
	if (!IsRightNumberInString(number))
	{
		throw runtime_error(INCORRECT_NUMBER + number);
	}
	return number;
}
double ExpressionParser::Calculate(double a, double b, Operator& op) {
	auto it = operators.find(op.op);
	return it != operators.end() ? it->second.second(a, b) : 0;
}
double ExpressionParser::GetValue() {
	string value = "";
	RemoveSpace();
	double result = 0;
	if (index >= expr.size())
		throw runtime_error(UNEXPECTED_ENDING);
	char ch = this->expr[index];
	if (IsNumber(ch))
	{
		value = ReadNumber();
	}
	else
		if (ch == '(')
		{
			index++;
			value = ToString(ParseExpr());
			RemoveSpace();
			if (expr[index] != ')')
			{
				string strIndex = ToString(index);
				throw runtime_error(SYNTAX_ERROR_EXIT_BRACKET + strIndex);
			}
			index++;
		}
		else
			if (ch == '-')
			{
				index++;
				result = -GetValue();
			}
			else
				if (!IsOperator(ch))
				{
					int start = index;
					int size = 1;
					ch = expr[++index];
					while (ch != ' ' && !IsNumber(ch) && !IsOperator(ch) && index < expr.size())
					{
						index++;
						size++;
						ch = expr[index];
					}
					string errorText = SYNTAX_ERROR + expr.substr(start, size);
					throw runtime_error(errorText);
				}

	result += ToDouble(value);
	return result;
}
double ExpressionParser::ParseExpr() {

	stck.push(OperatorWithValue());
	double value = GetValue();
	while (!stck.empty())
	{
		RemoveSpace();
		Operator op(expr[index]);
		if (op.priority != 0)
		{
			index++;
			if (index >= expr.size())
				throw runtime_error(UNEXPECTED_ENDING);
		}
		while (op.priority <= stck.top().GetPriority())
		{
			if (stck.top().IsNull() == true)
			{
				stck.pop();
				return value;
			}
			value = Calculate(stck.top().value, value, stck.top().op);
			stck.pop();
		}
		stck.push(OperatorWithValue(op, value));
		value = GetValue();
	}
	return 0;
}

ExpressionParser::ExpressionParser(const std::string& expr) {

	if (expr.empty())
	{
		throw runtime_error(EXPRESSION_ERROR);
	}
	this->expr = expr;
	this->index = 0;
}
double ExpressionParser::Result() {
	double result = RoundDouble(ParseExpr());
	if ((result >= BIGGER || result <= -BIGGER) && index >= expr.size())
	{
		throw runtime_error(RESULT_ERROR);
	}
	return result;
}
