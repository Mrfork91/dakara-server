//
// Created by horacio on 3/19/17.
//
#include "stdafx.h"
#include "Crypto.h"
#include "DotIOInventory.h"

DotIOInventory::DotIOInventory(int UserIndex, const std::string &Name, eRaza UserRaza, eGenero UserSexo,
                               eClass UserClase,
                               const std::string &UserEmail,
                               eCiudad Hogar, int Head) {
    this->UserIndex = UserIndex;
    this->Name = Name;
    this->UserRaza = UserRaza;
    this->UserSexo = UserSexo;
    this->UserClase = UserClase;
    this->UserEmail = UserEmail;
    this->Hogar = Hogar;
}

int DotIOInventory::getFirstFreeSlotNumber() {
    int slot = 1;
    while (UserList[UserIndex].Invent.Object[slot].ObjIndex != 0) {
        slot++;
    }
    return slot;
}

int DotIOInventory::addItem(int item) {
    int Slot = getFirstFreeSlotNumber();
    UserList[UserIndex].Invent.Object[Slot].ObjIndex = item;
    UserList[UserIndex].Invent.Object[Slot].Amount = 1;
    return Slot;
}

void DotIOInventory::initializeInventory() {

    int i, Slot, LoopC;

    setPotions();
    setWeapon();
    setArmor();
    setShield();
    setHelmet();
    setFood();

    Slot = getFirstFreeSlotNumber();

    /* ' Total Items */
    UserList[UserIndex].Invent.NroItems = getFirstFreeSlotNumber() - 1;
}

void DotIOInventory::setPotions() {
    /* 'Pocion Rojas */
    addItem(38);

    /* 'Pocion azules */
    if (UserList[UserIndex].Stats.MaxMAN > 0 || UserClase == eClass_Paladin || UserClase == eClass_Bandit) {
        addItem(37);
    }

    /* 'Pocion amarillas*/
    addItem(36);

    /* 'Pocion verde*/
    if (UserClase != eClass_Mage) {
        addItem(39);
    }

}

void DotIOInventory::setWeapon() {
    int weapon = 0;

    switch (UserClase) {
        case eClass_Mage:
            weapon = 660; // engarzado
            break;
        case eClass_Cleric:
        case eClass_Paladin:
            weapon = 129; // 2f
            break;
        case eClass_Warrior:
            weapon = 403; // esp. de plata
            break;
        case eClass_Assasin:
            weapon = 367; // daga +4
            break;
        case eClass_Thief:
            weapon = 159; // hacha de barbaro
            break;
        case eClass_Bard:
            weapon = 399; // cimitarra
            break;
        case eClass_Druid:
            weapon = 366; // daga +3
            break;
        case eClass_Bandit: //espada vikinga
            weapon = 123;
            break;
        case eClass_Hunter:
            weapon = 665;
            break;
        case eClass_Pirat:
            weapon = 125; //sable
            break;
    }
    int Slot = addItem(weapon);
    /* Equipar arma */
    UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
    UserList[UserIndex].Invent.WeaponEqpSlot = Slot;

    if (UserClase == eClass_Hunter) {
        Slot = addItem(553);
        /* ' Equipo flechas */
        UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
        UserList[UserIndex].Invent.MunicionEqpSlot = Slot;

        addItem(126); // hacha larga de guerra
    }
    if (UserClase == eClass_Warrior) {
        addItem(664); // arco compuesto
        Slot = addItem(480); //flecha
        /* ' Equipo flechas */
        UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
        UserList[UserIndex].Invent.MunicionEqpSlot = Slot;
        addItem(365); //daga +3

    }
    if (UserClase == eClass_Bard) {
        addItem(366); // flecha +3
    }

    if ((UserClase == eClass_Bandit) || (UserClase == eClass_Thief)) {
        addItem(1036); // guantes de lucha
        addItem(873); // guantes de hurto
    }
}

void DotIOInventory::setHelmet() {
    int helmet = 0;

    switch (UserClase) {
        case eClass_Mage:
            helmet = 662; // sombrero de mago
            break;
        case eClass_Paladin:
        case eClass_Warrior:
        case eClass_Cleric:
        case eClass_Bandit:
        case eClass_Assasin:
        case eClass_Hunter:
            helmet = 405; // casco de plata
            break;
        case eClass_Thief:
        case eClass_Bard:
            helmet = 132; // casco de hierro
            break;
        case eClass_Druid:
            helmet = 1003; // casco de oso
            break;
        case eClass_Pirat:
            helmet = 1010; // sombrero
            break;
    }

    if (helmet > 0) {
        int Slot = addItem(helmet);
        UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
        UserList[UserIndex].Invent.CascoEqpSlot = Slot;
    }

}

bool DotIOInventory::esAlto() {
    return ((UserRaza != eRaza_Enano) && (UserRaza != eRaza_Gnomo));
}

void DotIOInventory::setArmor() {
    int armor = 0;

    switch (UserClase) {
        case eClass_Mage: {
            int tunica = 519; // tunica legendaria
            int rand = RandomNumber(1, 10);
            if (rand == 1) {
                tunica = 614; // tunica de archimago
            }
            armor = esAlto() ? tunica : 932; // tunica legendaria (o tunica de archimago ) / Sotana de Gran Hechicero
            break;
        }
        case eClass_Cleric:
        case eClass_Paladin:
        case eClass_Warrior:
        case eClass_Bandit:
            armor = esAlto() ? 195 : 243; // placas / placas
            break;
        case eClass_Assasin:
            armor = esAlto() ? 356 : 854; // armadura de las sombras
            break;
        case eClass_Thief:
            armor = esAlto() ? 890 : 913; // armadura de cuero de oso pardo / ropaje de ermitaño
            break;
        case eClass_Bard:
        case eClass_Druid:
            armor = esAlto() ? 519 : 939; // legendaria / Tunica de gala roja
            break;
        case eClass_Hunter:
            armor = esAlto() ? 360 : 648; // armadura de cazador
            break;
        case eClass_Pirat:// Sombrero Pirata
            armor = esAlto() ? 359 : 922; // cota de mallas / traje de Capitán Pirata
            break;
    }

    int Slot = addItem(armor);

    /* ' Equipo ropa */
    UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
    UserList[UserIndex].Invent.ArmourEqpSlot = Slot;
}

void DotIOInventory::setShield() {
    int shield = 0;

    switch (UserClase) {
        case eClass_Paladin:
        case eClass_Warrior:
            shield = 130; // escudo de plata
            break;
        case eClass_Cleric:
        case eClass_Bandit:
            shield = 128; // escudo de hierro
            break;
        case eClass_Assasin:
        case eClass_Hunter:
        case eClass_Bard:
            shield = 404; // escudo de tortuga
            break;
        case eClass_Druid:
        case eClass_Thief:
        case eClass_Pirat:
            break;
    }

    if (shield > 0) {
        int Slot = addItem(shield);
        UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
        UserList[UserIndex].Invent.EscudoEqpSlot = Slot;
    }
}

void DotIOInventory::setFood() {

    /* ' Manzanas*/
    addItem(1);

    /* ' Agua */
    addItem(43);

}


//empty switch
//switch (UserClase) {
//case eClass_Mage:
//case eClass_Cleric:
//case eClass_Warrior:
//case eClass_Assasin:
//case eClass_Thief:
//case eClass_Bard:
//case eClass_Druid:
//case eClass_Bandit:
//case eClass_Paladin:
//case eClass_Hunter:
//case eClass_Pirat:
//}