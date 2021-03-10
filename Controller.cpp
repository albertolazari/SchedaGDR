#include "Controller.h"

#include <string>

Controller::Controller(QObject *parent) : QObject(parent), CurrentFile("") {
    connect(this, &Controller::levelChanged, &Controller::updateProficiencyBonus);
    connect(this, &Controller::abilityScoreChanged, &Controller::updateArmorClass);
    connect(this, &Controller::hpChanged, &Controller::updateHp);
    connect(this, &Controller::abilityScoreChanged, &Controller::updateAblityScore);

    // SavingThrows
    connect(this, &Controller::abilityScoreChanged, &Controller::updateSavingThrowBonus);
    connect(this, &Controller::savingThrowProficiencyChanged, &Controller::updateSavingThrowBonus);
    connect(this, &Controller::savingThrowProficiencyChanged, &Controller::updateSavingThrows);
    for (unsigned i = 0; i < enums::abilitiesNumber; ++i) {
        connect(
            this, &Controller::levelChanged,
            [=]() { updateSavingThrowBonus(static_cast<ability>(i)); }
        );
    }

    // Skills
    connect(this, &Controller::skillProficiencyChanged, &Controller::updateSkills);
    connect(
        this, &Controller::abilityScoreChanged,
        static_cast<void (Controller::*)(ability) const>(&Controller::updateSkillBonus)
    );
    connect(
        this, &Controller::skillProficiencyChanged,
        static_cast<void (Controller::*)(skill) const>(&Controller::updateSkillBonus)
    );
    for (unsigned i = 0; i < enums::abilitiesNumber; ++i) {
        connect(
            this, &Controller::levelChanged,
            [=]() { updateSkillBonus(static_cast<ability>(i)); }
        );
    }

    // Level
    connect(this, &Controller::levelChanged, &Controller::updateLevel);
}

void Controller::printItemDetails(std::ofstream &os, const Item *item) {
    if (item == nullptr) {
        os << "Empty" << std::endl;
        return;
    }
    if (typeid (*item) == typeid (Weapon)) os << "Weapon" << std::endl;
    if (typeid (*item) == typeid (AmmoWeapon)) os << "AmmoWeapon" << std::endl;
    if (typeid (*item) == typeid (Ranged)) os << "Ranged" << std::endl;
    if (typeid (*item) == typeid (Object)) os << "Object" << std::endl;
    if (typeid (*item) == typeid (Potion)) os << "Potion" << std::endl;
    if (typeid (*item) == typeid (Ammo)) os << "Ammo" << std::endl;

    const Weapon* w = dynamic_cast<const Weapon*>(item);

    if (w != nullptr) {
        os << (w->getName() != "" ? w->getName() : "!empty") << std::endl;
        os << w->getWeight() << std::endl;
        os << w->getDice().size() << std::endl;
        for (auto x : w->getDice()) {
            os << x.getFaces() << " ";
        }
        os << std::endl;
        os << (w->getDamageType() != "" ? w->getDamageType() : "!empty") << std::endl;
        os << w->getBonus() << std::endl;
        os << w->getProperties().size() << std::endl;
        for (const string& x : w->getProperties()) {
            os << (x != "" ? x : "!empty") << std::endl;
        }
        const Ranged* r = dynamic_cast<const Ranged*>(w);
        if (r != nullptr) {
            os << r->getRange() << std::endl;
            const AmmoWeapon* aw = dynamic_cast<const AmmoWeapon*>(r);
            if (aw != nullptr) {
                os << (aw->getAmmoUsed() != "" ? aw->getAmmoUsed() : "!empty") << std::endl;
            }
        }
    }
    const Object* o = dynamic_cast<const Object*>(item);
    if (o != nullptr) {
        os << (o->getName() != "" ? o->getName() : "!empty") << std::endl;
        os << o->Item::getWeight() << std::endl;
        os << o->getAmount() << std::endl;
        os << (o->getDescription() != "" ? o->getDescription() : "!empty") << std::endl;
        const Potion* p = dynamic_cast<const Potion*>(o);
        if (p != nullptr) {
            os << p->getDice().size() << std::endl;
            for (auto x : p->getDice()) {
                os << x.getFaces() << " ";
            }
            os << std::endl;
        }
        else {
            const Ammo* a = dynamic_cast<const Ammo*>(o);
            if (a != nullptr) {
                if (a->dealsBonusDamage()) {
                    os << "1" << std::endl;
                    os << (a->getDamageType() != "" ? a->getDamageType() : "!empty") << std::endl;
                    os << a->getBonusDamage().getFaces() << std::endl;
                }
                else os << "0" << std::endl;
            }
        }
    }
}

