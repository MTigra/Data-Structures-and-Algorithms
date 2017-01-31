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
    //TODO edit implementation? Copy constructor: const/!const, look in the copybook.
    //TODO =constructor
    std::getline(ins, subj.name);
    std::getline(ins, subj.title);

    int index = 0;
    std::string str = "default";

    while (std::getline(ins, str) && (index < Subject::MAX_LINES) && (str != "")) {
        subj.description[index++] = str;
    }

    return ins;
}


} // namespace xi

