//
// Created by horacio on 3/19/17.
//

#ifndef DAKARASERVER_DOTIOCHARINITIALIZER_H
#define DAKARASERVER_DOTIOCHARINITIALIZER_H


class DotIOInventory {
public:

    DotIOInventory(int UserIndex, const std::string &Name, eRaza UserRaza, eGenero UserSexo,
                   eClass UserClase,
                   const std::string &UserEmail,
                   eCiudad Hogar, int Head);

    void initializeInventory();

private:
    int getFirstFreeSlotNumber();

    int addItem(int item);

    void setPotions();

    void setWeapon();

    void setHelmet();

    void setArmor();

    bool esAlto();
    int UserIndex;
    std::string Name;
    eRaza UserRaza;
    eGenero UserSexo;
    eClass UserClase;
    std::string UserEmail;
    eCiudad Hogar;
    int Head;
};


#endif //DAKARASERVER_DOTIOCHARINITIALIZER_H
