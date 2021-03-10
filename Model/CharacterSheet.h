#ifndef CHARACTERSHEET_H
#define CHARACTERSHEET_H

#include "Bag.h"
#include "Character.h"

#include "Item/Potion.h"
#include "Item/AmmoWeapon.h"
#include "Item/Ammo.h"

#include "NormalThrow.h"
#include "AttackThrow.h"

class CharacterSheet {
private:
    Character character;
    Bag* inventory;

public:
    CharacterSheet();

    NormalThrow throwOn(ability, bool savingThrow) const;
    NormalThrow throwOn(skill) const;
    NormalThrow throwHitDie(const string& className);
    AttackThrow attack(Hand, unsigned range = 1);

    // Inventory:
    void changeBag(double MaxWeight);

    // può sollevare eccezioni (item troppo pesante)
    void addItem(const DeepPtr<Item>&);
    // può sollevare eccezioni (bag vuota o indice out of range)
    DeepPtr<Item> removeItem(unsigned i, unsigned amount = 1);

    double getMaxWeight();
    double getCarriedWeight();
    vector<DeepPtr<Item>>::const_iterator BagBegin() const;
    vector<DeepPtr<Item>>::const_iterator BagEnd() const;

    // Character:
    Character& getCharacter();

    void equip(Hand, unsigned);
    void drop(Hand);
    int useItem(Hand);
};

#endif // CHARACTERSHEET_H
