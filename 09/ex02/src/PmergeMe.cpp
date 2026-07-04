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
			throw(std::runtime_error("non positive integer not allowed: \"" + var_to_str(av[i]) + "\"" ));
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
	for (vec_int::const_iterator it = _array_vec.begin(); it != _array_vec.end(); it++)
		std::cout << *it << " ";
	std::cout << ";\n";
}

void PmergeMe::print_time(std::string container) const
{
	std::cout << CYN "time to process a range of [" DEF << _array_vec.size();
	std::cout <<  CYN "] values with std::" DEF << container << CYN ":\t" DEF;
	std::cout << _bench_end_time - _bench_start_time << "μs" << std::endl;
}

void PmergeMe::print_comp(std::string container) const
{
	std::cout << CYN "comparisons done on a range of [" DEF << _array_vec.size();
	std::cout <<  CYN "] values with std::" DEF << container << CYN ":\t" DEF;
	std::cout << _comp_amount << std::endl;
}

void PmergeMe::pair_print_vec(const vec_int &vec, size_t pair_size) const
{
	if (!DEBUG)
		return ;
	size_t i = 1;
	std::cout << BLK "\t";
	for (vec_int::const_iterator it = vec.begin(); it != vec.end(); it++)
	{
		if (i == pair_size / 2)
			std::cout << CYN;

		if (i == pair_size)
		{
			std::cout << DEF "\r(b) " << *it << BLK "\t(s)\n\t";
			i = 0;
		}
		else
			std::cout << "\t" << *it;
		if (i == pair_size / 2)
			std::cout << BLK;
		i++;
	}
	std::cout << DEF "\n";
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

	merge_vec(_array_vec, 2);
	
	_bench_end_time = get_curr_time();
}

void PmergeMe::merge_vec(vec_int &vec, size_t pair_size)
{
	if (pair_size > vec.size())
		return;
	
	// !!  n = number of players; 2r = n || 2r + 1 = n; r = half of players
	// -- pair off 2r of the players and let the pairs play in the first round
	// leaving one man out if n is odd
	merge_sort_segments_vec(vec, pair_size);

	if (DEBUG)
	{
		std::cout << RED "after sort segments\n" DEF;
		pair_print_vec(vec, pair_size);
	}

	// !! recursively sort the [ n / 2 ] larger elements from each pair
	// -- instead of comparing every number only compare the pairs
	// -- after that the pairs become pairs of pairs (less comparisons)
	merge_vec(vec, pair_size * 2);
	
	insert_segments_vec(vec, pair_size);

	if (DEBUG)
	{
		std::cout << RED "after insert segments " << pair_size << "\n" DEF;
		pair_print_vec(vec, pair_size / 2);
	}
}

void PmergeMe::merge_sort_segments_vec(vec_int &vec, size_t pair_size)
{
	if (DEBUG)
		std::cout << YEL "\n\nSORT SEGMENTS " DEF << pair_size << "\n\n";

	vec_int::iterator begin = vec.begin();
	vec_int::iterator end = begin + pair_size - 1;
	
	while (end < vec.end())
	{
		vec_int::iterator anchor = begin + ((end - begin + 1) / 2) - 1;

		if (DEBUG)
		{
			std::cout << "(S) " << *begin << "\t\t(B) " << *end << "\n";
			std::cout << YEL "anchor:\t\t" DEF "(A) " << *anchor << DEF "\n";
		}

		if (bigger_than(*anchor, *end))
		{
			std::swap_ranges(begin, anchor + 1, anchor + 1);
			if (DEBUG)
				std::cout << RED "swaping ranges...\n\n" DEF;
		}
		else if (DEBUG)
			std::cout << GRN "correct order!\n\n" DEF;

		begin += pair_size;
		end += pair_size;
	}
}

