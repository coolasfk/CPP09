#include "PmergeMe.hpp"
#include "Utils.hpp"

Pmerge::Pmerge()
{
}

Pmerge::Pmerge(std::string str)
{
	std::cout << std::endl;
	std::cout << BOLD << LIGHT_LIME<<  "Unsorted string: " << str << RESET << std::endl;
	std::cout << std::endl;
}

Pmerge::Pmerge(const Pmerge &other): _list(other._list), _deq(other._deq)
{
}

Pmerge &Pmerge::operator=(const Pmerge &other)
{
	if(this!= &other)
	{
		this->_deq = other._deq;
        this->_list = other._list;
	}
	
	return (*this);
}

Pmerge::~Pmerge()
{
}

void Pmerge::runTests(std::string str)
{
	float	time_deq;
	float	time_list;
	int		value;

	std::cout << B_PINK << "::::::::::::::::::::::::: GENERIC TEMPLATE TEST :::::::::::::::::::::::::" << RESET << std::endl;
	std::clock_t start = std::clock();
	mergeSort(_deq, str);
	std::clock_t end = std::clock();
	time_deq = double(end - start) / CLOCKS_PER_SEC;
	start = std::clock();
	mergeSort(_list, str);
	end = std::clock();
	time_list = double(end - start) / CLOCKS_PER_SEC;
	if (time_deq < time_list)
	{
		std::cout << BOLD << PASTEL_LAVENDER << "Deque is faster than the list: " << std::fixed << std::setprecision(7) << time_deq
					<< ", "
						"and the list: "
					<< time_list << RESET << std::endl;
	}
	else
	{
		std::cout << BOLD << PASTEL_LAVENDER << "List is faster than the deque: " << std::fixed << std::setprecision(7) << time_list
					<< ", "
						"and the deque: "
					<< std::fixed << std::setprecision(7) << time_deq << RESET << std::endl;
	}
	std::cout << std::endl;
	std::cout << B_PINK << "::::::::::::::::::::::::: INVDIVIDUAL TEST :::::::::::::::::::::::::" << RESET << std::endl;
	start = std::clock();
	_deq.clear();
	_list.clear();
	std::stringstream ss(str);
	while (ss >> value)
	{
		_list.push_back(value);
		_deq.push_back(value);
	}
	recursiveMergeSortDeque(_deq);
	end = std::clock();
	time_deq = double(end - start) / CLOCKS_PER_SEC;
	start = std::clock();
	recursiveMergeSortList(_list);
	end = std::clock();
	time_list = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Sorted deque: ";
	for (std::deque<int>::iterator it = _deq.begin(); it != _deq.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << "Sorted list: ";
	for (std::list<int>::iterator it = _list.begin(); it != _list.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	if (time_deq < time_list)
	{
		std::cout << BOLD << PASTEL_LAVENDER << "Deque is faster than the list: " << std::fixed << std::setprecision(7) << time_deq
					<< ", "
						"and the list: "
					<< std::fixed << std::setprecision(7) << time_list << RESET << std::endl;
	}
	else
	{
		std::cout << BOLD << PASTEL_LAVENDER << "List is faster than the deque: " << std::fixed << std::setprecision(7) << time_list
					<< ", "
						"and the deque: "
					<< std::fixed << std::setprecision(7) << time_deq << RESET << std::endl;
	}
}
std::list<int> Pmerge::getList() const
{
	return (_list);
}
std::deque<int> Pmerge::getDeq() const
{
	return (_deq);
}

void Pmerge::mergeList(std::list<int> &left, std::list<int> &right,
	std::list<int> &result)
{
	std::list<int>::iterator it_left = left.begin();
	std::list<int>::iterator it_right = right.begin();
	while (it_left != left.end() && it_right != right.end())
	{
		if (*it_left <= *it_right)
		{
			result.push_back(*it_left);
			++it_left;
		}
		else
		{
			result.push_back(*it_right);
			++it_right;
		}
	}
	result.insert(result.end(), it_left, left.end());
	result.insert(result.end(), it_right, right.end());
}

void Pmerge::recursiveMergeSortList(std::list<int> &container)
{
	if (container.size() <= 1)
		return ;
	std::list<int> left, right;
	std::list<int>::iterator it = container.begin();
	std::advance(it, container.size() / 2);
	left.splice(left.begin(), container, container.begin(), it);
	right.splice(right.begin(), container);
	recursiveMergeSortList(left);
	recursiveMergeSortList(right);
	mergeList(left, right, container);
}

void Pmerge::mergeDeque(std::deque<int> &left, std::deque<int> &right,
	std::deque<int> &result)
{
	std::deque<int>::iterator it_left = left.begin();
	std::deque<int>::iterator it_right = right.begin();
	while (it_left != left.end() && it_right != right.end())
	{
		if (*it_left <= *it_right)
		{
			result.push_back(*it_left);
			++it_left;
		}
		else
		{
			result.push_back(*it_right);
			++it_right;
		}
	}
	result.insert(result.end(), it_left, left.end());
	result.insert(result.end(), it_right, right.end());
}

void Pmerge::recursiveMergeSortDeque(std::deque<int> &container)
{
	int	size;
	int	i;

	if (container.size() <= 1)
		return ;
	std::deque<int> left, right;
	size = container.size();
	i = 0;
	for (std::deque<int>::iterator it = container.begin(); it != container.end(); ++it)
	{
		if (i < size / 2)
		{
			left.push_back(*it);
		}
		else
			right.push_back(*it);
		i++;
	}
	recursiveMergeSortDeque(left);
	recursiveMergeSortDeque(right);
	container.clear();
	mergeDeque(left, right, container);
}
