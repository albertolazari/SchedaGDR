#include "Potion.h"

Potion::Potion(
    const std::string& Name,
    double Weight,
    const vector<Die>& Dice,
    unsigned int Amount,
    const std::string& Desc
)
    : Object(Name, Weight, Amount, Desc), dice(Dice) {
    dice.sort();
}

Potion::Potion(const Object &o, const vector<Die> &Dice)
    : Object(o), dice(Dice){}

int Potion::use() {
    if (getAmount() == 0) return 0;
    Object::use();
    int out = 0;
    for (Die d : dice) {
        out += d.roll();
    }
    return out;
}

Potion* Potion::clone() const { return new Potion(*this); }

bool Potion::operator==(const Item& i) const {
    if (!Item::operator==(i))
        return false;
    const Potion& w = static_cast<const Potion&>(i);
    return dice == w.dice;
}
bool Potion::operator!=(const Item& i) const {
    if (Item::operator!=(i))
        return true;
    const Potion& w = static_cast<const Potion&>(i);
    return Object::operator!=(i) || dice != w.dice;
}

const vector<Die> &Potion::getDice() const
{
    return dice;
}
