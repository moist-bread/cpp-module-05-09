#include "../inc/Bureaucrat.hpp"

Bureaucrat::Bureaucrat(void) : _name("Nameless"), _grade(150)
{
	std::cout << GRN "the Bureaucrat [ " << getName() << " ] ";
	std::cout << "and grade [ " << getGrade() << " ] ";
	std::cout << UCYN "has been born" DEF << std::endl;
}

Bureaucrat::Bureaucrat(const std::string &name, int grade) : _name(name), _grade(grade)
{
	if (_grade < 1)
		throw(GradeTooHighException());
	if (_grade > 150)
		throw(GradeTooLowException());
	std::cout << GRN "the Bureaucrat [ " << getName() << " ] ";
	std::cout << "and grade [ " << getGrade() << " ] ";
	std::cout << UCYN "has been born" DEF << std::endl;
}

Bureaucrat::Bureaucrat(Bureaucrat const &source)
{
	*this = source;
	std::cout << GRN "the Bureaucrat [ " << getName() << " ] ";
	std::cout << "and grade [ " << getGrade() << " ] ";
	std::cout << UYEL "has been copy cloned" DEF << std::endl;
}

Bureaucrat::~Bureaucrat(void)
{
	std::cout << GRN "the Bureaucrat [ " << getName() << " ] ";
	std::cout << "and grade [ " << getGrade() << " ] ";
	std::cout << URED "has died" DEF << std::endl;
}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &source)
{
	std::cout << YEL "copy assignment operator overload..." DEF << std::endl;
	if (this != &source)
		_grade = source.getGrade();
	return (*this);
}

std::string Bureaucrat::getName(void) const
{
	return (_name);
}

int Bureaucrat::getGrade(void) const
{
	return (_grade);
}

void Bureaucrat::increment_grade(void)
{
	std::cout << "increment: ";
	if (_grade <= 1)
		throw(GradeTooHighException());
	_grade--;
}

void Bureaucrat::decrement_grade(void)
{
	std::cout << "decrement: ";
	if (_grade >= 150)
		throw(GradeTooLowException());
	_grade++;
}

void Bureaucrat::signForm(Form &form)
{
	try
	{
		form.beSigned(*this);
		std::cout << *this << GRN " signed the following Form:" DEF << std::endl;
		std::cout << form << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << *this << RED " couldn't sign the following Form:" DEF << std::endl;
		std::cout << form;
		std::cout << RED "motive: " DEF << e.what() << std::endl
				  << std::endl;
	}
}

const char *Bureaucrat::GradeTooHighException::what(void) const throw()
{
	return ("Bureaucrat:: high grade");
}

const char *Bureaucrat::GradeTooLowException::what(void) const throw()
{
	return ("Bureaucrat:: low grade");
}

std::ostream &operator<<(std::ostream &out, Bureaucrat const &source)
{
	out << BLU << source.getName() << DEF ", bureaucrat grade ";
	out << BLU << source.getGrade() << DEF;
	return (out);
}
