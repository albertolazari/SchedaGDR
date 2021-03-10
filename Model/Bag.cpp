#include "Bag.h"
#include <iostream>

Bag::Bag(double dim) : maxWeight(dim) {}

double Bag::getCarriedWeight() const {
    double weight = 0.0;
    for (const DeepPtr<Item>& item : items)
        weight += item->getWeight();

    return weight;
}
double Bag::getMaxWeight() const { return maxWeight; }

void Bag::add(const DeepPtr<Item>& i) {
    if (i != nullptr) {
        if (i->getWeight() + getCarriedWeight() > maxWeight)
            // l'eccezione viene gestita dalla view
            throw std::runtime_error("Superata la capienza massima della borsa!");

        if (dynamic_cast<Object*>(i.get()) != nullptr) {
            // i contiene almeno Object a questo punto
            bool found = false;
            for (DeepPtr<Item>& item : items)
                if (*item == *i) {
                    // a questo punto anche item contiene almeno un Object
                    Object* o = static_cast<Object*>(item.get());
                    o->add(static_cast<Object*>(i.get())->getAmount());
                    found = true;
                }
            if (!found) items.push_back(i);
        }
        else
            items.push_back(i);
    }
}

DeepPtr<Item> Bag::remove(vector<DeepPtr<Item>>::const_iterator it) {
    // se l'iteratore non ha un valore corretto viene sollevata un'eccezione da vector
    if (dynamic_cast<Object*>(it->get()) != nullptr) {
        Object* o = static_cast<Object*>(it->get());

        if (o->getAmount() <= 1){
            DeepPtr<Item> temp = *it;
            *items.erase(it);
            return temp;
        }

        Object* object = o->clone();
        object->remove(object->getAmount() - 1);

        o->remove();

        return DeepPtr<Item>(object);
    }
    DeepPtr<Item> temp = *it;
    items.erase(it);
    return temp;
}

double Bag::availableWeight() const { return maxWeight - getCarriedWeight(); }


vector<DeepPtr<Item>>::const_iterator Bag::begin() const { return items.begin(); }
vector<DeepPtr<Item>>::const_iterator Bag::end() const { return items.end(); }
