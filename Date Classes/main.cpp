//
//  main.cpp
//  Date Classes
//
//  Created by Sami ur Rahman Qazi on 14/02/2013.
//  Copyright (c) 2013 Sami ur Rahman Qazi. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include "GregorianDate.h"
#include "HijriDate.h"

using namespace std;

int main (int argc, char * const argv[])
{
//  HijriDate hdate(1, 1, 1);
    GregorianDate gdate(15, 10, 1962);
    int jdn = gdate;
    HijriDate hdate(jdn);
    
    cout << "islamic date: " << hdate << "\n";
    cout << "gregorian date: " << gdate << "\n";
    cout << "absolute date: " << jdn << "\n";
    gdate.calendar();
    
//  cout << "Julian day number for " << gdate << " " << jdn << endl;
    
    return 0;
}
