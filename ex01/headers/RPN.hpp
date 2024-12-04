#ifndef RPN_HPP
# define RPN_HPP

# include <exception>
#include <ostream>
# include <iostream>
# include <limits>
# include <sstream>
# include <string>
#include <stack>
#include <utility>
#include <algorithm>

class RPN
{
  private:
	std::stack<int> _nStack;
	int _result;

  public:
	RPN();
	RPN(int argc, char *argv[]);
	void 	runRPN(int argc, char *argv[]);
	~RPN();
	RPN(const RPN &other);
	void doOperations(char op);
	RPN &operator=(const RPN &other);
	int getResult() const;
};

std::ostream& operator<<(std::ostream& out, const RPN& src);
#endif