/* 
 * File:   StringToUpper.h
 * Author: nick
 *
 * Created on November 20, 2017, 11:52 AM
 */

#ifndef STRINGTOUPPER_H
#define STRINGTOUPPER_H

#include <string>

void strToUpper(string &lower)
{
    for (int i=0; i<lower.length(); ++i){
        lower[i] = toupper(lower[i]);
    }
}

#endif /* STRINGTOUPPER_H */

