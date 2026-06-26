#ifndef RPN_HPP
#define RPN_HPP

//-‵,┊ needed libs by class
#include <string>
#include <stack>

//-‵,┊ color defines

#define CYN "\e[0;36m"
#define RED "\e[0;31m"
#define DEF "\e[0m"

# ifndef DEBUG
#  define DEBUG 0
# endif

// -->┊( RPN )┊.´-★☆★

class RPN
{
public:
	static void process_expression(std::string exp);

private:
	RPN(void);	// default constructor
	RPN(RPN const &source);	// copy constructor
	~RPN(void);	// destructor
	RPN &operator=(RPN const &source);	// copy assignment operator overload

	static void operation(const char &op);
	static std::stack<int> _nums;
	static const char *_operators;
	static const short _amount_op;
};

#endif