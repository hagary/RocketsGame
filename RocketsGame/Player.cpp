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