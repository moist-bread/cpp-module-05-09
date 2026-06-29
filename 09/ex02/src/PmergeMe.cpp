#include "../inc/PmergeMe.hpp"
#include "../inc/utils.tpp"

#include <algorithm> // count
#include <math.h> // pow

PmergeMe::PmergeMe(void) {}

PmergeMe::PmergeMe(char **av): _bench_start_time(0), _bench_end_time(0), _comp_amount(0)
{
	for (size_t i = 0; av[i]; i++)
	{
		_array_vec.push_back(str_to_num<int>(av[i]));
		if (_array_vec.back() < 0)
			throw(std::runtime_error("negative integer not allowed: \"" + var_to_str(av[i]) + "\"" ));
		else if (std::count(_array_vec.begin(), _array_vec.end(), _array_vec.back()) > 1)
			throw(std::runtime_error("repeated integer not allowed: \"" + var_to_str(av[i]) + "\"" ));
		if (DEBUG)
			std::cout << YEL "inserted:\t" DEF << av[i] << std::endl;
	}
	if (DEBUG)
		std::cout << std::endl;
	_array_deque.insert (_array_deque.begin(), _array_vec.begin(), _array_vec.end());

	print_array("before");
	
	sort_vec();
	print_array("after");
	print_time("vector");
	print_comp("vector");
	
	sort_deque();
	print_time("deque ");
	print_comp("deque ");
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
	std::cout << CYN "[ "<< str << " ]\t" DEF;
	for (std::vector<int>::const_iterator it = _array_vec.begin(); it != _array_vec.end(); it++)
		std::cout << *it << " ";
	std::cout << ";" << std::endl;
}

void PmergeMe::print_time(std::string container) const
{
	std::cout << CYN "time to process a range of [" DEF << _array_vec.size();
	std::cout <<  CYN "] values with std::" DEF << container << CYN ":\t" DEF;
	std::cout << _bench_end_time - _bench_start_time << "ms" << std::endl;
}

void PmergeMe::print_comp(std::string container) const
{
	std::cout << CYN "comparisons done on a range of [" DEF << _array_vec.size();
	std::cout <<  CYN "] values with std::" DEF << container << CYN ":\t" DEF;
	std::cout << _comp_amount << std::endl;
}

void PmergeMe::sort_vec(void)
{
	_bench_start_time = get_curr_time();
	_comp_amount = 0;

	if (_array_vec.size() == 1)
	{
		_bench_end_time = get_curr_time();
		return ;
	}

	vector2 pairs;
	
	//  n = number of players; 2r = n || 2r + 1 = n; r = half of players

	// Pair off 2r of the players and let the pairs play in the first round leaving
	// one man out if n is odd
	for ( size_t i = 0; i + 2 <= _array_vec.size(); i += 2)
	{
		if (_array_vec[i] > _array_vec[i + 1])
			pairs.push_back(std::make_pair(_array_vec[i], _array_vec[i + 1]));
		else
			pairs.push_back(std::make_pair(_array_vec[i + 1], _array_vec[i]));
	}

	std::cout << YEL "\npairs...\n" DEF;
	for (vector2::const_iterator it = pairs.begin(); it != pairs.end(); it++)
		std::cout << "(b)" << it->first << BLK " \t\t(s)" << it->second << DEF "\n";
	std::cout << std::endl;
	if (_array_vec.size() % 2)
		std::cout << "stached: (n)" << _array_vec[_array_vec.size() - 1] << "\n\n";



	// !! Recursively sort the ⌊ n / 2 ⌋ larger elements from each pair
	// -- instead of comparing every number only compare the pairs
	// -- after that the pairs become pairs of pairs, so for 8 numbers you only need 1 comparison
	if (pairs.empty())
	{
		_bench_end_time = get_curr_time();
		return;
	}

	merge_vec(pairs, pairs.begin(), pairs.end() - 1);

	std::cout << YEL "\npairs...\n" DEF;
	for (vector2::const_iterator it = pairs.begin(); it != pairs.end(); it++)
		std::cout << "(b)" << it->first << BLK " \t\t(s)" << it->second << DEF "\n";
	std::cout << std::endl;

	// "call b1 and the a's the "main chain"""
	std::vector<int> main_chain;
	main_chain.reserve(_array_vec.size());

	// remaining b's and the stashed value are pending
	// keep them associated with their "bigger" pair value
	vec_match pending;
	pending.reserve(pairs.size() + (_array_vec.size() % 2));

	main_chain.push_back(pairs.begin()->second);
	main_chain.push_back(pairs.begin()->first);
	for (vector2::const_iterator it = pairs.begin() + 1; it != pairs.end(); it++)
	{
		main_chain.push_back(it->first);
		pending.push_back(std::make_pair(it->second, main_chain.end()));
	}
	if (_array_vec.size() % 2)
		pending.push_back(std::make_pair(_array_vec[_array_vec.size() - 1], main_chain.end()));
	
	binary_insert_vec(main_chain, pending);

	_bench_end_time = get_curr_time();
}


