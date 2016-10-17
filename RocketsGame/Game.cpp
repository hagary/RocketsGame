//
//  Game.cpp
//  Graphics
//
//  Created by Hagar Yasser Omar on 10/14/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#include "Game.hpp"

/*
 -------------------
 SHADERS FILES
 -------------------
*/
GLchar* texVertexFile = "texturevert.vs";
GLchar* texFragmentFile = "texturefrag.fs";
GLchar* defaultVertexFile = "basicvert.vs";
GLchar* defaultFragmentFile = "basicfrag.fs";

// Shader objects
GLuint textureProg;
GLuint defaultProg;
GLint texSampler;

/*--------------------END--------------------*/

/*
 -------------------
 TEXTURES VARIABLES
 -------------------
 */
#define NO_TEXTURES 13
#define SPACE 0
#define EXIT 1
#define GAME_OVER_BG 2
#define GAME_START_BG 3
#define TIME_MODE 4
#define ONE_SHOT_MODE 5
#define SPECIAL_POWER_BG 6
#define DOUBLE_SCORE_BG 7
#define CHASER_STUN_BG 8
#define POWER_ACTIVE_BG 9
#define POWER_READY_BG 10
#define POWER_USED_BG 11
#define NOT_NOW_BG 12



// Texture indices
GLuint tex_ids[NO_TEXTURES];

// Texture files
char texture_files[NO_TEXTURES][30] = {"Resources/space.jpg","Resources/close-01.png","Resources/game-over.png","Resources/game-start.png","Resources/time-mode.png","Resources/oneshot-mode.png","Resources/special-power.png","Resources/double-score.png","Resources/chaser-stun.png", "Resources/active.png","Resources/ready.png","Resources/used.png", "Resources/not-now.png"};

/*--------------------END--------------------*/


#define EXIT_WIDTH 80
#define EXIT_HEIGHT 90

#define TIME_GAME 0
#define ONE_SHOT_GAME 1
#define GAME_OVER 2
#define GAME_START 3
#define SPECIAL_POWER 4

#define ACTIVE 0
#define READY 1
#define USED 2


Player *player;
Chaser *chaser1;
Chaser *chaser2;
Chased *chased1;
Chased *chased2;

/*
 -------------------------
 GAME STATUS VARIABLES
 -------------------------
 */
int game_mode;
int global_game_mode;
int score;
int score_factor;
int power_status;
long timeSinceStart;
/*--------------------END--------------------*/



ISoundEngine *SoundEngine;

/*
 -------------------------
 MAIN FUNCTIONS
 -------------------------
*/
int main(int argc, char** argr){
    init();
    run(argc, argr);
    return 0;
}

void init(){
    //initialize game objects
    player =  new Player(500,500,playerColor);
    chaser1 = new Chaser(100,100,chaserColor);
    chaser2 = new Chaser(800,100, chaserColor);
    chased1 = new Chased(250,250,chasedColor);
    chased2 = new Chased(750,250, chasedColor);
    
    //initialize chaser&chased velocities
    chaser1->vel=chaser1Vel;
    chaser2->vel=chaser2Vel;
    chased1->vel=chased1Vel;
    chased2->vel=chased2Vel;
    
    //initialize game mode
    game_mode = GAME_START;
    power_status = READY;
    score_factor = 1;
    
    //initialize sound engine
   SoundEngine = createIrrKlangDevice();

}

void run(int argc, char** argr){
    glutInit(&argc, argr);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024,720);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Catch Me");
    glutFullScreen();
    glutDisplayFunc(display);
    glClearColor(1.0f,0.0f,0.0f,0.0f);
    glutPassiveMotionFunc(passM);
    glutMouseFunc(mouseClicks);
    glutGet(GLUT_ELAPSED_TIME);
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
    
    
    //play track
    SoundEngine->play2D("Resources/breakout.mp3", GL_TRUE);
    
    //start the display
    glutMainLoop();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    drawExit();
    
    if(game_mode==TIME_GAME || game_mode==ONE_SHOT_GAME)
        drawGame();
    if(game_mode==GAME_OVER)
        drawGameOver();
    if(game_mode==GAME_START)
        drawGameStart();
    if(game_mode==SPECIAL_POWER)
        drawSpecialPower();
    glFlush();
    // Swap buffers
    glutSwapBuffers();
    
}
/*--------------------END--------------------*/


