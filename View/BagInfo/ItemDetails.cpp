#include "ItemDetails.h"

ItemDetails::ItemDetails(QWidget *parent)
    : QFrame(parent),item_(nullptr),mainLayout(new QVBoxLayout(this)) {

    mainLayout->setAlignment(Qt::AlignTop);

    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setLineWidth(2);
    setLayout(mainLayout);
}

bool ItemDetails::isNull() const {
    return item_ == nullptr;
}

void ItemDetails::setItem(const Item* it) {
    item_=it;
    update();
}

void ItemDetails::printItem() {
    type = new QLabel(this);
    mainLayout->addWidget(type);
    mainLayout->addWidget(new QLabel(QString::fromStdString("Nome: "+item_->getName()),this));
    mainLayout->addWidget(new QLabel(ItemDetails::FixDecimals(
                                QString::fromStdString("Peso: "+std::to_string(item_->getWeight()))),this));
}

void ItemDetails::printWeapon() {
    type->setText("Arma da Mischia");
    const Weapon* weapon_ = dynamic_cast<const Weapon*>(item_);
    //dadi
    const vector<Die>v1 = weapon_->getDice();
    string st;
    st+="Dadi: ";
    for(auto x:v1){
        st+="d";
        st+=std::to_string(x.getFaces());
        st+= ", ";
    }
    st.pop_back(); st.pop_back();
    if(!v1.empty())mainLayout->addWidget(new QLabel(QString::fromStdString(st),this));
    else mainLayout->addWidget(new QLabel("Dadi: nessun dado"));

    //damagetype
    mainLayout->addWidget
            (new QLabel(QString::fromStdString("Tipo di Danno: "+weapon_->getDamageType()),this));

    //properties
    const vector<string>v2 = weapon_->getProperties();
    st.clear();
    st+="Proprietà:";
    for(const auto& x:v2){
        st+= "\n";
        st+="- ";
        st+=x;
    }

    if(!v2.empty())mainLayout->addWidget (new QLabel(QString::fromStdString(st),this));
    else mainLayout->addWidget(new QLabel("Proprietà: nessuna proprietà"));

    //bonus
    mainLayout->addWidget
            (new QLabel(QString::fromStdString("Bonus: " + std::to_string(weapon_->getBonus())),this));
}

void ItemDetails::printRanged() {
    type->setText("Arma a Distanza");
    const Ranged* ranged_ = dynamic_cast<const Ranged*>(item_);
    mainLayout->addWidget
            (new QLabel(QString::fromStdString("Gittata: "+std::to_string(ranged_->getRange())),this));
}

void ItemDetails::printAmmoWeapon() {
    type->setText("Arma a Munizioni");
    const AmmoWeapon* ammoweapon_ = dynamic_cast<const AmmoWeapon*>(item_);
    mainLayout->addWidget
            (new QLabel("Munizioni Utilizzate: " + QString::fromStdString(ammoweapon_->getAmmoUsed()),this));
}

void ItemDetails::printObject() {
    type->setText("Oggetto");
    const Object* object_ = dynamic_cast<const Object*>(item_);
    mainLayout->addWidget
            (new QLabel("Descrizione: "+QString::fromStdString(object_->getDescription()),this));
    mainLayout->addWidget
            (new QLabel(QString::fromStdString("Quantità: "+std::to_string(object_->getAmount())),this));
}

void ItemDetails::prinPotion() {
    type->setText("Pozione");
    const Potion* potion_ = dynamic_cast<const Potion*>(item_);

    //dadi
    const vector<Die>v1 = potion_->getDice();
    string st;
    st+="Dadi: ";
    for(auto x:v1){
        st+="d";
        st+=std::to_string(x.getFaces());
        st+= ", ";
    }
    st.pop_back(); st.pop_back();
    if(!v1.empty())mainLayout->addWidget(new QLabel(QString::fromStdString(st),this));
    else mainLayout->addWidget(new QLabel("Dadi: nessun dado"));
}

void ItemDetails::printAmmo() {
    type->setText("Munizioni");
    const Ammo* ammo_ = dynamic_cast<const Ammo*>(item_);

    if (ammo_->dealsBonusDamage()) {
        mainLayout->addWidget(
            new QLabel(QString::fromStdString("Tipo di Danno: "+ammo_->getDamageType()), this)
        );
        mainLayout->addWidget(
            new QLabel(
                QString::fromStdString("Dado Danno Bonus: "+std::to_string(ammo_->getBonusDamage().getFaces())),
                this
            )
        );
    }
}

QString ItemDetails::FixDecimals(const QString &decimal) {
    string s = decimal.toStdString();
    while(!s.empty() && s.back() == '0'){
        s.pop_back();
    }
    if(s.back() == '.' || s.back() == ',')s.pop_back();
    QString out = QString::fromStdString(s);
    return out;
}

void ItemDetails::update() {
    //distruzione widget vecchio layout
    // uso 1 per mantenere la label del tipo di oggetto
    if (mainLayout) {
        while(mainLayout->count() > 0){
            QLayoutItem *item = mainLayout->takeAt(0);
            QWidget* widget = item->widget();
            if(widget)
                delete widget;
            delete item;
        }
    }

    if(item_ != nullptr){
        printItem();
        if(dynamic_cast<const Weapon*>(item_)){
            printWeapon();
            if(dynamic_cast<const Ranged*>(item_)){
                printRanged();
                if(dynamic_cast<const AmmoWeapon*>(item_)){
                    printAmmoWeapon();
                }
            }
        }
        else if(dynamic_cast<const Object*>(item_)){
            printObject();

            if(dynamic_cast<const Potion*>(item_)){
                prinPotion();
            }
            else if(dynamic_cast<const Ammo*>(item_)){
                printAmmo();
            }

        }
    }
    setLayout(mainLayout);
}
