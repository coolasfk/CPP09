
#include "PmergeMe.hpp"
#include "Utils.hpp"

void	checkArguments(int argc, char *argv[], std::string &array)
{
	for (int k = 1; k < argc; k++)
	{
		for (size_t i = 0; argv[k][i] != '\0'; i++)
		{
			if (!isdigit(argv[k][i]) && argv[k][i] != ' ')
			{
				std::cerr << LIGHT_RED << "Invalid character in your input." << RESET << std::endl;
				exit(1);
			}
		}
	}
	(void)array;
}
int	main(int argc, char *argv[])
{
	int	i;

	std::string array;
	if (argc < 2)
	{
		std::cerr << "Provide at least 2 arguments." << std::endl;
		return (1);
	}
	checkArguments(argc, argv, array);
	i = 0;
	while (argc > ++i)
		array = array + ' ' + argv[i] + ' ';
	Pmerge pmerge(array);
	pmerge.runTests(array);
	std::cout << std::endl;
}
