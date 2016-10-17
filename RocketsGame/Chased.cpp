//
//  Chased.cpp
//  Graphics
//
//  Created by Hagar Yasser Omar on 10/14/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#include "Chased.hpp"
void Chased::translate(double playerX, double playerY){
    double changeX = playerX - this->x;
    double changeY = playerY - this->y;
    double magnitude = sqrt(changeX*changeX + changeY*changeY);
    if(magnitude!=0){
        double advanceX = changeX /magnitude;
        double advanceY = changeY/magnitude;
        double newChasedX= x-vel*advanceX;
        double newChasedY= y-vel*advanceY;
        if (newChasedX <0 || newChasedX >1024 || newChasedY<0 || newChasedY>720)
        //out of screen
        {
            x = initialX;
            y = initialY;
        }
        else
        {
            x = newChasedX;
            y = newChasedY;
        }
        
    }
}
void Chased::rotate(double playerX, double playerY){
    double changeX = playerX - x;
    double changeY = playerY - y;
    double angle = atan2(changeY,changeX);
    rotation =180+( -90 + (angle*180/M_PI));
}