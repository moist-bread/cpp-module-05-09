#pragma once

//-‵,┊ needed libs by class
#include "AForm.hpp"
#include <fstream>
#include <cstdlib>

//-‵,┊ text defines

#define ASCIITREE "\
                           xxxx\n\
                        xxxxε xxxxxxxx\n\
                     xxxxxxεε      xxxxxxx\n\
                   xxxεεε ε εεε       ºº xx\n\
                   xεεεεε               ººxx\n\
                  xxxε≈≈                 ººxx\n\
                xxεεεε≈ε    ≈≈  ≈≈        ººxxxx\n\
                xεεεε≈≈≈≈ ε≈≈  ≈≈          ººººxx        xxxxxx    xxxx\n\
    xxxxxx      xεε≈≈ε≈εεεεε  ε                 x       xx     xxxxx  xx\n\
  xxx    xxxx    xxxεεε≈ε≈xεεεε                 x      x ≈≈≈         ºº  x\n\
xx  ≈       ºxx    xxxxxxx xxxx x x        xxxxxx      xx ≈≈          ºº xx\n\
x ≈≈≈       ººxx             xxxxxx x x xxxx            xx ≈  ≈        ºº x\n\
x ≈≈≈≈≈≈     ººxxx            x xx                        xxxxxx≈x≈     º x\n\
xxxxxxx ≈≈    xxxx            xxx     xxxx                      xxxxx    x\n\
     xxxx    xx               xxx    xx                          x   xxxx\n\
     xx xxxxx                 xxxxxxx                           xx\n\
      x                       xxx                              xx\n\
      x                     xxxxx                              xx\n\
       xx                   x xxx                               xx\n\
       xx                  xxxxxx                                xxx\n\
       xx                xxxxxxxxx                               xxxx\n\
      xxx               xxx xxxxxxx                              xxxx\n\
     xxxxx              xx  xxxxxxxxxx                           xxxxx"

// -->┊( SHRUBBERY CREATION FORM )┊.´-★☆★

class ShrubberyCreationForm : public AForm
{
public:
    ShrubberyCreationForm(void); // default constructor
    ShrubberyCreationForm(const std::string &target);
    ShrubberyCreationForm(ShrubberyCreationForm const &source); // copy constructor
    virtual ~ShrubberyCreationForm(void);                       // destructor

    ShrubberyCreationForm &operator=(ShrubberyCreationForm const &source); // copy assignment operator overload

    void execute(Bureaucrat const &executor) const;
};

std::ostream &operator<<(std::ostream &out, ShrubberyCreationForm const &source);
