//
// Created by horacio on 3/19/17.
//
#include "stdafx.h"
#include "Crypto.h"
#include "DotIOInventory.h"
using namespace std;
const int STARTING_LEVEL = 30;
const int MAX_REWARD_LEVEL = 40;

void loadUserInventory(int UserIndex) {
    int LoopC;
    struct ObjData Obj;

    /* 'Obtiene el indice-objeto del arma */
    if (UserList[UserIndex].Invent.WeaponEqpSlot > 0) {
        UserList[UserIndex].Invent.WeaponEqpObjIndex =
                UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.WeaponEqpSlot].ObjIndex;
        UserList[UserIndex].Char.WeaponAnim = GetWeaponAnim(UserIndex,
                                                            UserList[UserIndex].Invent.WeaponEqpObjIndex);
    }

    /* 'Obtiene el indice-objeto del armadura */
    if (UserList[UserIndex].Invent.ArmourEqpSlot > 0) {
        Obj = ObjData[UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.ArmourEqpSlot].ObjIndex];
        UserList[UserIndex].Char.body = Obj.Ropaje;

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

        Obj = ObjData[UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.EscudoEqpSlot].ObjIndex];
        UserList[UserIndex].Char.ShieldAnim = Obj.ShieldAnim;
    }

    /* 'Obtiene el indice-objeto del casco */
    if (UserList[UserIndex].Invent.CascoEqpSlot > 0) {
        UserList[UserIndex].Invent.CascoEqpObjIndex =
                UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.CascoEqpSlot].ObjIndex;

        Obj = ObjData[UserList[UserIndex].Invent.Object[UserList[UserIndex].Invent.CascoEqpSlot].ObjIndex];
        UserList[UserIndex].Char.CascoAnim = Obj.CascoAnim;
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

static void emptyInventory(int UserIndex) {
    int slot = 1;
    while (UserList[UserIndex].Invent.Object[slot].ObjIndex != 0) {
        UserList[UserIndex].Invent.Object[slot].ObjIndex = 0;
        slot++;
    }
}

static int getFirstFreeSlotNumber(int UserIndex) {
    int slot = 1;
    while (UserList[UserIndex].Invent.Object[slot].ObjIndex != 0) {
        slot++;
    }
    return slot;
}

static int addItem(int UserIndex, int item) {
    int Slot = getFirstFreeSlotNumber(UserIndex);
    UserList[UserIndex].Invent.Object[Slot].ObjIndex = item;
    UserList[UserIndex].Invent.Object[Slot].Amount = 1;
    return Slot;
}

void updatePotions(int UserIndex) {
    eClass UserClase = UserList[UserIndex].clase;
    addItem(UserIndex,38); // Pociones rojas

    if (UserList[UserIndex].Stats.MaxMAN > 0 || UserClase == eClass_Paladin || UserClase == eClass_Bandit) {
        addItem(UserIndex,37); // Pociones azules
    }
    if (UserClase != eClass_Mage) {
        addItem(UserIndex,39); // Pociones verdes
    }
    addItem(UserIndex,36); // Pociones amarillas
}

