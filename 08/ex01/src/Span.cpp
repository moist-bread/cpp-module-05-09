#include "../inc/Span.hpp"

Span::Span(void) : N(1)
{
	std::cout << GRN "a Span with limit of [ " << N << " ] ";
	std::cout << UCYN "has been created" DEF << std::endl;
}

Span::Span(unsigned int n): N(n)
{
	std::cout << GRN "a Span with limit of [ " << N << " ] ";
	std::cout << UCYN "has been created" DEF << std::endl;
}

Span::Span(Span const &source)
{
	*this = source;
	std::cout << GRN "a Span with limit of [ " << N << " ] ";
	std::cout << UYEL "has been copy created" DEF << std::endl;
}

Span::~Span(void)
{
	std::cout << GRN "a Span with limit of [ " << N << " ] ";
	std::cout << URED "has been deleted" DEF << std::endl;
}

Span &Span::operator=(Span const &source)
{
	std::cout << YEL "copy assignment operator overload..." DEF << std::endl;
	if (this != &source)
	{
		N = source.N;
		_span = source.get_span();
	}
	return (*this);
}

void Span::addNumber(int nbr)
{
	if (_span.size() == N)
		throw (std::out_of_range("couldn't add due to range limit"));
	_span.push_back(nbr);
}

void Span::addRange(int_vec range)
{
	if (_span.size() + range.size() > N)
		throw (std::out_of_range("couldn't add due to range limit"));
	_span.insert(_span.end(), range.begin(), range.end());
}

int Span::shortestSpan(void) const
{
	if (_span.size() < 2)
		throw (std::out_of_range("no span can be found with such few elements"));
	
	int_vec sorted_span = get_span();
	sort(sorted_span.begin(), sorted_span.end());
	int_vec::iterator end = sorted_span.end() - 1;
	int shortest = std::numeric_limits<int>::max();
	for (int_vec::iterator i = sorted_span.begin(); i != end; i++)
	{
		int dif = *(i + 1) - *i;
		if (dif < shortest)
			shortest = dif;
	}
	return (shortest);
}

int Span::longestSpan(void) const
{
	if (_span.size() < 2)
		throw (std::out_of_range("no span can be found with such few elements"));
	int_vec sorted_span = get_span();
	sort(sorted_span.begin(), sorted_span.end());
	return (*(sorted_span.end() - 1) - *sorted_span.begin());
}

int_vec Span::get_span(void) const
{
	return (_span);
}

std::ostream &operator<<(std::ostream &out, Span const &source)
{
	int idx = 1;

	if (source.get_span().empty())
		out << BLU "no elements in vector" DEF << std::endl;

	int_vec span = source.get_span();
	for (int_vec::iterator i = span.begin(); i != span.end(); i++)
		out << BLU "elem " << idx++ << ": " DEF << *i << std::endl;
	return (out);
}
