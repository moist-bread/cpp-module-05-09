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
	std::cout << ";" << std::endl;
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
	
	// !!  n = number of players; 2r = n || 2r + 1 = n; r = half of players
	// -- pair off 2r of the players and let the pairs play in the first round
	// leaving one man out if n is odd
	for (size_t i = 0; i + 2 <= _array_vec.size(); i += 2)
	{
		if (bigger_than(_array_vec[i], _array_vec[i + 1]))
			pairs.push_back(std::make_pair(_array_vec[i], _array_vec[i + 1]));
		else
			pairs.push_back(std::make_pair(_array_vec[i + 1], _array_vec[i]));
	}

	bool is_odd = (_array_vec.size() % 2);

	if (DEBUG)
	{
		std::cout << YEL "\npairs...\n" DEF;
		for (vector2::const_iterator it = pairs.begin(); it != pairs.end(); it++)
			std::cout << "(b)" << it->first << BLK " \t\t(s)" << it->second << DEF "\n";
		std::cout << std::endl;
		if (is_odd)
			std::cout << "stached: (o)" << _array_vec.back() << "\n\n";
	}

	// !! recursively sort the [ n / 2 ] larger elements from each pair
	// -- instead of comparing every number only compare the pairs
	// -- after that the pairs become pairs of pairs (less comparisons)

	merge_vec(pairs, 2);

	// old_merge_vec(pairs, pairs.begin(), pairs.end() - 1); // -- REPLACE

	if (DEBUG)
	{
		std::cout << YEL "\nsorted pairs...\n" DEF;
		for (vector2::const_iterator it = pairs.begin(); it != pairs.end(); it++)
			std::cout << "(b)" << it->first << BLK " \t\t(s)" << it->second << DEF "\n";
		std::cout << std::endl;
	}

	// "call b1 and the a's the "main chain"""
	vec_int main_chain;
	main_chain.reserve(_array_vec.size());

	// remaining b's and the stashed value are pending
	// keep them associated with their "bigger" pair value
	vec_match pending;
	pending.reserve(pairs.size() - 1 + is_odd);

	// the jacobsthal numbers for the pending insertion index
	vec_size jacob;

	prep_for_insertion_vec(main_chain, pending, jacob, pairs, is_odd);
	if (!pending.empty())
		binary_insert_vec(main_chain, pending, jacob);

	_array_vec = main_chain;
	_bench_end_time = get_curr_time();
}


