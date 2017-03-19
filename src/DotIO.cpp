//
// Created by horacio on 3/12/17.
//
#include "stdafx.h"
#include "Crypto.h"
#include "DotIO.h"

void DotIO::setupUser(int UserIndex, const std::string &Name, eRaza UserRaza,
                      eGenero UserSexo, eClass UserClase, const std::string &UserEmail, eCiudad Hogar, int Head) {
    loadUserIni(UserIndex, Name, UserRaza, UserSexo, UserClase, UserEmail, Hogar, Head);
    loadUserReputacion(UserIndex);
    loadUserFlags(UserIndex);

    loadUserStats2(UserIndex, Name, UserRaza, UserSexo, UserClase, UserEmail, Hogar, Head);
    loadUserInventoryItems(UserIndex, Name, UserRaza, UserSexo, UserClase, UserEmail, Hogar, Head); // << ITEMS

    loadUserInventory(UserIndex, Name, UserRaza, UserSexo, UserClase, UserEmail, Hogar, Head);
    loadUserPosition(UserIndex);

    loadUserInit(UserIndex, UserRaza, UserSexo, UserClase, UserEmail, Hogar, Head);
    loadUserStats(UserIndex, UserRaza, UserSexo, UserClase, UserEmail, Hogar, Head);

    int i;
}

void
DotIO::loadUserInit(int UserIndex, eRaza UserRaza, eGenero UserSexo, eClass UserClase, const std::string &UserEmail,
                    eCiudad Hogar, int Head) {
    int LoopC;
    std::string ln;



}

void
DotIO::loadUserStats(int UserIndex, eRaza UserRaza, eGenero UserSexo, eClass UserClase, const std::string &UserEmail,
                     eCiudad Hogar, int Head) {
    int LoopC;

    for (LoopC = (1); LoopC <= (NUMATRIBUTOS); LoopC++) { //TODO - ACORDARSE MODIFICADORES X CLASE
        UserList[UserIndex].Stats.UserAtributos[LoopC] = 18;
        UserList[UserIndex].Stats.UserAtributosBackUP[LoopC] = UserList[UserIndex].Stats.UserAtributos[LoopC];
    }

    for (LoopC = (1); LoopC <= (NUMSKILLS); LoopC++) {
        UserList[UserIndex].Stats.UserSkills[LoopC] = 100;
        UserList[UserIndex].Stats.EluSkills[LoopC] = 0;
        UserList[UserIndex].Stats.ExpSkills[LoopC] = 0;
    }

    for (LoopC = (1); LoopC <= (MAXUSERHECHIZOS); LoopC++) { // TODO
        //UserList[UserIndex].Stats.UserHechizos[LoopC] = vb6::val(UserFile->GetValue("Hechizos", "H" + vb6::CStr(LoopC)));
        UserList[UserIndex].Stats.UserHechizos[LoopC] = 0;
    }

    UserList[UserIndex].Stats.GLD = 0;
    UserList[UserIndex].Stats.Banco = 0;

    UserList[UserIndex].Stats.MaxHp = 100; //TODO
    UserList[UserIndex].Stats.MinHp = 100; //TODO

    UserList[UserIndex].Stats.MinSta = 100; //TODO
    UserList[UserIndex].Stats.MaxSta = 100; //TODO

    UserList[UserIndex].Stats.MaxMAN = 100; //TODO
    UserList[UserIndex].Stats.MinMAN = 100; //TODO

    UserList[UserIndex].Stats.MaxHIT = 100; //TODO
    UserList[UserIndex].Stats.MinHIT = 100; //TODO

    UserList[UserIndex].Stats.MaxAGU = 100; //TODO
    UserList[UserIndex].Stats.MinAGU = 100; //TODO

    UserList[UserIndex].Stats.MaxHam = 100; //TODO
    UserList[UserIndex].Stats.MinHam = 100; //TODO

    UserList[UserIndex].Stats.SkillPts = 0;

    UserList[UserIndex].Stats.Exp = 0;
    UserList[UserIndex].Stats.ELU = 1000000000;
    UserList[UserIndex].Stats.ELV = 40;

    UserList[UserIndex].Stats.UsuariosMatados = 0;
    UserList[UserIndex].Stats.NPCsMuertos = 0;
}

