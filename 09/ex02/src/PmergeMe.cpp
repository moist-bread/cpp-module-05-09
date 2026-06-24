#include "../inc/PmergeMe.hpp"
#include "../inc/utils.tpp"

#include <algorithm> // count

PmergeMe::PmergeMe(void) {}

PmergeMe::PmergeMe(char **av): _bench_start_time(0), _bench_end_time(0)
{
	for (size_t i = 0; av[i]; i++)
	{
		_array_vec.push_back(str_to_num<int>(av[i]));
		if (_array_vec.back() < 0)
			throw(std::runtime_error("negative integer not allowed: \"" + var_to_str(av[i]) + "\"" ));
		else if (std::count(_array_vec.begin(), _array_vec.end(), _array_vec.back()) > 1)
			throw(std::runtime_error("repeated integer not allowed: \"" + var_to_str(av[i]) + "\"" ));
		if (DEBUG)
			std::cout << "inserted elem: " << av[i] << std::endl;
	}
	_array_deque.insert (_array_deque.begin(), _array_vec.begin(), _array_vec.end());

	print_array("before");
	sort_vec();
	print_array("after");
	print_time("vector");
	sort_deque();
	print_time("deque");
	
}

PmergeMe::PmergeMe(PmergeMe const &source)
{
	*this = source;
}

PmergeMe::~PmergeMe(void) {}

PmergeMe &PmergeMe::operator=(PmergeMe const &source)
{
	if (this != &source)
		(void)source;
	return (*this);
}

void PmergeMe::print_array(std::string str) const
{
	std::cout << CYN "[ "<< str << " ]	" DEF;
	for (std::vector<int>::const_iterator it = _array_vec.begin(); it != _array_vec.end(); it++)
		std::cout << " " << *it;
	std::cout << ";" << std::endl;
}

void PmergeMe::print_time(std::string container) const
{
	std::cout << CYN "time to process a range of [" DEF << _array_vec.size();
	std::cout <<  CYN "] values with std::" << container << ":	" DEF;
	std::cout << _bench_end_time - _bench_start_time << "ms" << std::endl;
}

void PmergeMe::sort_vec(void)
{
	std::cout << "sort_vec in process... " << std::endl;

	_bench_start_time = get_curr_time();
	vector2 pairs;
	
	for ( size_t i = 0; i + 2 < _array_vec.size(); i += 2)
	{
		if (_array_vec[i] > _array_vec[i + 1])
			pairs.push_back(std::make_pair(_array_vec[i], _array_vec[i + 1]));
		else
			pairs.push_back(std::make_pair(_array_vec[i + 1], _array_vec[i]));
	}

	std::cout << "\npairs...\n\n";
	for (vector2::const_iterator it = pairs.begin(); it != pairs.end(); it++)
		std::cout << "(b)" << it->first << " \t\t(s)" << it->second << "\n";
	std::cout << std::endl;


	// !! Recursively sort the ⌊ n / 2 ⌋ larger elements from each pair
	// -- instead of comparing every number only compare the pairs
	// -- after that the pairs become pairs of pairs, so for 8 numbers you only need 1 comparison
	merge_vec(pairs, pairs.begin(), pairs.end() - 1);

	_bench_end_time = get_curr_time();
}

void PmergeMe::merge_vec(vector2 &vec, vector2::iterator begin, vector2::iterator end)
{
	if (end - begin <= 2 ) // less than 2 elems
		return ;
	
	vector2::iterator pivot = begin + ((end - begin) / 2);
	std::cout << "math: " << ((end - begin) / 2) << std::endl;
	std::cout << "\npivot: ";
	std::cout << "(b)" << pivot->first << " \t\t(s)" << pivot->second << "\n";
	
	merge_vec(vec, begin, pivot);
	merge_vec(vec, pivot, end);
	
	merge_swap_segment_vec(vec, begin, end);
	(void)vec;
	(void)begin;
	(void)end;
}

void PmergeMe::merge_swap_segment_vec(vector2 &vec, vector2::iterator begin, vector2::iterator end)
{
	std::cout << "\nmerge swapping: ";
	std::cout << "(b)" << begin->first << "\t(s)" << begin->second << "\t\t(b)" << end->first << "\t(s)" << end->second << "\n";

	vector2::iterator anchor = begin + ((end - begin) / 2) + 1;
	std::cout << "\nanchor: ";
	std::cout << "(b)" << anchor->first << " \t\t(s)" << anchor->second << "\n";

	(void)vec;
	(void)begin;
	(void)end;
}

#include<unistd.h>

void PmergeMe::sort_deque(void)
{
	_bench_start_time = get_curr_time();
	std::cout << "sort_deque in process... " << std::endl;
	// sleep(4);
	_bench_end_time = get_curr_time();
}

/// @return current time in milliseconds
time_t	PmergeMe::get_curr_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}