//
// Created By Andrew Boun on 4/2/2025
//

#include <character/Character.hpp>
#include <dungeon/base/Cell.hpp>

Character::Character() : position(Point()), speed(0), currentCell(Cell()), symbol(' '), alive(true), ID(-1) {}
Character::Character(Point position, int speed, Cell currentCell, char symbol, bool alive, int ID)
    : position(position), speed(speed), currentCell(currentCell), symbol(symbol), alive(alive), ID(ID) {}

Character::~Character() {}

const Point& Character::getPosition() const {
    return position;
}
int Character::getSpeed() const {
    return speed;
}
const Cell& Character::getCurrentCell() const {
    return currentCell;
}
char Character::getSymbol() const {
    return symbol;
}
bool Character::isAlive() const {
    return alive;
}

void Character::setPosition(Point position) {
    this->position = position;
}

void Character::setCurrentCell(Cell currentCell) {
    this->currentCell = currentCell;
}

void Character::setAlive(bool alive) {
    this->alive = alive;
}