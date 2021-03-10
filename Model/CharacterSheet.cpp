#include "CharacterSheet.h"
using namespace enums;

// CharacterSheet
// ==============================================================================================
CharacterSheet::CharacterSheet() : inventory(new Bag) {}

NormalThrow CharacterSheet::throwOn(ability a, bool saving) const {
    bool bonus = saving && character.hasProficiency(a);
    return NormalThrow(
        Die(20).roll(),
        20,
        character.getAbilityModifier(a),
        bonus,
        bonus ? character.getProficiencyBonus() : 0
    );
}
NormalThrow CharacterSheet::throwOn(skill s) const {
    Character::Skill selectedSkill = character.getSkill(s);
    unsigned bonus = 0;
    if (selectedSkill.hasProficiency()) {
        if (selectedSkill.hasMastery())
            bonus = character.getProficiencyBonus() * 2;
        else
            bonus = character.getProficiencyBonus();
    }

    return NormalThrow(
        Die(20).roll(),
        20,
        character.getAbilityModifier(selectedSkill.getAbility()),
        // Il bonus di competenza è almeno 2 => se 0 allora non ha competenza
        bonus != 0,
        bonus
    );
}
NormalThrow CharacterSheet::throwHitDie(const string& className) {
    NormalThrow dieThrow(
        character.rollHitDie(className),
        character.getClass(className).getHitDieFaces(),
        character.getAbilityModifier(constitution)
    );
    character.heal(dieThrow.getThrow());

    return dieThrow;
}

AttackThrow CharacterSheet::attack(Hand h, unsigned range) {
    Weapon* w = dynamic_cast<Weapon*>(character.hand[h].get());
    if (w == nullptr)
        throw std::runtime_error("L'oggetto selezionato non può essere utilizzato per un attacco");

    AmmoWeapon* ammow = dynamic_cast<AmmoWeapon*>(w);
    if (ammow != nullptr) {
        Ammo* ammo = dynamic_cast<Ammo*>(character.hand[h == leftHand ? rightHand : leftHand].get());
        if (ammo == nullptr)
            throw std::runtime_error("Il personaggio non ha in mano munizioni per l'arma");
        if (ammo->getName() != ammow->getAmmoUsed())
            throw std::runtime_error(ammo->getName() + " non è la muzione adatta all'arma");
        if (ammow->getRange() < range)
            throw std::runtime_error("Nemico fuori portata");

        if (ammo->dealsBonusDamage())
            return AttackThrow(
                Die(20).roll(),
                useItem(h),
                ammow->getDamageType(),
                character.getAbilityModifier(dexterity),
                ammow->getBonus(),
                useItem(h == leftHand ? rightHand : leftHand),
                ammo->getDamageType()
            );
        else {
            useItem(h == leftHand ? rightHand : leftHand);

            return AttackThrow(
                Die(20).roll(),
                useItem(h),
                ammow->getDamageType(),
                character.getAbilityModifier(dexterity),
                ammow->getBonus()
            );
        }
    }
    Ranged* rangedw = dynamic_cast<Ranged*>(w);
    if (rangedw != nullptr) {
        if (range > 1) {
            if (rangedw->getRange() < range)
                throw std::runtime_error("Nemico fuori portata");
            AttackThrow ret = AttackThrow(
                Die(20).roll(),
                useItem(h),
                rangedw->getDamageType(),
                character.getAbilityModifier(strenght),
                rangedw->getBonus()
            );
            drop(h);
            return ret;
        }
        else
            return AttackThrow(
                Die(20).roll(),
                useItem(h),
                rangedw->getDamageType(),
                character.getAbilityModifier(strenght),
                rangedw->getBonus()
            );
    }
    if (range > 1)
        throw std::runtime_error("Nemico fuori portata");

    return AttackThrow(
        Die(20).roll(),
        useItem(h),
        w->getDamageType(),
        character.getAbilityModifier(strenght),
        w->getBonus()
    );
}

// Inventory
// ==============================================================================================
void CharacterSheet::changeBag(double MaxWeight) {
    if (inventory != nullptr) {
        if (MaxWeight < 0 || MaxWeight < inventory->getCarriedWeight()) {
            throw std::runtime_error("La capienza selezionata non può contenere tutti gli oggetti");
        }
        Bag* temp = new Bag(MaxWeight);
        for (const auto& item : *inventory) {
            temp->add(item);
        }
        delete inventory;
        inventory = temp;
    }
    else inventory = new Bag(MaxWeight);
}

void CharacterSheet::equip(Hand h, unsigned i) {
    inventory->add(character.pick(h, inventory->remove(inventory->begin() + i)));
}

void CharacterSheet::drop(Hand h) { inventory->add(character.drop(h)); }

void CharacterSheet::addItem(const DeepPtr<Item> & i) { inventory->add(i); }

DeepPtr<Item> CharacterSheet::removeItem(unsigned i, unsigned amount) {
    const DeepPtr<Item>& temp = *(inventory->begin() + i);

    if (dynamic_cast<Object*>(temp.get()) != nullptr) {
        Object* o = static_cast<Object*>(temp.get());
        unsigned oAmount = o->getAmount();
        o->remove(amount);
        Object* ret = o->clone();
        ret->remove(ret->getAmount());
        ret->add(oAmount >= amount ? amount : oAmount);
        if (o->getAmount() == 0) {
            inventory->remove(inventory->begin() + i);
        }
        return ret;
    }
    else return inventory->remove(inventory->begin() + i);
}

double CharacterSheet::getMaxWeight() { return inventory->getMaxWeight(); }

double CharacterSheet::getCarriedWeight() { return inventory->getCarriedWeight(); }

vector<DeepPtr<Item>>::const_iterator CharacterSheet::BagBegin() const {
    return inventory->begin();
}

vector<DeepPtr<Item>>::const_iterator CharacterSheet::BagEnd() const {
    return inventory->end();
}

// Character
// ==============================================================================================
Character& CharacterSheet::getCharacter() { return character; }

int CharacterSheet::useItem(Hand h) {
    if (character.hand[h] == nullptr)
        throw std::runtime_error("La mano è vuota");

    int n = character.hand[h]->use();
    Object* obj = dynamic_cast<Object*>(character.hand[h].get());
    // L'oggetto va eliminato, perché ha sempre quantità 1 se è in mano
    if (obj != nullptr) {
        if (dynamic_cast<Potion*>(obj) != nullptr) {
            int i = n + (character.getAbilityModifier(constitution) < 1 ? 1 : character.getAbilityModifier(constitution));
            character.heal(i);
        }
        character.drop(h);
    }
    return n;
}
