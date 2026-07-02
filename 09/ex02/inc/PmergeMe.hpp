#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

//-‵,┊ needed libs by class
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <limits>
#include <vector>
#include <deque>
#include <stdlib.h>
#include <unistd.h>
#include <ctime>
#include <sys/time.h>


//-‵,┊ color defines

#define YEL "\e[0;33m"
#define BLK "\e[0;30m"
#define CYN "\e[0;36m"
#define GRN "\e[0;32m"
#define RED "\e[0;31m"
#define DEF "\e[0m"

# ifndef DEBUG
#  define DEBUG 0
# endif

// -->┊( PMERGE ME )┊.´-★☆★

class PmergeMe
{
public:
	PmergeMe(char **av);
	PmergeMe(PmergeMe const &source);	// copy constructor
	~PmergeMe(void);	// destructor
	PmergeMe &operator=(PmergeMe const &source);	// copy assignment operator overload
	
	typedef std::vector<int> vec_int;
	typedef std::vector<std::pair<int, int> > vector2;
	
	typedef std::vector<std::pair<int, vec_int::iterator> > vec_match;
	typedef std::vector<std::pair<std::pair<int, int>, vector2::iterator> > vector2_match;
	
	typedef std::vector<size_t> vec_size;

private:
	PmergeMe(void);	// default constructor
	vec_int _array_vec;
	std::deque<int> _array_deque;
	time_t _bench_start_time;
	time_t _bench_end_time;
	size_t _comp_amount;
	
	void print_array(std::string str) const;
	void print_time(std::string container) const;
	void print_comp(std::string container) const;

	void sort_vec(void);
	void merge_vec(vector2 &vec, size_t pair_size);
	void merge_sort_segments_vec(vector2 &vec, size_t pair_size);
	void insert_segments_vec(vector2 &vec, size_t pair_size);
	void prep_segment_insertion_vec(vector2 &main_chain, vector2_match &pending, vec_size &jacob, vector2 &pairs, size_t pair_size);
	void binary_insert_segment_vec(vector2 &main_chain, vector2_match &pending, vec_size &jacob, int elem_size);



	void old_merge_vec(vector2 &vec, vector2::iterator begin, vector2::iterator end);
	void merge_swap_segment_vec(vector2::iterator begin, vector2::iterator end);
	void prep_for_insertion_vec(vec_int &main_chain, vec_match &pending, vec_size &jacob, vector2 &pairs, bool &is_odd);
	void binary_insert_vec(vec_int &main_chain, vec_match &pending, vec_size &jacob);
	
	void sort_deque(void);
	
	static time_t get_curr_time(void);
	bool bigger_than(int x, int y);
	size_t jacobsthal_gen(size_t n) const;
};

#endif