//
// Created by Andrew Boun on 4/8/25.
//

#include <ostream>

#ifndef DICE_HPP
#define DICE_HPP

class Dice {
public:
    int base;
    int numDice;
    int numSides;

    Dice(int base, int numDice, int numSides);
    Dice();
    ~Dice();


    std::ostream &print(std::ostream &os) const;
    
    // Stream insertion operator as friend function
    friend std::ostream &operator<<(std::ostream &os, const Dice &dice);

    int getRandNum(){
        int total = base;
        for (int i = 0; i < numDice; i++) {
            total += rand() % numSides + 1;
        }
        return total;
    }
    
};

#endif // DICE_HPP