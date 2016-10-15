//
//  Chased.hpp
//  Graphics
//
//  Created by Hagar Yasser Omar on 10/14/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#ifndef Chased_hpp
#define Chased_hpp

#include <stdio.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "Rocket.hpp"

class Chased : public Rocket{
public:
    using Rocket::Rocket;
    double vel;
    void translate(double, double);
};

#endif /* Chased_hpp */
