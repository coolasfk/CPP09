#include "BitcoinExchange.hpp"
#include "Utils.hpp"

Bitcoin::Bitcoin() : _path(""), _maxDate(0)
{
}

Bitcoin::Bitcoin(const std::string path) : _path(path), _maxDate(0), _minDate(2147483647)
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
		validateLine(line);
	}
}

void Bitcoin::validateLine(std::string &line)
{
	int		dot_count;
	float	value;
	int		monthArray[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	size_t	i = 0;
	std::string monthStr;
	std::string dayStr;
	std::string yearStr;
	std::string dateStr;
	int		month;
	int		date;
	int day;

	std::string str = line.substr(5, 2);
	std::stringstream ss(str);
	dot_count = 0;
	if(line == "date | value")
	{
		_data.push_back(std::make_pair(11, -1));
				return ;
	}
if(line[i] == '-')
{
	i++;
}
while(line[i] != '-' &&  line[i] != '\0')
{
	if(!isdigit(line[i]))
	{
		_data.push_back(std::make_pair(7, -1));
				return ;
	}
	yearStr = yearStr + line[i];
	i++;
}
if(line[i] != '-')
{
	_data.push_back(std::make_pair(1, -1));
				return ;
}
i++;
while(line[i] != '-' && line[i] != '\0')
{
	if(!isdigit(line[i]))
	{
		_data.push_back(std::make_pair(4, -1));
				return ;
	}
	monthStr = monthStr + line[i];
	i++;
}
month = strToNum(monthStr);
if(month < 1 || month > 12)
{
	_data.push_back(std::make_pair(4, -1));
				return ;
}
if(line[i] != '-')
{
	_data.push_back(std::make_pair(1, -1));
				return ;
}
i++;
while(line[i] != ' ' &&  line[i] != '\0')
{
	if(!isdigit(line[i]))
	{
		_data.push_back(std::make_pair(5, -1));
				return ;
	}
	dayStr = dayStr + line[i];
	i++;
}

day = strToNum(dayStr);
if(day > monthArray[month-1] || day < 1)
{
	_data.push_back(std::make_pair(5, -1));
				return ;
}

if(line[i] != ' ' && line[i+1] != '|' && line[i+2] != ' ')
{
	_data.push_back(std::make_pair(1, -1));
				return ;
}
i += 3;

	str = line.substr(i-1, MAX);
	ss << str;
	ss >> value;

	if (value > 1000 || value < 0)
	{
		_data.push_back(std::make_pair(9, -1));
				return ;
	}

while(line[i] != '\0' || i > line.length()) 
{
	
	if(!isdigit(line[i]) && line[i] != '.')
	{
		
		_data.push_back(std::make_pair(8, -1));
				return ;
	}
	else if(line[i] == '.')
	{
		dot_count++;
	}
	if(dot_count > 1)
	{
		
		_data.push_back(std::make_pair(8, -1));
				return ;
	}
	i++;
	}
	i++;
	
	dateStr = yearStr + monthStr + dayStr;
	
	date = strToNum(dateStr);
	if(date >= _maxDate)
	{
		date = _maxDate;
	}
	if(date < _minDate)
	{
		date = _minDate;
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
	float	value;

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
		if (line[0] != 'd')
		{
			std::stringstream ss(line.substr(0, 4) + line.substr(5, 2)
				+ line.substr(8, 2));
			ss >> date;
			ss.clear();
			std::stringstream ss1(line.substr(11, MAX));
			ss1 >> value;
			
			if(date > _maxDate)
			{
				_maxDate = date;
			}
			if(date < _minDate)
			{
				_minDate = date;
			}
			_dataBase.push_back(std::make_pair(date, value));
		}
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
	std::stringstream ss(str);

	int num = 0;
	ss >> num;
	return num;
}


void Bitcoin::searchDataBase()
{
	int		date;
	float	value;

	std::vector<std::pair<int, float> >::iterator it;
	std::vector<std::pair<int, float> >::iterator it2;
	std::string str;

	for (it = _data.begin(); it != _data.end(); ++it)
	{
		
		if (it->second < 0)
		{
			if(it->first == 11)
			{
				std::cout << '\n'<< BRIGHT_BLUE << _errorsBank[it->first] << RESET  << '\n'<< std::endl;
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
				if(value > 1000)
				{
					std::cout << SOFT_RED << "Error: Value needs to be smaller than 1001." << std::endl;
					break;
				}		
				else if (date <= it2->first)
				{
					--it2;
					str = intToString(date);
					std::cout << LIGHT_GREEN << str.substr(0,
						4) << '-' << str.substr(4, 2) << '-' << str.substr(6,
						2) << " => " << value << " = " << value
						* it2->second << RESET << std::endl;
					break ;
				}
			}
		}
	}
}

Bitcoin::~Bitcoin()
{
}