#ifndef ITEMDETAILS_H
#define ITEMDETAILS_H

#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <string>
#include "Model/Item/Item.h"
#include "Model/Item/AmmoWeapon.h"
#include "Model/Item/Ammo.h"
#include "Model/Item/Potion.h"

class ItemDetails : public QFrame {
    Q_OBJECT
private:
    const Item* item_;
    QVBoxLayout* mainLayout;
    QLabel* type;

    void update();

    void printItem();
    void printWeapon();
    void printRanged();
    void printAmmoWeapon();
    void printObject();
    void prinPotion();
    void printAmmo();
    
public:
    static QString FixDecimals (const QString& decimal);

    explicit ItemDetails(QWidget *parent = nullptr);
    bool isNull() const;

public slots:
    void setItem(const Item*);
};

#endif // ITEMDETAILS_H
