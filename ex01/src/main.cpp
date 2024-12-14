
#include "RPN.hpp"
#include "Utils.hpp"

void	checkArguments(int argc, char *argv[])
{
	int	digit_count;
	int	operant_count;

	digit_count = 0;
	operant_count = 0;
	if (argc < 2)
	{
		std::cerr << LIGHT_RED << "Pass as an argument one string which represents the inverted Polish Notation" << RESET << std::endl;
		exit(1);
	}
	for (int k = 1; k < argc; k++)
	{
		for (size_t i = 0; argv[k][i] != '\0'; i++)
		{

			if (isdigit(argv[k][i]) && isdigit(argv[k][i + 1]))
			{
				std::cerr << LIGHT_RED << "Your input contains numbers which are not allowed." << RESET << std::endl;
				exit(1);
			}
			if (isdigit(argv[k][i]))
			{
				digit_count++;
			}
			if (argv[k][i] != ' ' && argv[k][i] != '+' && argv[k][i] != '-'
				&& argv[k][i] != '*' && argv[k][i] != '/'
				&& !isdigit(argv[k][i]))
			{
				std::cerr << LIGHT_RED << "Your input contains forbidden characters: " << argv[k][i] << RESET << std::endl;
				std::cerr << LIGHT_BLUE << "Multiplication sign needs to be passed with '\\*' (escaped) or enclosed in quotes ('*'). * is being read as a wildcard =)" << RESET << std::endl;
				exit(1);
			}
			if (!isdigit(argv[k][i]) && argv[k][i] != ' ')
			{
				operant_count++;
			}

			if (digit_count <= 1 && operant_count == 1)
			{
				std::cerr << LIGHT_RED << "Wrong syntax. Get familiat with the Reverse Polish Notation." << RESET << std::endl;
				exit(1);
			}
		}
	}
	if (operant_count + 1 != digit_count)
	{
		std::cerr << LIGHT_RED << "Operands : operators ratio is not right." << RESET << std::endl;
		exit(1);
	}
	if (digit_count <= 1)
	{
		std::cerr << LIGHT_RED << "Not enough operands." << RESET << std::endl;
		exit(1);
	}
}

int	main(int argc, char *argv[])
{
	checkArguments(argc, argv);
	RPN rpn;
	try
	{
		rpn.runRPN(argc, argv);
		std::cout << PASTEL_LAVENDER << BOLD <<"Result of RPN: " << rpn << RESET <<std::endl;
	}
	catch (const std::runtime_error &e)
	{
		std::cerr <<LIGHT_RED <<  "Runtime  error: " << e.what() << RESET<<std::endl;
	}
	catch (const std::invalid_argument &e)
	{
		std::cerr <<LIGHT_RED  << "Invalid argument: " << e.what() << RESET<< std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr <<LIGHT_RED  <<"Exception caught: " << e.what() << std::endl;
	}

	
}