void PmergeMe::merge_vec(vector2 &vec, vector2::iterator begin, vector2::iterator end)
{
	std::cout << "\nbegin: ";
	std::cout << "(b)" << begin->first << BLK "\t(s)" << begin->second << DEF "\n";
	std::cout << "end: ";
	std::cout << "(b)" << end->first << BLK "\t(s)" << end->second << DEF "\n";

	if (end - begin < 1 )
	{
		std::cout << YEL "solo element" DEF << std::endl;
		return ;
	}
	
	vector2::iterator pivot = begin + ((end - begin + 1) / 2);

	std::cout << "end - begin + 1: " << (end - begin + 1);
	std::cout << " / by 2: " << ((end - begin + 1) / 2) << std::endl;
	std::cout << "pivot: ";
	std::cout << "(b)" << pivot->first << BLK " \t\t(s)" << pivot->second << DEF "\n";
	
	merge_vec(vec, begin, pivot - (begin != pivot));
	merge_vec(vec, pivot + (begin == pivot), end);
	
	std::cout << RED "\nbefore merge swapping\n" DEF;
	for (vector2::const_iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << "(b)" << it->first << BLK " \t\t(s)" << it->second << DEF "\n";
	
	merge_swap_segment_vec(begin, end);
	
	for (vector2::const_iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << "(b)" << it->first << BLK " \t\t(s)" << it->second << DEF "\n";
}

void PmergeMe::merge_swap_segment_vec(vector2::iterator begin, vector2::iterator end)
{
	vector2::iterator anchor = begin + ((end - begin + 1) / 2);

	std::cout << YEL "\nmerge swapping:\t" DEF;
	std::cout << "(b)" << begin->first << BLK "\t(s)" << begin->second;
	std::cout << DEF "\t\t(b)" << end->first << BLK "\t(s)" << end->second << DEF "\n";
	std::cout << YEL "end - begin + 1: " DEF << (end - begin + 1);
	std::cout << YEL " / by 2: " DEF << ((end - begin + 1) / 2) << std::endl;
	std::cout << YEL "anchor:\t\t" DEF;
	std::cout << "(b)" << anchor->first << BLK " \t(s)" << anchor->second << DEF "\n\n";

	// sorting pairs of pairs based on the anchor (leaving it unsorted) 
	// if (bigger_than(begin->first, anchor->first))
	// {
	// 	if (!((end - begin + 1) % 2))
	// 	{
	// 		std::swap_ranges(begin, anchor, anchor);
	// 		std::cout << RED "\npost swap ranges...\n" DEF;
	// 	}
	// 	else
	// 	{
	// 		while (anchor <= end)
	// 		{
	// 			std::cout << "\nanchor in loop: ";
	// 			std::cout << "(b)" << anchor->first << BLK " \t\t(s)" << anchor->second << DEF "\n";
	// 			std::swap(*begin, *anchor);
	// 			anchor++;
	// 			begin++;
	// 		}
	// 		std::cout << RED "\nOTHER swap...\n" DEF;
	// 	}
	// }
	// else
	// 	std::cout << GRN "\ncorrect order!\n" DEF;

	// merge sort (temporary, to be replaced with merge insert)
	while (begin <= end && anchor <= end)
	{
		if (bigger_than(begin->first, anchor->first))
		{
			std::cout << RED "swap an w/ bg:\t" DEF;
			std::cout << "(b)" << anchor->first << BLK "\t(s)" << anchor->second;
			std::cout << DEF "\t\t(b)" << begin->first << BLK "\t(s)" << begin->second << DEF "\n";

			std::pair<int, int> temp = *anchor;
			std::copy_backward(begin, anchor, anchor + 1);
			*begin = temp;
			anchor++;
		}
		else
			std::cout << GRN "correct order\n" DEF;
		begin++;
		if (begin == anchor)
			anchor++;
	}
	std::cout << std::endl;
}
void PmergeMe::binary_insert_vec(std::vector<int> &main_chain, vec_match &pending)
{
	(void)main_chain;
	(void)pending;
	std::cout << YEL "[ main chain ]\t" DEF;
	for (std::vector<int>::const_iterator it = main_chain.begin(); it != main_chain.end(); it++)
		std::cout << *it << " ";
	std::cout << ";" << std::endl;
	std::cout << std::endl;

	std::cout << YEL "[ pending ]\t" DEF;
	for (vec_match::const_iterator it = pending.begin(); it != pending.end(); it++)
		std::cout << it->first << " (b)" << *it->second << ", ";
	std::cout << ";" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << YEL "[ jacob ]\t" DEF;
	for (size_t i = 0; i < _array_vec.size(); i++)
		std::cout << jacobsthal_gen(i) << " ";
	std::cout << ";" << std::endl;
	std::cout << std::endl;

	main_chain.insert(main_chain.begin(), 1000);
	main_chain.insert(main_chain.begin() + 2, 100);

	std::cout << YEL "[ pending ]\t" DEF;
	for (vec_match::const_iterator it = pending.begin(); it != pending.end(); it++)
		std::cout << it->first << " (b)" << *it->second << ", ";
	std::cout << ";" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}

void PmergeMe::sort_deque(void)
{
	_bench_start_time = get_curr_time();
	_comp_amount = 0;

	std::cout << "sort_deque in process... " << std::endl;
	// sleep (1);

	_bench_end_time = get_curr_time();
}

/// @return current time in milliseconds
time_t	PmergeMe::get_curr_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

bool PmergeMe::bigger_than(int x, int y)
{
	_comp_amount++;
	return (x > y);
}
size_t PmergeMe::jacobsthal_gen(size_t n) const
{
	return ((std::pow(2, n) - std::pow(-1, n)) / 3); // (2^n -(-1)^n) / 3
}
