#include <lcom/lcf.h>

#include "score.h"

Scores s;

void loadScores(){
    FILE *best_scores = fopen("/z.txt", "r");

    printf("Try");
    if(best_scores == NULL) {
        //perror("File opening failed");
        printf("File not open");
        best_scores = fopen("z.txt", "w");
        fclose(best_scores);
        return;
    }

    printf("Opened!");

    //if (feof(best_scores)){
        s.scoreOne = 0;
        s.scoreTwo = 0;
        s.scoreThree = 0;
        s.scoreFour = 0;
        s.scoreFive = 0;
      //  return;
    //}

    if (feof(best_scores))
        return;

    char score[5];
    fgets(score, 5, best_scores);
    s.scoreOne = atoi(score);
    fgets(s.scoreOneDate, 20, best_scores);
    if (feof(best_scores)){
        s.scoreTwo = 0;
        s.scoreThree = 0;
        s.scoreFour = 0;
        s.scoreFive = 0;
        return;
    }

    printf("Read 1");

    fgets(score, 5, best_scores);
    s.scoreTwo = atoi(score);
    fgets(s.scoreTwoDate, 20, best_scores);
    if (feof(best_scores)){
        s.scoreThree = 0;
        s.scoreFour = 0;
        s.scoreFive = 0;
        return;
    }
    
    printf("Read 2");


    fgets(score, 5, best_scores);
    s.scoreThree = atoi(score);
    fgets(s.scoreThreeDate, 20, best_scores);
    if (feof(best_scores)){
        s.scoreFour = 0;
        s.scoreFive = 0;
        return;
    }

    printf("Read 3");

    fgets(score, 5, best_scores);
    s.scoreFour = atoi(score);
    fgets(s.scoreFourDate, 20, best_scores);
    if (feof(best_scores)){
        s.scoreFive = 0;
        return;
    }
    
    printf("Read 4");

    fgets(score, 5, best_scores);
    s.scoreFive = atoi(score);
    fgets(s.scoreFiveDate, 20, best_scores);
    if (feof(best_scores))
        return;
    printf("Read 5");
}

void saveScores(){

    FILE *best_scores = fopen("bestScores.txt", "w");

    if(!best_scores) {
        perror("File opening failed");
        return;// EXIT_FAILURE;
    }

    printf("sc 1");
    char *score = NULL;
    if (s.scoreOne != 0){
        printf("sc 2");
        sprintf(score, "%d;\n", s.scoreOne);
        printf("sc 3");
        printf(score);

        
        fputs(score, best_scores);
        printf("sc 4");
        fputs(s.scoreOneDate, best_scores);
        printf("sc 5");
        if (s.scoreTwo != 0){
            sprintf(score, "%d;\n", s.scoreTwo);
            fputs(score, best_scores);
            fputs(s.scoreTwoDate, best_scores);
            if (s.scoreThree != 0){
                sprintf(score, "%d;\n", s.scoreThree);
                fputs(score, best_scores);
                fputs(s.scoreThreeDate, best_scores);
                if (s.scoreFour != 0){
                    sprintf(score, "%d;\n", s.scoreFour);
                    fputs(score, best_scores);
                    fputs(s.scoreFourDate, best_scores);
                    if (s.scoreFive != 0){
                        sprintf(score, "%d;\n", s.scoreFive);
                        fputs(score, best_scores);
                        fputs(s.scoreFiveDate, best_scores);
                    }
                }
            }


        }
    }

    fclose(best_scores);
}

void addNewScore(int score){
    if (score < s.scoreFive)
        return;
    
    char * date = get_current_date_and_time();

    printf("1");

    if (s.scoreOne == 0){
        s.scoreOne = score;
        printf("1.5");
        s.scoreOneDate = date;
        printf("1.6");
        return;
    }
    else if (s.scoreTwo == 0){
        s.scoreTwo = score;
        s.scoreTwoDate = date;
        return;
    }
    else if (s.scoreThree == 0){
        s.scoreThree = score;
        s.scoreThreeDate = date;
        return;
    }
    else if (s.scoreFour == 0){
        s.scoreFour = score;
        s.scoreFourDate = date;
        return;
    }
    else if (s.scoreFive == 0){
        s.scoreFive = score;
        s.scoreFiveDate = date;
        return;
    }

    printf("2");


    if (score > s.scoreFive){
        s.scoreFive = score;
        s.scoreFiveDate = date;
        if (score > s.scoreFour){
            s.scoreFive = s.scoreFour;
            s.scoreFiveDate = s.scoreFourDate;
            s.scoreFour = score;
            s.scoreFourDate = date;
            if (score > s.scoreThree){
                s.scoreFour = s.scoreThree;
                s.scoreFourDate = s.scoreThreeDate;
                s.scoreThree = score;
                s.scoreThreeDate = date;
                if (score > s.scoreTwo){
                    s.scoreThree = s.scoreTwo;
                    s.scoreThreeDate = s.scoreTwoDate;
                    s.scoreTwo = score;
                    s.scoreTwoDate = date;
                    if (score > s.scoreOne){
                        s.scoreTwo = s.scoreOne;
                        s.scoreTwoDate = s.scoreOneDate;
                        s.scoreOne = score;
                        s.scoreOneDate = date; 
                    }
                }
            }
        }
    }
    printf("3");


}

