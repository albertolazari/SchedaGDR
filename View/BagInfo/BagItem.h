#ifndef BAGITEM_H
#define BAGITEM_H

#include <QListWidgetItem>
#include <QString>
#include "Model/Bag.h"

class BagItem : public QListWidgetItem {
private:
    vector<DeepPtr<Item>>::const_iterator item_;

public:
    BagItem(vector<DeepPtr<Item>>::const_iterator item,QListWidget* parent = nullptr);
    vector<DeepPtr<Item>>::const_iterator getItem() const;
};

#endif // BAGITEM_H
