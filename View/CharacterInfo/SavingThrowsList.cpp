#include "SavingThrowsList.h"

SavingThrowsList::SavingThrowsList(QWidget *parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout;
    setLayout(layout);

    QLabel* title = new QLabel("Tiri Salvezza", this);
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    for (unsigned i = 0; i < enums::abilitiesNumber; ++i)
        v.push_back(new SavingThrows(static_cast<ability>(i), this));

    bool first=true;
    QHBoxLayout* hlayout;
    for(auto x:v) {
        if(first){
            hlayout = new QHBoxLayout;
            hlayout->addWidget(x);
            first=false;
        }
        else{
            hlayout->addWidget(x);
            layout->addLayout(hlayout);
            first=true;
        }
    }
}

SavingThrows* SavingThrowsList::getSavingThrow(ability a) const { return v[a]; }
