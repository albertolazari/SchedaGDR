#include "MainWindow.h"
#include "Controller.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
    stats(new CharacterInfo(this)),
    middleWidget(new MiddleWidget(this)),
    bag(new InventoryViewer(this)) {
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    addMenu();
    addLabels();

    hLayout = new QHBoxLayout;
    mainLayout->addLayout(hLayout);
    hLayout->addWidget(stats);
    hLayout->addWidget(middleWidget);
    hLayout->addWidget(bag);
}

void MainWindow::setController(Controller *c) {
    controller = c;

    //inserisci Items
    connect(Arma->actions()[0], SIGNAL(triggered()), controller, SLOT(addWeapon()));
    connect(Arma->actions()[1], SIGNAL(triggered()), controller, SLOT(addRanged()));
    connect(Arma->actions()[2], SIGNAL(triggered()), controller, SLOT(addAmmoWeapon()));
    connect(Consumabile->actions()[0], SIGNAL(triggered()), controller, SLOT(addObject()));
    connect(Consumabile->actions()[1], SIGNAL(triggered()), controller, SLOT(addPotion()));
    connect(Consumabile->actions()[2], SIGNAL(triggered()), controller, SLOT(addAmmo()));

    //bag
    connect(bag->getDeleteButton(), SIGNAL(clicked()), controller, SLOT(deleteItem()));
    connect(bag->getREquipButton(), SIGNAL(clicked()), controller, SLOT(equipRight()));
    connect(bag->getLEquipButton(), SIGNAL(clicked()), controller, SLOT(equipLeft()));
    connect(Borsa->actions()[0], SIGNAL(triggered()), controller, SLOT(setMaxWeight()));
    connect(middleWidget->getRightHand()->getDropButton(), SIGNAL(clicked()), controller, SLOT(dropRight()));
    connect(middleWidget->getLeftHand()->getDropButton(), SIGNAL(clicked()), controller, SLOT(dropLeft()));
    connect(middleWidget->getRightHand()->getUseButton(), SIGNAL(clicked()), controller, SLOT(useRight()));
    connect(middleWidget->getLeftHand()->getUseButton(), SIGNAL(clicked()), controller, SLOT(useLeft()));
    connect(bag->getDieThrower()->getButton(), SIGNAL(clicked()), controller, SLOT(dieThrow()));

    //saving throws
    for (unsigned i = 0; i < enums::abilitiesNumber; ++i) {
        SavingThrows* t = stats->getModifierLists()->getSavingThrowsList()->getSavingThrow(static_cast<ability>(i));
        connect(
            t->getTick(),
            &QPushButton::clicked,
            controller,
            [=]() { controller->setSavingThrowsProf(static_cast<ability>(i)); }
        );
        connect(
            t->getModifierButton(),
            &QPushButton::clicked,
            controller,
            [=]() { controller->throwSavingThrowOn(static_cast<ability>(i)); }
        );
    }

    //skills
    for (unsigned i = 0; i < enums::skillsNumber; ++i) {
        Skills* s = stats->getModifierLists()->getSkillsList()->getSkill(static_cast<skill>(i));
        connect(
            s->getTick(),
            &QPushButton::clicked,
            controller,
            [=]() { controller->changeSkillProficiency(static_cast<skill>(i)); }
        );
        connect(
            s->getModifierButton(),
            &QPushButton::clicked,
            controller,
            [=]() { controller->throwOn(static_cast<skill>(i)); }
        );
    }

    //set Labels
    connect(Personaggio->actions()[0], SIGNAL(triggered()), controller, SLOT(setName()));
    connect(Personaggio->actions()[1], SIGNAL(triggered()), controller, SLOT(setRace()));
    connect(Personaggio->actions()[2], SIGNAL(triggered()), controller, SLOT(setAlignment()));

    //set abilities
    for (unsigned i = 0; i < enums::abilitiesNumber; ++i) {
        connect(
            Statistiche->actions()[i],
            &QAction::triggered,
            controller,
            [=]() { controller->setAbilityScore(static_cast<ability>(i)); }
        );
        connect(
            stats->getAbilitiesList()->getButton(static_cast<ability>(i)),
            &QPushButton::clicked,
            controller,
            [=]() { controller->throwOn(static_cast<ability>(i)); }
        );
    }

    //set hp
    connect(PuntiFerita->actions()[0], SIGNAL(triggered()), controller, SLOT(setMaxHp()));
    connect(PuntiFerita->actions()[1], SIGNAL(triggered()), controller, SLOT(setCurrentHp()));
    connect(PuntiFerita->actions()[2], SIGNAL(triggered()), controller, SLOT(setBonusHp()));

    //hp manager
    connect(middleWidget->getHpManager()->getHealButton(), SIGNAL(clicked()), controller, SLOT(heal()));
    connect(middleWidget->getHpManager()->getDamageButton(), SIGNAL(clicked()), controller, SLOT(takeDamage()));
    connect(middleWidget->getRestButton(), SIGNAL(clicked()), controller, SLOT(rest()));

    //classes
    connect(middleWidget->getClasses()->getAddButton(), SIGNAL(clicked()), controller, SLOT(addClass()));
    connect(middleWidget->getClasses()->getRemoveButton(), SIGNAL(clicked()), controller, SLOT(removeCurrentClass()));
    connect(middleWidget->getClasses()->getLevelUpButton(), SIGNAL(clicked()), controller, SLOT(levelUpCurrentClass()));

    //file
    connect(File->actions()[0], SIGNAL(triggered()), controller, SLOT(newCharacter()));
    connect(File->actions()[1], SIGNAL(triggered()), controller, SLOT(loadCharacterFile()));
    connect(File->actions()[2], SIGNAL(triggered()), controller, SLOT(save()));
    connect(File->actions()[3], SIGNAL(triggered()), controller, SLOT(saveAs()));

}

