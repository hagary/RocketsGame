//
//  Rocket.cpp
//  Graphics
//
//  Created by Hagar Yasser Omar on 10/14/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#include "Rocket.hpp"


Rocket::Rocket(double x, double y,GLfloat rocketColor[3] ){
    initialX = x;
    initialY = y;
    this->x = x;
    this->y = y;
    scaleX = rocketScaleX;
    scaleY =rocketScaleY;
    color[0]= rocketColor[0];
    color[1]= rocketColor[1];
    color[2]=rocketColor[2];
}
void Rocket::transform(){
    glTranslated(x,y,0);
    //    glRotated(rotation, 0, 0, 1);
}
void Rocket::rotate(double mouseX, double mouseY){
    double changeX = mouseX - x;
    double changeY = mouseY - y;
    double magnitude = sqrt(changeX*changeX + changeY*changeY);
    double angle = atan2(changeY/magnitude, changeX/magnitude)*(180/M_PI);
    rotation = angle -90;
}
void Rocket::drawRocket(){
    glScaled(this->scaleX, this->scaleY, 1);
    glTranslated(0,1.5,0);
    glColor3f(105.0/255, 105.0/255,105.0/255);
    drawInsideRectangle();
    glColor3f(color[0],color[1],color[2]);
    drawUpperTriangle();
    drawMainRectangle();
//    glColor3f(0.0, 0.0, 0.0);
    drawLowerRectangle();
    drawSideTriangle(-1);   //left one
    drawSideTriangle(1);    //right one
    
    //draw border
    glColor3f(105.0/255, 105.0/255,105.0/255);
    glLineWidth(8);
    glBegin(GL_LINES);
    glVertex3f(-0.5, 0.0, 0.0);
    glVertex3f(0, sqrt(3)/2.0, 0.0);
    glVertex3f(0, sqrt(3)/2.0, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.5, -2, 0.0);
    glVertex3f(0.5, -2, 0.0);
    glVertex3f(1, -3, 0.0);
    glVertex3f(1, -3, 0.0);
    glVertex3f(0.5, -3, 0.0);
    glVertex3f(0.5, -3, 0.0);
    glVertex3f(0.5, -3.5, 0.0);
    glVertex3f(0.5, -3.5, 0.0);
    glVertex3f(-0.5, -3.5, 0.0);
    glVertex3f(-0.5, -3.5, 0.0);
    glVertex3f(-0.5, -3, 0.0);
    glVertex3f(-0.5, -3, 0.0);
    glVertex3f(-1, -3, 0.0);
    glVertex3f(-1, -3, 0.0);
    glVertex3f(-0.5, -2, 0.0);
    glVertex3f(-0.5, -2, 0.0);
    glVertex3f(-0.5, 0.0, 0.0);
    glEnd();

}
void Rocket::drawUpperTriangle(){
    //upper equilateral triangle
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, 0.0, 0.0);
    glVertex3f(0, sqrt(3)/2.0, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glEnd();
}

void Rocket::drawMainRectangle(){
    //main rectangle
    glBegin(GL_POLYGON);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.5, -3, 0.0);
    glVertex3f(-0.5, -3, 0.0);
    glVertex3f(-0.5, 0.0, 0.0);
    glEnd();
}

void Rocket::drawInsideRectangle(){
    glBegin(GL_POLYGON);
    glVertex3f(-0.25, -0.5, 0.0);
    glVertex3f(0.25, -0.5, 0.0);
    glVertex3f(0.25, -1.5, 0.0);
    glVertex3f(-0.25, -1.5, 0.0);
    glEnd();
}

void Rocket::drawLowerRectangle(){
    //lower rectangle
    glBegin(GL_POLYGON);
    glVertex3f(0.5, -3, 0.0);
    glVertex3f(0.5, -3.5, 0.0);
    glVertex3f(-0.5, -3.5, 0.0);
    glVertex3f(-0.5, -3, 0.0);
    glEnd();
}

void Rocket::drawSideTriangle(int side){
    glBegin(GL_POLYGON);
    glVertex3f(side*0.5, -3, 0.0);
    glVertex3f(side*1, -3, 0.0);
    glVertex3f(side*0.5, -2, 0.0);
    glEnd();
}


