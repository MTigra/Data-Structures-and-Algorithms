////////////////////////////////////////////////////////////////////////////////
// Module Name:  stack_machine.h/cpp
// Authors:      Sergey Shershakov, Nikita Marinosyan
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include "stack_machine.h"
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <climits>

namespace xi {

//==============================================================================
// Free functions -- helpers
//==============================================================================

/**
 *
 * @param s - expression which is required to be split
 * @return list of tokens
 */
    std::vector<std::string> split_ws(std::string str) {
        std::vector<std::string> internal;
        std::stringstream ss(str); // Turn the string into a stream
        std::string token;

        while (getline(ss, token, ' ')) {
            internal.push_back(token);
        }

        return internal;
    }

/**
 * Converts the string representation
 * of the number to integer
 * @param s - string representation of the number which should be parsed
 * @param number - reference of the variable which will be containing the result of parsing
 * @return true - if the parse has been made correctly; false - otherwise
 */
    bool tryParseInt(std::string s, int& number) {
        char* t;
        const char *str = s.c_str();
        errno = 0;
        bool succeeded = true;
        long l = strtol(str, &t, 10);
        if (*t != '\0' || t == str || ((l == LONG_MIN || l == LONG_MAX) && errno == ERANGE))
            succeeded = false;
        number = (int) l;
        return succeeded;
    }

//==============================================================================
// class PlusOp
//==============================================================================


int PlusOp::operation(char op, int a, int b, int c)
{
    if(op != '+')
        throw std::logic_error("Operation other than Plus (+) are not supported");

    // here we just ignore unused operands
    return a + b;
}

IOperation::Arity PlusOp::getArity() const
{
    return arDue;
}

//==============================================================================
// class MinusOp
//==============================================================================


    int MinusOp::operation(char op, int a, int b, int c)
    {
        if(op != '-')
            throw std::logic_error("Operation other than Minus (-) are not supported");

        // Return the result of calculation
        // ignoring the unused operand
        return a - b;
    }

    IOperation::Arity MinusOp::getArity() const
    {
        return arDue;
    }

//==============================================================================
// class AndOp
//==============================================================================


    int AndOp::operation(char op, int a, int b, int c)
    {
        if(op != '&')
            throw std::logic_error("Operation other than AND (&) are not supported");

        // Return the result of calculation
        // ignoring the unused operand
        return a & b;
    }

    IOperation::Arity AndOp::getArity() const
    {
        return arDue;
    }

//==============================================================================
// class AndOp
//==============================================================================


    int OrOp::operation(char op, int a, int b, int c)
    {
        if(op != '|')
            throw std::logic_error("Operation other than OR (|) are not supported");

        // Return the result of calculation
        // ignoring the unused operand
        return a | b;
    }

    IOperation::Arity OrOp::getArity() const
    {
        return arDue;
    }

//==============================================================================
// class StackMachine
//==============================================================================

    void StackMachine::registerOperation(char symb, IOperation *oper) {

        // Check if this operation is already registered
        SymbolToOperMapConstIter it = _opers.find(symb);
        if (it != _opers.end())
            throw std::logic_error("An operation '" + std::string(1, symb) + "' is already registered");

        _opers[symb] = oper;
    }

    IOperation* StackMachine::getOperation(char symb) {

        // Check if there is no such operation registered
        SymbolToOperMapConstIter it = _opers.find(symb);
        if (it == _opers.end())
            return nullptr;

        return it->second;
    }

    int StackMachine::calculate(const std::string &expr, bool clearStack) {
        // Clear the stack if needed
        if (clearStack) getStack().clear();

        // Split expression into tokens assuming WS as delimiter
        std::vector<std::string> tokens = split_ws(expr);

        // Iterate through the tokens checking if they are correct
        for (int i = 0; i < tokens.size(); ++i) {
            int current_t; // Current token

            // Check if this is an operand
            if (tryParseInt(tokens[i], current_t)) {
                // Push the operand to the top of the stack
                _s.push(current_t);
            }
            // Check if this is a registered operator
            else if (tokens[i].length() == 1 && getOperation(tokens[i][0]) != nullptr) {

                IOperation* current_op = getOperation(tokens[i][0]);
                // Get the arity of the operation
                if (current_op->getArity() == IOperation::arUno) { // Unary operation

                    // Take the value from the top of the stack
                    // Checking if there are enough operands in the stack
                    int a;
                    try {
                        a = _s.pop();
                    }
                    catch (std::logic_error&) {
                        throw std::logic_error("Not enough operands!");
                    }
                    _s.push(current_op->operation(tokens[i][0], a, 0, 0));
                }
                else if (current_op->getArity() == IOperation::arDue) { // Binary operation

                    // Similarly to the unary operation but in this case
                    // we need to take the top 2 elements from the stack
                    // Apply the operation on them and push the result to the stack
                    int a, b;
                    try { // Check if there are enough operands in the stack
                        // Take respectively to the commutativity
                        b = _s.pop();
                        a = _s.pop();
                    }
                    catch (std::logic_error&) {
                        throw std::logic_error("Not enough operands!");
                    }
                    _s.push(current_op->operation(tokens[i][0], a, b, 0));
                }
                else { // Ternary operation

                    // Similarly to the previous ones
                    int a, b, c;
                    try {
                        c = _s.pop();
                        b = _s.pop();
                        a = _s.pop();
                    }
                    catch (std::logic_error&) {
                        throw std::logic_error("Not enough operands!");
                    }
                    _s.push(current_op->operation(tokens[i][0], a, b, c));
                }
            }
            else {
                throw std::logic_error("Invalid expression: " + tokens[i]);
            }
        }
        if (_s.isEmpty()) {
            throw std::logic_error("Can't evaluate the expression!");
        }
        else {
            return _s.top();
        }
    }

} // namespace xi