void MainWindow::addMenu() {
    QMenuBar* menu = new QMenuBar(this);

    File = new QMenu("File", menu);
    menu->addMenu(File);
    QAction* quit = new QAction("Chiudi", File);
    File->addAction(new QAction("Nuovo", File));
    File->addAction(new QAction("Apri", File));
    File->addAction(new QAction("Salva", File));
    File->addAction(new QAction("Salva con Nome", File));
    File->addAction(quit);

    Inserisci = new QMenu("Inserisci", menu);
    menu->addMenu(Inserisci);

    Arma = new QMenu("Arma", Inserisci);
    Arma->addAction(new QAction("Da mischia", Arma));
    Arma->addAction(new QAction("A distanza", Arma));
    Arma->addAction(new QAction("A munizioni", Arma));
    Inserisci->addMenu(Arma);

    Consumabile = new QMenu("Consumabile", Inserisci);
    Consumabile->addAction(new QAction("Oggetto", Consumabile));
    Consumabile->addAction(new QAction("Pozione", Consumabile));
    Consumabile->addAction(new QAction("Munizione", Consumabile));
    Inserisci->addMenu(Consumabile);

    Modifica = new QMenu("Modifica", menu);
    menu->addMenu(Modifica);

    Personaggio = new QMenu("Personaggio", Modifica);
    Personaggio->addAction(new QAction("Nome", Personaggio));
    Personaggio->addAction(new QAction("Razza", Personaggio));
    Personaggio->addAction(new QAction("Allineamento", Personaggio));
    Modifica->addMenu(Personaggio);

    Statistiche = new QMenu("Statistiche", Modifica);
    Statistiche->addAction(new QAction("Forza", Statistiche));
    Statistiche->addAction(new QAction("Destrezza", Statistiche));
    Statistiche->addAction(new QAction("Costituzione", Statistiche));
    Statistiche->addAction(new QAction("Intelligenza", Statistiche));
    Statistiche->addAction(new QAction("Saggezza", Statistiche));
    Statistiche->addAction(new QAction("Carisma", Statistiche));
    Modifica->addMenu(Statistiche);

    PuntiFerita = new QMenu("Punti Ferita", Modifica);
    Modifica->addMenu(PuntiFerita);
    PuntiFerita->addAction(new QAction("Massimi", PuntiFerita));
    PuntiFerita->addAction(new QAction("Attuali", PuntiFerita));
    PuntiFerita->addAction(new QAction("Temporanei", PuntiFerita));

    Borsa = new QMenu("Borsa", Modifica);
    Borsa->addAction(new QAction("Capienza Massima", Borsa));
    Modifica->addMenu(Borsa);

    connect(quit, SIGNAL(triggered()), this, SLOT(close()));

    mainLayout->addWidget(menu);
}

