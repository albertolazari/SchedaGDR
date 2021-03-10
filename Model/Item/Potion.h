#ifndef POTION_H
#define POTION_H
#include "Object.h"
#include "../Die.h"
#include "../vector.h"
class Potion : public Object {
private:
    vector<Die> dice;
public:
    Potion(
        const string& Name,
        double Weight,
        const vector<Die>& Dice,
        unsigned int Amount = 1,
        const string& Desc = ""
    );
    Potion (const Object& o, const vector<Die>& Dice);

    int use() override;
    Potion* clone() const override;
    bool operator== (const Item &)const override;
    bool operator!= (const Item &)const override;

    const vector<Die>& getDice () const;
};

#endif // POTION_H
