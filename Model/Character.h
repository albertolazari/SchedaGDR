#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
using std::string;

#include "vector.h"
#include "Item/Item.h"
#include "DeepPtr.h"
#include "Die.h"
#include "AbilitiesEnums.h"
using enums::ability;
using enums::skill;

enum Hand { leftHand, rightHand };

class CharacterSheet;

class Character {
public:
    class Class {
    private:
        string name;
        unsigned level;
        Die hitDie;
        unsigned hitDiceUsed;

    public:
        Class() = default;
        Class(string name, Die, unsigned level = 1);

        const string& getName() const;
        unsigned getLevel() const;

        unsigned getHitDieFaces() const;
        unsigned getHitDiceUsed() const;
        unsigned getHitDiceLeft() const;
        unsigned rollHitDie();
        void restoreDice();

        void levelUp();
    };
    class Skill {
    private:
        ability a;
        bool proficiency, mastery;

    public:
        Skill() = default;
        Skill(ability, bool Proficiency = false, bool Mastery = false);

        ability getAbility() const;
        bool hasProficiency() const;
        bool hasMastery() const;

        void setProficiency(bool Proficiency, bool Mastery);
    };

friend class CharacterSheet;
private:
    string name, race, alignement;
    vector<Class> classes;
    unsigned maxHp, hp, bonusHp;
    DeepPtr<Item> hand[2];
    vector<unsigned> abilityScore;
    vector<bool> savingThrow;
    vector<Skill> skills;

    // Metodi che utilizza solo CharacterSheet
    DeepPtr<Item> pick(Hand, const DeepPtr<Item>&);
    DeepPtr<Item> drop(Hand);
    // Solleva un'eccezione se non esiste la classe
    // Attenzione: ritorna il risultato del dado senza il bonus di Costituzione
    unsigned rollHitDie(const string& className);

public:
    static const unsigned maxLevel;

    Character();
    const string& getName() const;
    const string& getRace() const;
    const string& getAlignement() const;
    const vector<Class>& getClasses() const;
    // Solleva un'eccezione se non esiste la classe "className"
    const Class& getClass(const string& className) const;
    unsigned getLevel() const;
    unsigned getArmorClass() const;
    unsigned getMaxHp() const;
    unsigned getCurrentHp() const;
    unsigned getBonusHp() const;
    unsigned getProficiencyBonus() const;

    unsigned getAbilityScore(ability) const;
    int getAbilityModifier(ability) const;
    bool hasProficiency(ability) const;
    const Skill& getSkill(skill) const;

    DeepPtr<const Item> getHandItem(Hand) const;

    void setName(const string&);
    void setRace(const string&);
    void setAlignment(const string&);

    void addClass(const Class&);
    void removeClass(const string& className);

    void setMaxHp(unsigned);
    void setCurrentHp(unsigned);
    void takeDamage(unsigned);
    void heal(unsigned);
    void setBonusHp(unsigned);

    void rest();
    // Solleva un'eccezione se non esiste la classe o se il personaggio è al livello massimo
    void levelUp(const string& className);

    void setAbilityScore(ability, unsigned);
    void setSavingThrowProficiency(ability, bool Proficiency);
    void setSkillProficiency(skill, bool Proficiency, bool Mastery = false);
};

#endif // CHARACTER_H
