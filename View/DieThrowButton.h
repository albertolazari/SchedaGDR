#ifndef DIETHROWBUTTON_H
#define DIETHROWBUTTON_H

#include <QPushButton>

class DieThrowButton : public QPushButton {
public:
    DieThrowButton(int bonus = 0, QWidget* parent = nullptr);

    void updateBonus(int);
    QPushButton* getButton();
};

#endif // DIETHROWBUTTON_H
