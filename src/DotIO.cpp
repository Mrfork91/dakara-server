//
// Created by horacio on 3/12/17.
//
#include "stdafx.h"
#include "Crypto.h"
#include "DotIO.h"

void DotIO::setupUser(int userIndex) {
    loadUserInit(userIndex);
    loadUserStats(userIndex);
    loadUserReputacion(userIndex);
    return;
}

void DotIO::loadUserInit(int UserIndex){
    int LoopC;
    std::string ln;

    UserList[UserIndex].Faccion.ArmadaReal = 0;
    UserList[UserIndex].Faccion.FuerzasCaos = 0;
    UserList[UserIndex].Faccion.CiudadanosMatados = 0;
    UserList[UserIndex].Faccion.CriminalesMatados = 0;
    UserList[UserIndex].Faccion.RecibioArmaduraCaos = 0;
    UserList[UserIndex].Faccion.RecibioArmaduraReal = 0;
    UserList[UserIndex].Faccion.RecibioExpInicialCaos = 0;
    UserList[UserIndex].Faccion.RecibioExpInicialReal = 0;
    UserList[UserIndex].Faccion.RecompensasCaos = 0;
    UserList[UserIndex].Faccion.RecompensasReal = 0;
    UserList[UserIndex].Faccion.Reenlistadas = 0;
    UserList[UserIndex].Faccion.NivelIngreso = 0;
    UserList[UserIndex].Faccion.FechaIngreso = "No hay ingresado a ninguna faccion";
    UserList[UserIndex].Faccion.MatadosIngreso = 0;
    UserList[UserIndex].Faccion.NextRecompensa = 0;

    UserList[UserIndex].flags.Muerto = 0;
    UserList[UserIndex].flags.Escondido = 0;

    UserList[UserIndex].flags.Hambre = 0;
    UserList[UserIndex].flags.Sed = 0;
    UserList[UserIndex].flags.Desnudo = 0;
    UserList[UserIndex].flags.Navegando = 0;
    UserList[UserIndex].flags.Envenenado = 0;
    UserList[UserIndex].flags.Paralizado = 0;

    /* 'Matrix */
    UserList[UserIndex].flags.lastMap = 0;

    if (UserList[UserIndex].flags.Paralizado == 1) {
        UserList[UserIndex].Counters.Paralisis = IntervaloParalizado;
    }

    UserList[UserIndex].Counters.Pena = 0;
    UserList[UserIndex].Counters.AsignedSkills = 0;

    UserList[UserIndex].email = "asdd@gmail.com";

    UserList[UserIndex].Genero = eGenero_Hombre; // TODO
    UserList[UserIndex].clase = eClass_Assasin; // TODO
    UserList[UserIndex].raza = eRaza_Drow; // TODO
    UserList[UserIndex].Hogar = eCiudad_cUllathorpe; // TODO
    UserList[UserIndex].Char.heading = eHeading_SOUTH; // TODO

    UserList[UserIndex].OrigChar.Head = 1;
    UserList[UserIndex].OrigChar.body = 1;
    UserList[UserIndex].OrigChar.WeaponAnim = 1;
    UserList[UserIndex].OrigChar.ShieldAnim = 1;
    UserList[UserIndex].OrigChar.CascoAnim = 1;

    UserList[UserIndex].OrigChar.heading = eHeading_SOUTH;

    /* # IF ConUpTime THEN */
    UserList[UserIndex].UpTime = 1;
    /* # END IF */

    if (UserList[UserIndex].flags.Muerto == 0) {
        UserList[UserIndex].Char = UserList[UserIndex].OrigChar;
    } else {
        UserList[UserIndex].Char.body = iCuerpoMuerto;
        UserList[UserIndex].Char.Head = iCabezaMuerto;
        UserList[UserIndex].Char.WeaponAnim = NingunArma;
        UserList[UserIndex].Char.ShieldAnim = NingunEscudo;
        UserList[UserIndex].Char.CascoAnim = NingunCasco;
    }

    UserList[UserIndex].desc = "";

    UserList[UserIndex].Pos.Map = 1; //TODO
    UserList[UserIndex].Pos.X = 50; //TODO
    UserList[UserIndex].Pos.Y = 50; //TODO

    UserList[UserIndex].Invent.NroItems = 1; //TODO

    UserList[UserIndex].BancoInvent.NroItems = 0;
    /* 'Lista de objetos del banco */
    for (LoopC = (1); LoopC <= (MAX_BANCOINVENTORY_SLOTS); LoopC++) {
        UserList[UserIndex].BancoInvent.Object[LoopC].ObjIndex = 0;
        UserList[UserIndex].BancoInvent.Object[LoopC].Amount = 0;
    }

    /* 'Lista de objetos */
    for (LoopC = (1); LoopC <= (MAX_INVENTORY_SLOTS); LoopC++) { //TODO
//        ln = UserFile->GetValue("Inventory", "Obj" + vb6::CStr(LoopC));
//        UserList[UserIndex].Invent.Object[LoopC].ObjIndex = vb6::val(ReadField(1, ln, 45));
//        UserList[UserIndex].Invent.Object[LoopC].Amount = vb6::val(ReadField(2, ln, 45));
//        UserList[UserIndex].Invent.Object[LoopC].Equipped = vb6::val(ReadField(3, ln, 45));
        UserList[UserIndex].Invent.Object[LoopC].ObjIndex = 0;
        UserList[UserIndex].Invent.Object[LoopC].Amount = 0;
        UserList[UserIndex].Invent.Object[LoopC].Equipped = 0;
    }

    /* 'Obtiene el indice-objeto del arma */
    UserList[UserIndex].Invent.WeaponEqpSlot = 0; // TODO
    if (UserList[UserIndex].Invent.WeaponEqpSlot > 0) {
        UserList[UserIndex].Invent.WeaponEqpObjIndex =
                UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.WeaponEqpSlot].ObjIndex;
    }

    /* 'Obtiene el indice-objeto del armadura */
    UserList[UserIndex].Invent.ArmourEqpSlot = 0; // TODO
    if (UserList[UserIndex].Invent.ArmourEqpSlot > 0) {
        UserList[UserIndex].Invent.ArmourEqpObjIndex =
                UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.ArmourEqpSlot].ObjIndex;
        UserList[UserIndex].flags.Desnudo = 0;
    } else {
        UserList[UserIndex].flags.Desnudo = 1;
    }

    /* 'Obtiene el indice-objeto del escudo */
    UserList[UserIndex].Invent.EscudoEqpSlot = 0; // TODO
    if (UserList[UserIndex].Invent.EscudoEqpSlot > 0) {
        UserList[UserIndex].Invent.EscudoEqpObjIndex =
                UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.EscudoEqpSlot].ObjIndex;
    }

    /* 'Obtiene el indice-objeto del casco */
    UserList[UserIndex].Invent.CascoEqpSlot = 0; // TODO
    if (UserList[UserIndex].Invent.CascoEqpSlot > 0) {
        UserList[UserIndex].Invent.CascoEqpObjIndex =
                UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.CascoEqpSlot].ObjIndex;
    }

    /* 'Obtiene el indice-objeto barco */
    UserList[UserIndex].Invent.BarcoSlot = 0; // TODO
    if (UserList[UserIndex].Invent.BarcoSlot > 0) {
        UserList[UserIndex].Invent.BarcoObjIndex =
                UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.BarcoSlot].ObjIndex;
    }

    /* 'Obtiene el indice-objeto municion */
    UserList[UserIndex].Invent.MunicionEqpSlot = 0; // TODO
    if (UserList[UserIndex].Invent.MunicionEqpSlot > 0) {
        UserList[UserIndex].Invent.MunicionEqpObjIndex =
                UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.MunicionEqpSlot].ObjIndex;
    }

    /* '[Alejo] */
    /* 'Obtiene el indice-objeto anilo */
    UserList[UserIndex].Invent.AnilloEqpSlot = 0; // TODO
    if (UserList[UserIndex].Invent.AnilloEqpSlot > 0) {
        UserList[UserIndex].Invent.AnilloEqpObjIndex =
                UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.AnilloEqpSlot].ObjIndex;
    }

    UserList[UserIndex].Invent.MochilaEqpSlot = 0; // TODO
    if (UserList[UserIndex].Invent.MochilaEqpSlot > 0) {
        UserList[UserIndex].Invent.MochilaEqpObjIndex =
                UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.MochilaEqpSlot].ObjIndex;
    }

    UserList[UserIndex].NroMascotas = 0;
    for (LoopC = (1); LoopC <= (MAXMASCOTAS); LoopC++) {
        UserList[UserIndex].MascotasType[LoopC] = 0;
    }

    UserList[UserIndex].GuildIndex = 0;


}

void DotIO::loadUserStats(int UserIndex){
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

    if (0) {
        UserAsignarPrivilegios(UserIndex, PlayerType_RoyalCouncil);
    }

    if (0) {
        UserAsignarPrivilegios(UserIndex, PlayerType_ChaosCouncil);
    }
}

void DotIO::loadUserReputacion(int UserIndex){
    UserList[UserIndex].Reputacion.AsesinoRep = 0;
    UserList[UserIndex].Reputacion.BandidoRep = 0;
    UserList[UserIndex].Reputacion.BurguesRep = 0;
    UserList[UserIndex].Reputacion.LadronesRep = 0;
    UserList[UserIndex].Reputacion.NobleRep = 0;
    UserList[UserIndex].Reputacion.PlebeRep = 0;
    UserList[UserIndex].Reputacion.Promedio = 0;
}