void MainWindow::addLabels() {
    QHBoxLayout* labelsLayout = new QHBoxLayout;
    mainLayout->addLayout(labelsLayout);

    nameLabel = new Label("Nome", this);
    labelsLayout->addWidget(nameLabel);

    raceLabel = new Label("Razza", this);
    labelsLayout->addWidget(raceLabel);

    levelLabel = new Label("Livello", this);
    levelLabel->setText("1");
    labelsLayout->addWidget(levelLabel);

    alignmentLabel = new Label("Allineamento", this);
    labelsLayout->addWidget(alignmentLabel);
}

Weapon* MainWindow::ShowAddWeaponDialog() {
    bool ok = true;

    string name = QInputDialog::getText(this, "Aggiungi Arma", "Nome:", QLineEdit::Normal, QString(), &ok).toStdString();
    if (!ok)return nullptr;

    double weight = QInputDialog::getDouble(this, "Aggiungi Arma", "Peso:", 0, 0, 2147483647, 1, &ok);//maggiore di 0
    if (!ok)return nullptr;

    int nDice = QInputDialog::getInt(this, "Aggiungi Arma", "Numero di Dadi:", 0, 0, 2147483647, 1, &ok);
    if (!ok)return nullptr;

    vector<Die>v;
    for (int i = 0; i < nDice; i++) {
        int die = QInputDialog::getInt(this, "Aggiungi Arma",
            QString::fromStdString("Numero di facce Dado " + std::to_string(i + 1) + ":"), 1, 1, 2147483647, 1, &ok);
        if (!ok)return nullptr;
        v.push_back(Die(die));
    }

    string dmgtype = QInputDialog::getText(
        this, "Aggiungi Arma", "Tipo di Danno:", QLineEdit::Normal, QString(), &ok).toStdString();
    if (!ok)return nullptr;

    int nProp = QInputDialog::getInt(this, "Aggiungi Arma", "Numero di Proprietà:", 0, 0, 2147483647, 1, &ok);
    if (!ok)return nullptr;

    vector<string>properties;
    for (int i = 0; i < nProp; i++) {
        QString pro = QInputDialog::getText(this, "Aggiungi Arma",
            QString::fromStdString("Proprietà " + std::to_string(i + 1) + ":"), QLineEdit::Normal, QString(), &ok);
        if (!ok)return nullptr;
        properties.push_back(pro.toStdString());
    }

    int bonus = QInputDialog::getInt(this, "Aggiungi Arma", "Bonus:", 0, -2147483647, 2147483647, 1, &ok);
    if (!ok)return nullptr;

    return new Weapon(name, weight, v, dmgtype, bonus, properties);
}

Ranged *MainWindow::ShowAddRangedDialog() {
    Weapon* w = ShowAddWeaponDialog();
    if (w == nullptr) return nullptr;

    bool ok = true;

    unsigned range = QInputDialog::getInt(this, "Aggiungi Arma", "Range:", 0, 0, 2147483647, 1, &ok);
    if (!ok) {
        delete w;
        return nullptr;
    }

    return new Ranged(*w, range);
}

