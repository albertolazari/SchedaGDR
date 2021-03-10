#ifndef BAG_H
#define BAG_H

#include "vector.h"
#include "DeepPtr.h"
#include "Item/Item.h"
#include "Item/Object.h"

class Bag {
private:
    vector<DeepPtr<Item>> items;
    double maxWeight;

public:
    Bag(double = 0);

    double getCarriedWeight() const;
    double getMaxWeight() const;

    void add(const DeepPtr<Item>&);
    DeepPtr<Item> remove(vector<DeepPtr<Item>>::const_iterator);
    double availableWeight() const;

    vector<DeepPtr<Item>>::const_iterator begin() const;
    vector<DeepPtr<Item>>::const_iterator end() const;
};

#endif // BAG_H
