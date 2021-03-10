#ifndef DIETHROWER_H
#define DIETHROWER_H

#include <QFrame>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>

#include "Model/Die.h"

class DieThrower : public QFrame {
private:
    QVBoxLayout* mainLayout;
    QHBoxLayout* hLayout;
    QComboBox* selector;
    QPushButton* button;

    void addSelector() const;

public:
    explicit DieThrower(QWidget* parent = nullptr);

    QPushButton* getButton() const;

    Die getSelectedDie() const;
};

#endif // DIETHROWER_H
