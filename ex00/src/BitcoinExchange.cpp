#include "BitcoinExchange.hpp"
#include "Utils.hpp"

Bitcoin::Bitcoin() : _path(""), _maxDate(0)
{
}

Bitcoin::Bitcoin(const std::string path) : _path(path), _maxDate(0),
	_minDate(2147483647)
{
	_errorsBank[0] = "Error: Value cannot be negative.";
	_errorsBank[1] = "Error: Invalid syntax.";
	_errorsBank[2] = "Error: Your value has too many decimal points.";
	_errorsBank[3] = "Error: Value cannot be left empty.";
	_errorsBank[4] = "Error: Invalid month format.";
	_errorsBank[5] = "Error: Invalid day format.";
	_errorsBank[6] = "Error: value is too big.";
	_errorsBank[7] = "Error: Invalid year format.";
	_errorsBank[8] = "Error: Invalid value format.";
	_errorsBank[9] = "Error: Value out of range.";
	_errorsBank[10] = "Error: Date out of range.";
	_errorsBank[11] = "date | value";
	std::ifstream file;
	std::string line;
	std::stringstream ss;
	std::string dateStr;
	std::string valueStr;
	loadDataBase();
	file.open(path.c_str());
	while (std::getline(file, line))
	{
		validateLine(line, 2);
	}
}

