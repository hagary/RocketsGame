//
//  Rocket.hpp
//  Graphics
//
//  Created by Hagar Yasser Omar on 10/14/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#ifndef Rocket_hpp
#define Rocket_hpp

#include <stdio.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

const int rocketScaleX = 40;
const int rocketScaleY = 30;
class Rocket{
public:

    Rocket(double,double,GLfloat[3]);
    double x;
    double y;
    double initialX;
    double initialY;
    double rotation;
    double scaleX;
    double scaleY;
    GLfloat color[3];
    void drawUpperTriangle();
    void drawMainRectangle();
    void drawInsideRectangle();
    void drawLowerRectangle();
    void drawSideTriangle(int);
    void drawRocket();
    void transform();
    void rotate(double,double);

};
#endif /* Rocket_hpp */