/*
 -------------------------
 DRAW FUNCTIONS
 -------------------------
*/
void drawGameStart(){
    drawOptions(TIME_MODE, ONE_SHOT_MODE);
    drawBackground(GAME_START_BG);
}

void drawSpecialPower(){
    drawOptions(DOUBLE_SCORE_BG, CHASER_STUN_BG);
    drawNotNowOption();
    drawBackground(SPECIAL_POWER_BG);
}
void drawNotNowOption(){
    glPushMatrix();
    // TODO: Bind  texture
    // Activate shader program
    glUseProgram(textureProg);
    glUniform1i(texSampler,0);
    
    glBindTexture(GL_TEXTURE_2D,tex_ids[NOT_NOW_BG]);
    
    // TODO: Draw space background with texture coordinates
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f,0.0f);    glVertex3f(750,570,0);
    glTexCoord2f(1.0f,0.0f);    glVertex3f(950,570,0);
    glTexCoord2f(1.0f,1.0f);    glVertex3f(950,650,0);
    glTexCoord2f(0.0f,1.0f);    glVertex3f(750,650,0);
    glEnd();
    glPopMatrix();
}

void drawOptions(int option1, int option2){
    /*
     ----------------------
     DRAW OPTION 1: TIME MODE OR DOUBLE SCORE
     ----------------------
     */
    glPushMatrix();
    // TODO: Bind space texture
    // Activate shader program
    glUseProgram(textureProg);
    glUniform1i(texSampler,0);
    
    glBindTexture(GL_TEXTURE_2D,tex_ids[option1]);
    
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f,0.0f);    glVertex3f(150,300,0);
    glTexCoord2f(1.0f,0.0f);    glVertex3f(350,300,0);
    glTexCoord2f(1.0f,1.0f);    glVertex3f(350,500,0);
    glTexCoord2f(0.0f,1.0f);    glVertex3f(150,500,0);
    glEnd();
    glPopMatrix();
    
    /*
     -----END-----
     */
    
    
    /*
     ----------------------
     DRAW OPTION 2: ONE SHOT OR CHASER STUN
     ----------------------
     */
    glPushMatrix();
    // TODO: Bind space texture
    // Activate shader program
    glUseProgram(textureProg);
    glUniform1i(texSampler,0);
    
    glBindTexture(GL_TEXTURE_2D,tex_ids[option2]);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f,0.0f);    glVertex3f(650,300,0);
    glTexCoord2f(1.0f,0.0f);    glVertex3f(850,300,0);
    glTexCoord2f(1.0f,1.0f);    glVertex3f(850,500,0);
    glTexCoord2f(0.0f,1.0f);    glVertex3f(650,500,0);
    glEnd();
    glPopMatrix();
    
    /*
     -----END-----
     */
}

void drawGame(){
    glUseProgram(defaultProg);
    drawRocket(player);
    drawRocket(chaser1);
    drawRocket(chaser2);
    drawRocket(chased1);
    drawRocket(chased2);
    
    drawTime();
    drawScore();
    drawPowerStatus();
    
    drawBackground(SPACE);
}

