//
// Created by NTMat on 12/9/2024.
//

#ifndef JINGLE_BALLERS_FULLSIZEASSETS_H
#define JINGLE_BALLERS_FULLSIZEASSETS_H
struct colora{
public:
    int R=0,G=0,B=0,A=0;

};

#include "SDL_Plotter.h"
class fullsizeAssets{
private:


public:
    int numAssets;
    colora ***asset;
    //Loads fullsize assets into colora array containing array of pixel maps (frames)
    fullsizeAssets(string *s, int n=1);

/*
 * description: Draws the background to the screen
 * return: void
 * precondition: No background
 * postcondition: Background drawn on screen
 *
*/
    void draw(SDL_Plotter &g, int frame, int x, int y);

/*
* description: get the colors for each pixel on the background
* return: color**
* precondition: Colors of the background are not set
* postcondition: Sets the colors of the background to the Asset
*
*/
    color** getColors(int frame=0){
        color **col;
        col = new color*[1080];
        for(int i=0; i<1080; i++){
            col[i] = new color[1920];
        }
        for(int i=0; i<1080; i++){
            for(int j=0; j<1920; j++){
                col[i][j].R = asset[frame][i][j].R;
                col[i][j].G = asset[frame][i][j].G;
                col[i][j].B = asset[frame][i][j].B;
            }
        }
        return col;
    }
};




#endif //JINGLE_BALLERS_FULLSIZEASSETS_H