void Controller::saveAs() {
    QString temp = QFileDialog::getSaveFileName(View, "Salva", "./Saved Characters", "*.character");
    if (temp != "") {
        CurrentFile = temp;
        saveCharacter();
    }
}

void Controller::save() {
    if (CurrentFile != "") {
        saveCharacter();
    }
    else saveAs();
}

void Controller::updateSavingThrows() const {
    for (unsigned i = 0; i < enums::abilitiesNumber; ++i) {
        bool p = Model->getCharacter().hasProficiency(static_cast<ability>(i));
        View->getStats()->getModifierLists()->getSavingThrowsList()->getSavingThrow(static_cast<ability>(i))->setProf(p);
    }
}

std::string Controller::getLine(std::ifstream& input) {
    string s;
    char c = input.get();
    while (c == ' ' || c == '\n')
        c = input.get();

    while (c != '\n') {
        s.push_back(c);
        c = input.get();
    }
    if (s == "!empty") return "";
    return s;
}
Item* Controller::getItem(std::ifstream& input) {
    string itemType = getLine(input);
    if (itemType == "Empty") return nullptr;

    string name = getLine(input);
    double weight;
    input >> weight;

    if (itemType == "Weapon" || itemType == "Ranged" || itemType == "AmmoWeapon") {
        unsigned n;
        input >> n;
        vector<Die> dice;
        for (unsigned i = 0; i < n; ++i) {
            unsigned faces;
            input >> faces;
            dice.push_back(Die(faces));
        }
        string damageType = getLine(input);
        int bonus;
        input >> bonus;

        vector<string> properties;
        input >> n;
        for (unsigned i = 0; i < n; ++i)
            properties.push_back(getLine(input));

        Weapon* weapon = new Weapon(name, weight, dice, damageType, bonus, properties);
        if (itemType == "Weapon") return weapon;

        unsigned range;
        input >> range;
        Ranged* ranged = new Ranged(*weapon, range);
        if (itemType == "Ranged") return ranged;

        string ammo = getLine(input);
        return new AmmoWeapon(*ranged, ammo);
    }
    if (itemType == "Object" || itemType == "Potion" || itemType == "Ammo") {
        unsigned amount;
        input >> amount;
        string description = getLine(input);

        Object* object = new Object(name, weight, amount, description);
        if (itemType == "Object") return object;
        if (itemType == "Potion") {
            unsigned n;
            input >> n;
            vector<Die> dice;
            for (unsigned i = 0; i < n; ++i) {
                unsigned faces;
                input >> faces;
                dice.push_back(Die(faces));
            }

            return new Potion(*object, dice);
        }
        bool hasBonusDmg;
        input >> hasBonusDmg;
        if (hasBonusDmg) {
            string dmgType = getLine(input);
            unsigned die;
            input >> die;

            return new Ammo(*object, hasBonusDmg, dmgType, Die(die));
        }
        return new Ammo(*object);
    }

    input.close();
    throw std::runtime_error("C'è stato un errore nel caricamento del file");
}

