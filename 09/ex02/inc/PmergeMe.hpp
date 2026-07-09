#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

//-‵,┊ needed libs by class

#include <vector>
#include <list>
#include <string>
#include <stddef.h>
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
	typedef std::vector<std::pair<int, vec_int::iterator> > vec_match;
	typedef std::vector<size_t> vec_size;
	
	
	typedef std::list<int> list_int;
	typedef std::list<std::pair<int, list_int::iterator> > list_match;
	typedef std::list<size_t> list_size;

private:
	PmergeMe(void);	// default constructor
	vec_int _array_vec;
	list_int _array_list;
	time_t _bench_start_time;
	time_t _bench_end_time;
	size_t _comp_amount;
	
	void print_time(std::string container) const;
	void print_comp(std::string container) const;

	void sort_vec(void);
	void merge_vec(const size_t pair_size);
	void merge_sort_segments_vec(const size_t pair_size);
	void insert_segments_vec(const size_t pair_size);
	void prep_segment_insertion_vec(vec_int &main_chain, vec_match &pending, vec_size &jacob, const size_t pair_size);
	void add_odd_elements_vec(vec_int &main_chain, vec_match &pending, vec_size &jacob, const size_t elem_size, vec_int::iterator &begin);
	void binary_insert_segment_vec(vec_int &main_chain, vec_match &pending, vec_size &jacob, int elem_size);
	void binary_search_vec(vec_int &main_chain, int elem_size, vec_match::iterator &curr_insert);

	void sort_list(void);
	void merge_list(const size_t pair_size);
	void merge_sort_segments_list(const size_t pair_size);
	void insert_segments_list(const size_t pair_size);
	void prep_segment_insertion_list(list_int &main_chain, list_match &pending, list_size &jacob, const size_t pair_size);
	void binary_insert_segment_list(list_int &main_chain, list_match &pending, list_size &jacob, int elem_size);
	void binary_search_list(list_int &main_chain, int elem_size, list_match::iterator &curr_insert);

	static time_t get_curr_time(void);
	bool bigger_than(int x, int y);
	size_t jacobsthal_gen(size_t n) const;
};

#endif