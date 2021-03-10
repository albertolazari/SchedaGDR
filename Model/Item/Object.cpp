#include "Object.h"

Object::Object(const std::string & n, double w, unsigned int a, const std::string & d) :
    Item(n, w), description(d), amount(a == 0 ? 1 : a) {}

int Object::use() {
    if (amount != 0) amount--;
    return amount;
}

double Object::getWeight() const { return Item::getWeight() * amount; }
std::string Object::getDescription() const { return description; }
unsigned int Object::getAmount() const { return amount; }

void Object::add(unsigned int x) { amount += x; }

void Object::remove(unsigned x) {
    if (static_cast<int>(amount) - static_cast<int>(x) >= 0)
        amount -= x;
    else
        amount = 0;
}

void Object::changeDescripion(const std::string& s) {
    description = s;
}

Object *Object::clone() const {
    return new Object(*this);
}

bool Object::operator==(const Item& i) const {
    if (!Item::operator==(i))
        return false;
    const Object& w = static_cast<const Object&>(i);
    return Item::operator==(i) && description == w.description;
}
bool Object::operator!=(const Item& i) const {
    if (Item::operator!=(i))
        return true;
    const Object& w = static_cast<const Object&>(i);
    return description != w.description;
}

