//
// Created by cthomasset on 16/02/19.
//

#include "Test.h"

Test::Test(int a) : a(a) {

}

int Test::add(int b){
    return a += b;
}