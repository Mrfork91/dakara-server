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
    bool IsPaladin;

    setPotions();
    setWeapon();

    /* ' Ropa (Newbie) */
    Slot = getFirstFreeSlotNumber();
    switch (UserRaza) {
        case eRaza_Humano:
            UserList[UserIndex].Invent.Object[Slot].ObjIndex = 463;
            break;

        case eRaza_Elfo:
            UserList[UserIndex].Invent.Object[Slot].ObjIndex = 464;
            break;

        case eRaza_Drow:
            UserList[UserIndex].Invent.Object[Slot].ObjIndex = 465;
            break;

        case eRaza_Enano:
            UserList[UserIndex].Invent.Object[Slot].ObjIndex = 466;
            break;

        case eRaza_Gnomo:
            UserList[UserIndex].Invent.Object[Slot].ObjIndex = 466;
            break;

        default:
            break;
    }

    /* ' Equipo ropa */
    UserList[UserIndex].Invent.Object[Slot].Amount = 1;
    UserList[UserIndex].Invent.Object[Slot].Equipped = 1;

    UserList[UserIndex].Invent.ArmourEqpSlot = Slot;






    /* ' Manzanas (Newbie) */
    Slot = Slot + 1;
    UserList[UserIndex].Invent.Object[Slot].ObjIndex = 467;
    UserList[UserIndex].Invent.Object[Slot].Amount = 100;

    /* ' Jugos (Nwbie) */
    Slot = Slot + 1;
    UserList[UserIndex].Invent.Object[Slot].ObjIndex = 468;
    UserList[UserIndex].Invent.Object[Slot].Amount = 100;

    /* ' Sin casco y escudo */
    UserList[UserIndex].Char.ShieldAnim = NingunEscudo;
    UserList[UserIndex].Char.CascoAnim = NingunCasco;

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
        case eClass_Bandit: //hacha de barbaro
            weapon = 159;
            break;
        case eClass_Hunter:
            weapon = 665;
            break;
        case eClass_Pirat://Traje de Capitán Pirata // Alifafe de Pirata (E/G) // Sombrero Pirata
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
}

void DotIOInventory::setHelmet() {
    int Slot = getFirstFreeSlotNumber();

}

void DotIOInventory::setArmor() {
    int Slot = getFirstFreeSlotNumber();

//    switch (UserRaza) {
//        case eRaza_Humano:
//            UserList[UserIndex].Invent.Object[Slot].ObjIndex = 463;
//            break;
//
//        case eRaza_Elfo:
//            UserList[UserIndex].Invent.Object[Slot].ObjIndex = 464;
//            break;
//
//        case eRaza_Drow:
//            UserList[UserIndex].Invent.Object[Slot].ObjIndex = 465;
//            break;
//
//        case eRaza_Enano:
//            UserList[UserIndex].Invent.Object[Slot].ObjIndex = 466;
//            break;
//
//        case eRaza_Gnomo:
//            UserList[UserIndex].Invent.Object[Slot].ObjIndex = 466;
//            break;
//
//        default:
//            break;
//    }
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