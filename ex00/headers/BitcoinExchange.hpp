#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <exception>
# include <fstream>
# include <iostream>
# include <limits>
# include <sstream>
# include <string>
# include <vector>
#include <utility>
#include <algorithm>

# define WRONG_YEAR 1
# define WRONG_VALUE 2
# define MAX std::numeric_limits<int>::max()

typedef struct s_validation
{
	std::string monthStr;
	std::string dayStr;
	std::string yearStr;
	std::string dateStr;
	int day;
	int month;
	int year;

} t_validate;

class Bitcoin
{
  private:
	std::string _path;
	std::vector<std::pair<int, double> > _data;
    std::vector<std::pair<int, double> > _dataBase;
    std::string _errorsBank[12];
	int strToNum(std::string str);
	t_validate dates;
	int _maxDate;
	int _minDate;
	int validateYear(std::string &line, size_t &i, int flag, int &year);
	int validateMonth(std::string &line, size_t &i, int flag, int &month);
	int validateDay(std::string &line, size_t &i, int flag, int &date, int month, int year);

  public:
	Bitcoin();
	Bitcoin(const std::string path);
	~Bitcoin();
	Bitcoin(const Bitcoin &other);
	Bitcoin &operator=(const Bitcoin &other);
	void validateLine(std::string &line, int flag);
    void loadDataBase(); 
    void searchDataBase();
    std::string intToString(int num);
};
#endif