void drawTime(){
    /*----- Display Time Elapsed -------------------
     */
    glUseProgram(0);
    long totalSecs = long((glutGet(GLUT_ELAPSED_TIME)-timeSinceStart)/1000);
    int secsCount = totalSecs%60;
    int minsCount = int(totalSecs/60);
    if(totalSecs == 30){ //30 secs passed since game start
        game_mode = SPECIAL_POWER;
        return;
    }
    if(minsCount == GAME_DURATION)
    {
        game_mode = GAME_OVER;
        //        glutPostRedisplay();
        return;
    }
    std::string secs = std:: to_string(secsCount);
    std::string mins = std:: to_string(minsCount);
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
    std::string playerScore= "SCORE "+ std:: to_string(score);
    
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
    drawScore();
    drawBackground(GAME_OVER_BG);
    
}

void drawBackground(int bg){
    // Draw textured quad
    glPushMatrix();
    // TODO: Bind space texture
    // Activate shader program
    glUseProgram(textureProg);
    glUniform1i(texSampler,0);
    
    glBindTexture(GL_TEXTURE_2D,tex_ids[bg]);
    
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

void drawPowerStatus(){
    int texture;
    if(power_status == ACTIVE)
        texture = POWER_ACTIVE_BG;
    else
        if(power_status == READY)
            texture = POWER_READY_BG;
        else
            texture = POWER_USED_BG;
    
    glPushMatrix();
    // TODO: Bind  texture
    // Activate shader program
    glUseProgram(textureProg);
    glUniform1i(texSampler,0);
    
    glBindTexture(GL_TEXTURE_2D,tex_ids[texture]);
    
    // TODO: Draw space background with texture coordinates
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f,0.0f);    glVertex3f(600,650,0);
    glTexCoord2f(1.0f,0.0f);    glVertex3f(720,650,0);
    glTexCoord2f(1.0f,1.0f);    glVertex3f(720,700,0);
    glTexCoord2f(0.0f,1.0f);    glVertex3f(600,700,0);
    glEnd();
    glPopMatrix();
}

/*--------------------END--------------------*/


/*
 ----------------------------
 CONTROL FUNCTIONS
 ----------------------------
*/

/*
 -----------HELPER FUNCTIONS----------------
*/
void modifyPowerStatus(int new_status){
    power_status = new_status;
}
void resetScoreFactor(int val){
    score_factor=1;
    modifyPowerStatus(USED);

}
void resetChaserVel(int val){
    chaser1->vel = chaser1Vel;
    chaser2->vel = chaser2Vel;
    modifyPowerStatus(USED);
}
void testOptionClicked(int mouseX, int mouseY){
    if(mouseX>150 && mouseX<350 && mouseY>300 && mouseY<500){
        if(game_mode==GAME_START)
        {
            game_mode = TIME_GAME;
            global_game_mode = TIME_GAME;
            score=2000;
            timeSinceStart=glutGet(GLUT_ELAPSED_TIME);
            return;
        }
        if(game_mode==SPECIAL_POWER)
        {
            //DOUBLE SCORE OPTION CLICKED
            score_factor=2;
            modifyPowerStatus(ACTIVE);
            game_mode = global_game_mode;
            glutTimerFunc(30*1000, resetScoreFactor, 0);
            return;
        }
    }
    if(mouseX>650 && mouseX<850 && mouseY>300 && mouseY<500){
        if(game_mode==GAME_START)
        {
            timeSinceStart=glutGet(GLUT_ELAPSED_TIME);
            score=0;
            game_mode=ONE_SHOT_GAME;
            global_game_mode = ONE_SHOT_GAME;
            return;
        }
        if(game_mode==SPECIAL_POWER)
        {
            //CHASER STUN OPTION CLICKED
            chaser1->vel = 0;
            chaser2->vel = 0;
            modifyPowerStatus(ACTIVE);
            game_mode = global_game_mode;
            glutTimerFunc(30*1000, resetChaserVel, 0);
            return;
            
        }
    }
}
void testExitClicked(int mouseX, int mouseY){
    if(mouseX<EXIT_WIDTH && mouseY> 720 - EXIT_HEIGHT){
        //click within exit button
        printf("exit requested \n");
        exit(0);
    }
    
}
void testTouch(){
    if(fabs(chased1->x - player->x )<= 1*rocketScaleX && fabs(chased1->y-player->y)<=2*rocketScaleY){
        SoundEngine->play2D("Resources/ding.wav", false);
        score+=(score_factor*10);
    }
    if(fabs(chased2->x - player->x )<= 1*rocketScaleX && fabs(chased2->y-player->y)<=2*rocketScaleY){
        SoundEngine->play2D("Resources/ding.wav", false);
        score+=(score_factor*10);
    }
    
    if(fabs(chaser1->x - player->x )<= 1*rocketScaleX && fabs(chaser1->y-player->y)<=2*rocketScaleY){
        
        if(game_mode==TIME_GAME)
        {
            SoundEngine->play2D("Resources/smash.mp3", false);
            score-=(score_factor*10);
        }
        else
        {
            game_mode=GAME_OVER;
            return;
        }
    }
    if(fabs(chaser2->x - player->x )<= 1*rocketScaleX && fabs(chaser2->y-player->y)<=2*rocketScaleY){
        if(game_mode==TIME_GAME)
        {
            SoundEngine->play2D("Resources/smash.mp3", false);
            score-=(score_factor*10);
        }
        else
        {
            game_mode=GAME_OVER;
            return;
        }
    }
}
void testPowerClicked(int mouseX, int mouseY){
    if(mouseX>600 && mouseX<720 && mouseY>650 && mouseY<700){
        game_mode = SPECIAL_POWER;
        return;
    }
}

