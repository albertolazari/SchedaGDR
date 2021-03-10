#include "InventoryViewer.h"

InventoryViewer::InventoryViewer(QWidget *parent) : QWidget(parent) {
    mainLayout = new QVBoxLayout;

    thrower = new DieThrower(this);
    mainLayout->addWidget(thrower);

    QLabel* title = new QLabel("Borsa", this);
    title->setAlignment(Qt::AlignCenter);
    title->setFont(QFont("Helvetica", 8, QFont::Bold));
    mainLayout->addWidget(title);

    QHBoxLayout* WLayout = new QHBoxLayout;
    WLayout->setAlignment(Qt::AlignLeft);
    WLayout->setSpacing(0);
    carriedWeight = new QLabel("Peso Trasportato: 0", this);
    maxWeight = new QLabel(" / 0",this);
    WLayout->addWidget(carriedWeight);
    WLayout->addWidget(maxWeight);
    mainLayout->addLayout(WLayout);

    bag = new BagList(this);
    mainLayout->addWidget(bag);

    details = new ItemDetails(this);
    QScrollArea* scrollDetails = new QScrollArea(this);
    scrollDetails->setWidget(details);
    scrollDetails->setWidgetResizable(true);
    mainLayout->addWidget(scrollDetails);

    QHBoxLayout* Blayout = new QHBoxLayout;
    del = new QPushButton("Elimina",this);
    REquip = new QPushButton("Equipaggia a Destra",this);
    LEquip = new QPushButton("Equipaggia a Sinistra",this);
    Blayout->addWidget(del);
    Blayout->addWidget(LEquip);
    Blayout->addWidget(REquip);
    mainLayout->addLayout(Blayout);

    setLayout(mainLayout);
    setMaximumWidth(450);

    connect(bag,&BagList::itemSelected, details, &ItemDetails::setItem);
    connect(bag->getTab(),&QTabWidget::currentChanged,this,&InventoryViewer::changeTab);
}

void InventoryViewer::updateMaxWeight(double weight) const {
    maxWeight->setText(ItemDetails::FixDecimals( QString::fromStdString(" / "+std::to_string(weight))));
}

void InventoryViewer::updateCarriedWeight(double weight) const {
    carriedWeight->setText(ItemDetails::FixDecimals( QString::fromStdString("Peso Trasportato: "+std::to_string(weight))));
}

BagList *InventoryViewer::getBagList() const {
    return bag;
}

ItemDetails *InventoryViewer::getItemDetails() const {
    return details;
}

DieThrower *InventoryViewer::getDieThrower() const {
    return thrower;
}

QPushButton *InventoryViewer::getDeleteButton() const {
    return del;
}

QPushButton *InventoryViewer::getREquipButton() const {
    return REquip;
}

QPushButton *InventoryViewer::getLEquipButton() const {
    return LEquip;
}

void InventoryViewer::changeTab(int i) const {
    auto it = bag->SelectedItem(i);
    if(it == nullptr)details->setItem(nullptr);
    else details->setItem(bag->SelectedItem(i)->get());
}