void updateWeapons(int UserIndex, double progressRatio) {
    eClass UserClase = UserList[UserIndex].clase;
    int weapon = 0;
    int Slot = 0;

    switch (UserClase) {
        case eClass_Mage:
            if (progressRatio >= 0) weapon = 658; // Vara de fresno
            if (progressRatio >= 0.3) weapon = 659; // Nudoso
            if (progressRatio >= 1) weapon = 660; // Engarzado
            break;
        case eClass_Cleric:
            if (progressRatio >= 0) weapon = 124; // Katana
            if (progressRatio >= 0.3) weapon = 990; // Mazo del juicio
            if (progressRatio >= 0.9) weapon = 129; // 2 filos
            break;
        case eClass_Paladin:
            if (progressRatio >= 0) weapon = 990; // Mazo del juicio
            if (progressRatio >= 0.4) weapon = 129; // 2 filos
            if (progressRatio >= 1) weapon = 403; // Espada de plata
            break;
        case eClass_Warrior:
            if (progressRatio >= 0) weapon = 123; // Espada vikinga
            if (progressRatio >= 0.2) weapon = 159; // Hacha de barbaro            
            if (progressRatio >= 0.5) weapon = 129; // 2 filos
            if (progressRatio >= 0.8) weapon = 403; // Espada de plata
            break;
        case eClass_Assasin:
            if (progressRatio >= 0) weapon = 365; // Daga +2
            if (progressRatio >= 0.2) weapon = 366; // Daga +3
            if (progressRatio >= 0.7) weapon = 367; // Daga +4
            break;
        case eClass_Thief:
            if (progressRatio >= 0) weapon = 159; // Hacha de barbaro
            break;
        case eClass_Bard: // TODO
            if (progressRatio >= 0) weapon = 165; // Daga +1
            if (progressRatio >= 0.4) weapon = 399; // Cimitarra
            if (progressRatio >= 1) weapon = 367; // Daga +4
            break;
        case eClass_Druid:
            if (progressRatio >= 0) weapon = 165; // Daga +1
            if (progressRatio >= 0.3) weapon = 399; // Cimitarra
            break;
        case eClass_Bandit: //espada vikinga
            weapon = 123;
            if (progressRatio >= 0) weapon = 124; // Katana
            if (progressRatio >= 0.4) weapon = 123; // Espada vikinga
            if (progressRatio >= 1) weapon = 403; // Espada de plata
            break;
        case eClass_Hunter:
            if (progressRatio >= 0) weapon = 479; // Arco compuesto
            if (progressRatio >= 0.4) weapon = 664; // Arco compuesto reforzado
            if (progressRatio >= 0.8) weapon = 665; // Arco de cazador
            break;
        case eClass_Pirat:
            addItem(UserIndex,125); // Sable
            weapon = 1009; // Cuchillas
            break;
        case eClass_Worker:
        case eClass_None:
            break;
    }

    if (weapon > 0){
        int Slot = addItem(UserIndex,weapon);
        UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
        UserList[UserIndex].Invent.WeaponEqpSlot = Slot;
    }

    if (UserClase == eClass_Hunter) {
        int arrows = 480; // Flecha
        if (progressRatio >= 0.1) arrows = 551; // Flecha +1
        if (progressRatio >= 0.3) arrows = 552; // Flecha +2
        if (progressRatio >= 0.7) arrows = 553; // Flecha +3
        Slot = addItem(UserIndex,arrows);
        UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
        UserList[UserIndex].Invent.MunicionEqpSlot = Slot;
        if (progressRatio > 0.4) {
            addItem(UserIndex,126); // hacha larga de guerra
        }
    }
    if (UserClase == eClass_Warrior) {
        int bow = 478; // Arco simple
        if (progressRatio >= 0.3) bow = 663; // Arco simple reforzado
        if (progressRatio >= 0.6) bow = 479; // Arco compuesto
        if (progressRatio >= 0.9) bow = 664; // Arco compuesto reforzado
        addItem(UserIndex,bow);
        int arrows = 480; // Flecha
        if (progressRatio >= 0.3) arrows = 551; // Flecha +1
        if (progressRatio >= 0.9) arrows = 552; // Flecha +2
        Slot = addItem(UserIndex,arrows);
        UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
        UserList[UserIndex].Invent.MunicionEqpSlot = Slot;
        if (progressRatio >= 0.6){
            addItem(UserIndex, 366); //daga +3
        } else {
            addItem(UserIndex, 365); //daga +2
        }
    }
    if (UserClase == eClass_Bard) {
        if (progressRatio > 0.6) {
            Slot = addItem(UserIndex,1049); //laud magico
            UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
            UserList[UserIndex].Invent.AnilloEqpSlot = Slot;
        }
    }
    if (UserClase == eClass_Druid) {
        if (progressRatio > 0.3) {
            Slot = addItem(UserIndex,1050); //flauta elfica
            UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
            UserList[UserIndex].Invent.AnilloEqpSlot = Slot;
        }
    }

    if ((UserClase == eClass_Bandit) || (UserClase == eClass_Thief)) {
        Slot = addItem(UserIndex,873); // guantes de hurto
        UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
    }
}

