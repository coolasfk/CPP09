
#include "BitcoinExchange.hpp"
#include "Utils.hpp"

void	checkArguments(int argc, char *argv[])
{
	std::ifstream file;
	if (argc != 2)
		{
        std::cerr << B_SOFTBLUE << ":::>>> Launch btc with the correct path to the input file." << RESET << std::endl;
        std::cerr << B_SOFTBLUE << "hint: ./data/input2.txt" << RESET << std::endl;
        std::cerr << BRIGHT_RED << "Wrong number of arguments" << RESET << std::endl;
        exit(1);
        }
      
	try
	{
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		file.open(argv[1]);
	}
	catch (const std::out_of_range &e)
	{
		std::cout << BRIGHT_RED << "Wrong value error in the file detected! Put the value between 0 and 1000 please." << e.what() << RESET << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << BRIGHT_RED << "Error caught: " << e.what() << RESET << std::endl;
		std::cout << B_SOFTBLUE << ":::>>> Launch btc with the correct path to the input file." << RESET << std::endl;
        std::cout << B_SOFTBLUE << "hint: ./btc ./data/input2.txt" << RESET << std::endl;
		exit(1);
	}
	file.close();
}

int	main(int argc, char *argv[])
{
	checkArguments(argc, argv);

	Bitcoin ex(argv[1]);
   ex.searchDataBase();
}