void testNotNowClicked(int mouseX, int mouseY){
    if(mouseX>750 && mouseX<950 && mouseY>570 && mouseY<650){
        game_mode = global_game_mode;
        return;
    }
}

/*
 -----------INVOKED FUNCTIONS----------------
 */
void passM(int mouseX,int mouseY)
{
    if(game_mode==TIME_GAME || game_mode==ONE_SHOT_GAME){
        
        double winH =glutGet(GLUT_WINDOW_HEIGHT);
        double winW =glutGet(GLUT_WINDOW_WIDTH);
        mouseX  = mouseX/winW*1024;
        mouseY= 720 - (mouseY/winH*720);
        player->rotate(mouseX, mouseY);
        player->translate(mouseX, mouseY);
        chaser1->translate(player->x, player->y);
        chaser1->rotate(player->x, player->y);
        chaser2->translate(player->x, player->y);
        chaser2->rotate(player->x, player->y);
        chased1->translate(player->x, player->y);
        chased1->rotate(player->x, player->y);
        chased2->translate(player->x, player->y);
        chased2->rotate(player->x, player->y);

        //    translateChased();
        glutPostRedisplay();
        
    }
}
void mouseClicks(int button, int state, int mouseX, int mouseY){
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        /* Readjust coordinate system */
        double winH =glutGet(GLUT_WINDOW_HEIGHT);
        double winW =glutGet(GLUT_WINDOW_WIDTH);
        mouseX  = mouseX/winW*1024;
        mouseY= 720 - mouseY/winH*720;
        
        testExitClicked(mouseX, mouseY);
        
        if(game_mode==GAME_START || game_mode==SPECIAL_POWER){
            testOptionClicked(mouseX,mouseY);
            if(game_mode==SPECIAL_POWER)
                testNotNowClicked(mouseX, mouseY);
        }
        if(power_status == READY && (game_mode == TIME_GAME || game_mode == ONE_SHOT_GAME))
            testPowerClicked(mouseX, mouseY);
        
    }
}

void anim(){
    if(game_mode==TIME_GAME || game_mode==ONE_SHOT_GAME){
        chaser1->translate(player->x, player->y);
        chaser2->translate(player->x, player->y);
        chased1->translate(player->x, player->y);
        chased2->translate(player->x, player->y);
        testTouch();
    }
    glutPostRedisplay();
}

/*--------------------END--------------------*/


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

/*--------------------END--------------------*/




