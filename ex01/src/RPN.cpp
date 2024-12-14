#include "RPN.hpp"
#include "Utils.hpp"

RPN::RPN() : _result(0)
{
}

RPN::RPN(int argc, char *argv[]) : _result(0)
{
	int	num;

	for (int k = 1; k < argc; k++)
	{
		for (size_t i = 0; argv[k][i] != '\0'; i++)
		{
			if (isdigit(argv[k][i]))
			{
				num = argv[k][i] - 48;
				_nStack.push(num);
			}
			if (!isdigit(argv[k][i]) && isdigit(argv[k][i]) != ' ')
			{
				doOperations(argv[k][i]);
			}
		}
	}
	_result = _nStack.top();
}

void RPN::runRPN(int argc, char *argv[])
{
	int	num;

	for (int k = 1; k < argc; k++)
	{
		for (size_t i = 0; argv[k][i] != '\0'; i++)
		{
			if (isdigit(argv[k][i]))
			{
				num = argv[k][i] - 48;
				_nStack.push(num);
			}
			else if (!isdigit(argv[k][i]) && argv[k][i] != ' ')
			{
				doOperations(argv[k][i]);
			}
		}
	}
	_result = _nStack.top();
}

void RPN::doOperations(char op)
{
	int	num1;
	int	num2;

if(_nStack.size() < 2)
{
	throw std::invalid_argument("Insufficient number of operands!");
}
	num1 = _nStack.top();
	
	_nStack.pop();
	num2 = _nStack.top();
	_nStack.pop();
	
	
	switch (op)
	{
	case '+':
		_nStack.push(num1 + num2);
		break ;
	case '-':
		_nStack.push(num2 - num1);
		break ;
	case '*':
		_nStack.push(num1 * num2);
		break ;
	case '/':
		if (num1 == 0)
		{
			throw std::runtime_error("Division by zero error");
		}
		_nStack.push(num2 / num1);
		break ;
	default:
		throw std::invalid_argument("Invalid operator");
	}
}

RPN::RPN(const RPN &other) : _nStack(other._nStack)
{
}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		_nStack = other._nStack;
	}
	return (*this);
}

RPN::~RPN()
{
}

int RPN::getResult() const
{
	return (_result);
}

std::ostream &operator<<(std::ostream &out, const RPN &src)
{
	return (out << src.getResult());
}
