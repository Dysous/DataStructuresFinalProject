//
// Created by NTMat on 11/24/2024.
//

#ifndef JINGLE_BALLERS_BIGTEXT_H
#define JINGLE_BALLERS_BIGTEXT_H
#include <iostream>
#include <fstream>
#include "SDL_Plotter.h"
using namespace std;

class bigText{
public:
    bool ***letters;

    /*
     * Description: Default Constructor
     * Return: Nothing
     * Precondition: letters.txt file has been made properly
     * Post condition: bigText object ready to be called
     */
    bigText( string fileName="letters.txt"){
        letters = new bool**[37];
        fstream infile;
        infile.open(fileName);//add try/throw statment

        for(int i=0; i<37; i++){
            letters[i] = new bool*[20];
            for(int j=0 ;j<20; j++){
                letters[i][j] = new bool[20];
                for(int k=0; k<20; k++){
                    infile >> letters[i][j][k];
                }
            }
        }

        infile.close();
    }

    /*
     * Description: Draws text on the screen from a string
     * Return: Nothing
     * Precondition: SDL_Plotter object
     * Post condition: Text on the screen
     */
    void draw(SDL_Plotter &g,string data, int xpos, int ypos, int R=0, int G=0, int B=0){
        for(int i=0; i< data.length(); i++){
            letter(g, toupper(data[i]), xpos+(20*i), ypos, R,G,B);
        }
    }

    /*
     * Description: Draws text on the screen from an int
     * Return: Nothing
     * Precondition: SDL_Plotter object
     * Post condition: Number on the screen
     */
    void draw(SDL_Plotter &g,int data, int xpos, int ypos, int R=0, int G=0, int B=0, int i=-1){
        int temp=data;
        do{
            i++;
            temp /=10;
        }while(temp>0);

        do {
            letter(g, data%10, xpos + (20 * i), ypos, R, G, B);
            i--;
            data/=10;
        }while(data>0);
    }

    void drawCentered(SDL_Plotter &g,int data, int xpos, int ypos, int R=0, int G=0, int B=0, int i=-1){
        int xoff = 0;
        int datac = data;
        //cout << "Centering " << data << endl;
        while(datac>9){
            xoff+=10;
            datac/=10;
            //cout << "X offset: " << xoff << endl;
        }

        draw(g, data, xpos-xoff-10, ypos-10, R, G, B, i);
    }

    /*
     * Description: Used to draw in individual character
     * Return: Nothing
     * Precondition: SDL_Plotter Object
     * Post condition: A Letter on the screen
     */
    void letter(SDL_Plotter &g, int c, int xpos, int ypos, int R=0, int G=0, int B=0){
        int index;
        if(c>64){
            index = c-55;
        }else if(c>47){
            index = c-48;
        }else if(c<10){
            index = c;
        }else if(c == 32){
            index = 36;
        }else{
            index = c;
        }


        for(int i=0 ;i<20; i++){
            for(int j=0; j<20; j++){
                if(letters[index][i][j] == 1) {
                    g.plotPixel(xpos + j, ypos + i, R, G, B);
                }
            }
        }
    }

};
#endif //JINGLE_BALLERS_BIGTEXT_H