AmmoWeapon *MainWindow::ShowAddAmmoWeaponDialog() {
    Ranged* r = ShowAddRangedDialog();
    if (r == nullptr)return nullptr;

    bool ok = true;

    string ammo = QInputDialog::getText(
        this, "Aggiungi Arma", "Munizioni Utilizzate:", QLineEdit::Normal, QString(), &ok).toStdString();
    if (!ok) {
        delete r;
        return nullptr;
    }

    return new AmmoWeapon(*r, ammo);
}

Object *MainWindow::ShowAddObjectDialog() {
    bool ok = true;

    string name = QInputDialog::getText(
        this, "Aggiungi Consumabile", "Nome:",
        QLineEdit::Normal, QString(), &ok
    ).toStdString();
    if (!ok) return nullptr;

    double weight = QInputDialog::getDouble(this, "Aggiungi Consumabile", "Peso:", 0, 0, 2147483647, 1, &ok);//maggiore di 0
    if (!ok) return nullptr;

    string description = QInputDialog::getText(
        this, "Aggiungi Consumabile", "Descrizione:",
        QLineEdit::Normal, QString(), &ok
    ).toStdString();
    if (!ok) return nullptr;

    unsigned amount = QInputDialog::getInt(this, "Aggiungi Consumabile", "Quantità:", 1, 1, 2147483647, 1, &ok);
    if (!ok) return nullptr;

    return new Object(name, weight, amount, description);
}

Potion *MainWindow::ShowAddPotionDialog() {
    Object* o = ShowAddObjectDialog();
    if (o == nullptr) return nullptr;

    bool ok = true;

    int nDice = QInputDialog::getInt(this, "Aggiungi Consumabile", "Numero di Dadi:", 0, 0, 2147483647, 1, &ok);
    if (!ok) {
        delete o;
        return nullptr;
    }

    vector<Die>v;
    for (int i = 0; i < nDice; i++) {
        int die = QInputDialog::getInt(this, "Aggiungi Consumabile",
            QString::fromStdString("Numero di facce Dado " + std::to_string(i + 1) + ":"), 1, 1, 2147483647, 1, &ok);
        if (!ok) {
            delete o;
            return nullptr;
        }

        v.push_back(Die(die));
    }
    return new Potion(*o, v);
}

Ammo *MainWindow::ShowAddAmmoDialog() {
    Object* o = ShowAddObjectDialog();
    if (o == nullptr) return nullptr;

    if (showMessageBox("Aggiungi Consumabile", "La munizione infligge danni bonus?")) {
        bool ok = true;

        string dmgtype = QInputDialog::getText(
            this, "Aggiungi Consumabile", "Tipo di Danno:",
            QLineEdit::Normal, QString(), &ok
        ).toStdString();
        if (!ok) {
            delete o;
            return nullptr;
        }

        int die = QInputDialog::getInt(this, "Aggiungi Consumabile", "Facce del Dado:", 1, 1, 2147483647, 1, &ok);
        if (!ok) {
            delete o;
            return nullptr;
        }

        return new Ammo(*o, true, dmgtype, Die(die));
    }
    return new Ammo(*o);
}

Character::Class MainWindow::ShowAddClassDialog(bool* ok) {
    if (*ok) {
        QString name = ShowAddStringDialog("Nome della Classe", ok);
        if (*ok) {
            unsigned lvl = ShowAddIntDialog("Livello di partenza", 1, ok);
            if (*ok) {
                unsigned dieFaces = ShowAddIntDialog("Facce dei Dadi Vita", 4, ok);
                if (*ok) return Character::Class(name.toStdString(), Die(dieFaces), lvl);
            }
        }
    }

    return Character::Class();
}

QString MainWindow::showFileSelectDialog(const QString &title, bool* ok) {
    QString path = QFileDialog::getOpenFileName(this, title, "../Saved Characters", "*.character");
    if (path == "" && ok != nullptr) *ok = false;
    return path;
}
QString MainWindow::ShowAddStringDialog(const QString & title, bool *ok) {
    return QInputDialog::getText(this, "Inserisci", title, QLineEdit::Normal, QString(), ok);
}
bool MainWindow::showMessageBox(const QString& title, const QString &text) {
    QMessageBox* messageBox = new QMessageBox(this);
    messageBox->setWindowTitle(title);
    messageBox->setText(text);
    QAbstractButton* yes = messageBox->addButton("Si", QMessageBox::YesRole);
    messageBox->addButton("No", QMessageBox::NoRole);
    messageBox->exec();

    return messageBox->clickedButton() == yes;
}
unsigned MainWindow::ShowAddIntDialog(const QString & title, unsigned min, bool *ok) {
    return QInputDialog::getInt(this, "Inserisci", title, min, min, 2147483647, 1, ok);
}

