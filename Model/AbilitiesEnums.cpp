#include "AbilitiesEnums.h"

string enums::fromAbilityToString(ability a) {
    switch (a) {
        case 0: return "Forza";
        case 1: return "Destrezza";
        case 2: return "Costituzione";
        case 3: return "Intelligenza";
        case 4: return "Saggezza";
        case 5: return "Carisma";
    }
    return "";
}

string enums::fromSkillToString(skill s) {
    switch (s) {
    case 0: return "Acrobazia";
    case 1: return "Addestrare Animali";
    case 2: return "Arcano";
    case 3: return "Atletica";
    case 4: return "Inganno";
    case 5: return "Storia";
    case 6: return "Intuizione";
    case 7: return "Intimidire";
    case 8: return "Indagare";
    case 9: return "Medicina";
    case 10: return "Natura";
    case 11: return "Percezione";
    case 12: return "Intrattenere";
    case 13: return "Persuasione";
    case 14: return "Religione";
    case 15: return "Rapidità di mano";
    case 16: return "Furtività";
    case 17: return "Sopravvivenza";
    }
    return "";
}
