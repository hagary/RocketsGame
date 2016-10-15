//
//  Player.hpp
//  Graphics
//
//  Created by Hagar Yasser Omar on 10/14/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <stdio.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "Rocket.hpp"

class Player : public Rocket{
public:
    using Rocket::Rocket;
    void translate(double , double);
    
};

#endif /* Player_hpp */
