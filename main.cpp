/*
 * Author: Nathan Garcia, Ethan Vowels, Rylan Kinzle,
           Noah Mathew, Ethan Pritchett
 * Assignment Title: Red-Black Tree
 * Assignment Description: Implements a red-black tree
 * Due Date: 12/8/2024
 * Date Created: 10/5/2024
 * Date Last Modifed: 12/8/2024
 */


#include <iostream>
#include <fstream>
#include "Red_Black_Tree.h"
#include "SDL_Plotter.h"
#include <cmath>
#include "display.h"
#include "bigText.h"
#include "fullsizeAssets.h"

void drawBoxText(SDL_Plotter *p, int n);
bool drawBoxInsert(SDL_Plotter *p);
bool drawBoxFind(SDL_Plotter *p);
bool drawBoxDelete(SDL_Plotter *p);
bool drawBoxClear(SDL_Plotter *p);


bigText bt;


void drawCircle(point loc, int size, color c, SDL_Plotter& g){
    for(double i = -size; i <= size;i+=0.1){
        for(double j = -size; j <= size; j+=0.1){
            if(i*i + j*j <= size*size){
                g.plotPixel(round(loc.x+i),round(loc.y+j),c);
            }
        }
    }

}



int main(int argc, char ** argv) {
    bool showMiku = false;
    const unsigned char *dirchars;
    char key;
    int number = -1;


    //a.test();

    display<int> screen;
    point p;
    color c;
    int size;
    Uint32 RGB;

    string *fullsizeNames;
    fullsizeNames = new string[8];
    fullsizeNames[0] = "santamikufull.txt";

    fullsizeAssets miku(fullsizeNames, 1);


    //Initialize sound
    Plot.initSound("pop.wav");
    Plot.initSound("insert.wav");
    Plot.initSound("GoodDesign.wav");
    Plot.initSound("swap.wav");
    Plot.initSound("notFound.wav");
    Mix_Music *bgMusic = Mix_LoadMUS("BgMusic.mp3");
    Mix_VolumeMusic(10);
    Mix_PlayMusic(bgMusic, -1);


    while(!Plot.getQuit()){
        dirchars = SDL_GetKeyboardState(nullptr);
        if(Plot.kbhit()){
            key = Plot.getKey()-48;
            if (key < 10 && key >= 0 && number<10000000) {
                if(number == -1) number = 0;
                number *= 10;
                number += key;
            }
        }

        if(dirchars[42]){
            number /= 10;
            if(number == 0) number = -1;
            Plot.Sleep(50);
        }
        if(dirchars[16]){
            if(showMiku){
                showMiku = false;
            }
            else{
                showMiku = true;
            }
        }
        if(Plot.mouseClick() || dirchars[40]){
            p = Plot.getMouseClick();
            Plot.getMouseLocation(p.x,p.y);
            if((p.x>=200 && p.x<=320 && p.y>=5 && p.y<=35) || dirchars[40]) {
                if(number>=0) {//Insert Button
                    //p->plotPixel(i, j, 100, 100, 100);
                    //cout << "Pressing INSERT button" << endl;
                    //cout << "Number: " << number << endl;
                    //If there is a number search for where to insert it
                    if(a.getRoot()->data >= 0) {
                        screen.drawFindInsert(a,number);
                    }
                    //actually do the insert in the RBT
                    a.insert(number);
                    number = -1;
                    Plot.clear();
                    //Plot the moment all nodes are inserted before any rotations
                    if(!treeInstructions.empty())
                        screen.updateTree(*treeInstructions.front().treeBefore, true);
                    Plot.update();
                    //given the tree before rotations, if there is any rotations animate rotations
                    screen.readInstructions();
                    Plot.clear();
                    //update displayed tree to actual tree to view any differences
                    screen.updateTree(a);
                    Plot.playSound("insert.wav");
                    Plot.update();
                }
            }
            else if(p.x>=440 && p.x<=560 && p.y>=5 && p.y<=35){//Remove button
                //cout << "Pressing REMOVE button" << endl;
                //cout << "Number: " << number << endl;
                //Find where the deleted node is
                screen.drawFind(a, number);
                if(a.remove(number)){//actually delete and play sound effect
                    Plot.playSound("pop.wav");
                }
                else {
                    Plot.playSound("notFound.wav");
                }
                number = -1;
                Plot.clear();
                //show RBT tree right before rotates
                if(!treeInstructions.empty())
                    screen.updateTree(*treeInstructions.front().treeBefore, true);
                // animate instructions
                Plot.update();
                Plot.Sleep(100);
                //Animate any rotations in queue
                screen.readInstructions();
                Plot.clear();
                //make it match actual tree to spot any differences
                screen.updateTree(a);
                Plot.update();
            }
            else if(p.x>=340 && p.x<=420 && p.y>=5 && p.y<=35){
                if(number>=0) {//Find button
                    //cout << "Pressing FIND button" << endl;
                    //cout << "Number: " << number << endl;
                    //Simply highlight each node until finding node
                    //If not found write to screen
                    screen.drawFind(a, number);
                    //screen.animateRotate({&a,false,0,0});
                    number = -1;
                    //cout << "Contains number (1 for True 0 for false): "<< a.contains(number) << endl;
                }
            }
            else if(p.x>=580 && p.x<=680 && p.y>=5 && p.y<=35){//Clear button
                //cout << "Pressing CLEAR button" << endl;
                a.clear();
                Plot.clear();
                Plot.playSound("GoodDesign.wav");
                screen.updateTree(a);
                Plot.update();
            }
        }
        Plot.update();
        //UI Buttons
        drawBoxInsert(&Plot);
        drawBoxFind(&Plot);
        drawBoxDelete(&Plot);
        drawBoxClear(&Plot);
        drawBoxText(&Plot,number);
        if(showMiku){
            miku.draw(Plot,0,0,0);
        }

        Plot.update();
    }

    return 0;
}