CharacterSheet* Controller::loadCharacter(const QString& path) {
    std::ifstream input(path.toStdString(), std::ios::in);

    string s;
    unsigned u;
    double d;

    s = getLine(input);
    if (s != "Character:") {
        input.close();
        throw std::runtime_error("C'è stato un errore nel caricamento del file");
    }
    CharacterSheet* sheet = new CharacterSheet;
    Character& character = sheet->getCharacter();

    character.setName(getLine(input));
    character.setRace(getLine(input));
    character.setAlignment(getLine(input));

    input >> u;
    for (unsigned i = 0; i < u; ++i) {
        string className = getLine(input);
        unsigned level, die, dieUsed;
        input >> level >> die >> dieUsed;
        Character::Class c(className, Die(die), level);
        for (unsigned i = 0; i < dieUsed; ++i)
            c.rollHitDie();
        character.addClass(c);
    }
    input >> u; character.setMaxHp(u);
    input >> u; character.setCurrentHp(u);
    input >> u; character.setBonusHp(u);

    sheet->changeBag(INT32_MAX);

    Item* item = getItem(input);
    if (item != nullptr) {
        sheet->addItem(item);
        sheet->equip(Hand::leftHand, 0);
    }

    item = getItem(input);
    if (item != nullptr) {
        sheet->addItem(item);
        sheet->equip(Hand::rightHand, 0);
    }

    for (unsigned i = 0; i < enums::abilitiesNumber; ++i) {
        unsigned score;
        input >> score;
        character.setAbilityScore(static_cast<ability>(i), score);
    }
    for (unsigned i = 0; i < enums::abilitiesNumber; ++i) {
        bool proficient;
        input >> proficient;
        character.setSavingThrowProficiency(static_cast<ability>(i), proficient);
    }

    for (unsigned i = 0; i < enums::skillsNumber; ++i) {
        bool p, m;
        input >> p >> m;
        character.setSkillProficiency(static_cast<skill>(i), p, m);
    }

    s = getLine(input);
    if (s != "Bag:") {
        input.close();
        throw std::runtime_error("C'è stato un errore nel caricamento del file");
    }

    input >> d; sheet->changeBag(d);
    input >> u;
    for (unsigned i = 0; i < u; ++i)
        sheet->addItem(getItem(input));

    input.close();
    return sheet;
}

void Controller::refreshBag()const {
    InventoryViewer* bag = View->getBag();
    bag->updateCarriedWeight(Model->getCarriedWeight());
    bag->updateMaxWeight(Model->getMaxWeight());
    bag->getBagList()->clear();
    for (auto it = Model->BagBegin(); it != Model->BagEnd(); ++it) {
        bag->getBagList()->addItem(it);
    }
    View->getMiddleWidget()->setLeftHand(Model->getCharacter().getHandItem(Hand::leftHand).get());
    View->getMiddleWidget()->setRightHand(Model->getCharacter().getHandItem(Hand::rightHand).get());
    bag->getItemDetails()->setItem(nullptr);
}

void Controller::setModel(CharacterSheet *m) {
    Model = m;

    const Character& character = m->getCharacter();

    View->setName(QString::fromStdString(character.getName()));
    View->setRace(QString::fromStdString(character.getRace()));
    View->setAlignment(QString::fromStdString(character.getAlignement()));

    emit levelChanged();
    emit hpChanged();

    for (unsigned i = 0; i < enums::abilitiesNumber; ++i) {
        emit abilityScoreChanged(static_cast<ability>(i));
        emit savingThrowProficiencyChanged(static_cast<ability>(i));
    }
    for (unsigned i = 0; i < enums::skillsNumber; ++i)
        emit skillProficiencyChanged(static_cast<skill>(i));

    updateClasses();
    refreshBag();
}
void Controller::setView(MainWindow *v) { View = v; }

void Controller::equipRight() const {
    if (!(View->getBag()->getItemDetails()->isNull())) {
        auto it = View->getBag()->getBagList()->SelectedItem(View->getBag()->getBagList()->getTab()->currentIndex());

        Model->equip(Hand::rightHand, it - Model->BagBegin());
        refreshBag();
    }
}

void Controller::equipLeft() const {
    if (!(View->getBag()->getItemDetails()->isNull())) {
        auto it = View->getBag()->getBagList()->SelectedItem(View->getBag()->getBagList()->getTab()->currentIndex());

        Model->equip(Hand::leftHand, it - Model->BagBegin());
        refreshBag();
    }
}

void Controller::dropRight() const {
    Model->drop(rightHand);
    refreshBag();
}

void Controller::dropLeft() const {
    Model->drop(leftHand);
    refreshBag();
}

