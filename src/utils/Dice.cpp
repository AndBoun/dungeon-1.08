//
// Created by Andrew Boun on 4/8/25.
//

#include <utils/Dice.hpp>

Dice::Dice(int base, int numDice, int numSides) : base(base), numDice(numDice), numSides(numSides) {}
Dice::Dice() : base(0), numDice(0), numSides(0) {}
Dice::~Dice() {}

std::ostream& Dice::print(std::ostream &os) const {
    os << base << "+" << numDice << "d" << numSides;
    return os;
}
    
// Stream insertion operator as friend function
std::ostream &operator<<(std::ostream &os, const Dice &dice){
    return dice.print(os);
}