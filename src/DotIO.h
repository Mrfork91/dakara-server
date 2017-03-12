//
// Created by horacio on 3/12/17.
//

#ifndef DAKARASERVER_DOTIO_H
#define DAKARASERVER_DOTIO_H


class DotIO {
public:
    static void setupUser(int userIndex);
private:
    static void loadUserInit(int userIndex);
    static void loadUserStats(int userIndex);
    static void loadUserReputacion(int userIndex);
};


#endif //DAKARASERVER_DOTIO_H