void Controller::useRight() const {
    if (dynamic_cast<const Weapon*>(Model->getCharacter().getHandItem(rightHand).get())) {
        try {
            bool ok = true;
            int d = View->ShowAddIntDialog("Inserire la distanza dal nemico: ", 0, &ok);
            if (!ok)return;
            View->showDieThrowDialog(Model->attack(rightHand, d));
        }
        catch (const std::runtime_error& e) { View->showWarning(e.what()); }
    }
    else {
        bool potion = dynamic_cast<const Potion*>(Model->getCharacter().getHandItem(rightHand).get());
        int dice;

        try {
            dice = Model->useItem(rightHand);

            if (potion) {
                View->setCurrentHp(Model->getCharacter().getCurrentHp());
                View->showHealDialog(dice, Model->getCharacter().getAbilityModifier(ability::constitution));
            }

        }
        catch (const std::runtime_error& e) { View->showWarning(e.what()); }

    }
    refreshBag();
}

void Controller::useLeft() const {
    if (dynamic_cast<const Weapon*>(Model->getCharacter().getHandItem(leftHand).get())) {
        try {
            bool ok = true;
            int d = View->ShowAddIntDialog("Inserire la distanza dal nemico: ", 0, &ok);
            if (!ok)return;
            View->showDieThrowDialog(Model->attack(leftHand, d));
        }
        catch (const std::runtime_error& e) { View->showWarning(e.what()); }
    }
    else {
        bool potion = dynamic_cast<const Potion*>(Model->getCharacter().getHandItem(leftHand).get());
        int dice;
        try {
            dice = Model->useItem(leftHand);
            if (potion) {
                View->setCurrentHp(Model->getCharacter().getCurrentHp());
                View->showHealDialog(dice, Model->getCharacter().getAbilityModifier(ability::constitution));
            }
        }
        catch (const std::runtime_error& e) { View->showWarning(e.what()); }
    }
    refreshBag();
}

void Controller::setName() const {
    QString s = View->ShowAddStringDialog("Nome");
    Model->getCharacter().setName(s.toStdString());
    View->setName(s);
}

void Controller::setSavingThrowsProf(ability a) const {
    bool prof = Model->getCharacter().hasProficiency(a);
    Model->getCharacter().setSavingThrowProficiency(a, prof ? false : true);
    View->getStats()->getModifierLists()->getSavingThrowsList()->getSavingThrow(a)->changeProf();

    emit savingThrowProficiencyChanged(a);
}

void Controller::updateSavingThrowBonus(ability a) const {
    Character& character = Model->getCharacter();
    View->getStats()->getModifierLists()->getSavingThrowsList()->getSavingThrow(a)->updateBonus(
        character.getAbilityModifier(a) +
        (character.hasProficiency(a) ? character.getProficiencyBonus() : 0)
    );
}

void Controller::throwSavingThrowOn(ability a) const {
    NormalThrow dieThrow = Model->throwOn(a, true);
    View->showDieThrowDialog(dieThrow);
}

void Controller::updateSkills() const {
    for (unsigned i = 0; i < enums::skillsNumber; ++i) {
        skill s = static_cast<skill>(i);
        bool p = Model->getCharacter().getSkill(s).hasProficiency();
        bool m = Model->getCharacter().getSkill(s).hasMastery();
        View->getStats()->getModifierLists()->getSkillsList()->getSkill(s)->setProf(p, m);
    }
}

void Controller::changeSkillProficiency(skill s) const {
    Character& character = Model->getCharacter();
    if (character.getSkill(s).hasProficiency()) {
        character.setSkillProficiency(
            s,
            (character.getSkill(s).hasMastery() ? false : true),
            (character.getSkill(s).hasMastery() ? false : true)
        );
    }
    else
        character.setSkillProficiency(s, true);

    Character::Skill selectedSkill = character.getSkill(s);

    View->getStats()->getModifierLists()->getSkillsList()->getSkill(s)->changeProf();
    View->getStats()->getModifierLists()->getSkillsList()->getSkill(s)->setBonus(
        character.getAbilityModifier(selectedSkill.getAbility()) +
        (selectedSkill.hasProficiency() ? character.getProficiencyBonus() : 0) +
        (selectedSkill.hasMastery() ? character.getProficiencyBonus() : 0)
    );

    emit skillProficiencyChanged(s);
}