void DotIO::loadUserReputacion(int UserIndex) {
    UserList[UserIndex].Reputacion.AsesinoRep = 0;
    UserList[UserIndex].Reputacion.BandidoRep = 0;
    UserList[UserIndex].Reputacion.BurguesRep = 0;
    UserList[UserIndex].Reputacion.LadronesRep = 0;
    UserList[UserIndex].Reputacion.NobleRep = 1000;
    UserList[UserIndex].Reputacion.PlebeRep = 30;
    UserList[UserIndex].Reputacion.Promedio = 30 / 6;
}

void DotIO::loadUserFlags(int UserIndex) {
    UserList[UserIndex].flags.Muerto = 0;
    UserList[UserIndex].flags.Escondido = 0;
    UserList[UserIndex].flags.Hambre = 0;
    UserList[UserIndex].flags.Sed = 0;
    UserList[UserIndex].flags.Desnudo = 0;
    UserList[UserIndex].flags.Navegando = 0;
    UserList[UserIndex].flags.Envenenado = 0;
    UserList[UserIndex].flags.Paralizado = 0;
    UserList[UserIndex].flags.lastMap = 0;
}

void DotIO::loadUserIni(int UserIndex, const std::string &Name, eRaza UserRaza, eGenero UserSexo, eClass UserClase,
                        const std::string &UserEmail,
                        eCiudad Hogar, int Head) {
    int LoopC;

    UserList[UserIndex].Name = Name;
    UserList[UserIndex].clase = UserClase;
    UserList[UserIndex].raza = UserRaza;
    UserList[UserIndex].Genero = UserSexo;
    UserList[UserIndex].email = UserEmail;
    UserList[UserIndex].Hogar = Hogar;

    UserList[UserIndex].Char.heading = eHeading_SOUTH;

    DarCuerpo(UserIndex); // <-- !!!
    UserList[UserIndex].Char.Head = Head;

    UserList[UserIndex].OrigChar = UserList[UserIndex].Char;

    UserList[UserIndex].LogOnTime = vb6::Now();
    UserList[UserIndex].UpTime = 0;
    UserList[UserIndex].desc = "";

    UserList[UserIndex].Faccion.ArmadaReal = 0;
    UserList[UserIndex].Faccion.CiudadanosMatados = 0;
    UserList[UserIndex].Faccion.CriminalesMatados = 0;
    UserList[UserIndex].Faccion.FuerzasCaos = 0;
    UserList[UserIndex].Faccion.FechaIngreso = "No ingresó a ninguna Facción";
    UserList[UserIndex].Faccion.RecibioArmaduraCaos = 0;
    UserList[UserIndex].Faccion.RecibioArmaduraReal = 0;
    UserList[UserIndex].Faccion.RecibioExpInicialCaos = 0;
    UserList[UserIndex].Faccion.RecibioExpInicialReal = 0;
    UserList[UserIndex].Faccion.RecompensasCaos = 0;
    UserList[UserIndex].Faccion.RecompensasReal = 0;
    UserList[UserIndex].Faccion.Reenlistadas = 0;
    UserList[UserIndex].Faccion.NivelIngreso = 0;
    UserList[UserIndex].Faccion.MatadosIngreso = 0;
    UserList[UserIndex].Faccion.NextRecompensa = 0;

    UserList[UserIndex].Counters.Pena = 0;
    UserList[UserIndex].Counters.AsignedSkills = 0;

    UserList[UserIndex].GuildIndex = 0;

    UserList[UserIndex].NroMascotas = 0;
    for (LoopC = (1); LoopC <= (MAXMASCOTAS); LoopC++) {
        UserList[UserIndex].MascotasType[LoopC] = 0;
    }
}

