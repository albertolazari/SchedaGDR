#ifndef BAGLIST_H
#define BAGLIST_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>

#include "BagItem.h"
#include "Model/Item/Item.h"
#include "Model/Item/Weapon.h"
#include "Model/Item/Object.h"

class BagList : public QWidget {
    Q_OBJECT
private:
    QListWidget* weaponList, *objectList;
    QTabWidget* tabWidget;
    QVBoxLayout* mainlayout;

public:
    explicit BagList(QWidget *parent = nullptr);
    void addItem(vector<DeepPtr<Item>>::const_iterator item) const;
    void clear() const;
    vector<DeepPtr<Item>>::const_iterator SelectedItem(int currentTab) const;

public slots:
    void selectItem (QListWidgetItem*) const;
    QTabWidget* getTab() const;

signals:
    void itemSelected(Item*) const;
};

#endif // BAGLIST_H
