#include "BagList.h"

BagList::BagList(QWidget *parent) : QWidget(parent),mainlayout(new QVBoxLayout) {
    //Aggiunta del menù a tab
    tabWidget = new QTabWidget(this);

    weaponList = new QListWidget(tabWidget);
    objectList = new QListWidget(tabWidget);

    weaponList->setFlow(QListView::Flow::TopToBottom);
    objectList->setFlow(QListView::Flow::TopToBottom);

    tabWidget->addTab(weaponList, "Armi");
    tabWidget->addTab(objectList, "Consumabili");

    mainlayout->addWidget(tabWidget);

    mainlayout->setContentsMargins(0,0,0,0);

    setLayout(mainlayout);

    connect(weaponList, &QListWidget::itemClicked, this, &BagList::selectItem);
    connect(objectList, &QListWidget::itemClicked, this, &BagList::selectItem);
}

void BagList::addItem(vector<DeepPtr<Item>>::const_iterator item) const {
    if (dynamic_cast<Weapon*>(item->get())) weaponList->addItem(new BagItem(item,weaponList));
    if (dynamic_cast<Object*>(item->get())) objectList->addItem(new BagItem(item,objectList));
}

void BagList::selectItem(QListWidgetItem* i) const {
    BagItem* b = dynamic_cast<BagItem*>(i);
    if(b == nullptr)throw std::runtime_error ("item nullptr nella borsa");
    emit itemSelected(b->getItem()->get());
}

QTabWidget *BagList::getTab() const {
    return tabWidget;
}

void BagList::clear() const {
    weaponList->clear();
    objectList->clear();
}

vector<DeepPtr<Item>>::const_iterator BagList::SelectedItem(int tab) const {
    if (tab == 0){
        if(weaponList->count() == 0) return nullptr;
        int indice = weaponList->currentRow();
        BagItem* b = dynamic_cast<BagItem*>(weaponList->item(indice));
        if(b == nullptr)return nullptr;
        return b->getItem();
    }
    else{
        if(objectList->count() == 0) return nullptr;
        int indice = objectList->currentRow();
        BagItem* b = dynamic_cast<BagItem*>(objectList->item(indice));
        if(b == nullptr)return nullptr;
        return b->getItem();
    }
}
