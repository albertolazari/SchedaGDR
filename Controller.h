#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <fstream>

#include <QObject>
#include <fstream>
#include "View/MainWindow.h"
#include "Model/CharacterSheet.h"

class Controller : public QObject {
    Q_OBJECT
private:
    CharacterSheet* Model;
    MainWindow* View;
    QString CurrentFile;

    static void printItemDetails (std::ofstream& os, const Item* item);
    void saveCharacter ();


    static string getLine(std::ifstream&);
    static Item* getItem(std::ifstream&);
    static CharacterSheet* loadCharacter(const QString& path);
    void refreshBag() const;

public:
    explicit Controller(QObject *parent = nullptr);

    void setModel(CharacterSheet* m);
    void setView(MainWindow* v);

public slots:

    void updateSavingThrows() const;
    void setSavingThrowsProf(enums::ability) const;
    void updateSavingThrowBonus(enums::ability) const;
    void throwSavingThrowOn(enums::ability) const;

    void updateSkills() const;
    void changeSkillProficiency(enums::skill) const;
    void updateSkillBonus(enums::ability) const;
    void updateSkillBonus(enums::skill) const;
    void throwOn(enums::skill) const;

    void addWeapon() const;
    void addRanged() const;
    void addAmmoWeapon() const;
    void addObject() const;
    void addPotion() const;
    void addAmmo() const;

    void deleteItem() const;

    void equipRight() const;
    void equipLeft() const;
    void dropRight() const;
    void dropLeft() const;
    void useRight() const;
    void useLeft() const;

    void setMaxWeight() const;

    void setName() const;
    void setRace() const;
    void updateLevel() const;
    void setAlignment() const;

    void updateAblityScore(enums::ability) const;
    void setAbilityScore(enums::ability) const;
    void throwOn(enums::ability) const;

    void updateProficiencyBonus() const;
    void updateArmorClass(enums::ability abilityChanged) const;

    void setMaxHp() const;
    void setCurrentHp() const;
    void setBonusHp() const;
    void updateHp() const;

    void heal() const;
    void takeDamage() const;
    void rest() const;

    void updateClasses() const;
    void addClass() const;
    void removeCurrentClass() const;
    void levelUpCurrentClass() const;
    void throwHitDieOnClass(const QString& className) const;

    void dieThrow() const;

    void newCharacter();
    void loadCharacterFile();

    void saveAs ();
    void save ();


signals:
    void levelChanged() const;

    void abilityScoreChanged(enums::ability) const;
    void savingThrowProficiencyChanged(enums::ability) const;
    void skillProficiencyChanged(enums::skill) const;

    void hpChanged() const;
};

#endif // CONTROLLER_H
