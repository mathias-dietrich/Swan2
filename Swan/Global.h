//
//  Global.h
//  Swan
//
//  Created by Mathias Dietrich on 28.10.20.
//

#pragma once

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>
#include <cstdlib>
#include<fstream>

using namespace std;

extern ofstream myfile;