void updateShield(int UserIndex, double progressRatio) {
    eClass UserClase = UserList[UserIndex].clase;
    int shield = 0;
    switch (UserClase) {
        case eClass_Warrior:
            if (progressRatio >= 0) shield = 404; // escudo de tortuga
            if (progressRatio >= 0.1) shield = 128; // escudo de hierro
            if (progressRatio >= 0.5) shield = 130; // escudo de plata
            break;
        case eClass_Paladin:
        case eClass_Thief:
        case eClass_Cleric:
        case eClass_Bandit:
            if (progressRatio >= 0) shield = 404; // escudo de tortuga
            if (progressRatio >= 0.5) shield = 128; // escudo de hierro
            if (progressRatio >= 1) shield = 130; // escudo de plata
            break;
        case eClass_Assasin:
        case eClass_Hunter:
        case eClass_Pirat:
        case eClass_Bard:
            shield = 404; // escudo de tortuga
            break;
        case eClass_Druid:
        case eClass_Mage:
            break;
        case eClass_Worker:
        case eClass_None:
            break;
    }

    if (shield > 0) {
        int Slot = addItem(UserIndex, shield);
        UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
        UserList[UserIndex].Invent.EscudoEqpSlot = Slot;
    }
}

void updateRing(int UserIndex, double progressRatio) {
    eClass UserClase = UserList[UserIndex].clase;
    int ring = 0;
    switch (UserClase) {
        case eClass_Warrior:
            if (progressRatio >= 0.2) ring = 697; // Anillo de defensa magica
            if (progressRatio >= 0.5) ring = 698; // Anillo de resistencia magica
            if (progressRatio >= 1) ring = 699; // Anillo de disolucion magica
            break;
        case eClass_Paladin:
        case eClass_Thief:
        case eClass_Cleric:
        case eClass_Bandit:
        case eClass_Assasin:
        case eClass_Hunter:
        case eClass_Pirat:
            if (progressRatio >= 0.5) ring = 697; // Anillo de defensa magica
            if (progressRatio >= 1) ring = 698; // Anillo de resistencia magica
            break;
        case eClass_Bard:
        case eClass_Druid:
        case eClass_Mage:
            break;
        case eClass_Worker:
        case eClass_None:
            break;
    }

    if (ring > 0) {
        int Slot = addItem(UserIndex, ring);
        UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
        UserList[UserIndex].Invent.AnilloEqpSlot = Slot;
    }
}

void updateHelmet(int UserIndex, double progressRatio) {
    eClass UserClase = UserList[UserIndex].clase;
    int helmet = 0;
    switch (UserClase) {
        case eClass_Mage:
            if (progressRatio >= 0.1) helmet = 661;
            if (progressRatio >= 0.5) helmet = 383;
            if (progressRatio >= 1) helmet = 662;
            break;
        case eClass_Paladin:
            if (progressRatio >= 0.2) helmet = 1002; // Casco de lobo
            if (progressRatio >= 0.5) helmet = 132; // Casco de hierro
            if (progressRatio >= 0.8) helmet = 131; // Casco de hierro completo
            if (progressRatio >= 1) helmet = 405; // Casco de plata
            break;
        case eClass_Warrior:
            if (progressRatio >= 0.1) helmet = 132; // Casco de hierro
            if (progressRatio >= 0.3) helmet = 131; // Casco de hierro completo
            if (progressRatio >= 1) helmet = 405; // Casco de plata
            break;
        case eClass_Cleric:
            if (progressRatio >= 0.2) helmet = 1002; // Casco de lobo
            if (progressRatio >= 0.5) helmet = 132; // Casco de hierro
            if (progressRatio >= 0.8) helmet = 131; // Casco de hierro completo
            if (progressRatio >= 1) helmet = 405; // Casco de plata
            break;
        case eClass_Bandit:
            if (progressRatio >= 0.5) helmet = 132; // Casco de hierro
            if (progressRatio >= 0.8) helmet = 131; // Casco de hierro completo
            if (progressRatio >= 1) helmet = 405; // Casco de plata
            break;
        case eClass_Assasin:
            if (progressRatio >= 0.1) helmet = 1002; // Casco de lobo
            if (progressRatio >= 0.5) helmet = 132; // Casco de hierro
            if (progressRatio >= 0.8) helmet = 131; // Casco de hierro completo
            if (progressRatio >= 1) helmet = 405; // Casco de plata
            break;
        case eClass_Hunter:
            if (progressRatio >= 0.1) helmet = 1001; // Casco de aguila
            if (progressRatio >= 0.3) helmet = 131; // Casco de hierro completo
            if (progressRatio >= 1) helmet = 405; // Casco de plata
            break;
        case eClass_Thief:
            if (progressRatio >= 0.2) helmet = 1002; // Casco de lobo
            break;
        case eClass_Bard:
            if (progressRatio >= 0.5) helmet = 132; // Casco de hierro
            break;
        case eClass_Druid:
            if (progressRatio >= 0.1) helmet = 1001; // Casco de aguila
            if (progressRatio >= 0.3) helmet = 1002; // Casco de Lobo
            if (progressRatio >= 0.6) helmet = 1003; // Casco de Oso
            if (progressRatio >= 1) helmet = 1004; // Casco de tigre
            break;
        case eClass_Pirat:
            if (progressRatio >= 0.1) helmet = 1010; // Sombrero pirata
            break;
        case eClass_Worker:
        case eClass_None:
            break;
    }

    if (helmet > 0) {
        int Slot = addItem(UserIndex, helmet);
        UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
        UserList[UserIndex].Invent.CascoEqpSlot = Slot;
    }
}