void PmergeMe::insert_segments_vec(vec_int &vec, size_t pair_size)
{
	if (DEBUG)
		std::cout << YEL "\n\nINSERT SEGMENTS " DEF << pair_size << "\n\n";

	if (vec.size() < pair_size)
		return ;

	// "call b1 and the a's the "main chain"""
	vec_int main_chain;
	main_chain.reserve(vec.size());

	// remaining b's and the stashed value are pending
	// keep them associated with their "bigger" pair value
	vec_match pending;

	size_t odd_elems = ((vec.size() % pair_size >= pair_size / 2) * (pair_size / 2));
	pending.reserve(((vec.size() - (vec.size() % pair_size) ) / 2) - (pair_size / 2) + odd_elems);

	// the jacobsthal numbers for the pending insertion index
	vec_size jacob;
	prep_segment_insertion_vec(main_chain, pending, jacob, vec, pair_size);

	if (!pending.empty())
		binary_insert_segment_vec(main_chain, pending, jacob, pair_size / 2);

	vec = main_chain;
}

void PmergeMe::prep_segment_insertion_vec(vec_int &main_chain, vec_match &pending, vec_size &jacob, vec_int &pairs, size_t pair_size)
{
	size_t pending_max = (pending.capacity() ? pending.capacity() : 1) - 1;
	jacob.push_back((pair_size - 1 > pending_max ? pending_max : pair_size - 1));

	for (size_t i = 4; jacob.back() < pending_max; i++)
	{
		jacob.push_back((jacobsthal_gen(i) - 1) * (pair_size / 2) - 1);
		if (jacob.back() > pending_max)
			jacob.back() = pending_max;
	}

	// b1, a1, b2, a2, ..., bn, an
	// b1 = [ begin, ..., anchor - 1 ] 
	// a1 = [ anchor, ..., end ] 

	main_chain.insert(main_chain.end(), pairs.begin(), pairs.begin() + pair_size); // b1 + a1
	
	vec_size::iterator insertion_pivot = jacob.begin();
	vec_int::iterator begin = pairs.begin() + pair_size;
	
	for (; begin + pair_size - 1 < pairs.end(); begin += pair_size)
	{
		vec_int::iterator end = begin + pair_size;
		if (pending.size() > *insertion_pivot)
			insertion_pivot++;

		size_t offset = (insertion_pivot == jacob.begin() ? 0 : *(insertion_pivot - 1) + 1);
		offset += *insertion_pivot - pending.size();
		
		if (DEBUG)
			std::cout << YEL "[ offset ]\t" DEF << offset << "\n";

		for (vec_int::iterator it = begin; it < end - (pair_size / 2); it++)
		{
			pending.push_back(std::make_pair(*it, main_chain.end() + offset));
			if (DEBUG)
				std::cout << YEL "[ add pending ]\t" DEF << pending.back().first << "\n";
		}
		
		main_chain.insert(main_chain.end(), begin + (pair_size / 2), end);
	}

	if (pairs.size() % pair_size >= pair_size / 2) // is odd
	{
		for (size_t i = 0; i < (pair_size / 2); i++)
		{
			if (DEBUG)
				std::cout << YEL "[ odd offset ]\t\t" DEF << - 1 + (jacob.end() - 2 < jacob.begin() ? 0 : *(jacob.end() - 2) + 1) + jacob.back() - pending.size() << "\n";
			pending.push_back(std::make_pair(*(begin++), main_chain.end() - 1 + (jacob.end() - 2 < jacob.begin() ? 0 : *(jacob.end() - 2) + 1) + jacob.back() - pending.size()));
		}
	}

	if (DEBUG)
	{
		std::cout << YEL "\n[ main chain ]\t" DEF;
		for (vec_int::const_iterator it = main_chain.begin(); it != main_chain.end(); it++)
			std::cout << *it << " ";
		std::cout << ";\n";
		std::cout << YEL "[ pending ]\t" DEF;
		for (vec_match::const_iterator it = pending.begin(); it != pending.end(); it++)
			std::cout << it->first << " ";
		std::cout << ";\n";
	}

	if (begin < pairs.end())
		main_chain.insert(main_chain.end(), begin, pairs.end());

	if (DEBUG)
	{
		std::cout << YEL "[ main chain with leftovers ]\t" DEF;
		for (vec_int::const_iterator it = main_chain.begin(); it != main_chain.end(); it++)
			std::cout << *it << " ";
		std::cout << ";\n";
		std::cout << std::endl;
	}

}

