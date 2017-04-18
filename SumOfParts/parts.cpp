#include <iostream>
#include "parts.h"

/**
 * @author Nikita Marinosyan
 * @date 18.04.2017
 * Higher School of Economics,
 * Department of Software Engineering
 */

void Part::describe()
{
    std::cout << "Part " << this->name << " subparts are:" << std::endl;

    // Create iterator and check
    // if the part has subparts
    std::map<Part*, int>::iterator it = subparts.begin();
    if (it == subparts.end())
        // Indicate that there
        // are no subparts
        std::cout << "    It has no subparts." << std::endl;

    // Iterate through the subparts
    for (; it != subparts.end() ; ++it)
        std::cout << "\t" << it->second << " " << it->first->name << std::endl;
}

int Part::countHowMany(const Part* p)
{
    // Check if this is the
    // part we are looking for
    if (this == p)
        return 1;

    // Search for the part in the
    // subparts of the current object
    int numberOfSubparts = 0;
    for (std::map<Part*, int>::iterator it = subparts.begin();  it != subparts.end() ; ++it)
        numberOfSubparts += it->first->countHowMany(p) * it->second;

    return numberOfSubparts;
}

Part* NameContainer::lookup(const std::string& name)
{
    // Add the part if
    // it does not exist
    if (_nameMap.find(name) == _nameMap.end())
        _nameMap[name] = new Part(name);

    // Return the found object
    return  _nameMap.find(name)->second;
}

void NameContainer::addPart(const std::string& part, int quantity, const std::string& subpart)
{
    // Find the where to insert the subpart
    // in the subparts map and record the quantity
   lookup(part)->subparts[lookup(subpart)] = quantity;
}

