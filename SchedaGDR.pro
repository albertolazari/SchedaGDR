QT       += core gui
RC_ICONS += iconaProgetto.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    Controller.h \
    Model/AbilitiesEnums.h \
    Model/AttackThrow.h \
    Model/Bag.h \
    Model/Character.h \
    Model/CharacterSheet.h \
    Model/Item/Ammo.h \
    Model/Item/AmmoWeapon.h \
    Model/Item/Object.h \
    Model/Item/Potion.h \
    Model/Item/Item.h \
    Model/Item/Ranged.h \
    Model/Item/Weapon.h \
    Model/Die.h \
    Model/NormalThrow.h \
    Model/vector.h \
    Model/vector.tcc \
    Model/DeepPtr.h \
    Model/DeepPtr.tcc \
    View/BagInfo/BagList.h \
    View/BagInfo/BagItem.h \
    View/MiddleWidget/HandFrame.h \
    View/CharacterInfo/AbilitiesList.h \
    View/CharacterInfo/Ability.h \
    View/CharacterInfo/CharacterInfo.h \
    View/CharacterInfo/HpIndicator.h \
    View/CharacterInfo/ModifierLists.h \
    View/CharacterInfo/SavingThrows.h \
    View/CharacterInfo/SavingThrowsList.h \
    View/CharacterInfo/Skills.h \
    View/CharacterInfo/SkillsList.h \
    View/CharacterInfo/Stat.h \
    View/MiddleWidget/ClassDetails.h \
    View/MiddleWidget/ClassInfo.h \
    View/MiddleWidget/ClassesList.h \
    View/BagInfo/DieThrower.h \
    View/MiddleWidget/HitDiceManager.h \
    View/DieThrowButton.h \
    View/BagInfo/ItemDetails.h \
    View/BagInfo/InventoryViewer.h \
    View/MiddleWidget/HpManager.h \
    View/Label.h \
    View/MainWindow.h \
    View/MiddleWidget/MiddleWidget.h

SOURCES += \
    Controller.cpp \
    Model/AbilitiesEnums.cpp \
    Model/AttackThrow.cpp \
    Model/Bag.cpp \
    Model/Character.cpp \
    Model/CharacterSheet.cpp \
    Model/Item/Ammo.cpp \
    Model/Item/AmmoWeapon.cpp \
    Model/Item/Item.cpp \
    Model/Item/Object.cpp \
    Model/Item/Potion.cpp \
    Model/Item/Ranged.cpp \
    Model/Item/Weapon.cpp \
    Model/Die.cpp \
    Model/NormalThrow.cpp \
    View/BagInfo/BagList.cpp \
    View/MiddleWidget/HandFrame.cpp \
    View/BagInfo/InventoryViewer.cpp \
    View/BagInfo/ItemDetails.cpp \
    View/BagInfo/BagItem.cpp \
    View/CharacterInfo/AbilitiesList.cpp \
    View/CharacterInfo/Ability.cpp \
    View/CharacterInfo/CharacterInfo.cpp \
    View/CharacterInfo/HpIndicator.cpp \
    View/CharacterInfo/ModifierLists.cpp \
    View/CharacterInfo/SavingThrows.cpp \
    View/CharacterInfo/SavingThrowsList.cpp \
    View/CharacterInfo/Skills.cpp \
    View/CharacterInfo/SkillsList.cpp \
    View/CharacterInfo/Stat.cpp \
    View/MiddleWidget/ClassDetails.cpp \
    View/MiddleWidget/ClassInfo.cpp \
    View/MiddleWidget/ClassesList.cpp \
    View/BagInfo/DieThrower.cpp \
    View/MiddleWidget/HitDiceManager.cpp \
    View/DieThrowButton.cpp \
    View/MiddleWidget/HpManager.cpp \
    View/Label.cpp \
    View/MainWindow.cpp \
    View/MiddleWidget/MiddleWidget.cpp \
    main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