void PmergeMe::binary_insert_segment_vec(vec_int &main_chain, vec_match &pending, vec_size &jacob, int elem_size)
{
	if (DEBUG)
	{
		std::cout << YEL "\n\nBINARY INSERT SEGMENTS " DEF << elem_size * 2 << "\n\n";
		std::cout << YEL "[ jacob idxs ]\t" DEF;
		for (vec_size::iterator it = jacob.begin(); it != jacob.end(); it++)
			std::cout << *it << " ";
		std::cout << ";\n";
		std::cout << std::endl;	
	}

	vec_match::iterator curr_insert;
	vec_match::iterator already_inserted =  pending.begin() - 1;

	for (vec_size::iterator curr_jacob = jacob.begin(); curr_jacob != jacob.end(); curr_jacob++)
	{
		curr_insert = (pending.begin() + *curr_jacob >= pending.end() ? pending.end() - 1 : pending.begin() + *curr_jacob);

		while (curr_insert > already_inserted)
		{
			if (DEBUG)
				std::cout << YEL "\n[ curr insert ]\t" DEF << curr_insert->first << " (b)" << *curr_insert->second << ";\n\n";
			
			binary_search_vec(main_chain, elem_size, curr_insert);
			curr_insert -= elem_size;
		}
		
		already_inserted = (pending.begin() + *curr_jacob >= pending.end() ? pending.end() - 1 : pending.begin() + *curr_jacob);
		
		if (DEBUG)
			std::cout << GRN "\n[ CURR JACOB DONE ]\n\n" DEF;
	}
}

void PmergeMe::binary_search_vec(vec_int &main_chain, int elem_size, vec_match::iterator &curr_insert)
{
	vec_int::iterator begin = main_chain.begin() + elem_size - 1;
	vec_int::iterator end = curr_insert->second;

	while (true)
	{
		if (DEBUG)
			std::cout << YEL "[ range ]\t" DEF << "(b)" << *begin << " (e)" << *end << ";\n";

		if (end - begin <= elem_size)
		{
			if (DEBUG)
			{
				std::cout << YEL "[ at end ]\t" DEF << (end ==  curr_insert->second) << ";\n";
				std::cout << YEL "[ at begin ]\t" DEF << (begin ==  main_chain.begin() + elem_size - 1) << ";\n";
			}
			
			vec_int::iterator placement;

			if (end ==  curr_insert->second && bigger_than(curr_insert->first, *end))
				placement = end + 1;
			else if (begin ==  main_chain.begin() + elem_size - 1 && bigger_than(*begin, curr_insert->first))
				placement = main_chain.begin();
			else
				placement = begin + 1;
				
			for (vec_match::iterator it = curr_insert; it > curr_insert - elem_size; it--)
				main_chain.insert(placement, it->first);
			
			if (DEBUG)
			{
				std::cout << GRN "\n[ POSITION FOUND ]\n" DEF;
				std::cout << YEL "[ new main chain ]\t" DEF;
				for (vec_int::const_iterator it = main_chain.begin(); it != main_chain.end(); it++)
					std::cout << *it << " ";
				std::cout << ";\n";
			}
			break;
		}

		vec_int::iterator anchor = begin + ((((end - begin) / elem_size) / 2) * elem_size);
		
		if (DEBUG)
			std::cout << YEL "[ anchor ]\t" DEF << *anchor << ";\n\n";

		if (bigger_than(curr_insert->first, *anchor))
			begin = anchor;
		else
			end = anchor;
	}
}

void PmergeMe::sort_deque(void)
{
	_bench_start_time = get_curr_time();
	_comp_amount = 0;

	std::cout << "sort_deque in process... " << std::endl;

	_bench_end_time = get_curr_time();
}

/// @return current time in microseconds
time_t	PmergeMe::get_curr_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000) + tv.tv_usec);
}

bool PmergeMe::bigger_than(int x, int y)
{
	_comp_amount++;
	return (x > y);
}
size_t PmergeMe::jacobsthal_gen(size_t n) const
{
	size_t result = (std::pow(2, n) - std::pow(-1, n)) / 3;
	if (DEBUG)
		std::cout << RED "[ jacobsthal ]\t" DEF << result << ";\n";
	return (result); // (2^n -(-1)^n) / 3
}