bool drawBoxInsert(SDL_Plotter *p){
    int x,y;
    p->getMouseLocation(x,y);
    for(int i=200; i<320; i++){
        for(int j=5; j<35; j++){
            if(x>=200 && x<=320 && y>=5 && y<=35) {
                p->plotPixel(i, j, 100, 100, 100);
            }else{
                p->plotPixel(i, j, 150, 150, 150);
            }
        }
    }
    bt.draw(*p,"Insert",200,10);
    if(x>=200 && x<=320 && y>=5 && y<=35) {
        return true;
    }
    return false;
}

bool drawBoxFind(SDL_Plotter *p){
    int x,y;
    p->getMouseLocation(x,y);
    for(int i=340; i<420; i++){
        for(int j=5; j<35; j++){
            if(x>=340 && x<=420 && y>=5 && y<=35) {
                p->plotPixel(i, j, 100, 100, 100);
            }else{
                p->plotPixel(i, j, 150, 150, 150);
            }
        }
    }
    bt.draw(*p,"Find",340,10);
    if(x>=340 && x<=420 && y>=5 && y<=35) {
        return true;
    }
    return false;
}

bool drawBoxDelete(SDL_Plotter *p){
    int x,y;
    p->getMouseLocation(x,y);
    for(int i=440; i<560; i++){
        for(int j=5; j<35; j++){
            if(x>=440 && x<=560 && y>=5 && y<=35) {
                p->plotPixel(i, j, 100, 100, 100);
            }else{
                p->plotPixel(i, j, 150, 150, 150);
            }
        }
    }
    bt.draw(*p,"Delete",440,10);
    if(x>=440 && x<=560 && y>=5 && y<=35) {
        return true;
    }
    return false;
}

void drawBoxText(SDL_Plotter *p, int n){
    for(int i=20; i<180; i++){
        for(int j=5; j<35; j++){
            p->plotPixel(i,j,200,200,200);
        }
    }
    if(n>=0) bt.draw(*p,n,20,10);
}

bool drawBoxClear(SDL_Plotter *p){
    int x,y;
    p->getMouseLocation(x,y);
    for(int i=580; i<680; i++){
        for(int j=5; j<35; j++){
            if(x>=580 && x<=680 && y>=5 && y<=35) {
                p->plotPixel(i, j, 100, 100, 100);
            }else{
                p->plotPixel(i, j, 150, 150, 150);
            }
        }
    }
    bt.draw(*p,"Clear",580,10);
    if(x>=580 && x<=680 && y>=5 && y<=35) {
        return true;
    }
    return false;
}
