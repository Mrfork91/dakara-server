//
// Created by horacio on 3/12/17.
//
#include "stdafx.h"
#include "Crypto.h"
#include "DotIO.h"
#include "DotIOInventory.h"
#include "Matematicas.h"

DotIO::DotIO(int UserIndex, const std::string &Name, eRaza UserRaza, eGenero UserSexo,
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
    this->Head = Head;
}

void DotIO::setupUser() {
    loadUserIni();
    loadUserReputacion();
    loadUserFlags();
    loadUserStats();
    loadUserHechizos();

    updateUserPosition();
    updateUserLevel();
}

void DotIO::addSpell(int number) {
    int lastSlot = 35;
    while (UserList[UserIndex].Stats.UserHechizos[lastSlot] != 0) {
        lastSlot--;
    }
    UserList[UserIndex].Stats.UserHechizos[lastSlot] = number;
}

void DotIO::loadUserHechizos() {

    if (UserClase == eClass_Thief || UserClase == eClass_Warrior || UserClase == eClass_Hunter){
        return;
    }
    addSpell(10); // remover paralisis
    addSpell(24); // inmovilizar
    if (UserClase == eClass_Cleric || UserClase == eClass_Mage || UserClase == eClass_Bard || UserClase == eClass_Druid){
        addSpell(25); // apocalipsis
    }
    addSpell(23); // descargar electrica
    addSpell(15); // tormenta
    addSpell(8); // misil magico
    //addSpell(14); // invisibilidad
    addSpell(5); // curar heridas graves
}

void DotIO::loadUserReputacion() {
    UserList[UserIndex].Reputacion.AsesinoRep = 2000;
    UserList[UserIndex].Reputacion.BandidoRep = 0;
    UserList[UserIndex].Reputacion.BurguesRep = 0;
    UserList[UserIndex].Reputacion.LadronesRep = 0;
    UserList[UserIndex].Reputacion.NobleRep = 1000;
    UserList[UserIndex].Reputacion.PlebeRep = 30;
    UserList[UserIndex].Reputacion.Promedio = 30 / 6;
}

void DotIO::loadUserFlags() {
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

void DotIO::loadUserIni() {
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

void DotIO::loadUserStats() {
    int i;
    UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza] = 18 + ModRaza[UserRaza].Fuerza;
    UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad] = 18 + ModRaza[UserRaza].Agilidad;

    // Dopa
    UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza] *= 2;
    UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad] *= 2;
	if (UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza] > MAXATRIBUTOS) {
				UserList[UserIndex].Stats.UserAtributos[eAtributos_Fuerza] = MAXATRIBUTOS;
	}
    if (UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad] > MAXATRIBUTOS) {
			UserList[UserIndex].Stats.UserAtributos[eAtributos_Agilidad] = MAXATRIBUTOS;
	}
    //

    UserList[UserIndex].Stats.UserAtributos[eAtributos_Inteligencia] =
            18 + ModRaza[UserRaza].Inteligencia;
    UserList[UserIndex].Stats.UserAtributos[eAtributos_Carisma] =
            18 + ModRaza[UserRaza].Carisma;
    UserList[UserIndex].Stats.UserAtributos[eAtributos_Constitucion] =
            18 + ModRaza[UserRaza].Constitucion;

    for (i = (1); i <= (NUMATRIBUTOS); i++) {
        UserList[UserIndex].Stats.UserAtributosBackUP[i] = UserList[UserIndex].Stats.UserAtributos[i];
    }

    for (i = (1); i <= (NUMSKILLS); i++) {
        UserList[UserIndex].Stats.UserSkills[i] = 100;
        UserList[UserIndex].Stats.EluSkills[i] = 0;
        UserList[UserIndex].Stats.ExpSkills[i] = 0;
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

    UserList[UserIndex].Stats.MaxHIT = 2;
    UserList[UserIndex].Stats.MinHIT = 1;

    UserList[UserIndex].Stats.GLD = 0;
    UserList[UserIndex].Stats.Banco = 0;

    UserList[UserIndex].Stats.Exp = 0;
    UserList[UserIndex].Stats.ELU = 300;
    UserList[UserIndex].Stats.ELV = 1;

    UserList[UserIndex].Stats.UsuariosMatados = 0;
    UserList[UserIndex].Stats.NPCsMuertos = 0;
}

void DotIO::updateUserPosition() {
    int map = 272;
    int y;
    int entrada = RandomNumber(0,2);
    if (entrada == 0){
        y  = RandomNumber(66,70);
    }
    else if (entrada == 1){
        y  = RandomNumber(45,49);
    }
    else if (entrada == 2){
        y  = RandomNumber(24,28);
    }
    int x = RandomNumber(72,82);
    UserList[UserIndex].Pos.Map = map;
    UserList[UserIndex].Pos.X = x;
    UserList[UserIndex].Pos.Y = y;
}

void DotIO::updateUserLevel() {
    UserList[UserIndex].Stats.Exp = 5679050;
    CheckUserLevel(UserIndex, false);
    UserList[UserIndex].Stats.MinMAN = UserList[UserIndex].Stats.MaxMAN;
    UserList[UserIndex].Stats.MinSta = UserList[UserIndex].Stats.MaxSta;
}