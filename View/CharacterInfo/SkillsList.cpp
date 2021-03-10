#include "SkillsList.h"

SkillsList::SkillsList(QWidget *parent) :QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout;
    setLayout(layout);

    QLabel* title = new QLabel("Abilità", this);
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    v.push_back(new Skills(enums::dexterity, enums::acrobatics, this));
    v.push_back(new Skills(enums::wisdom, enums::animal_handling, this));
    v.push_back(new Skills(enums::intelligence, enums::arcana, this));
    v.push_back(new Skills(enums::strenght, enums::athletics, this));
    v.push_back(new Skills(enums::charisma, enums::deception, this));
    v.push_back(new Skills(enums::intelligence, enums::history, this));
    v.push_back(new Skills(enums::wisdom, enums::insight, this));
    v.push_back(new Skills(enums::charisma, enums::intimidation, this));
    v.push_back(new Skills(enums::intelligence, enums::investigation, this));
    v.push_back(new Skills(enums::wisdom, enums::medicine, this));
    v.push_back(new Skills(enums::intelligence, enums::nature, this));
    v.push_back(new Skills(enums::wisdom, enums::perception, this));
    v.push_back(new Skills(enums::charisma, enums::performance, this));
    v.push_back(new Skills(enums::charisma, enums::persuasion, this));
    v.push_back(new Skills(enums::intelligence, enums::religion, this));
    v.push_back(new Skills(enums::dexterity, enums::sleight_of_hand, this));
    v.push_back(new Skills(enums::dexterity, enums::stealth, this));
    v.push_back(new Skills(enums::wisdom, enums::survival, this));

    for (auto x : v)
        layout->addWidget(x);
}

Skills *SkillsList::getSkill(skill s) const { return v[s]; }

vector<Skills*> SkillsList::getSkills(ability a) const {
    vector<Skills*> ret;
    for (Skills* s : v) {
        if (s->getAssociatedAbility() == a)
            ret.push_back(s);
    }
    return ret;
}