void Controller::updateSkillBonus(ability a) const {
    auto v = View->getStats()->getModifierLists()->getSkillsList()->getSkills(a);
    Character& character = Model->getCharacter();

    unsigned abilityModifier = character.getAbilityModifier(a);
    unsigned proficiencyBonus = character.getProficiencyBonus();

    for (auto s : v) {
        Character::Skill selectedSkill = character.getSkill(s->getSkill());
        s->setBonus(
            abilityModifier +
            (selectedSkill.hasProficiency() ? proficiencyBonus : 0) +
            (selectedSkill.hasMastery() ? proficiencyBonus : 0)
        );
    }
}

void Controller::updateSkillBonus(skill s) const {
    Character& character = Model->getCharacter();
    Character::Skill selectedSkill = character.getSkill(s);

    View->getStats()->getModifierLists()->getSkillsList()->getSkill(s)->setBonus(
        character.getAbilityModifier(selectedSkill.getAbility()) +
        (selectedSkill.hasProficiency() ? character.getProficiencyBonus() : 0) +
        (selectedSkill.hasMastery() ? character.getProficiencyBonus() : 0)
    );
}

void Controller::throwOn(skill s) const {
    NormalThrow dieThrow = Model->throwOn(s);
    View->showDieThrowDialog(dieThrow);
}

void Controller::addWeapon()const {
    try {
        Model->addItem(View->ShowAddWeaponDialog());
        refreshBag();
    }
    catch (const std::runtime_error& e) { View->showWarning(e.what()); }
}

void Controller::addRanged() const {
    try {
        Model->addItem(View->ShowAddRangedDialog());
        refreshBag();
    }
    catch (const std::runtime_error& e) { View->showWarning(e.what()); }
}

void Controller::addAmmoWeapon() const {
    try {
        Model->addItem(View->ShowAddAmmoWeaponDialog());
        refreshBag();
    }
    catch (const std::runtime_error& e) { View->showWarning(e.what()); }
}

void Controller::addObject() const {
    try {
        Model->addItem(View->ShowAddObjectDialog());
        refreshBag();
    }
    catch (const std::runtime_error& e) { View->showWarning(e.what()); }
}

void Controller::addPotion() const {
    try {
        Model->addItem(View->ShowAddPotionDialog());
        refreshBag();
    }
    catch (const std::runtime_error& e) { View->showWarning(e.what()); }
}

void Controller::addAmmo()const {
    try {
        Model->addItem(View->ShowAddAmmoDialog());
        refreshBag();
    }
    catch (const std::runtime_error& e) { View->showWarning(e.what()); }
}

void Controller::deleteItem() const {
    if (!(View->getBag()->getItemDetails()->isNull())) {
        auto it = View->getBag()->getBagList()->SelectedItem(View->getBag()->getBagList()->getTab()->currentIndex());
        if (dynamic_cast<Object*>(it->get())) {
            bool ok = true;
            int amount = View->ShowAddIntDialog("Quantità da rimuovere", 1, &ok);
            if (!ok)return;
            Model->removeItem(it - Model->BagBegin(), amount);
        }
        else Model->removeItem(it - Model->BagBegin());
        refreshBag();
    }
}

void Controller::setMaxWeight() const {
    try {
        double d = View->ShowAddDoubleDialog("Peso: ");
        Model->changeBag(d);

        refreshBag();
    }
    catch (const std::runtime_error& e) { View->showWarning(e.what()); }
}

void Controller::setRace() const {
    QString s = View->ShowAddStringDialog("Razza");
    Model->getCharacter().setRace(s.toStdString());
    View->setRace(s);
}
void Controller::updateLevel() const {
    View->setLevel(Model->getCharacter().getLevel());
}

void Controller::setAlignment() const {
    QString s = View->ShowAddStringDialog("Allineamento");
    Model->getCharacter().setAlignment(s.toStdString());
    View->setAlignment(s);
}

void Controller::updateAblityScore(ability a) const {
    View->setAbilityScore(a, Model->getCharacter().getAbilityScore(a));
    View->setAbilityModifier(a, Model->getCharacter().getAbilityModifier(a));
}
void Controller::setAbilityScore(ability a) const {
    unsigned score = View->ShowAddIntDialog("Punteggio di Caratteristica");
    Model->getCharacter().setAbilityScore(a, score);

    emit abilityScoreChanged(a);
}

