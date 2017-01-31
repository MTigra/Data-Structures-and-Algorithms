////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Definition of some methods for class Subject
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      30.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
///
////////////////////////////////////////////////////////////////////////////////


#include "subject.h"



namespace xi {


std::ostream& operator<<(std::ostream& outs, const Subject& subj)
{   
    outs << subj.name << ": " << subj.title << "\n";
   
    int index = 0;
    while (subj.description[index] != "") 
        outs << subj.description[index++] << "\n";

    return outs;
}



std::istream& operator>>(std::istream& ins, Subject& subj)
{
    // TODO: здесь необходимо дописать реализацию метода

    return ins;
}


} // namespace xi

