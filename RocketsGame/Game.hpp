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

void run(int , char** );
void display();
void anim();
void init();
void passM(int, int);
void mouseClicks(int, int, int, int);
bool load_textures();
void drawBackground();
void drawExit();
void drawTime();
void drawGameOver();
void drawScore();
void testExitClicked(int , int );
void drawRocket(Rocket*);
void drawTimeGame();
#endif /* Game_hpp */
