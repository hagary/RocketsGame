//
//  Player.cpp
//  Graphics
//
//  Created by Hagar Yasser Omar on 10/14/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#include "Player.hpp"
void Player::translate(double mouseX, double mouseY){
    this->x = mouseX;
    this->y = mouseY;
}

void Player::rotate(double mouseX, double mouseY){
    double changeX = mouseX - x;
    double changeY = mouseY - y;
    double angle = atan2(changeY,changeX);
    rotation = -90 + (angle*180/M_PI);
}