void Controller::throwOn(ability a) const {
    NormalThrow dieThrow = Model->throwOn(a, false);
    View->showDieThrowDialog(dieThrow);
}

void Controller::updateProficiencyBonus() const {
    View->setProficiencyBonus(Model->getCharacter().getProficiencyBonus());
}
void Controller::updateArmorClass(ability a) const {
    if (a == enums::dexterity)
        View->setArmorClass(Model->getCharacter().getArmorClass());
}

void Controller::setMaxHp() const {
    unsigned n = View->ShowAddIntDialog("Punti Ferita Massimi");
    Model->getCharacter().setMaxHp(n);

    emit hpChanged();
}
void Controller::setCurrentHp() const {
    try {
        unsigned n = View->ShowAddIntDialog("Punti Ferita Attuali");
        Model->getCharacter().setCurrentHp(n);

        emit hpChanged();
    }
    catch (const std::runtime_error& e) { View->showWarning(e.what()); }
}
void Controller::setBonusHp() const {
    unsigned n = View->ShowAddIntDialog("Punti Ferita Temporanei");
    Model->getCharacter().setBonusHp(n);

    emit hpChanged();
}

void Controller::updateHp() const {
    const Character& character = Model->getCharacter();

    View->setMaxHp(character.getMaxHp());
    View->setCurrentHp(character.getCurrentHp());
    View->setBonusHp(character.getBonusHp());
}

void Controller::heal() const {
    Model->getCharacter().heal(View->getMiddleWidget()->getHpManager()->getValue());

    emit hpChanged();
}
void Controller::takeDamage() const {
    Model->getCharacter().takeDamage(View->getMiddleWidget()->getHpManager()->getValue());

    emit hpChanged();
}

void Controller::rest() const {
    Model->getCharacter().rest();

    emit hpChanged();

    auto classes = Model->getCharacter().getClasses();
    for (const Character::Class& c : classes) {
        unsigned hitDiceUsed = Model->getCharacter().getClass(c.getName()).getHitDiceUsed();
        View->getMiddleWidget()->getClasses()->setHitDiceUsed(QString::fromStdString(c.getName()), hitDiceUsed);
    }
}

void Controller::updateClasses() const {
    View->getMiddleWidget()->getClasses()->removeClasses();

    vector<Character::Class> classes = Model->getCharacter().getClasses();
    for (const Character::Class& c : classes) {
        View->getMiddleWidget()->getClasses()->addClass(c);

        connect(
            View->getMiddleWidget()->getClasses()->getThrowButton(QString::fromStdString(c.getName())),
            &QPushButton::clicked,
            this,
            [=]() { throwHitDieOnClass(QString::fromStdString(c.getName())); }
        );
    }
}
void Controller::addClass() const {
    try {
        bool ok = true;
        Character::Class c = View->ShowAddClassDialog(&ok);
        if (ok) {
            Model->getCharacter().addClass(c);
            View->getMiddleWidget()->getClasses()->addClass(c);

            connect(
                View->getMiddleWidget()->getClasses()->getThrowButton(QString::fromStdString(c.getName())),
                &QPushButton::clicked,
                this,
                [=]() { throwHitDieOnClass(QString::fromStdString(c.getName())); }
            );

            emit levelChanged();
        }
    }
    catch (const std::runtime_error& e) {
        View->showWarning(e.what());
    }
}

void Controller::removeCurrentClass() const {
    try {
        vector<Character::Class> classes = Model->getCharacter().getClasses();
        if (!classes.empty()) {
            Model->getCharacter().removeClass(View->getMiddleWidget()->getClasses()->getCurrentClassName().toStdString());
            updateClasses();

            emit levelChanged();
        }
    }
    catch (const std::runtime_error& e) {
        View->showWarning(e.what());
    }
}

void Controller::levelUpCurrentClass() const {
    try {
        if (!Model->getCharacter().getClasses().empty()) {
            QString currentClassName = View->getMiddleWidget()->getClasses()->getCurrentClassName();
            Model->getCharacter().levelUp(currentClassName.toStdString());

            View->getMiddleWidget()->getClasses()->levelUpSelectedClass();
            View->getMiddleWidget()->getClasses()->setHitDiceUsed(
                currentClassName,
                Model->getCharacter().getClass(currentClassName.toStdString()).getHitDiceUsed()
            );

            emit levelChanged();
        }
    }
    catch (const std::runtime_error& e) {
        View->showWarning(e.what());
    }
}

