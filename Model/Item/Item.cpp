#include "Item.h"
#include <iostream>
#include <typeinfo>

Item::Item(const string& n, double w) : name(n), weight(w) {}

bool Item::operator==(const Item & i) const {
    return typeid(*this) == typeid(i) && name == i.name && weight == i.weight;
}

bool Item::operator!=(const Item & i) const {
    return typeid(*this) != typeid(i) || name != i.name || weight != i.weight;
}

std::string Item::getName() const { return name; }

double Item::getWeight() const { return weight; }
