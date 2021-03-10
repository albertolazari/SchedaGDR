#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenuBar>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>

#include "CharacterInfo/CharacterInfo.h"
#include "BagInfo/InventoryViewer.h"
#include "MiddleWidget/MiddleWidget.h"
#include "Label.h"

#include "Model/Item/AmmoWeapon.h"
#include "Model/Item/Potion.h"
#include "Model/Item/Ammo.h"
#include "Model/AttackThrow.h"

class Controller;

class MainWindow : public QWidget {
    Q_OBJECT

private:
    Controller* controller;

    QVBoxLayout* mainLayout;
    QHBoxLayout* hLayout;

    //Labels
    Label* nameLabel;
    Label* raceLabel;
    Label* levelLabel;
    Label* alignmentLabel;

    CharacterInfo* stats;
    MiddleWidget* middleWidget;
    InventoryViewer* bag;

    //Menù
    QMenu* File;

    QMenu* Inserisci;
        QMenu* Arma;
        QMenu* Consumabile;

    QMenu* Modifica;
        QMenu* Personaggio;
        QMenu* Borsa;
        QMenu* Statistiche;
        QMenu* PuntiFerita;

    void addMenu();
    void addTabLayout();
    void addLabels();

public:
    explicit MainWindow(QWidget* parent = nullptr);

    void setController(Controller* c);

    Weapon* ShowAddWeaponDialog();
    Ranged* ShowAddRangedDialog();
    AmmoWeapon* ShowAddAmmoWeaponDialog();
    Object* ShowAddObjectDialog();
    Potion* ShowAddPotionDialog();
    Ammo* ShowAddAmmoDialog();

    Character::Class ShowAddClassDialog(bool* ok);

    QString showFileSelectDialog(const QString& title, bool* ok = nullptr);
    QString ShowAddStringDialog(const QString& title, bool* ok = nullptr);
    bool showMessageBox(const QString& title, const QString& text);
    double ShowAddDoubleDialog (const QString& title);
    unsigned ShowAddIntDialog(const QString& title, unsigned min = 0, bool* ok = nullptr);
    unsigned ShowRangeDialog();

    void showWarning(const QString& message);
    void showHealDialog(int diceSum,int modifier);
    void showDieThrowDialog(int result);
    void showDieThrowDialog(const NormalThrow&);

    CharacterInfo* getStats() const;
    MiddleWidget* getMiddleWidget() const;
    InventoryViewer* getBag() const;

    //set Labels
    void setName(const QString&) const;
    void setRace(const QString&) const;
    void setLevel(unsigned) const;
    void setAlignment(const QString&) const;

    //set abilities
    void setAbilityScore(ability, unsigned score) const;
    void setAbilityModifier(ability, int modifier) const;

    //set statistics
    void setProficiencyBonus(unsigned) const;
    void setArmorClass(unsigned) const;

    //set hp
    void setMaxHp(unsigned) const;
    void setCurrentHp(unsigned) const;
    void setBonusHp(unsigned) const;
};

#endif // MAINWINDOW_H
