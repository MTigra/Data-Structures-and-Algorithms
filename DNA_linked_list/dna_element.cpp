//
// Created by Nikita Marinosyan on 07.02.17.
//

#include "dna_element.h"

DNAElement::DNAElement(const std::string& description)
{
    readFromString(description);
}

void DNAElement::readFromString(const std::string& description)
{
    if (description.length() != 4 || description[2] != ':')
        throw std::invalid_argument("Incorrect DNA format!");

    char c = description[0];
    if (c < 'a' || c > 'z')
    {
        throw std::invalid_argument("Incorrect DNA format: invalid id!");
    }
    id = c;

    c = description[1];
    if (c < '0' || c > '9')
    {
        throw std::invalid_argument("Incorrect DNA format: invalid number!");
    }
    number = (int)c - 48;

    c = description[3];
    if (c != NitrogenousBase::Adenine && c != NitrogenousBase::Cytosine
              && c != NitrogenousBase::Guanine && c != NitrogenousBase::Thymine)
    {
        throw std::invalid_argument("Incorrect DNA format: invalid base!");
    }
    base = (NitrogenousBase)c;
}

DNAElement::DNAElement()
{}
