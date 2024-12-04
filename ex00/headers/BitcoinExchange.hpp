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


class Bitcoin
{
  private:
	std::string _path;
	std::vector<std::pair<int, float> > _data;
    std::vector<std::pair<int, float> > _dataBase;
    std::string _errorsBank[12];
	int strToNum(std::string str);
	int _maxDate;
	int _minDate;

  public:
	Bitcoin();
	Bitcoin(const std::string path);
	~Bitcoin();
	Bitcoin(const Bitcoin &other);
	Bitcoin &operator=(const Bitcoin &other);
	void validateLine(std::string &line);
    void loadDataBase(); 
    void searchDataBase();
    std::string intToString(int num);
};
#endif