#include "Character.h"
using namespace enums;

// Character::Class
// ==============================================================================================
Character::Class::Class(std::string s, Die d, unsigned l)
    : name(s), level(l), hitDie(d), hitDiceUsed(0) {}

const string& Character::Class::getName() const { return name; }
unsigned Character::Class::getLevel() const { return level; }
unsigned Character::Class::getHitDieFaces() const { return hitDie.getFaces(); }
unsigned Character::Class::getHitDiceUsed() const { return hitDiceUsed; }
unsigned Character::Class::getHitDiceLeft() const { return level - hitDiceUsed; }
unsigned Character::Class::rollHitDie() {
    if (hitDiceUsed >= level)
        throw std::runtime_error("Non sono disponibili altri dadi vita per la classe " + name);
    ++hitDiceUsed;
    return hitDie.roll();
}
void Character::Class::restoreDice() { hitDiceUsed = 0; }
void Character::Class::levelUp() { ++level; }

// Character::Skill
// ==============================================================================================
Character::Skill::Skill(ability ab, bool p, bool m) : a(ab), proficiency(p), mastery(m) {}

ability Character::Skill::getAbility() const { return a; }
bool Character::Skill::hasProficiency() const { return proficiency; }
bool Character::Skill::hasMastery() const { return mastery; }

void Character::Skill::setProficiency(bool p, bool m) {
    proficiency = p;
    mastery = m;
}

// Character
// ==============================================================================================
const unsigned Character::maxLevel = 20;

Character::Character()
    : maxHp(1),
      hp(1),
      bonusHp(0),
      abilityScore(enums::abilitiesNumber, 1),
      savingThrow(enums::abilitiesNumber, false),
      skills(
        {
            dexterity,
            wisdom,
            intelligence,
            strenght,
            charisma,
            intelligence,
            wisdom,
            charisma,
            intelligence,
            wisdom,
            intelligence,
            wisdom,
            charisma,
            charisma,
            intelligence,
            dexterity,
            dexterity,
            wisdom
        }
    ) {}

const std::string &Character::getName() const { return name; }
const std::string &Character::getRace() const { return race; }
const std::string &Character::getAlignement() const { return alignement; }
const vector<Character::Class> &Character::getClasses() const { return classes; }
const Character::Class& Character::getClass(const string& n) const {
    for (const Class& c : classes)
        if (c.getName() == n)
            return c;

    throw std::runtime_error(name + " non ha la classe " + n);
}

unsigned Character::getLevel() const {
    unsigned sum = 0;
    for (const Class& c : classes)
        sum += c.getLevel();
    return (sum == 0 ? 1 : sum);
}
unsigned Character::getArmorClass() const {
    return 10 + getAbilityModifier(dexterity);
}
unsigned Character::getMaxHp() const { return maxHp; }
unsigned Character::getBonusHp() const { return bonusHp; }
unsigned Character::getCurrentHp() const { return hp; }

DeepPtr<const Item> Character::getHandItem(Hand h) const {
    if(hand[h].get() == nullptr) return nullptr;
    return hand[h].get()->clone();
}

unsigned Character::getProficiencyBonus() const { return ((getLevel() - 1) / 4) + 2; }

unsigned Character::getAbilityScore(ability a) const { return abilityScore[a]; }
int Character::getAbilityModifier(ability a) const { return (abilityScore[a] / 2) - 5; }
bool Character::hasProficiency(ability a) const { return savingThrow[a]; }

const Character::Skill& Character::getSkill(skill s) const { return skills[s]; }

DeepPtr<Item> Character::pick(Hand h, const DeepPtr<Item> & i) {
    DeepPtr<Item> ret = hand[h];
    hand[h] = i;
    return ret;
}

DeepPtr<Item> Character::drop(Hand h) { return hand[h].release(); }

unsigned Character::rollHitDie(const string& className) {
    for (Class& c : classes)
        if (c.getName() == className)
            return c.rollHitDie();

    throw std::runtime_error(name + " non ha la classe " + className);
}

void Character::setName(const string& n) { name = n; }
void Character::setRace(const string& r) { race = r; }
void Character::setAlignment(const string& a) { alignement = a; }

void Character::addClass(const Class& newClass) {
    for (const Class& c : classes) {
        if (c.getName() == newClass.getName())
            throw std::runtime_error("Il personaggio ha già questa classe");
    }

    if (newClass.getLevel() + getLevel() > maxLevel)
        throw std::runtime_error("Il personaggio non può superare il livello " + std::to_string(maxLevel));

    classes.push_back(newClass);
}
void Character::removeClass(const string& className) {
    bool found = false;
    vector<Class>::const_iterator cit = classes.begin();
    while (cit != classes.end() && !found) {
        if (cit->getName() == className) {
            classes.erase(cit);
            found = true;
        }
        else
            ++cit;
    }
    if (!found)
        throw std::runtime_error(name + " non ha la classe " + className);
}

void Character::takeDamage(unsigned damage) {
    if (damage > bonusHp) {
        damage -= bonusHp;
        bonusHp = 0;
        hp = (static_cast<int>(hp - damage) < 0 ? 0 : hp - damage);
    }
    else
        bonusHp -= damage;
}
void Character::heal(unsigned h) { hp = ((hp + h) > maxHp ? maxHp : hp + h); }
void Character::setMaxHp(unsigned n) {
    maxHp = n;
    if (hp > maxHp)
        hp = maxHp;
}
void Character::setCurrentHp(unsigned n){
    if (n > maxHp)
        throw std::runtime_error("Il personaggio non può avere Punti Ferita superiori al massimo");
    hp = n;
}
void Character::setBonusHp(unsigned n) { bonusHp = n; }
void Character::rest() {
    hp = maxHp;

    for (Class& c : classes)
        c.restoreDice();
}

void Character::levelUp(const std::string& className) {
    if (getLevel() >= maxLevel)
        throw std::runtime_error("Il personaggio ha già raggiunto il livello massimo");

    bool found = false;
    for (Class& c : classes)
        if (c.getName() == className) {
            c.levelUp();
            found = true;
        }
    if (!found)
        throw std::runtime_error(name + " non ha la classe " + className);
}

void Character::setAbilityScore(ability a, unsigned n) { abilityScore[a] = n < 1 ? 1 : n; }
void Character::setSavingThrowProficiency(ability a, bool p) { savingThrow[a] = p; }
void Character::setSkillProficiency(skill s, bool p, bool m) { skills[s].setProficiency(p, m); }