void PmergeMe::merge_vec(vector2 &vec, size_t pair_size)
{
	if (pair_size >= vec.size())
		return;
	
	merge_sort_segments_vec(vec, pair_size);

	std::cout << RED "after sort segments\n" DEF;
	for (vector2::const_iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << "(b)" << it->first << BLK " \t\t(s)" << it->second << DEF "\n";

	merge_vec(vec, pair_size * 2);
	
	insert_segments_vec(vec, pair_size);

	std::cout << RED "after insert segments " << pair_size << "\n" DEF;
	for (vector2::const_iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << "(b)" << it->first << BLK " \t\t(s)" << it->second << DEF "\n";

}

void PmergeMe::merge_sort_segments_vec(vector2 &vec, size_t pair_size)
{
	vector2::iterator begin = vec.begin();
	vector2::iterator end = begin + pair_size - 1;

	std::cout << YEL "\nsort segments:\n\n" DEF;
	
	while (end < vec.end())
	{
		vector2::iterator anchor = begin + ((end - begin + 1) / 2) - 1;

		std::cout << "(b)" << begin->first << BLK "\t(s)" << begin->second;
		std::cout << DEF "\t\t(b)" << end->first << BLK "\t(s)" << end->second << DEF "\n";
		std::cout << YEL "end - begin + 1: " DEF << (end - begin + 1);
		std::cout << YEL " / by 2: " DEF << ((end - begin + 1) / 2) << std::endl;
		std::cout << YEL "anchor:\t\t" DEF;
		std::cout << "(b)" << anchor->first << BLK " \t(s)" << anchor->second << DEF "\n";

		if (bigger_than(anchor->first, end->first))
		{
			std::swap_ranges(begin, anchor + 1, anchor + 1);
			std::cout << RED "swaping ranges...\n\n" DEF;
		}
		else
			std::cout << GRN "correct order!\n\n" DEF;

		begin += pair_size;
		end += pair_size;
	}
}

void PmergeMe::insert_segments_vec(vector2 &vec, size_t pair_size)
{
	std::cout << YEL "\ninsert segments:\n\n" DEF;

	std::cout << YEL "[ pair_size ]\t" DEF << pair_size << ";\n";

	// "call b1 and the a's the "main chain"""
	vector2 main_chain;
	main_chain.reserve(vec.size());

	// remaining b's and the stashed value are pending
	// keep them associated with their "bigger" pair value
	vector2_match pending;


	// pending.reserve(pairs.size() - 1 + is_odd);

	
	size_t odd_elems = ((vec.size() % pair_size >= pair_size / 2) * (pair_size / 2));
	pending.reserve(((vec.size() - (vec.size() % pair_size) ) / 2) - (pair_size / 2) + odd_elems);

	std::cout << YEL "[ vec.size() ]\t" DEF << vec.size() << ";\n";
	std::cout << YEL "[ odds ]\t" DEF << odd_elems << ";\n";



	// the jacobsthal numbers for the pending insertion index
	vec_size jacob;
	prep_segment_insertion_vec(main_chain, pending, jacob, vec, pair_size);

	if (!pending.empty())
		binary_insert_segment_vec(main_chain, pending, jacob, pair_size / 2);

	vec = main_chain;
}

void PmergeMe::prep_segment_insertion_vec(vector2 &main_chain, vector2_match &pending, vec_size &jacob, vector2 &pairs, size_t pair_size)
{
	size_t pending_max = (pending.capacity() ? pending.capacity() : 1) - 1;
	jacob.push_back((pair_size - 1 > pending_max ? pending_max : pair_size - 1));

	std::cout << YEL "[ pending_max ]\t" DEF << pending_max << ";\n";
	std::cout << YEL "[ pending.capacity() ]\t" DEF << pending.capacity() << ";\n";
	for (size_t i = 4; jacob.back() < pending_max; i++)
	{
		jacob.push_back((jacobsthal_gen(i) - 2) * (pair_size / 2));
		if (jacob.back() > pending_max)
			jacob.back() = pending_max;
	}

	bool is_odd = (pairs.size() % pair_size >= pair_size / 2);
	std::cout << YEL "[ is_odd ]\t" DEF << is_odd << ";\n\n";

	// b1, a1, b2, a2, ..., bn, an
	// b1 = [ begin, ..., anchor - 1 ] 
	// a1 = [ anchor, ..., end ] 

	// vector2::iterator anchor = begin + ((end - begin + 1) / 2);
	
	main_chain.insert(main_chain.end(), pairs.begin(), pairs.begin() + pair_size); // b1 + a1
	
	vec_size::iterator insertion_pivot = jacob.begin();

	vector2::iterator begin = pairs.begin() + pair_size;
	
	for (; begin + pair_size - 1 < pairs.end(); begin += pair_size)
	{
		vector2::iterator end = begin + pair_size;
		if (pending.size() > *insertion_pivot * pair_size)
			insertion_pivot++;
		





		size_t offset = (insertion_pivot == jacob.begin() ? 0 : (*(insertion_pivot - 1) * pair_size) + pair_size);

		std::cout << YEL "[ prev jacob insertions ]\t" DEF << offset << ";\n";

		offset += (*insertion_pivot - (*insertion_pivot % (pair_size / 2)));
		// offset += (*insertion_pivot - (*insertion_pivot % (pair_size / 2))) - pending.size() + (pending.size() % (pair_size / 2));

		std::cout << YEL "[ (*insertion_pivot - (*insertion_pivot % (pair_size / 2))) ]\t" DEF << (*insertion_pivot - (*insertion_pivot % (pair_size / 2))) << ";\n";
		// std::cout << YEL "[ pending.size() ]\t" DEF << pending.size() << ";\n";
		// std::cout << YEL "[ (pending.size() % (pair_size / 2)) ]\t" DEF << (pending.size() % (pair_size / 2)) << ";\n";
		// std::cout << YEL "[ distance from pivot ]\t" DEF << (*insertion_pivot - (*insertion_pivot % (pair_size / 2))) - pending.size() + (pending.size() % (pair_size / 2)) << ";\n";
		std::cout << YEL "[ distance from pivot ]\t" DEF << (*insertion_pivot - (*insertion_pivot % (pair_size / 2))) << ";\n";

		// if (is_odd && insertion_pivot == jacob.end() - 1)
			// offset -= pair_size / 2;
		
		std::cout << YEL "[ offset ]\t" DEF << offset << ";\n";

		sleep(1);





		for (vector2::iterator it = begin; it < end - (pair_size / 2); it++)
		{
			pending.push_back(std::make_pair(*it, main_chain.end() + (pair_size / 2) + offset));
			std::cout << YEL "[ added to pending ]\t" DEF;
			std::cout << (pending.end() - 1)->first.first << " (b) " BLK << (pending.end() - 1)->second->first << DEF "\n";
		}
		
		main_chain.insert(main_chain.end(), begin + (pair_size / 2), end);
	}

	if (is_odd)
	{
		for (size_t i = 0; i < (pair_size / 2); i++)
			pending.push_back(std::make_pair(*(begin++), main_chain.end() + 1 + (insertion_pivot == jacob.begin() ? 0 : *(insertion_pivot - 1) + pair_size + (pair_size / 2))));
	}

	std::cout << YEL "[ main chain ]\t" DEF;
	for (vector2::const_iterator it = main_chain.begin(); it != main_chain.end(); it++)
		std::cout << it->first << " ";
	std::cout << ";" << std::endl;

	std::cout << YEL "[ pending ]\t" DEF;
	for (vector2_match::const_iterator it = pending.begin(); it != pending.end(); it++)
		std::cout << it->first.first << " (b) " BLK << it->second->first << DEF ", ";
	std::cout << ";" << std::endl;

	if (begin < pairs.end())
		main_chain.insert(main_chain.end(), begin, pairs.end());
	std::cout << YEL "[ main chain with leftovers ]\t" DEF;
	for (vector2::const_iterator it = main_chain.begin(); it != main_chain.end(); it++)
		std::cout << it->first << " ";
	std::cout << ";" << std::endl;
	std::cout << std::endl;

}

void PmergeMe::binary_insert_segment_vec(vector2 &main_chain, vector2_match &pending, vec_size &jacob, int elem_size)
{
	std::cout << YEL "\nbinary insert segments:\n\n" DEF;

	std::cout << YEL "[ elem_size ]\t" DEF << elem_size << ";\n";

	std::cout << YEL "[ jacob indexes ]\t" DEF;
	for (vec_size::iterator it = jacob.begin(); it != jacob.end(); it++)
		std::cout << *it << " ";
	std::cout << ";" << std::endl;
	std::cout << std::endl;	

	(void)main_chain;
	(void)pending;
	(void)jacob;
	(void)elem_size;

	vector2_match::iterator curr_insert;
	vector2_match::iterator already_inserted =  pending.begin() - 1;

	for (vec_size::iterator curr_jacob = jacob.begin(); curr_jacob != jacob.end(); curr_jacob++)
	{
		(void)already_inserted;
		curr_insert = (pending.begin() + *curr_jacob >= pending.end() ? pending.end() - 1 : pending.begin() + *curr_jacob);

		while (curr_insert > already_inserted)
		{
			std::cout << YEL "\n[ curr insert ]\t" DEF;
			std::cout << curr_insert->first.first << " (b)" << curr_insert->second->first << ";\n\n";
			
			vector2::iterator begin = main_chain.begin() + elem_size - 1;
			vector2::iterator end = curr_insert->second;

			
			while (true)
			{
				std::cout << YEL "[ range ]\t" DEF;
				std::cout << "(b)" << begin->first << " (e)" << end->first << ";\n";

				std::cout << YEL "[ GAP ]\t" DEF << (end - begin) << ";\n";
				if (end - begin <= elem_size * 2)
				{
					vector2::iterator placement;
					if (bigger_than(curr_insert->first.first, begin->first))
						placement = end;
					else
						placement = begin;
						
					for (vector2_match::iterator it = curr_insert - elem_size; it < curr_insert; it++)
						main_chain.insert(placement++, it->first);
					
					std::cout << GRN "[ POSITION FOUND ]\n" DEF;
					break;
				}

				vector2::iterator anchor = begin + ((end - begin - 2) / 2);
				std::cout << YEL "[ DIFF ]\t" DEF << (end - begin) << ";\n";
				std::cout << YEL "[ anchor ]\t" DEF << anchor->first << ";\n";

				if (bigger_than(curr_insert->first.first, anchor->first))
					begin = anchor;
				else
					end = anchor;










				sleep(2);
			}


			
			curr_insert -= elem_size;
		}






	}

}

void PmergeMe::old_merge_vec(vector2 &vec, vector2::iterator begin, vector2::iterator end)
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
	
	old_merge_vec(vec, begin, pivot - (begin != pivot));
	old_merge_vec(vec, pivot + (begin == pivot), end);
	
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

void PmergeMe::prep_for_insertion_vec(vec_int &main_chain, vec_match &pending, vec_size &jacob, vector2 &pairs, bool &is_odd)
{
	jacob.push_back(1);
	size_t pending_max = (pending.capacity() ? pending.capacity() : 1) - 1;
	
	for (size_t i = 4; jacob.back() < pending_max; i++)
	{
		jacob.push_back(jacobsthal_gen(i) - 2);
		if (jacob.back() > pending_max)
			jacob.back() = pending_max;
	}
	
	main_chain.push_back(pairs.begin()->second);
	main_chain.push_back(pairs.begin()->first);
	
	vec_size::iterator insertion_pivot = jacob.begin();

	for (vector2::const_iterator it = pairs.begin() + 1; it != pairs.end(); it++)
	{
		if (pending.size() > *insertion_pivot)
			insertion_pivot++;
		
		size_t offset = (insertion_pivot == jacob.begin() ? 0 : *(insertion_pivot - 1) + 1);
		offset += *insertion_pivot - pending.size();
		if (is_odd && insertion_pivot == jacob.end() - 1)
			offset -= 1;

		pending.push_back(std::make_pair(it->second, main_chain.end() + offset));
		main_chain.push_back(it->first);
	}
	
	if (is_odd)
		pending.push_back(std::make_pair(_array_vec.back(), main_chain.end() + (insertion_pivot == jacob.begin() ? 0 : *(insertion_pivot - 1) + 1)));
}

void PmergeMe::binary_insert_vec(vec_int &main_chain, vec_match &pending, vec_size &jacob)
{
	std::cout << YEL "[ main chain ]\t" DEF;
	for (vec_int::const_iterator it = main_chain.begin(); it != main_chain.end(); it++)
		std::cout << *it << " ";
	std::cout << ";" << std::endl;
	std::cout << std::endl;

	std::cout << YEL "[ pending ]\t" DEF;
	for (vec_match::const_iterator it = pending.begin(); it != pending.end(); it++)
		std::cout << it->first << " (b)" << *it->second << ", ";
	std::cout << ";" << std::endl;
	std::cout << std::endl;
		
	vec_match::iterator curr_insert;
	vec_match::iterator already_inserted =  pending.begin() - 1;

	for (vec_size::iterator curr_jacob = jacob.begin(); curr_jacob != jacob.end(); curr_jacob++)
	{
		curr_insert = (pending.begin() + *curr_jacob >= pending.end() ? pending.end() - 1 : pending.begin() + *curr_jacob);

		while (curr_insert > already_inserted)
		{
			std::cout << YEL "\n[ curr insert ]\t" DEF;
			std::cout << curr_insert->first << " (b)" << *curr_insert->second << ";\n\n";
			
			vec_int::iterator begin = main_chain.begin();
			vec_int::iterator end = curr_insert->second;

			while (true)
			{
				std::cout << YEL "[ range ]\t" DEF;
				std::cout << "(b)" << *begin << " (e)" << *end << ";\n";
				
				if (end - begin == 1)
				{
					if (bigger_than(curr_insert->first, *begin))
						main_chain.insert(end, curr_insert->first);
					else
						main_chain.insert(begin, curr_insert->first);
					
					std::cout << GRN "[ POSITION FOUND ]\n" DEF;
					break;
				}

				vec_int::iterator anchor = begin + ((end - begin + 1) / 2);
				std::cout << YEL "[ anchor ]\t" DEF << *anchor << ";\n";

				if (bigger_than(curr_insert->first, *anchor))
					begin = anchor;
				else
					end = anchor;
			}

			std::cout << YEL "\n[ main chain ]\t" DEF;
			for (vec_int::const_iterator it = main_chain.begin(); it != main_chain.end(); it++)
				std::cout << *it << " ";
			std::cout << ";" << std::endl;

			curr_insert--;
		}

		std::cout << GRN "\n[ CURR JACOB DONE ]\n\n" DEF;
		
		std::cout << YEL "[ pending ]\t" DEF;
		for (vec_match::const_iterator it = pending.begin(); it != pending.end(); it++)
			std::cout << it->first << " (b)" << *it->second << ", ";
		std::cout << ";" << std::endl;

		already_inserted = (pending.begin() + *curr_jacob >= pending.end() ? pending.end() - 1 : pending.begin() + *curr_jacob);
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
