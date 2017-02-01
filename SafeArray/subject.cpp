////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Definition of some methods for class Subject
/// \author    Nikita Marinosyan
/// \date      31.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
///
////////////////////////////////////////////////////////////////////////////////


#include "subject.h"


namespace xi {

/**
* Fixing compilation error on the following line
* on MS Visual Studio.
*/
#if !defined(_MSC_VER)

const int Subject::MAX_LINES;

#endif

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
    if (!std::getline(ins, subj.name))
        return ins;
    if (!std::getline(ins, subj.title))
        return ins;

    int index = 0;

    while (std::getline(ins, subj.description[index]) && (index < Subject::MAX_LINES) &&
           (subj.description[index] != ""))
    {
        index++;
    }

    return ins;
}


} // namespace xi

