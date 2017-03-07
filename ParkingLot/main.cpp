///////////////////////////////////////////////////////////////////////////////
///
/// @author Nikita Marinosyan
/// @date 06.03.2017
/// Higher School of Economics, Faculty of Computer Science
///
///////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stack>
#include <stdexcept>
#include <vector>
#include <algorithm>

#include "car.h"



const int PARKING_SPOTS_PER_AISLE = 3;      ///< Determines a number of cars per an aisle
const int NUMBER_OF_AISLES = 5;             ///< Determines a number of aisls in the parking


/** \brief Defines an Aisle in some parking */
typedef std::stack<std::string> ParkAisle;

/** \brief Defines a parking containing some aisles */
typedef std::vector<ParkAisle> Parking;

/** \brief Defines a collection of cars most likely implemented as a vector of cars */
typedef std::vector<Car> Cars;



/** \brief Iterates through the vector of stacks, looking for the first stack that 
 *  does not contain three cars. If all five aisles (stacks) are full, output a message 
 *  indicating such; otherwise place the license plate into the first non-full stack.
 */
void handle_arrival(Cars& cars, Parking& parking_lot,
    const std::string& plate);


/** \brief Locates the departing vehicle from the \a cars vector using function \a find_car() and
 *  removes the departing car's license plate from the corresponding aisle.
 */
void handle_departure(Cars& cars, Parking& parking_lot, const std::string& plate);


/** \brief Returns a reference to the \a Car object stored in the vector \a cars 
 *  whose license plate equals the parameter \a plate.
 */
Car& find_car(Cars& cars, const std::string& plate);


//------------------------------------------------------------------------------


/** \brief Main entry point of the program
 *
 *  Should obtain at least 1 command line parameter, which is interpreted as the name of a 
 *  file with parking day's payload
 */
int main(int argc, char* argv[]) 
{
    try {
        if (argc < 2)       
        {                   
            std::cerr << "Usage:\n" << argv[0] << " data-file";
            return EXIT_FAILURE;
        }    

        std::ifstream inf(argv[1]);
        if (!inf) 
        {
            std::cerr << "Could not open " << argv[1];
            return EXIT_FAILURE;
        }

        Cars cars;
        Parking parking_lot(NUMBER_OF_AISLES);

        while (!inf.eof()) 
        {
        
            std::string action, plate;
            inf >> plate >> action;
        
            if (action == "arrives") 
            {
                handle_arrival(cars, parking_lot, plate);
            } 
            else if (action == "departs") 
            {
                handle_departure(cars, parking_lot, plate);            
            } else 
            {
                std::cerr << "Unknown action: " << action << std::endl;
            }
        
        }
        inf.close();    

        std::cout << "\nHere are all the cars that visited the lot today:\n";

        // Sort the car's licences
        std::sort(cars.begin(), cars.end());

        // Output the license plates of all the
        // cars that visited the lot, in alphabetical order
        for (Cars::iterator it = cars.begin(); it != cars.end(); ++it)
        {
            std::cout << it->getPlate() << " moved " << it->getTimesMoved() << " times" << std::endl;
        }

        return EXIT_SUCCESS;        
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown exception caught!" << std::endl;
    }
    
    return EXIT_FAILURE;
}

//------------------------------------------------------------------------------

/** 
 *  This is essentially "parking" the car. For this
 *  arriving car, also add an entry of type \a Car to the vector \a cars. In this \a Car instance, 
 *  make sure to record properly the index of the aisle where this car is parked. 
 */
void handle_arrival(Cars& cars, Parking& parking_lot,
    const std::string& plate) 
{
    // Iterate through the vector of stacks, looking for
    // the first stack that does not contain three cars
    int i;
    for (i = 0; i < parking_lot.size(); ++i)
    {
        // Check if this row
        // has empty lots full
        if (parking_lot[i].size() != PARKING_SPOTS_PER_AISLE)
        {
            // Park the car
            parking_lot[i].push(plate);

            // Add the car to the collection of cars
            cars.push_back(Car(plate, i));

            // Return from the method
            return;
        }
    }

    std::cout << "Unable to park the car: parking is full!" << std::endl;
}

//------------------------------------------------------------------------------


/** 
 *  Another stack must be used to move, temporarily, any cars that may be in front of the
 *  departing car. Record the number of times a car is moved when accommodating the
 *  departure of another car. For the departing car, display the number of times it was moved
 *  while it was parked in the lot.
 */
void handle_departure(Cars& cars, Parking& parking_lot, const std::string& plate)
{
    // Utility stack to store the cars blocking
    // the one which is about to leave the parking
    ParkAisle buffer_zone;

    // Find the car and its aisle on the parking
    Car& car_departing = find_car(cars, plate);
    int aisle = car_departing.getAisle();

    // Move the blocking car to the buffer zone
    // in order to let the departing car leave the parking
    while (parking_lot[aisle].top() != plate)
    {
        // Move the blocking car to the buffer zone
        Car current_car = parking_lot[aisle].top();
        buffer_zone.push(current_car.getPlate());

        // Remove it from the stack of parked cars
        parking_lot[aisle].pop();

        // Move to the next car
    }

    // Printout the info about departing car
    std::cout << car_departing.getPlate() + " moved " << car_departing.getTimesMoved() << " times" << std::endl;

    // The car leaves the parking
    parking_lot[aisle].pop();

    // Park the cars from the buffer zone back
    while (!buffer_zone.empty())
    {
        // Park the vehicle
        std::string& current_plate = buffer_zone.top();
        parking_lot[aisle].push(current_plate);

        // Increment times moved value
        Car& current_car = find_car(cars, buffer_zone.top());
        current_car.setTimesMoved(current_car.getTimesMoved() + 1);

        // Remove the car from the buffer zone
        buffer_zone.pop();
    }
}


//------------------------------------------------------------------------------


/** 
 *  Use the STL \a find() function to perform this task. To use the function correctly, you
 *  must supply it with three arguments. The first two arguments specify a range to search.
 *  The third argument is the value that the function attempts to find. This argument must be
 *  of type \a Car.
 *
 *  * http://www.cplusplus.com/reference/algorithm/find/
 */
Car& find_car(Cars& cars, const std::string& plate)
{
    // Find the car using STL find method
    Cars::iterator it = std::find(cars.begin(), cars.end(), plate);

    // Check if the car was found
    if (it == cars.end())
        throw std::logic_error("No car with such license plate");

    // Return a reference to the Car object whose
    // license plate equals the parameter 'plate'
    return *it;
}
