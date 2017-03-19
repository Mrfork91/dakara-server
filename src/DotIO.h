//
// Created by horacio on 3/12/17.
//

#ifndef DAKARASERVER_DOTIO_H
#define DAKARASERVER_DOTIO_H


class DotIO {
public:
    static void
    setupUser(int userIndex, const std::string &Name, eRaza UserRaza, eGenero UserSexo, eClass UserClase,
              const std::string &UserEmail,
              eCiudad Hogar, int Head);

private:
    static void
    loadUserStats(int UserIndex, const std::string &Name, eRaza UserRaza, eGenero UserSexo, eClass UserClase,
                  const std::string &UserEmail,
                  eCiudad Hogar, int Head);

    static void loadUserReputacion(int userIndex);


    static void loadUserFlags(int UserIndex);

    static void loadUserIni(int UserIndex, const std::string &Name, eRaza UserRaza, eGenero UserSexo, eClass UserClase,
                            const std::string &UserEmail,
                            eCiudad Hogar, int Head);

    static void
    loadUserInventoryItems(int UserIndex, const std::string &Name, eRaza UserRaza, eGenero UserSexo, eClass UserClase,
                           const std::string &UserEmail,
                           eCiudad Hogar, int Head);

    static void
    loadUserInventory(int UserIndex, const std::string &Name, eRaza UserRaza, eGenero UserSexo, eClass UserClase,
                      const std::string &UserEmail,
                      eCiudad Hogar, int Head);

    static void loadUserPosition(int UserIndex);
};


#endif //DAKARASERVER_DOTIO_H
