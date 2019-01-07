#ifndef SCORE_H
#define SCORE_H

#include "rtc.h"
#include <stdio.h>


typedef struct 
{
    int scoreOne;
    char * scoreOneDate;
    int scoreTwo;
    char * scoreTwoDate;
    int scoreThree;
    char * scoreThreeDate;
    int scoreFour;
    char * scoreFourDate;
    int scoreFive;
    char * scoreFiveDate;

} Scores;

void loadScores();

void saveScores();

void addNewScore(int score);



#endif