void DotIO::loadUserStats2(int UserIndex, const std::string &Name, eRaza UserRaza, eGenero UserSexo, eClass UserClase,
                           const std::string &UserEmail,
                           eCiudad Hogar, int Head) {
    int i;
    UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza] =
            18 + ModRaza[UserRaza].Fuerza;
    UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad] =
            18 + ModRaza[UserRaza].Agilidad;
    UserList[UserIndex].Stats.UserAtributos[eAtributos_Inteligencia] =
            18 + ModRaza[UserRaza].Inteligencia;
    UserList[UserIndex].Stats.UserAtributos[eAtributos_Carisma] =
            18 + ModRaza[UserRaza].Carisma;
    UserList[UserIndex].Stats.UserAtributos[eAtributos_Constitucion] =
            18 + ModRaza[UserRaza].Constitucion;

    for (i = (1); i <= (NUMSKILLS); i++) {
        UserList[UserIndex].Stats.UserSkills[i] = 100;
    }

    UserList[UserIndex].Stats.SkillPts = 0;


    int MiInt;
    MiInt = RandomNumber(1, UserList[UserIndex].Stats.UserAtributos[eAtributos_Constitucion] / 3);

    UserList[UserIndex].Stats.MaxHp = 15 + MiInt;
    UserList[UserIndex].Stats.MinHp = 15 + MiInt;

    MiInt = RandomNumber(1, UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad] / 6);
    if (MiInt == 1) {
        MiInt = 2;
    }

    UserList[UserIndex].Stats.MaxSta = 20 * MiInt;
    UserList[UserIndex].Stats.MinSta = 20 * MiInt;

    UserList[UserIndex].Stats.MaxAGU = 100;
    UserList[UserIndex].Stats.MinAGU = 100;

    UserList[UserIndex].Stats.MaxHam = 100;
    UserList[UserIndex].Stats.MinHam = 100;

    if (UserClase == eClass_Mage) {
        MiInt = UserList[UserIndex].Stats.UserAtributos[eAtributos_Inteligencia] * 3;
        UserList[UserIndex].Stats.MaxMAN = MiInt;
        UserList[UserIndex].Stats.MinMAN = MiInt;
    } else if (UserClase == eClass_Cleric || UserClase == eClass_Druid || UserClase == eClass_Bard
               || UserClase == eClass_Assasin) {
        UserList[UserIndex].Stats.MaxMAN = 50;
        UserList[UserIndex].Stats.MinMAN = 50;
        /* 'Mana Inicial del Bandido (ToxicWaste) */
    } else if (UserClase == eClass_Bandit) {
        UserList[UserIndex].Stats.MaxMAN = 50;
        UserList[UserIndex].Stats.MinMAN = 50;
    } else {
        UserList[UserIndex].Stats.MaxMAN = 0;
        UserList[UserIndex].Stats.MinMAN = 0;
    }

    if (UserClase == eClass_Mage || UserClase == eClass_Cleric || UserClase == eClass_Druid
        || UserClase == eClass_Bard || UserClase == eClass_Assasin) {
        UserList[UserIndex].Stats.UserHechizos[1] = 2;

        if (UserClase == eClass_Druid) {
            UserList[UserIndex].Stats.UserHechizos[2] = 46;
        }
    }

    UserList[UserIndex].Stats.MaxHIT = 2;
    UserList[UserIndex].Stats.MinHIT = 1;

    UserList[UserIndex].Stats.GLD = 0;

    UserList[UserIndex].Stats.Exp = 0;
    UserList[UserIndex].Stats.ELU = 300;
    UserList[UserIndex].Stats.ELV = 1;
}

void DotIO::loadUserInventoryItems(int UserIndex, const std::string &Name, eRaza UserRaza, eGenero UserSexo, eClass UserClase,
                              const std::string &UserEmail,
                              eCiudad Hogar, int Head) {
    int i, Slot, LoopC;
    /* '???????????????? INVENTARIO ¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿ */
    bool IsPaladin;

    IsPaladin = UserClase == eClass_Paladin;

    /* 'Pociones Rojas (Newbie) */
    Slot = 1;
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
    switch (UserClase) {
        case eClass_Hunter:
            /* ' Arco (Newbie) */
            UserList[UserIndex].Invent.Object[Slot].ObjIndex = 859;
            break;

        case eClass_Worker:
            /* ' Herramienta (Newbie) */
            UserList[UserIndex].Invent.Object[Slot].ObjIndex = RandomNumber(561, 565);
            break;

        default:
            /* ' Daga (Newbie) */
            UserList[UserIndex].Invent.Object[Slot].ObjIndex = 460;
            break;
    }

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
    UserList[UserIndex].Invent.NroItems = Slot;
}