int Bitcoin::validateDay(std::string &line, size_t &i, int flag, int &day,
	int month, int year)
{
	int	monthArray[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int	leapArray[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	dates.dayStr = "";
	while ((flag == 2 && (line[i] != ' ' && line[i] != '\0')) || (flag == 1
			&& line[i] != ',' && line[i] != '\0'))
	{
		if (!isdigit(line[i]))
		{
			if (flag == 1)
			{
				line = "Syntax error in the first database.";
				return (-1);
			}
			_data.push_back(std::make_pair(5, -1));
			return (-1);
		}
		dates.dayStr = dates.dayStr + line[i];
		i++;
	}
	day = strToNum(dates.dayStr);
	if (year % 4 != 0)
	{
		if (day > monthArray[month - 1] || day < 1)
		{
			if (flag == 1)
			{
				line = "Syntax error in the first database.";
				return (-1);
			}
			_data.push_back(std::make_pair(5, -1));
			return (-1);
		}
	}
	else
	{
		if (day > leapArray[month - 1] || day < 1)
		{
			if (flag == 1)
			{
				line = "Syntax error in the first database.";
				return (-1);
			}
			_data.push_back(std::make_pair(5, -1));
			return (-1);
		}
	}
	return (day);
}

int Bitcoin::validateMonth(std::string &line, size_t &i, int flag, int &month)
{
	dates.monthStr = "";
	if (line[i] != '-')
	{
		if (flag == 1)
		{
			line = "Syntax error in the first database.";
			return (-1);
		}
		_data.push_back(std::make_pair(1, -1));
		return (-1);
	}
	i++;
	while (line[i] != '-' && line[i] != '\0')
	{
		if (!isdigit(line[i]))
		{
			if (flag == 1)
			{
				line = "Syntax error in the first database.";
				return (-1);
			}
			_data.push_back(std::make_pair(4, -1));
			return (-1);
		}
		dates.monthStr = dates.monthStr + line[i];
		i++;
	}
	month = strToNum(dates.monthStr);
	if (month < 1 || month > 12)
	{
		if (flag == 1)
		{
			line = "Syntax error in the first database.";
			return (-1);
		}
		_data.push_back(std::make_pair(4, -1));
		return (-1);
	}
	return (month);
}

int Bitcoin::validateYear(std::string &line, size_t &i, int flag, int &year)
{
	dates.yearStr = "";
	if (line[i] == '-')
	{
		i++;
	}
	while (line[i] != '-' && line[i] != '\0')
	{
		if (!isdigit(line[i]))
		{
			if (flag == 1)
			{
				line = "Syntax error in the first database.";
				return (-1);
			}
			_data.push_back(std::make_pair(7, -1));
			return (-1);
		}
		dates.yearStr = dates.yearStr + line[i];
		i++;
	}
	year = strToNum(dates.yearStr);
	return (year);
}

void Bitcoin::validateLine(std::string &line, int flag)
{
	int		dot_count;
	double	value;
	size_t	i;
	int		month;
	int		date;
	int		day;
	int		year;

	std::string dateStr;
	i = 0;
	dot_count = 0;
	if (line == "date | value")
	{
		_data.push_back(std::make_pair(11, -1));
		return ;
	}
	if (validateYear(line, i, flag, year) == -1)
	{
		return ;
	}
	if (validateMonth(line, i, flag, month) == -1)
	{
		return ;
	}
	if (line[i] != '-')
	{
		if (flag == 1)
		{
			line = "Syntax error in the first database.";
			return ;
		}
		_data.push_back(std::make_pair(1, -1));
		return ;
	}
	i++;
	if (validateDay(line, i, flag, day, month, year) == -1)
	{
		return ;
	}
	if (flag == 1)
	{
		if (line[i] != ',')
		{
			line = "Syntax error in the first database.";
			return ;
		}
		i++;
	}
	else if (flag == 2)
	{
		if (line[i] != ' ' && line[i + 1] != '|' && line[i + 2] != ' ')
		{
			_data.push_back(std::make_pair(1, -1));
			return ;
		}
		i += 3;
	}
	std::string str = line.substr(i, MAX);
	std::stringstream ss(str);
	ss << str;
	ss >> value;
	if (flag == 2)
	{
		if (value > 1000 || value < 0 || str[0] == '\0' || !str[0]
			|| str[0] == ' ')
		{
			_data.push_back(std::make_pair(9, -1));
			return ;
		}
	}
	while (line[i] != '\0' || i > line.length())
	{
		if (!isdigit(line[i]) && line[i] != '.')
		{
			if (flag == 1)
		{
			line = "Syntax error in the first database.";
			return ;
		}
			_data.push_back(std::make_pair(8, -1));
			return ;
		}
		else if (line[i] == '.')
		{
			dot_count++;
		}
		if (dot_count > 1)
		{
			if (flag == 1)
		{
			line = "Syntax error in the first database.";
			return ;
		}
			_data.push_back(std::make_pair(8, -1));
			return ;
		}
		i++;
	}
	i++;
	if (flag == 1)
	{
		return ;
	}
	dateStr = dates.yearStr + dates.monthStr + dates.dayStr;
	date = strToNum(dateStr);
	if (date >= _maxDate)
	{
		date = _maxDate;
	}
	if (date < _minDate)
	{
		date = _minDate;
	}
	if (dateStr.length() != 8)
	{
		_data.push_back(std::make_pair(1, -1));
		return ;
	}
	_data.push_back(std::make_pair(date, value));
}

Bitcoin::Bitcoin(const Bitcoin &other) : _path(other._path), _data(other._data)
{
}

Bitcoin &Bitcoin::operator=(const Bitcoin &other)
{
	if (this != &other)
	{
		_path = other._path;
		_data = other._data;
	}
	return (*this);
}

void Bitcoin::loadDataBase()
{
	int		date;
	double	value;
	int		i;

	i = 1;
	std::ifstream file("./data/data.csv");
	std::string line;
	std::string valueStr;
	if (!file.is_open())
	{
		std::cout << "Data file is invalid." << std::endl;
		exit(1);
	}
	while (std::getline(file, line))
	{
		if (line != "date,exchange_rate")
		{
			std::stringstream ss(line.substr(0, 4) + line.substr(5, 2)
				+ line.substr(8, 2));
			validateLine(line, 1);
			if (line == "Syntax error in the first database.")
			{
				std::cout << BRIGHT_RED << BOLD << "LINE NR: " << i << " IN THE FIRST DATABASE CONTAINS AN ERROR. PROCEED WITH CAUTION.\n" << std::endl;
			}
			else
			{
				ss >> date;
				ss.clear();
				std::stringstream ss1(line.substr(11, MAX));
				ss1 >> value;
				if (date > _maxDate)
				{
					_maxDate = date;
				}
				if (date < _minDate)
				{
					_minDate = date;
				}
				_dataBase.push_back(std::make_pair(date, value));
			}
		}
		i++;
	}
}

std::string Bitcoin::intToString(int num)
{
	std::stringstream ss;
	ss << num;
	return (ss.str());
}

int Bitcoin::strToNum(std::string str)
{
	int	num;

	std::stringstream ss(str);
	num = 0;
	ss >> num;
	return (num);
}

void Bitcoin::searchDataBase()
{
	int		date;
	double	value;
	double	newValue;

	std::vector<std::pair<int, double> >::iterator it;
	std::vector<std::pair<int, double> >::iterator it2;
	std::string str;
	for (it = _data.begin(); it != _data.end(); ++it)
	{
		if (it->second < 0)
		{
			if (it->first == 11)
			{
				std::cout << '\n' << BRIGHT_BLUE << _errorsBank[it->first] << RESET << '\n' << std::endl;
			}
			else
			{
				std::cout << SOFT_RED << _errorsBank[it->first] << RESET << std::endl;
			}
		}
		else
		{
			date = it->first;
			value = it->second;
			for (it2 = _dataBase.begin(); it2 != _dataBase.end(); ++it2)
			{
				if (value > 1000)
				{
					std::cout << SOFT_RED << "Error: Value needs to be smaller than 1001." << std::endl;
					break ;
				}
				else if (date <= it2->first)
				{
					if (date < it2->first)
					{
						--it2;
					}
					newValue = value * it2->second;
					str = intToString(date);
					std::cout << LIGHT_GREEN << str.substr(0,
						4) << '-' << str.substr(4, 2) << '-' << str.substr(6,
						2) << " => " << value << " = " << std::setprecision(10) << newValue << RESET << std::endl;
					break ;
				}
			}
		}
	}
}

Bitcoin::~Bitcoin()
{
}