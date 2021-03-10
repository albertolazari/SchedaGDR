#ifndef ITEM_H
#define ITEM_H
#include <string>
using std::string;

class Item {
private:
    string name;
    double weight;
public:
    Item(const string&, double);
    virtual ~Item() = default;
    virtual Item* clone() const = 0;
    virtual int use() = 0;
    virtual bool operator== (const Item&) const;
    virtual bool operator!= (const Item&) const;
    string getName() const;
    virtual double getWeight() const;
};

#endif // ITEM_H