void DotIO::loadUserInventory(int UserIndex, const std::string &Name, eRaza UserRaza, eGenero UserSexo, eClass UserClase,
                              const std::string &UserEmail,
                              eCiudad Hogar, int Head) {
    int i, Slot, LoopC;

    /* 'Lista de objetos */
    for (LoopC = (Slot + 1); LoopC <= (MAX_INVENTORY_SLOTS); LoopC++) {
        UserList[UserIndex].Invent.Object[LoopC].ObjIndex = 0;
        UserList[UserIndex].Invent.Object[LoopC].Amount = 0;
        UserList[UserIndex].Invent.Object[LoopC].Equipped = 0;
    }

    /* 'Obtiene el indice-objeto del arma */
    if (UserList[UserIndex].Invent.WeaponEqpSlot > 0) {
        UserList[UserIndex].Invent.WeaponEqpObjIndex =
                UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.WeaponEqpSlot].ObjIndex;
        UserList[UserIndex].Char.WeaponAnim = GetWeaponAnim(UserIndex,
                                                            UserList[UserIndex].Invent.WeaponEqpObjIndex);
    }

    /* 'Obtiene el indice-objeto del armadura */
    if (UserList[UserIndex].Invent.ArmourEqpSlot > 0) {
        UserList[UserIndex].Invent.ArmourEqpObjIndex =
                UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.ArmourEqpSlot].ObjIndex;
        UserList[UserIndex].flags.Desnudo = 0;
    } else {
        UserList[UserIndex].flags.Desnudo = 1;
    }

    /* 'Obtiene el indice-objeto del escudo */
    if (UserList[UserIndex].Invent.EscudoEqpSlot > 0) {
        UserList[UserIndex].Invent.EscudoEqpObjIndex =
                UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.EscudoEqpSlot].ObjIndex;
    }

    /* 'Obtiene el indice-objeto del casco */
    if (UserList[UserIndex].Invent.CascoEqpSlot > 0) {
        UserList[UserIndex].Invent.CascoEqpObjIndex =
                UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.CascoEqpSlot].ObjIndex;
    }

    /* 'Obtiene el indice-objeto barco */
    if (UserList[UserIndex].Invent.BarcoSlot > 0) {
        UserList[UserIndex].Invent.BarcoObjIndex =
                UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.BarcoSlot].ObjIndex;
    }

    /* 'Obtiene el indice-objeto municion */
    if (UserList[UserIndex].Invent.MunicionEqpSlot > 0) {
        UserList[UserIndex].Invent.MunicionEqpObjIndex =
                UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.MunicionEqpSlot].ObjIndex;
    }

    /* '[Alejo] */
    /* 'Obtiene el indice-objeto anilo */
    if (UserList[UserIndex].Invent.AnilloEqpSlot > 0) {
        UserList[UserIndex].Invent.AnilloEqpObjIndex =
                UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.AnilloEqpSlot].ObjIndex;
    }

    if (UserList[UserIndex].Invent.MochilaEqpSlot > 0) {
        UserList[UserIndex].Invent.MochilaEqpObjIndex =
                UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.MochilaEqpSlot].ObjIndex;
    }








    UserList[UserIndex].BancoInvent.NroItems = 0;
    /* 'Lista de objetos del banco */
    for (LoopC = (1); LoopC <= (MAX_BANCOINVENTORY_SLOTS); LoopC++) {
        UserList[UserIndex].BancoInvent.Object[LoopC].ObjIndex = 0;
        UserList[UserIndex].BancoInvent.Object[LoopC].Amount = 0;
    }
}

void DotIO::loadUserPosition(int UserIndex){
    UserList[UserIndex].Pos.Map = 1; //TODO
    UserList[UserIndex].Pos.X = 50; //TODO
    UserList[UserIndex].Pos.Y = 50; //TODO
}