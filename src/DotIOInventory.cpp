//
// Created by horacio on 3/19/17.
//
#include "stdafx.h"
#include "Crypto.h"
#include "DotIOInventory.h"

DotIOInventory::DotIOInventory(int UserIndex, const std::string &Name, eRaza UserRaza, eGenero UserSexo,
               eClass UserClase,
               const std::string &UserEmail,
               eCiudad Hogar, int Head){
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

void DotIOInventory::initializeInventory() {

    int i, Slot, LoopC;
    bool IsPaladin;

    IsPaladin = UserClase == eClass_Paladin;

    /* 'Pociones Rojas (Newbie) */
    Slot = getFirstFreeSlotNumber();
    UserList[UserIndex].Invent.Object[Slot].ObjIndex = 857;
    UserList[UserIndex].Invent.Object[Slot].Amount = 200;

    /* 'Pociones azules (Newbie) */
    if (UserList[UserIndex].Stats.MaxMAN > 0 || IsPaladin) {
        Slot = Slot + 1;
        UserList[UserIndex].Invent.Object[Slot].ObjIndex = 856;
        UserList[UserIndex].Invent.Object[Slot].Amount = 200;

    } else {
        /* 'Pociones amarillas (Newbie) */
        Slot = Slot + 1;
        UserList[UserIndex].Invent.Object[Slot].ObjIndex = 855;
        UserList[UserIndex].Invent.Object[Slot].Amount = 100;

        /* 'Pociones verdes (Newbie) */
        Slot = Slot + 1;
        UserList[UserIndex].Invent.Object[Slot].ObjIndex = 858;
        UserList[UserIndex].Invent.Object[Slot].Amount = 50;

    }

    /* ' Ropa (Newbie) */
    Slot = Slot + 1;
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

    /* 'Arma (Newbie) */
    Slot = Slot + 1;
    UserList[UserIndex].Invent.Object[Slot].ObjIndex = 12;//setUserWeapon(UserIndex, UserRaza, UserSexo, UserClase);

    /* ' Equipo arma */
    UserList[UserIndex].Invent.Object[Slot].Amount = 1;
    UserList[UserIndex].Invent.Object[Slot].Equipped = 1;

    UserList[UserIndex].Invent.WeaponEqpSlot = Slot;



    /* ' Municiones (Newbie) */
    if (UserClase == eClass_Hunter) {
        Slot = Slot + 1;
        UserList[UserIndex].Invent.Object[Slot].ObjIndex = 860;
        UserList[UserIndex].Invent.Object[Slot].Amount = 150;

        /* ' Equipo flechas */
        UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
        UserList[UserIndex].Invent.MunicionEqpSlot = Slot;
    }

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
    UserList[UserIndex].Invent.NroItems = getFirstFreeSlotNumber();
}

void setPotions() {

}
void DotIOInventory::setUserWeapon() {

//    switch (UserClase) {
//        case eClass_Hunter:
//            /* ' Arco (Newbie) */
//            UserList[UserIndex].Invent.Object[Slot].ObjIndex = 859;
//            break;
//
//        case eClass_Worker:
//            /* ' Herramienta (Newbie) */
//            UserList[UserIndex].Invent.Object[Slot].ObjIndex = RandomNumber(561, 565);
//            break;
//
//        case eClass_Cleric || eClass_Paladin:
//            UserList[UserIndex].Invent.Object[Slot].ObjIndex = 129;
//        default:
//            /* ' Daga (Newbie) */
//            UserList[UserIndex].Invent.Object[Slot].ObjIndex = 460;
//            break;
//    }
//
//    return Slot + 1;
}

void DotIOInventory::setUserHelmet() {

}

void DotIOInventory::setUserArmor() {

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