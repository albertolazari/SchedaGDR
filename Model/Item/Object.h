#ifndef OBJECT_H
#define OBJECT_H
#include "Item.h"

class Object : public Item {
private:
    string description;
    unsigned int amount;
public:
    Object(const string&, double, unsigned int = 1, const string & = "");

    int use() override;

    double getWeight() const override;
    string getDescription()const;
    unsigned int getAmount()const;
    void add(unsigned Amount = 1);
    void remove(unsigned Amount = 1);
    void changeDescripion(const string&);
    Object* clone()const override;
    bool operator== (const Item &)const override;
    bool operator!= (const Item &)const override;
};

#endif // OBJECT_H
