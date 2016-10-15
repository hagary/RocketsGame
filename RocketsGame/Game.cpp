//
//  Game.cpp
//  Graphics
//
//  Created by Hagar Yasser Omar on 10/14/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#include "Game.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <SOIL/SOIL.h>
// Shader file utility functions
#include "shaderutils.h"
#include "constants.h"


// Shader files
GLchar* texVertexFile = "texturevert.vs";
GLchar* texFragmentFile = "texturefrag.fs";
GLchar* defaultVertexFile = "basicvert.vs";
GLchar* defaultFragmentFile = "basicfrag.fs";

// Shader objects
GLuint textureProg;
GLuint defaultProg;
GLint texSampler;

// Texture constants
#define NO_TEXTURES 3
#define SPACE 0
#define EXIT 1
#define GAME_OVER 3

#define EXIT_WIDTH 80
#define EXIT_HEIGHT 90



#define TIME_GAME 0
#define ONE_SHOT_GAME 1
#define GAME_OVER 2
#define GAME_START 3
#define SPECIAL_POWER 4

int game_mode=TIME_GAME;

// Texture indices
GLuint tex_ids[NO_TEXTURES];

// Texture files
char texture_files[NO_TEXTURES][30] = {"Resources/space.jpg","Resources/close-01.png","Resources/game-over.png"};

//Game *Game::game = NULL;
Player *player =  new Player(500,500,playerColor);
Chaser *chaser1 = new Chaser(100,100,chaserColor);
Chaser *chaser2 = new Chaser(800,100, chaserColor);
Chased *chased1 = new Chased(250,250,chasedColor);
Chased *chased2 = new Chased(750,250, chasedColor);

int score = INITIAL_SCORE;

#include <irrklang/irrKlang.h>
using namespace irrklang;

ISoundEngine *SoundEngine = createIrrKlangDevice();

int main(int argc, char** argr){
    init();
    run(argc, argr);
    return 0;
}
void init(){
    chaser1->vel=chaser1Vel;
    chaser2->vel=chaser2Vel;
    
    chased1->vel=chased1Vel;
    chased2->vel=chased2Vel;
}

void run(int argc, char** argr){
    glutInit(&argc, argr);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    // Set the window size to image size
    glutInitWindowSize(1024,720);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Catch Me");
    glutFullScreen();
    glutDisplayFunc(display);
    // Set background color to black (...outer space!)
    glClearColor(1.0f,0.0f,0.0f,0.0f);
    glutPassiveMotionFunc(passM);
    glutMouseFunc(mouseClicks);
    
    glutIdleFunc(anim);
    gluOrtho2D(0.0, 1024, 0.0, 720);
    // Set shading model
    glEnable(GL_DEPTH_TEST);
    // Load textures
    if (!load_textures())
    {   printf("failed to load image\n");
        exit(0);
    }
    // Load shader programs
    textureProg = load_shaders(texVertexFile,texFragmentFile);
    defaultProg = load_shaders(defaultVertexFile,defaultFragmentFile);
    
    // Associate and assign sampler parameter
    texSampler = glGetUniformLocation(textureProg,"texMap");
    SoundEngine->play2D("Resources/breakout.mp3", GL_TRUE);
    
    glutMainLoop();
}

void display(){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(game_mode==TIME_GAME)
        drawTimeGame();
    if(game_mode==GAME_OVER)
        drawGameOver();
    
    glFlush();
    // Swap buffers
    glutSwapBuffers();
    
}
void drawTimeGame(){
    glUseProgram(defaultProg);
    drawRocket(player);
    drawRocket(chaser1);
    drawRocket(chaser2);
    drawRocket(chased1);
    drawRocket(chased2);
    
    drawExit();
    
    drawTime();
    drawScore();
    
    drawBackground();
}
void drawTime(){
    /*----- Display Time Elapsed -------------------
     */
    glUseProgram(0);
    int totalSecs =int(glutGet(GLUT_ELAPSED_TIME)/1000);
    std::string secs= std:: to_string(totalSecs%60);
    std::string mins=std:: to_string(int(totalSecs/60));
    if(mins == GAME_DURATION)
    {
        game_mode=GAME_OVER;
//        glutPostRedisplay();
        return;
    }
    std::string time = mins +" : "+ secs;
    glColor3f(1.0f,1.0f,1.0f);
    glPushMatrix();
    
    glRasterPos2f(150, 660);
    for (unsigned int i = 0; i<time.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, time[i]);
    }
    glPopMatrix();
}

void drawScore(){
    /*----- Display Player Score -------------------
     */
    
    //calculate
    std::string playerScore= std:: to_string(score);
    
    //display
    glUseProgram(0);
    glColor3f(1.0f,1.0f,1.0f);
    glPushMatrix();
    glRasterPos2f(900, 660);
    for (unsigned int i = 0; i<playerScore.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, playerScore[i]);
    }
    glPopMatrix();
}
void drawRocket(Rocket* r){
    glPushMatrix();
    r->transform();
    r->drawRocket();
    glPopMatrix();
}

