//
//  main.cpp
//  WaterJug_A*
//
//  Created by Liza Girsova on 10/22/14.
//  Copyright (c) 2014 CMSC470. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include "Domain.h"
#include "AStar.h"

using namespace std;

int main(int argc, const char * argv[])
{

    Domain d;
    AStar newAStar;
    newAStar.runAStar(d, NULL, NULL);
    return 0;
}