void Controller::throwHitDieOnClass(const QString& className) const {
    try {
        if (Model->getCharacter().getClass(className.toStdString()).getHitDiceLeft() != 0) {
            NormalThrow dieThorw = Model->throwHitDie(className.toStdString());
            View->showDieThrowDialog(dieThorw);

            unsigned hitDiceUsed = Model->getCharacter().getClass(className.toStdString()).getHitDiceUsed();
            View->getMiddleWidget()->getClasses()->setHitDiceUsed(className, hitDiceUsed);

            emit hpChanged();
        }
    }
    catch (const std::runtime_error& e) {
        View->showWarning(e.what());
    }
}

void Controller::dieThrow() const {
    Die d = View->getBag()->getDieThrower()->getSelectedDie();
    View->showDieThrowDialog(d.roll());
}

void Controller::newCharacter() {
    if (View->showMessageBox(
        "Conferma",
        QString("Tutte le informazioni del personaggio corrente non salvate andranno perse. ") +
        QString("Sei sicuro di voler continuare?")
    )) {
        setModel(new CharacterSheet);
        CurrentFile = "";
    }
}

void Controller::loadCharacterFile() {
    try {
        bool ok = true;
        QString path = View->showFileSelectDialog("Apri", &ok);
        if (ok) {
            setModel(loadCharacter(path));
            CurrentFile = path;
        }
    }
    catch (const std::runtime_error& e) {
        View->showWarning(e.what());
    }
}

void Controller::saveCharacter() {

    std::ofstream out(CurrentFile.toStdString());
    out << "Character:" << std::endl;
    out << (Model->getCharacter().getName() != "" ? Model->getCharacter().getName() : "!empty") << std::endl;
    out << (Model->getCharacter().getRace() != "" ? Model->getCharacter().getRace() : "!empty") << std::endl;
    out << (Model->getCharacter().getAlignement() != "" ? Model->getCharacter().getAlignement() : "!empty") << std::endl;
    out << Model->getCharacter().getClasses().size() << std::endl;
    for (const Character::Class& x : Model->getCharacter().getClasses()) {
        out << (x.getName() != "" ? x.getName() : "!empty") << std::endl;
        out << x.getLevel() << std::endl;
        out << x.getHitDieFaces() << std::endl;
        out << x.getHitDiceUsed() << std::endl;
    }
    out << Model->getCharacter().getMaxHp() << std::endl;
    out << Model->getCharacter().getCurrentHp() << std::endl;
    out << Model->getCharacter().getBonusHp() << std::endl;

    const Item* sx = Model->getCharacter().getHandItem(leftHand).release();
    printItemDetails(out, sx);
    delete sx;

    const Item* dx = Model->getCharacter().getHandItem(rightHand).release();
    printItemDetails(out, dx);
    delete dx;

    for (unsigned i = 0; i < enums::abilitiesNumber; ++i) {
        out << Model->getCharacter().getAbilityScore(static_cast<ability>(i)) << " ";
    }
    out << std::endl;

    for (unsigned i = 0; i < enums::abilitiesNumber; ++i) {
        if (Model->getCharacter().hasProficiency(static_cast<ability>(i)))
            out << "1 ";
        else out << "0 ";
    }
    out << std::endl;

    for (unsigned i = 0; i < enums::skillsNumber; ++i) {
        Character::Skill temp = Model->getCharacter().getSkill(static_cast<skill>(i));
        if (temp.hasProficiency()) out << "1 ";
        else out << "0 ";
        if (temp.hasMastery()) out << "1" << std::endl;
        else out << "0" << std::endl;
    }

    out << "Bag:" << std::endl;
    out << Model->getMaxWeight() << std::endl;
    out << Model->BagEnd() - Model->BagBegin() << std::endl;
    for (auto it = Model->BagBegin(); it != Model->BagEnd(); ++it) {
        printItemDetails(out, it->get());
    }

    out.close();
}
