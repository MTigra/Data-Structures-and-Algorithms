/**
 * @author Nikita Marinosyan
 * @date 18.04.2017
 * Higher School of Economics,
 * Department of Software Engineering
 */

#ifndef _PARTS_H_
#define _PARTS_H_

#include <vector>
#include <map>
#include <string>

// using namespace std;

//**************** Part ****************
class Part  {
public:
	std::string name;
    std::map<Part*, int> subparts;
	
	Part(const std::string& n) : name(n) {};
	void describe();
	int countHowMany(const Part* p);
};


//**************** NameContainer ****************
class NameContainer  {
public:        
	NameContainer() {};
    
    void addPart(const std::string& part, int quantity, const std::string& subpart);
	Part* lookup(const std::string& name);
        
    // You can add some methods here 
        
private:
	std::map<std::string, Part*> _nameMap;

};

#endif // _PARTS_H_