vector<int> getValidArmors(int UserIndex) {
    vector<int> validArmors;
    string sMotivo;

    eClass UserClase = UserList[UserIndex].clase;
    bool noTunicas = UserClase == eClass_Assasin || UserClase == eClass_Paladin || UserClase == eClass_Warrior || 
        UserClase == eClass_Hunter || UserClase == eClass_Thief || UserClase == eClass_Pirat;

	for (int ObjIndex = 1; ObjIndex <= NumObjDatas; ++ObjIndex) {
        if (ObjData[ObjIndex].OBJType != eOBJType_otArmadura) {
            continue;
        }
        if (noTunicas && (ObjData[ObjIndex].Name.find("Tunica") != string::npos || ObjData[ObjIndex].Name.find("Túnica") != string::npos)) {
            continue;
        }
        if (ObjData[ObjIndex].Newbie == 1) {
            continue;
	    }
        if (ObjData[ObjIndex].Valor == 0) {
            continue;
        }
        if (ClasePuedeUsarItem(UserIndex, ObjIndex, sMotivo)
				&& SexoPuedeUsarItem(UserIndex, ObjIndex, sMotivo)
				&& CheckRazaUsaRopa(UserIndex, ObjIndex, sMotivo)
			    && FaccionPuedeUsarItem(UserIndex, ObjIndex, sMotivo)) {
            validArmors.push_back(ObjIndex);
        }
    }

    sort(validArmors.begin( ), validArmors.end( ), [ ]( int a, int b ){ return ObjData[a].Valor < ObjData[b].Valor; });
    unique(validArmors.begin( ), validArmors.end( ), [ ]( int a, int b ){ return ObjData[a].Name == ObjData[b].Name; });

    return validArmors;
}

void updateArmor(int UserIndex, double progressRatio) {
    vector<int> validArmors = getValidArmors(UserIndex);
    int armorIndex = validArmors.at(round((validArmors.size() - 1) * progressRatio));
    int Slot = addItem(UserIndex, armorIndex);

    UserList[UserIndex].Invent.Object[Slot].Equipped = 1;
    UserList[UserIndex].Invent.ArmourEqpSlot = Slot;
}

void updateInventory(int UserIndex) {
    int level = UserList[UserIndex].Stats.ELV;
    double progressRatio = (double)(level - STARTING_LEVEL) / (double)(MAX_REWARD_LEVEL - STARTING_LEVEL);
    if (progressRatio > 1) progressRatio = 1;

    emptyInventory(UserIndex);
    updatePotions(UserIndex);
    updateWeapons(UserIndex, progressRatio);
    updateArmor(UserIndex, progressRatio);
    updateShield(UserIndex, progressRatio);
    updateRing(UserIndex, progressRatio);
    updateHelmet(UserIndex, progressRatio);

    loadUserInventory(UserIndex);
    UpdateUserInv(true, UserIndex, 0);
    ChangeUserChar(UserIndex, UserList[UserIndex].Char.body, UserList[UserIndex].Char.Head,
		UserList[UserIndex].Char.heading, UserList[UserIndex].Char.WeaponAnim,
		UserList[UserIndex].Char.ShieldAnim, UserList[UserIndex].Char.CascoAnim);
}