double MainWindow::ShowAddDoubleDialog(const QString & title) {
    return QInputDialog::getDouble(this, "Inserisci", title);
}

void MainWindow::setName(const QString & name) const { nameLabel->setText(name); }
void MainWindow::setRace(const QString & race) const { raceLabel->setText(race); }
void MainWindow::setLevel(unsigned lvl) const {
    levelLabel->setText(QString::fromStdString(std::to_string(lvl)));

}
void MainWindow::setAlignment(const QString & a) const { alignmentLabel->setText(a); }

void MainWindow::setAbilityScore(ability a, unsigned score) const { stats->setAbilityScore(a, score); }
void MainWindow::setAbilityModifier(ability a, int modifier) const { stats->setAbilityModifier(a, modifier); }

void MainWindow::setProficiencyBonus(unsigned n) const { stats->setProficiencyBonus(n); }
void MainWindow::setArmorClass(unsigned n) const { stats->setArmorClass(n); }

void MainWindow::setMaxHp(unsigned n) const { stats->setMaxHp(n); }
void MainWindow::setCurrentHp(unsigned n) const { stats->setCurrentHp(n); }
void MainWindow::setBonusHp(unsigned n) const { stats->setBonusHp(n); }

unsigned MainWindow::ShowRangeDialog() {
    unsigned i = QInputDialog::getInt(this, "Attacco", "Inserire la distanza dal nemico", 0, 0);

    return i;
}

void MainWindow::showWarning(const QString & message) {
    QDialog* dialog = new QDialog(this);
    QLabel* dialogLabel = new QLabel(message, dialog);
    dialog->setLayout(new QHBoxLayout);
    dialog->layout()->addWidget(dialogLabel);
    dialog->layout()->setAlignment(Qt::AlignCenter);
    dialog->layout()->setContentsMargins(30, 30, 30, 30);
    dialogLabel->setFont(QFont("Helvetica", 9, QFont::Bold));

    dialog->layout()->setSizeConstraint(QLayout::SetFixedSize);
    dialog->setWindowTitle("Errore");
    dialog->show();
}

void MainWindow::showHealDialog(int diceSum, int modifier) {
    QDialog* dialog = new QDialog(this);
    QVBoxLayout* layout = new QVBoxLayout;
    dialog->setLayout(layout);

    QLabel* results = new QLabel(
        QString::fromStdString(
            std::to_string(diceSum) + "(Somma dei dadi)" +
            (
                modifier < 0 ?
                " - " + std::to_string(modifier * -1) :
                " + " + std::to_string(modifier)
                ) + "(Modificatore di Costituzione)"
        ),
        this
    );
    layout->addWidget(results);

    QLabel* total = new QLabel("--> Totale Cura: " + QString::fromStdString(std::to_string(diceSum + modifier)), this);
    total->setFont(QFont("Helvetica", 10, QFont::Bold));
    layout->addWidget(total);

    layout->setAlignment(Qt::AlignCenter);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    dialog->show();
}

void MainWindow::showDieThrowDialog(int result) {
    QDialog* dialog = new QDialog(this);
    dialog->setLayout(new QVBoxLayout);

    QLabel* out = new QLabel(QString::fromStdString(std::to_string(result)), this);
    dialog->layout()->addWidget(out);

    out->setFont(QFont("Helvetica", 50, QFont::Bold));

    dialog->layout()->setAlignment(Qt::AlignCenter);
    dialog->layout()->setSizeConstraint(QLayout::SetFixedSize);
    dialog->layout()->setContentsMargins(100, 60, 100, 60);

    dialog->show();
}

