#ifndef ABILITIESENUMS_H
#define ABILITIESENUMS_H

#include <string>
using std::string;

namespace enums {
    enum ability {
        strenght,
        dexterity,
        constitution,
        intelligence,
        wisdom,
        charisma
    };
    const unsigned abilitiesNumber = 6;
    string fromAbilityToString(ability);

    enum skill {
        acrobatics,
        animal_handling,
        arcana,
        athletics,
        deception,
        history,
        insight,
        intimidation,
        investigation,
        medicine,
        nature,
        perception,
        performance,
        persuasion,
        religion,
        sleight_of_hand,
        stealth,
        survival
    };
    const unsigned skillsNumber = 18;
    string fromSkillToString(skill);
};

#endif // ABILITIESENUMS_H
