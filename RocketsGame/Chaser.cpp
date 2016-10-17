//
//  Chaser.cpp
//  Graphics
//
//  Created by Hagar Yasser Omar on 10/14/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#include "Chaser.hpp"
#include <iostream>

void Chaser::translate(double playerX, double playerY){
    double changeX = playerX - x;
    double changeY = playerY - y;
    double magnitude = sqrt(changeX*changeX + changeY*changeY);
    if(magnitude!=0){
        double advanceX = changeX /magnitude;
        double advanceY = changeY/magnitude;
        x+=vel*advanceX;
        y+=vel*advanceY;
    }
}

void Chaser::rotate(double playerX, double playerY){
    double changeX = playerX - x;
    double changeY = playerY - y;
    double angle = atan2(changeY,changeX);
    rotation = -90 + (angle*180/M_PI);
}