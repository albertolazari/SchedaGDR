#include "BagItem.h"



BagItem::BagItem(vector<DeepPtr<Item>>::const_iterator item, QListWidget *parent)
    :QListWidgetItem(QString::fromStdString((*item)->getName()),parent),item_(item) { }

vector<DeepPtr<Item>>::const_iterator BagItem::getItem() const
{
    return item_;
}
