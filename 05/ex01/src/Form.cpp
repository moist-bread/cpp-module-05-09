#include "../inc/Form.hpp"

Form::Form(void) : _name("Nameless"), _signed(false), _grade_to_sign(150), _grade_to_execute(150)
{
	std::cout << GRN "a Form ";
	std::cout << UCYN "has been printed..." DEF << std::endl;
	std::cout << *this;
}

Form::Form(const std::string &name, int grade_to_sign, int grade_to_exe) : _name(name),  _signed(false), _grade_to_sign(grade_to_sign), _grade_to_execute(grade_to_exe)
{
	if (_grade_to_sign < 1 || _grade_to_execute < 1)
		throw(GradeTooHighException());
	if (_grade_to_sign > 150 || _grade_to_execute > 150)
		throw(GradeTooLowException());
	std::cout << GRN "a Form ";
	std::cout << UCYN "has been printed..." DEF << std::endl;
	std::cout << *this;
}

Form::Form(Form const &source) : _name(source.get_name()), _grade_to_sign(source.get_grade_to_sign()),  _grade_to_execute(source.get_grade_to_execute())
{
	*this = source;
	std::cout << GRN "a Form ";
	std::cout << UYEL "has been scanned and copied" DEF << std::endl;
	std::cout << *this;
}

Form::~Form(void)
{
	std::cout << GRN "a Form ";
	std::cout << URED "has been shredded" DEF << std::endl;
	std::cout << *this;
}

Form &Form::operator=(Form const &source)
{
	if (this != &source)
		_signed = source.get_signed();
	return (*this);
}

std::string Form::get_name(void) const
{
	return (_name);
}

bool Form::get_signed(void) const
{
	return (_signed);
}

int Form::get_grade_to_sign(void) const
{
	return (_grade_to_sign);
}

int Form::get_grade_to_execute(void) const
{
	return (_grade_to_execute);
}

void Form::beSigned(Bureaucrat &source)
{
	if (source.getGrade() <= _grade_to_sign)
	{
		_signed = true;	
		std::cout << GRN "Form [ " << _name << " ] is now signed ☑";
		std::cout << DEF << std::endl;
	}
	else
		throw(GradeTooLowException());
}

const char *Form::GradeTooHighException::what(void) const throw()
{
	return ("grade too high");
}

const char *Form::GradeTooLowException::what(void) const throw()
{
	return ("grade too low");
}

std::ostream &operator<<(std::ostream &out, Form const &source)
{
	out << "╆─────────────────────────────────────────────── ─--- -- -" << std::endl;
	out << "╵   " << "Form: " << source.get_name() << std::endl;
	if (source.get_signed())
		out << "╵   "  GRN "signed ☑" DEF << std::endl;
	else
		out << "╵   " RED "not signed ☒" DEF << std::endl;
	out << "╵   " YEL "▖ GRADE TO SIGN: " DEF << source.get_grade_to_sign();
	out << "   " BLU "▖ GRADE TO EXE: " DEF << source.get_grade_to_execute() << std::endl;
	out << "╆─────────────────────────────────────────────── ─--- -- -" << std::endl;
	out << std::endl;

	return (out);
}
