//
// Created by horacio on 3/12/17.
//

#ifndef DAKARASERVER_DOTIO_H
#define DAKARASERVER_DOTIO_H


class DotIO {
public:
    DotIO(int UserIndex, const std::string &Name, eRaza UserRaza, eGenero UserSexo,
                   eClass UserClase,
                   const std::string &UserEmail,
                   eCiudad Hogar, int Head);

    void setupUser();

private:

    void loadUserHechizos();

    void loadUserStats();

    void loadUserReputacion();


    void loadUserFlags();

    void loadUserIni();

    void updateUserPosition();
    void updateUserLevel();

    void addSpell(int number);

    int UserIndex;
    std::string Name;
    eRaza UserRaza;
    eGenero UserSexo;
    eClass UserClase;
    std::string UserEmail;
    eCiudad Hogar;
    int Head;
};


#endif //DAKARASERVER_DOTIO_H