void drawExit(){
    // Draw textured quad
    glPushMatrix();
    // TODO: Bind space texture
    // Activate shader program
    glUseProgram(textureProg);
    glUniform1i(texSampler,0);
    
    glBindTexture(GL_TEXTURE_2D,tex_ids[EXIT]);
    
    // TODO: Draw space background with texture coordinates
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f,0.0f);    glVertex3f(10,720-EXIT_HEIGHT-10,0);
    glTexCoord2f(1.0f,0.0f);    glVertex3f(EXIT_WIDTH+10,720-EXIT_HEIGHT-10,0);
    glTexCoord2f(1.0f,1.0f);    glVertex3f(EXIT_WIDTH+10,720-10,0);
    glTexCoord2f(0.0f,1.0f);    glVertex3f(10,720-10,0);
    glEnd();
    glPopMatrix();
    
}
void drawGameOver(){
    drawExit();
    drawScore();
    // Draw textured quad
    glPushMatrix();
    // TODO: Bind space texture
    // Activate shader program
    glUseProgram(textureProg);
    glUniform1i(texSampler,0);
    
    glBindTexture(GL_TEXTURE_2D,tex_ids[GAME_OVER]);
    
    // TODO: Draw space background with texture coordinates
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0,0,0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(1024,0,0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(1024,720,0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0,720,0);
    glEnd();
    glPopMatrix();
    
}

void drawBackground(){
    // Draw textured quad
    glPushMatrix();
    // TODO: Bind space texture
    // Activate shader program
    glUseProgram(textureProg);
    glUniform1i(texSampler,0);
    
    glBindTexture(GL_TEXTURE_2D,tex_ids[SPACE]);
    
    // TODO: Draw space background with texture coordinates
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0,0,0);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(1024,0,0);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(1024,720,0);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0,720,0);
    glEnd();
    glPopMatrix();
    
}
void passM(int mouseX,int mouseY)
{
    if(game_mode==TIME_GAME){
        
        double winH =glutGet(GLUT_WINDOW_HEIGHT);
        double winW =glutGet(GLUT_WINDOW_WIDTH);
        mouseX  = mouseX/winW*1024;
        mouseY= mouseY/winH*720;
        //    rotateRocket(updatedX, updatedY);
        player->translate(mouseX, mouseY);
        chaser1->translate(player->x, player->y);
        chaser2->translate(player->x, player->y);
        chased1->translate(player->x, player->y);
        chased2->translate(player->x, player->y);
        //    translateChased();
        glutPostRedisplay();
        
    }
}

void mouseClicks(int button, int state, int mouseX, int mouseY){
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        testExitClicked(mouseX, mouseY);
    }
}

void testExitClicked(int mouseX, int mouseY){
    
    double winH =glutGet(GLUT_WINDOW_HEIGHT);
    double winW =glutGet(GLUT_WINDOW_WIDTH);
    mouseX  = mouseX/winW*1024;
    mouseY= 720 - mouseY/winH*720;
    
    if(mouseX<EXIT_WIDTH && mouseY> 720 - EXIT_HEIGHT){
        //click within exit button
        printf("exit requested \n");
        exit(0);
    }
    
}
void testTouch(){
    if(fabs(chased1->x - player->x )<= 1*rocketScaleX && fabs(chased1->y-player->y)<=2*rocketScaleY){
        SoundEngine->play2D("Resources/ding.wav", false);
        score+=10;
    }
    if(fabs(chased2->x - player->x )<= 1*rocketScaleX && fabs(chased2->y-player->y)<=2*rocketScaleY){
        SoundEngine->play2D("Resources/ding.wav", false);
        score+=10;
    }
    
    if(fabs(chaser1->x - player->x )<= 1*rocketScaleX && fabs(chaser1->y-player->y)<=2*rocketScaleY){
        SoundEngine->play2D("Resources/smash.mp3", false);
        score-=10;
    }
    if(fabs(chaser2->x - player->x )<= 1*rocketScaleX && fabs(chaser2->y-player->y)<=2*rocketScaleY){
        SoundEngine->play2D("Resources/smash.mp3", false);
        score-=10;
    }
    
}
void anim(){
    if(game_mode==TIME_GAME){
        chaser1->translate(player->x, player->y);
        chaser2->translate(player->x, player->y);
        testTouch();
    }
    glutPostRedisplay();
}

/*
 
 ----------------------------
 TEXTURES PART
 ----------------------------
 
 */

// Routine to load textures using SOIL
bool load_textures()
{
    for (int i=0; i < NO_TEXTURES; i++)
    {
        // TODO: Load images
        tex_ids[i] = SOIL_load_OGL_texture(texture_files[i],SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
        
        
        // Set texture properties if successfully loaded
        if (tex_ids[i] != 0)
        {
            // TODO: Set scaling filters
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
            
            // TODO: Set wrapping modes
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        }
        // Otherwise texture failed to load
        else
        {
            return false;
        }
    }
    return true;
}





