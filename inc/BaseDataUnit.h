//
// Created by mariussolomes on 20/07/19.
//

#ifndef KERASTOCPP_BASEDATAUNIT_H
#define KERASTOCPP_BASEDATAUNIT_H

#include <vector>
#include <assert.h>
#include <string>

#include "Matrix4D.h"
using namespace std;


class BaseDataUnit{
public:
    BaseDataUnit(array4d input, string name);

    virtual array4d forward()=0;

    array4d data;
private:
    array4d input;
};

#endif //KERASTOCPP_BASEDATAUNIT_H
