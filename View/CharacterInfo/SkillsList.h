#ifndef SKILLSLIST_H
#define SKILLSLIST_H

#include <QWidget>
#include <QVBoxLayout>

#include "Skills.h"
#include "Model/vector.h"

class SkillsList : public QWidget {
    Q_OBJECT
private:
    vector<Skills*>v;

public:
    explicit SkillsList(QWidget *parent = nullptr);

    Skills* getSkill(skill) const;
    // getSkills ritorna tutte le skills relative all'abilità passata per parametro
    vector<Skills*> getSkills(ability) const;
};

#endif // SKILLSLIST_H
