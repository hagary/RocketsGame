//
//  constants.h
//  RocketsGame
//
//  Created by Hagar Yasser Omar on 10/15/16.
//  Copyright © 2016 Hagar Yasser Omar. All rights reserved.
//

#ifndef constants_h
#define constants_h


//rockets colors
 GLfloat playerColor[3]={64.0/255,9.0/255,71.0/255};
 GLfloat chaserColor[3]={25.0/255, 25.0/255, 112.0/255};
 GLfloat chasedColor[3]={0.6, 0.6, 0.6};

const int chaser1Vel =8;
const int chaser2Vel =4;

const int chased1Vel =8;
const int chased2Vel =10;

const int GAME_DURATION = 5; //in minutes

const int INITIAL_SCORE = 2000;

#endif /* constants_h */
