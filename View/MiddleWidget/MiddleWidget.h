#ifndef MIDDLEWIDGET_H
#define MIDDLEWIDGET_H

#include <QBoxLayout>
#include <QScrollArea>

#include "ClassInfo.h"
#include "HpManager.h"
#include "HandFrame.h"
#include "View/BagInfo/ItemDetails.h"

class MiddleWidget : public QWidget {
    Q_OBJECT
private:
    HandFrame* rightHand, *leftHand;
    ItemDetails *rightHandDetails, *leftHandDetails;
    HpManager* hp;
    QPushButton* rest;
    ClassInfo* classes;

public:
    explicit MiddleWidget(QWidget *parent = nullptr);

    HpManager* getHpManager() const;
    QPushButton* getRestButton() const;

    ClassInfo* getClasses() const;

    void setRightHand (const Item* item)const;
    void setLeftHand (const Item* item)const;
    HandFrame* getRightHand() const;
    HandFrame* getLeftHand() const;
};

#endif // MIDDLEWIDGET_H