void MainWindow::showDieThrowDialog(const NormalThrow& result) {
    QDialog* dialog = new QDialog(this);
    QVBoxLayout* layout = new QVBoxLayout;
    dialog->setLayout(layout);

    if (dynamic_cast<const AttackThrow*>(&result) != nullptr) {
        const AttackThrow& attack = static_cast<const AttackThrow&>(result);

        QString hit, damage;
        int temp = attack.getAbilityModifier();

        hit += "TOT tiro per colpire: ";
        hit += QString::fromStdString(std::to_string(attack.getThrow()));
        QLabel* hitTitle = new QLabel(hit, this);
        hitTitle->setFont(QFont("Helvetica", 10, QFont::Bold));
        layout->addWidget(hitTitle);

        hit.clear();
        hit += QString::fromStdString(std::to_string(attack.getDieScore()));
        hit += "(d20) ";
        if (temp < 0) hit += "- ";
        else hit += "+ ";
        hit += QString::fromStdString(std::to_string(temp > 0 ? temp : -temp));
        hit += "(Modificatore Abilità)";
        if (attack.getWeaponBonus() != 0) {
            hit += " + ";
            hit += QString::fromStdString(std::to_string(attack.getWeaponBonus()));
            hit += "(Bonus Arma)";
        }
        layout->addWidget(new QLabel(hit, this));

        damage += "TOT Danni: ";
        damage += QString::fromStdString(std::to_string(attack.getTotalDamage()));
        QLabel* damageTitle = new QLabel(damage, this);
        damageTitle->setFont(QFont("Helvetica", 10, QFont::Bold));
        layout->addWidget(damageTitle);

        damage.clear();
        damage += QString::fromStdString(std::to_string(attack.getDamage()));
        damage += "(";
        damage += QString::fromStdString(attack.getDamageType());
        damage += ") ";
        if (temp < 0) damage += "- ";
        else damage += "+ ";
        damage += QString::fromStdString(std::to_string(temp > 0 ? temp : -temp));
        damage += "(Modificatore Abilità)";
        if (attack.getWeaponBonus() != 0) {
            damage += " + ";
            damage += QString::fromStdString(std::to_string(attack.getWeaponBonus()));
            damage += "(Bonus Arma)";
        }
        if (attack.getBonusDamage() != 0) {
            damage += " + ";
            damage += QString::fromStdString(std::to_string(attack.getBonusDamage()));
            damage += "(";
            damage += QString::fromStdString(attack.getBonusDamageType());
            damage += ")";
        }
        layout->addWidget(new QLabel(damage, this));

        layout->setAlignment(Qt::AlignCenter);

        layout->setSizeConstraint(QLayout::SetFixedSize);
    }
    else {
        QLabel* results = new QLabel(
            QString::fromStdString(
                std::to_string(result.getDieScore()) +
                "(" + "d" + std::to_string(result.getDieFaces()) + ") " +
                (
                    result.getAbilityModifier() < 0 ?
                    " - " + std::to_string(result.getAbilityModifier() * -1) :
                    " + " + std::to_string(result.getAbilityModifier())
                    ) + "(Modificatore di Caratteristica)" +
                (
                    result.isProficiencyApplied() ?
                    " + " + std::to_string(result.getProficiencyBonus()) + "(Bonus di Competenza)" :
                    ""
                    )
            ),
            this
        );
        layout->addWidget(results);

        QLabel* total = new QLabel("--> Totale: " + QString::fromStdString(std::to_string(result.getThrow())), this);
        total->setFont(QFont("Helvetica", 10, QFont::Bold));
        layout->addWidget(total);
    }

    dialog->show();
}

CharacterInfo* MainWindow::getStats() const { return stats; }
MiddleWidget *MainWindow::getMiddleWidget() const { return middleWidget; }
InventoryViewer* MainWindow::getBag() const { return bag; }
