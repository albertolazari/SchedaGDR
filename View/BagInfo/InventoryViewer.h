#ifndef INVENTORYVIEWER_H
#define INVENTORYVIEWER_H

#include <QWidget>
#include <QTabWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>

#include "Model/Item/Item.h"
#include "Model/Item/Weapon.h"
#include "Model/Item/Object.h"
#include "BagItem.h"
#include "ItemDetails.h"
#include "BagList.h"
#include "DieThrower.h"
#include <QScrollArea>

class InventoryViewer : public QWidget {
    Q_OBJECT
private:
    QVBoxLayout* mainLayout;
    BagList* bag;
    ItemDetails* details;
    DieThrower* thrower;

    QPushButton* del;
    QPushButton* REquip;
    QPushButton* LEquip;

    QLabel* maxWeight;
    QLabel* carriedWeight;

public:
    explicit InventoryViewer(QWidget *parent = nullptr);

    void updateMaxWeight(double weight) const;
    void updateCarriedWeight (double weight) const;

    BagList* getBagList() const;
    ItemDetails* getItemDetails() const;
    DieThrower* getDieThrower() const;
    QPushButton* getDeleteButton() const;
    QPushButton* getREquipButton() const;
    QPushButton* getLEquipButton() const;

public slots:
    void changeTab(int i) const;

};

#endif // INVENTORYVIEWER_H
