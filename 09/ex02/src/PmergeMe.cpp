#include "../inc/PmergeMe.hpp"
#include "../inc/utils.tpp"

#include <algorithm> // count
#include <math.h> // pow
#include <iterator> // distance

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
	_array_list.insert (_array_list.begin(), _array_vec.begin(), _array_vec.end());

	print_array("before");
	
	sort_vec();
	print_array("after");
	print_time("vector");
	print_comp("vector");
	
	sort_list();
	print_time("list ");
	print_comp("list ");
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
	std::cout <<  CYN "] values with std::" DEF << container << CYN ": " DEF;
	std::cout << _bench_end_time - _bench_start_time << "μs" << std::endl;
}

void PmergeMe::print_comp(std::string container) const
{
	std::cout << CYN "comparisons done on a range of [" DEF << _array_vec.size();
	std::cout <<  CYN "] values with std::" DEF << container << CYN ": " DEF;
	std::cout << _comp_amount << std::endl;
}

void PmergeMe::pair_print_vec(const size_t pair_size) const
{
	if (!DEBUG)
		return ;
	size_t i = 1;
	std::cout << BLK "\t";
	for (vec_int::const_iterator it = _array_vec.begin(); it != _array_vec.end(); it++)
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

void PmergeMe::pair_print_list(const size_t pair_size) const
{
	if (!DEBUG)
		return ;
	size_t i = 1;
	std::cout << BLK "\t";
	for (list_int::const_iterator it = _array_list.begin(); it != _array_list.end(); it++)
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

// -->┊ SORTING STD::VECTOR

void PmergeMe::sort_vec(void)
{
	_bench_start_time = get_curr_time();
	_comp_amount = 0;

	if (_array_vec.size() == 1)
	{
		_bench_end_time = get_curr_time();
		return ;
	}

	merge_vec(2);
	
	_bench_end_time = get_curr_time();
}

void PmergeMe::merge_vec(const size_t pair_size)
{
	if (pair_size > _array_vec.size())
		return;
	
	// !!  n = number of players; 2r = n || 2r + 1 = n; r = half of players
	// -- pair off 2r of the players and let the pairs play in the first round
	// leaving one man out if n is odd
	merge_sort_segments_vec(pair_size);

	if (DEBUG)
	{
		std::cout << RED "after sort segments\n" DEF;
		pair_print_vec(pair_size);
	}

	// !! recursively sort the [ n / 2 ] larger elements from each pair
	// -- instead of comparing every number only compare the pairs
	// -- after that the pairs become pairs of pairs (less comparisons)
	merge_vec(pair_size * 2);
	
	insert_segments_vec(pair_size);

	if (DEBUG)
	{
		std::cout << RED "after insert segments " << pair_size << "\n" DEF;
		pair_print_vec(pair_size / 2);
	}
}

void PmergeMe::merge_sort_segments_vec(const size_t pair_size)
{
	if (DEBUG)
		std::cout << YEL "\n\nSORT SEGMENTS " DEF << pair_size << "\n\n";

	vec_int::iterator begin = _array_vec.begin();
	vec_int::iterator end = begin + pair_size - 1;
	
	while (end < _array_vec.end())
	{
		vec_int::iterator anchor = begin + (pair_size / 2) - 1;

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

void PmergeMe::insert_segments_vec(const size_t pair_size)
{
	if (DEBUG)
		std::cout << YEL "\n\nINSERT SEGMENTS " DEF << pair_size << "\n\n";

	if (_array_vec.size() < pair_size)
		return ;

	// "call b1 and the a's the "main chain"""
	vec_int main_chain;
	main_chain.reserve(_array_vec.size());

	// remaining b's and the stashed value are pending
	// keep them associated with their "bigger" pair value
	vec_match pending;

	size_t odd_elems = ((_array_vec.size() % pair_size >= pair_size / 2) * (pair_size / 2));
	pending.reserve(((_array_vec.size() - (_array_vec.size() % pair_size) ) / 2) - (pair_size / 2) + odd_elems);

	// the jacobsthal numbers for the pending insertion index
	vec_size jacob;
	prep_segment_insertion_vec(main_chain, pending, jacob, pair_size);

	if (!pending.empty())
		binary_insert_segment_vec(main_chain, pending, jacob, pair_size / 2);

	_array_vec = main_chain;
}

void PmergeMe::prep_segment_insertion_vec(vec_int &main_chain, vec_match &pending, vec_size &jacob, const size_t pair_size)
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

	main_chain.insert(main_chain.end(), _array_vec.begin(), _array_vec.begin() + pair_size); // b1 + a1
	
	vec_size::iterator insertion_pivot = jacob.begin();
	vec_int::iterator begin = _array_vec.begin() + pair_size;
	
	for (; begin + pair_size - 1 < _array_vec.end(); begin += pair_size)
	{
		vec_int::iterator end = begin + pair_size;
		if (pending.size() > *insertion_pivot)
			insertion_pivot++;

		size_t offset = (insertion_pivot == jacob.begin() ? 0 : *(insertion_pivot - 1) + 1);
		std::cout << YEL "[ offset ]\t" DEF << offset << "\n";
		std::cout << YEL "[ *insertion_pivot ]\t" DEF << *insertion_pivot << "\n";
		std::cout << YEL "[ pending.size() ]\t" DEF << pending.size() << "\n";
		offset += *insertion_pivot - pending.size();
		
		if (DEBUG)
			std::cout << YEL "[ offset ]\t" DEF << offset << "\n";

		vec_int::iterator match = main_chain.end() + offset;
		for (vec_int::iterator it = begin; it < end - (pair_size / 2); it++)
		{
			pending.push_back(std::make_pair(*it, match));
			if (DEBUG)
				std::cout << YEL "[ add pending ]\t" DEF << pending.back().first << "\n";
		}
		
		std::cout << YEL "[ main_chain end ]\t" DEF << *(main_chain.end() - 1) << "\n";
		main_chain.insert(main_chain.end(), begin + (pair_size / 2), end);
	}

	if (_array_vec.size() % pair_size >= pair_size / 2) // is odd
	{
		vec_int::iterator match = main_chain.end() - 1 + (jacob.end() - 2 < jacob.begin() ? 0 : *(jacob.end() - 2) + 1) + jacob.back();
		for (size_t i = 0; i < (pair_size / 2); i++)
		{
			pending.push_back(std::make_pair(*(begin++), match - pending.size()));
			if (DEBUG)
				std::cout << YEL "[ odd offset ]\t\t" DEF << - 1 + (jacob.end() - 2 < jacob.begin() ? 0 : *(jacob.end() - 2) + 1) + jacob.back() - pending.size() << "\n";
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

	if (begin < _array_vec.end())
		main_chain.insert(main_chain.end(), begin, _array_vec.end());

	if (DEBUG)
	{
		std::cout << YEL "[ main chain w/ leftovers ]\t" DEF;
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
		vec_match::iterator to_insert = curr_insert;


		while (curr_insert > already_inserted)
		{
			if (DEBUG)
				std::cout << YEL "\n[ curr insert ]\t" DEF << curr_insert->first << " (b)" << *curr_insert->second << ";\n\n";
			
			binary_search_vec(main_chain, elem_size, curr_insert);
			curr_insert -= elem_size;
		}
		
		already_inserted = to_insert;
		
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

		vec_int::iterator anchor = begin + (((std::distance(begin, end) / elem_size) / 2) * elem_size);
		
		if (DEBUG)
			std::cout << YEL "[ anchor ]\t" DEF << *anchor << ";\n\n";

		if (bigger_than(curr_insert->first, *anchor))
			begin = anchor;
		else
			end = anchor;
	}
}

// -->┊ SORTING STD::LIST

void PmergeMe::sort_list(void)
{
	_bench_start_time = get_curr_time();
	_comp_amount = 0;

	if (_array_list.size() == 1)
	{
		_bench_end_time = get_curr_time();
		return ;
	}

	merge_list(2);
	
	_bench_end_time = get_curr_time();
}

void PmergeMe::merge_list(const size_t pair_size)
{
	if (pair_size > _array_list.size())
		return;

	merge_sort_segments_list(pair_size);

	if (DEBUG)
	{
		std::cout << RED "after sort segments\n" DEF;
		pair_print_list(pair_size);
	}

	merge_list(pair_size * 2);
	
	insert_segments_list( pair_size);

	if (DEBUG)
	{
		std::cout << RED "after insert segments " << pair_size << "\n" DEF;
		pair_print_list(pair_size / 2);
	}
}

void PmergeMe::merge_sort_segments_list(const size_t pair_size)
{
	if (DEBUG)
		std::cout << YEL "\n\nSORT SEGMENTS " DEF << pair_size << "\n\n";

	list_int::iterator begin = _array_list.begin();
	list_int::iterator end = safe_move_list_iterator(begin, pair_size - 1, _array_list);
	
	while (end != _array_list.end())
	{
		list_int::iterator anchor = safe_move_list_iterator(begin, (pair_size / 2) - 1, _array_list);

		if (DEBUG)
		{
			std::cout << "(S) " << *begin << "\t\t(B) " << *end << "\n";
			std::cout << YEL "anchor:\t\t" DEF "(A) " << *anchor << DEF "\n";
		}

		if (bigger_than(*anchor, *end))
		{
			std::swap_ranges(begin, safe_move_list_iterator(anchor, 1, _array_list), safe_move_list_iterator(anchor, 1, _array_list));
			if (DEBUG)
				std::cout << RED "swaping ranges...\n\n" DEF;
		}
		else if (DEBUG)
			std::cout << GRN "correct order!\n\n" DEF;

		begin = safe_move_list_iterator(begin, pair_size, _array_list);
		end = safe_move_list_iterator(end, pair_size, _array_list);
	}
}

void PmergeMe::insert_segments_list(const size_t pair_size)
{
	if (DEBUG)
		std::cout << YEL "\n\nINSERT SEGMENTS " DEF << pair_size << "\n\n";

	if (_array_list.size() < pair_size)
		return ;

	// "call b1 and the a's the "main chain"""
	list_int main_chain;
	main_chain.resize(_array_list.size());

	// remaining b's and the stashed value are pending
	// keep them associated with their "bigger" pair value
	list_match pending;

	size_t odd_elems = ((_array_list.size() % pair_size >= pair_size / 2) * (pair_size / 2));
	pending.resize(((_array_list.size() - (_array_list.size() % pair_size) ) / 2) - (pair_size / 2) + odd_elems);

	// the jacobsthal numbers for the pending insertion index
	list_size jacob;
	prep_segment_insertion_list(main_chain, pending, jacob, pair_size);
	
	if (!pending.empty())
		binary_insert_segment_list(main_chain, pending, jacob, pair_size / 2);

	_array_list = main_chain;
}

void PmergeMe::prep_segment_insertion_list(list_int &main_chain, list_match &pending, list_size &jacob, const size_t pair_size)
{
	size_t odd_elems = ((_array_list.size() % pair_size >= pair_size / 2) * (pair_size / 2));
	size_t pending_max = (((_array_list.size() - (_array_list.size() % pair_size) ) / 2) - (pair_size / 2) + odd_elems > 0 ? ((_array_list.size() - (_array_list.size() % pair_size) ) / 2) - (pair_size / 2) + odd_elems : 1) - 1;
	
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

	std::copy(_array_list.begin(), safe_move_list_iterator(_array_list.begin(), pair_size, _array_list), main_chain.begin()); // b1 + a1
	
	list_size::iterator insertion_pivot = jacob.begin();
	list_int::iterator begin = safe_move_list_iterator(_array_list.begin(), pair_size, _array_list);
	
	list_match::iterator place_pending = pending.begin();
	list_int::iterator place_main = safe_move_list_iterator(main_chain.begin(), pair_size, main_chain);
	for (; safe_move_list_iterator(begin, pair_size - 1, _array_list) != _array_list.end(); begin = safe_move_list_iterator(begin, pair_size, _array_list))
	{
		list_int::iterator end = safe_move_list_iterator(begin, pair_size, _array_list);
		if ((size_t)std::distance(pending.begin(), place_pending) > *insertion_pivot)
			insertion_pivot++;


		int offset;
		if (insertion_pivot == jacob.begin())
			offset = 0;
		else
		{
			insertion_pivot--;
			offset = *insertion_pivot + 1;
			insertion_pivot++;
		}
		std::cout << YEL "[ offset ]\t" DEF << offset << "\n";

		// -- PENDING SIZE DOESNT WORK HERE
		std::cout << YEL "[ *insertion_pivot ]\t" DEF << *insertion_pivot << "\n";
		std::cout << YEL "[ std::distance(pending.begin(), place_pending) ]\t" DEF << std::distance(pending.begin(), place_pending) << "\n";
		offset += *insertion_pivot - std::distance(pending.begin(), place_pending);
		
		if (DEBUG)
			std::cout << YEL "[ offset ]\t" DEF << offset << "\n";
			
		std::cout << YEL "[ *place_main ]\t" DEF << *place_main << "\n";



		list_int::iterator match = move_list_iterator(place_main, offset);
		
		



		// size_t offset = (insertion_pivot == jacob.begin() ? 0 : *(insertion_pivot - 1) + 1);
		// std::cout << YEL "[ pending.size() ]\t" DEF << pending.size() << "\n";
		// offset += *insertion_pivot - pending.size();
		
		// if (DEBUG)
		// 	std::cout << YEL "[ offset ]\t" DEF << offset << "\n";

		// vec_int::iterator match = main_chain.end() + offset;
		// for (vec_int::iterator it = begin; it < end - (pair_size / 2); it++)
		// {
		// 	pending.push_back(std::make_pair(*it, match));
		// 	if (DEBUG)
		// 		std::cout << YEL "[ add pending ]\t" DEF << pending.back().first << "\n";
		// }
		



		
		
		list_int::iterator limit = safe_move_list_iterator(end, -(pair_size / 2), _array_list);
		std::cout << YEL "[ limit ]\t" DEF << *limit << "\n";
		list_int::iterator val = begin;
		for (size_t i = 0; i < pair_size / 2; i++)
		{
			*(place_pending++) = std::make_pair(*val, match);
			if (DEBUG)
				std::cout << YEL "[ add pending ]\t" DEF << *val << "\n";
			val++;
		}

		std::copy(safe_move_list_iterator(begin, pair_size / 2, _array_list), end, place_main);

		std::cout << YEL "[ *place_main ]\t" DEF << *place_main << "\n";


		place_main = safe_move_list_iterator(place_main, pair_size / 2, main_chain);
	}

	if (_array_list.size() % pair_size >= pair_size / 2) // is odd
	{
		list_size::iterator last_prev_jacob = jacob.end();
		int offset;

		for (size_t i = 0; i < 2; i++)
		{
			last_prev_jacob--;
			if (!i && last_prev_jacob == jacob.begin())
			{
				offset = 0;	
				break;
			}
			else if (i)
				offset = *last_prev_jacob;
		}
		

		// ------ THIS IS WRONG ??
		list_int::iterator match = move_list_iterator(place_main, - 1 + offset + jacob.back());
		// list_int::iterator match = move_list_iterator(main_chain.end(), - 1 + (jacob.end() - 2 < jacob.begin() ? 0 : *(jacob.end() - 2) + 1) + jacob.back());
		for (size_t i = 0; i < (pair_size / 2); i++)
		{
			*(place_pending++) = std::make_pair(*(begin++), move_list_iterator(match, -pending.size()));
			if (DEBUG)
				std::cout << RED "[ odd offset ]\t\t" DEF << - 1 + offset + jacob.back() - pending.size() << "\n";
				// std::cout << YEL "[ odd offset ]\t\t" DEF << - 1 + (jacob.end() - 2 < jacob.begin() ? 0 : *(jacob.end() - 2) + 1) + jacob.back() - pending.size() << "\n";
		}
	}

	if (DEBUG)
	{
		std::cout << YEL "\n[ main chain ]\t" DEF;
		for (list_int::const_iterator it = main_chain.begin(); it != main_chain.end(); it++)
			std::cout << *it << " ";
		std::cout << ";\n";
		std::cout << YEL "[ pending ]\t" DEF;
		for (list_match::const_iterator it = pending.begin(); it != pending.end(); it++)
			std::cout << it->first << " ";
		std::cout << ";\n";
	}

	if (begin != _array_list.end())
		std::copy(begin, _array_list.end(), place_main);

	if (DEBUG)
	{
		std::cout << YEL "[ main chain w/ leftovers ]\t" DEF;
		for (list_int::const_iterator it = main_chain.begin(); it != main_chain.end(); it++)
			std::cout << *it << " ";
		std::cout << ";\n";
		std::cout << std::endl;
	}
}

void PmergeMe::binary_insert_segment_list(list_int &main_chain, list_match &pending, list_size &jacob, int elem_size)
{
	if (DEBUG)
	{
		std::cout << YEL "\n\nBINARY INSERT SEGMENTS " DEF << elem_size * 2 << "\n\n";
		std::cout << YEL "[ jacob idxs ]\t" DEF;
		for (list_size::iterator it = jacob.begin(); it != jacob.end(); it++)
			std::cout << *it << " ";
		std::cout << ";\n";
		std::cout << std::endl;	
	}

	list_match::iterator curr_insert;
	list_match::iterator already_inserted =  pending.begin();
	already_inserted--;

	for (list_size::iterator curr_jacob = jacob.begin(); curr_jacob != jacob.end(); curr_jacob++)
	{
		curr_insert = safe_move_list_match_iterator(pending.begin(), *curr_jacob, pending);
		if (curr_insert == pending.end())
			curr_insert--;
		list_match::iterator to_insert = curr_insert;

		// curr_insert = (pending.begin() + *curr_jacob >= pending.end() ? pending.end() - 1 : pending.begin() + *curr_jacob);

		while (curr_insert != already_inserted)
		{
			if (DEBUG)
				std::cout << YEL "\n[ curr insert ]\t" DEF << curr_insert->first << " (b)" << *curr_insert->second << ";\n\n";
			
			binary_search_list(main_chain, elem_size, curr_insert);
			curr_insert = safe_move_list_match_iterator(curr_insert, -elem_size, pending);
			// curr_insert -= elem_size;
		}
		
		already_inserted = to_insert;
		// already_inserted = (pending.begin() + *curr_jacob >= pending.end() ? pending.end() - 1 : pending.begin() + *curr_jacob);
		
		if (DEBUG)
			std::cout << GRN "\n[ CURR JACOB DONE ]\n\n" DEF;
	}
}

void PmergeMe::binary_search_list(list_int &main_chain, int elem_size, list_match::iterator &curr_insert)
{
	list_int::iterator begin = move_list_iterator(main_chain.begin(), elem_size - 1);
	list_int::iterator end = curr_insert->second;

	while (true)
	{
		sleep(1);
		if (DEBUG)
			std::cout << YEL "[ range ]\t" DEF << "(b)" << *begin << " (e)" << *end << ";\n";

		std::cout << YEL "[ after range ]\t" DEF << ";\n";
		if (std::distance(begin, end) <= elem_size)
		{
			if (DEBUG)
			{
				std::cout << YEL "[ at end ]\t" DEF << (end ==  curr_insert->second) << ";\n";
				std::cout << YEL "[ at begin ]\t" DEF << (begin ==  move_list_iterator(main_chain.begin(), elem_size - 1)) << ";\n";
			}
			
			list_int::iterator placement;

			if (end ==  curr_insert->second && bigger_than(curr_insert->first, *end))
				placement = move_list_iterator(end, 1);
			else if (begin ==  move_list_iterator(main_chain.begin(), elem_size - 1) && bigger_than(*begin, curr_insert->first))
				placement = main_chain.begin();
			else
				placement = move_list_iterator(begin, 1);
				



			std::copy_backward(placement, move_list_iterator(placement, std::distance(placement, main_chain.end()) - elem_size), main_chain.end());


			// for (list_match::iterator it = curr_insert; it > curr_insert - elem_size; it--)
			std::cout << YEL "[ dist ]\t" DEF << std::distance(curr_insert, curr_insert) << ";\n\n";
			for (list_match::iterator it = move_list_match_iterator(curr_insert, -elem_size + 1); std::distance(it, curr_insert) >= 0; it++)
			{
				std::cout << YEL "[ dist ]\t" DEF << std::distance(it, curr_insert) << ";\n";
				std::cout << YEL "[ placing ]\t" DEF << it->first << ";\n\n";











				*placement = it->first;
				placement++;







				
				// sleep(1);
				// main_chain.insert(placement, it->first);
				// dont pop!!!!!!!
				// main_chain.pop_back();



				if (std::distance(it, curr_insert) == 0)
					break;
			}
			// main_chain.insert(placement, it->first);
			








			if (DEBUG)
			{
				std::cout << GRN "\n[ POSITION FOUND ]\n" DEF;
				std::cout << YEL "[ new main chain ]\t" DEF;
				for (list_int::const_iterator it = main_chain.begin(); it != main_chain.end(); it++)
					std::cout << *it << " ";
				std::cout << ";\n";
			}
			break;
		}

		std::cout << YEL "[ before sleep ]\t" DEF << ";\n";
		// sleep(1);
		// list_int::iterator anchor = begin + ((((end - begin) / elem_size) / 2) * elem_size);
		list_int::iterator anchor = safe_move_list_iterator(begin, ((std::distance(begin, end) / elem_size) / 2) * elem_size, main_chain);
		
		if (DEBUG)
			std::cout << YEL "[ anchor ]\t" DEF << *anchor << ";\n\n";

		if (bigger_than(curr_insert->first, *anchor))
			begin = anchor;
		else
			end = anchor;
	}
} 

PmergeMe::list_int::iterator PmergeMe::safe_move_list_iterator(list_int::iterator it, const int distance, const list_int &list) const
{
	if (distance > 0)
		for (int moved = 0; moved < distance && it != list.end(); moved++)
			it++;
	else if (distance < 0)
	{
		list_int::const_iterator limit = list.begin();
		limit--;
		for (int moved = 0; moved > distance && it != limit; moved--)
			it--;
	}
	return (it);
}

PmergeMe::list_int::iterator PmergeMe::move_list_iterator(list_int::iterator it, const int distance) const
{
	if (distance > 0)
		for (int moved = 0; moved < distance; moved++)
			it++;
	else if (distance < 0)
		for (int moved = 0; moved > distance; moved--)
			it--;
	return (it);
}

PmergeMe::list_match::iterator PmergeMe::safe_move_list_match_iterator(list_match::iterator it, const int distance, const list_match &list) const
{
	if (distance > 0)
		for (int moved = 0; moved < distance && it != list.end(); moved++)
			it++;
	else if (distance < 0)
	{
		list_match::const_iterator limit = list.begin();
		limit--;
		for (int moved = 0; moved > distance && it != limit; moved--)
			it--;
	}
	return (it);
}

PmergeMe::list_match::iterator PmergeMe::move_list_match_iterator(list_match::iterator it, const int distance) const
{
	if (distance > 0)
		for (int moved = 0; moved < distance; moved++)
			it++;
	else if (distance < 0)
		for (int moved = 0; moved > distance; moved--)
			it--;
	return (it);
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
