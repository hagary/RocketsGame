//
//  Game.hpp
//  Graphics
//
//  Created by Hagar Yasser Omar on 10/14/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <GLUT/glut.h>
#include "Player.hpp"
#include "Chased.hpp"
#include "Chaser.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <SOIL/SOIL.h>
// Shader file utility functions
#include "shaderutils.h"
#include "constants.h"
#include <irrklang/irrKlang.h>
using namespace irrklang;

void run(int , char** );
void display();
void anim();
void init();
void passM(int, int);
void mouseClicks(int, int, int, int);
bool load_textures();
void drawBackground(int);
void drawExit();
void drawGameStart();
void drawTime();
void drawGameOver();
void drawSpecialPower();
void drawOptions(int option1, int option2);
void drawScore();
void drawNotNowOption();
void testExitClicked(int , int );
void testOptionClicked(int , int );
void drawRocket(Rocket*);
void drawGame();
void drawPowerStatus();
#endif /* Game_hpp */
