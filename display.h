/*
 * Author: Nathan Garcia, Ethan Vowels, Rylan Kinzle,
           Noah Mathew, Ethan Pritchett
 * Assignment Title: Red-Black Tree
 * Assignment Description: Implements a red-black tree
 * Due Date: 12/8/2024
 * Date Created: 10/5/2024
 * Date Last Modifed: 12/8/2024
 */


#ifndef JINGLE_BALLERS_DISPLAY_H
#define JINGLE_BALLERS_DISPLAY_H

#include <iostream>
#include "Red_Black_Tree.h"
#include "SDL_Plotter.h"
#include "bigText.h"
#include <cmath>
using namespace std;

const int screenw = 1920;
const int screenh = 1080;

int nodeRadius = 30;
int highlightRadius = 35;

SDL_Plotter Plot(1080,1920, true);
RedBlackTree a;

template<typename T>
class display{
private:
    bigText text;
public:
    /*
     * Description: Default constructor
     * Return: Nothing
     * Precondition: Nothing
     * Post condition: Usable object of type display
     */
    display(){}

    /*
     * Description: Calls the Tree drawing function
     * Return: Nothing
     * Precondition: Global SDL_Plotter object, and filled RedBlackTree object
     * Post condition: Calls updateTreeRecursive to represent the tree on plot
     */
    void updateTree(RedBlackTree Tree, bool white = false){
        if(!Tree.isEmpty())
            updateTreeRecursive(Tree.getRoot(), 0, 0, Tree.maxDepth(), white);
    }

    /*
     * Description: Draws the tree
     * Return: nothing
     * Precondition: updateTree function called
     * Post condition: drawNode and drawArrow called
     */
    void updateTreeRecursive(Node *n, int depth = 0, int breadth = 0, int scale = 0, bool white = false){

        if(n->left->data>=0){
            drawArrow(depth,breadth,0,scale, white);
            updateTreeRecursive(n->left, depth + 1, breadth * 2, scale, white);
        }
        if(n->right->data>=0){
            drawArrow(depth,breadth,1,scale, white);
            updateTreeRecursive(n->right, depth + 1, (breadth * 2) + 1, scale, white);
        }

        drawNode(n, depth, breadth, scale);
    }

    /*
     * Description: Draws nodes on the plot
     * Return: nothing
     * Precondition: updateTreeRecursive function called
     * Post condition: drawNodeCircle called and bigText drawCentered called
     */
    void drawNode(Node *n, int depth, int breadth, int scale){
        if(n->data>=0) {
            int x, y;
            color c = {0, 0, 0};
            if (n->color == RED)
                c = {255, 0, 0};

            //cout << "Drawing Node At: " << (1920 * (breadth + 1)) / (pow(2, depth + 1)) << ", " << (1080 * (depth + 1) - 500) / (pow(2, depth + 1));

            x = (1920 * (2 * breadth + 1)) / (pow(2, depth + 1));
            y = (1000 * (depth + 1))/(scale+1);

            drawNodeCircle({x, y}, 4*(nodeRadius + 20)/scale, c, Plot);
            text.drawCentered(Plot, n->data, x, y, 255, 255, 255);
        }
    }

    /*
     * Description: Draws arrows on plot
     * Return: nothing
     * Precondition: updateTreeRecursive called
     * Post condition: lines between nodes drawn on plot
     */
    void drawArrow(int depth, int breadth, bool right, int scale, bool white = false){
        int x1,x2,y1,y2;
        double xx,yy;
        color c = {0,0,0};
        if(white) c={255,255,255};

        x1 = (1920 * (2 * breadth + 1)) / (pow(2, depth + 1));
        y1 = (1000 * (depth + 1))/(scale+1);
        if(right){
            x2 = (1920 * (2 * (breadth*2 + 1) + 1)) / (pow(2, depth + 2));
        }else {
            x2 = (1920 * (2 * (2*breadth) + 1)) / (pow(2, depth + 2));
        }
        y2 = (1000 * (depth + 2))/(scale+1);

        for(float t=0.2; t<0.8; t+=0.002) {
            xx = x1 + t * (x2 - x1);
            yy = y1 + t * (y2 - y1);
            Plot.plotPixel(xx,yy, c);
        }
    }

    /*
     * Description: Draws a circle on the screen
     * Return: nothing
     * Precondition: drawNode called
     * Post condition: circle drawn on the screen
     */
    void drawNodeCircle(point loc, int size, color c, SDL_Plotter &g){
        for(double i = -size; i <= size;i+=0.1){
            for(double j = -size; j <= size; j+=0.1){
                if(i*i + j*j <= size*size){
                    g.plotPixel(round(loc.x+i),round(loc.y+j),c);
                }
            }
        }

    }

    /*
     * Description: begins the find animation
     * Return: nothing
     * Precondition: RedBlackTree and SDL_Plotter objects made
     * Post condition: drawFindRecursive called
     */
    void drawFind(RedBlackTree Tree, int num){
        if(!Tree.isEmpty() && num)
            drawFindRecursive(Tree.getRoot(),num,Tree.maxDepth());
    }

    /*
     * Description: calles animations for find animation
     * Return: nothing
     * Precondition: drawFind called
     * Post condition: animateFind called
     */
    void drawFindRecursive(Node *n, int num, int scale, int breadth= 0, int depth= 0){
        int x, y;

        x = (1920 * (2 * breadth + 1)) / (pow(2, depth + 1));
        y = (1000 * (depth + 1))/(scale+1);

        if(n->data == -1){
            text.draw(Plot, "Number not found",20,50);
            Plot.update();
            Plot.Sleep(2000);
            text.draw(Plot, "Number not found",20,50,255,255,255);
        }

        else if(n->data == num){
            for(int i=-((4*(nodeRadius + 20)/scale)+((highlightRadius-nodeRadius))); i<((4*(nodeRadius + 20)/scale)+((highlightRadius-nodeRadius))); i++) {
                for (int j=-((4*(nodeRadius + 20)/scale)+((highlightRadius-nodeRadius))); j<((4*(nodeRadius + 20)/scale)+((highlightRadius-nodeRadius))); j++) {
                    if ((i * i + j * j) >= pow((4*(nodeRadius + 20)/scale),2) &&
                        (i * i + j * j) <= pow((4*(nodeRadius + 20)/scale)+((highlightRadius-nodeRadius)),2)) {
                        Plot.plotPixel(i+x, j+y, 255, 255, 0);
                    }
                }
            }
            Plot.update();
            Plot.Sleep(1000);
            for(int i=-((4*(nodeRadius + 20)/scale)+((highlightRadius-nodeRadius))); i<((4*(nodeRadius + 20)/scale)+((highlightRadius-nodeRadius))); i++) {
                for (int j=-((4*(nodeRadius + 20)/scale)+((highlightRadius-nodeRadius))); j<((4*(nodeRadius + 20)/scale)+((highlightRadius-nodeRadius))); j++) {
                    if ((i * i + j * j) >= pow((4*(nodeRadius + 20)/scale),2) &&
                        (i * i + j * j) <= pow((4*(nodeRadius + 20)/scale)+((highlightRadius-nodeRadius)),2)) {
                        Plot.plotPixel(i+x, j+y, 255, 255, 255);
                    }
                }
            }
        }
        else if(n->data>num){
            animateFind(breadth,depth,scale,false);
            Plot.Sleep(500);
            drawFindRecursive(n->left, num, scale, (breadth*2), depth + 1);
        }
        else{
            animateFind(breadth,depth,scale,true);
            Plot.Sleep(500);
            drawFindRecursive(n->right, num, scale, (breadth*2) + 1, depth + 1);
        }
    }

    /*
     * Description: draws find animation played before an insert
     * Return: nothing
     * Precondition: RedBlackTree and SDL_Plotter objects made
     * Post condition: DrawFindInsertRecursive called
     */
    void drawFindInsert(RedBlackTree Tree, int num){
        if(!Tree.isEmpty() && num) {
            if(treeInstructions.empty()) {
                drawFindInsertRecursive(Tree.getRoot(), num, Tree.maxDepth());
            }else{
                drawFindInsertRecursive(treeInstructions.front().treeBefore->getRoot(), num, treeInstructions.front().treeBefore->maxDepth()-1);
            }
        }
    }

    /*
     * Description: calls animations for insert find
     * Return: nothing
     * Precondition: drawFindInsert called
     * Post condition: animateFind called
     */
    void drawFindInsertRecursive(Node *n, int num, int scale, int breadth= 0, int depth= 0){
        if(scale>0){

            int x, y;

            x = (1920 * (2 * breadth + 1)) / (pow(2, depth + 1));
            y = (1000 * (depth + 1)) / (scale + 1);

            if (n->data == -1) {
                for (int i = -((4 * (nodeRadius + 20) / scale) + ((highlightRadius - nodeRadius)));
                     i < ((4 * (nodeRadius + 20) / scale) + ((highlightRadius - nodeRadius))); i++) {
                    for (int j = -((4 * (nodeRadius + 20) / scale) + ((highlightRadius - nodeRadius)));
                         j < ((4 * (nodeRadius + 20) / scale) + ((highlightRadius - nodeRadius))); j++) {
                        if ((i * i + j * j) >= pow((4 * (nodeRadius + 20) / scale), 2) &&
                            (i * i + j * j) <=
                            pow((4 * (nodeRadius + 20) / scale) + ((highlightRadius - nodeRadius)), 2)) {
                            Plot.plotPixel(i + x, j + y, 255, 255, 255);
                        }
                    }
                }
                Plot.update();
                //Plot.Sleep(1000);
                for (int i = -((4 * (nodeRadius + 20) / scale) + ((highlightRadius - nodeRadius)));
                     i < ((4 * (nodeRadius + 20) / scale) + ((highlightRadius - nodeRadius))); i++) {
                    for (int j = -((4 * (nodeRadius + 20) / scale) + ((highlightRadius - nodeRadius)));
                         j < ((4 * (nodeRadius + 20) / scale) + ((highlightRadius - nodeRadius))); j++) {
                        if ((i * i + j * j) >= pow((4 * (nodeRadius + 20) / scale), 2) &&
                            (i * i + j * j) <=
                            pow((4 * (nodeRadius + 20) / scale) + ((highlightRadius - nodeRadius)), 2)) {
                            Plot.plotPixel(i + x, j + y, 255, 255, 255);
                        }
                    }
                }
            } else if (n->data > num) {
                animateFind(breadth, depth, scale, false);
                Plot.Sleep(300);
                drawFindInsertRecursive(n->left, num, scale, (breadth * 2), depth + 1);
            } else {
                animateFind(breadth, depth, scale, true);
                Plot.Sleep(300);
                drawFindInsertRecursive(n->right, num, scale, (breadth * 2) + 1, depth + 1);
            }
        }
    }

    /*
     * Description: animates find animations
     * Return: nothing
     * Precondition: either drawFindInsertRecursive or drawFindRecursive called
     * Post condition: single step of a find animation shown on screen
     */
    void animateFind(int breadth, int depth, int scale, bool right){
        int ringRadius = (4*(nodeRadius + 20)/scale)+((highlightRadius-nodeRadius));
        color **ground = new color*[2*ringRadius];
        for(int i=0; i<2*ringRadius; i++){
            ground[i] = new color[2*ringRadius];
        }
        Uint32 cc;
        int x1,x2,y1,y2;
        double xx,yy;

        x1 = (1920 * (2 * breadth + 1)) / (pow(2, depth + 1));
        y1 = (1000 * (depth + 1))/(scale+1);
        if(right){
            x2 = (1920 * (2 * (breadth*2 + 1) + 1)) / (pow(2, depth + 2));
        }else {
            x2 = (1920 * (2 * (2*breadth) + 1)) / (pow(2, depth + 2));
        }
        y2 = (1000 * (depth + 2))/(scale+1);



        for(float t=0; t<1; t+=0.01) {
            int R,G,B;
            for(int i=-ringRadius; i<ringRadius; i++){
                for(int j=-ringRadius; j<ringRadius; j++){
                    xx = x1 + t*(x2-x1);
                    yy = y1 + t*(y2-y1);

                    if (i + xx < 1920 && j + yy < 1080 && i + xx >= 0 && j + yy >=0) {
                        cc = Plot.getColor(i + xx, j + yy);
                    } else {
                        cc = Plot.getColor(1, 1);
                    }

                    //cc = Plot.getColor(i+xx,j+yy);
                    B=cc%256;
                    cc = cc/256;
                    G=cc%256;
                    cc = cc/256;
                    R=cc%256;
                    ground[i+ringRadius][j+ringRadius].R=R;
                    ground[i+ringRadius][j+ringRadius].G=G;
                    ground[i+ringRadius][j+ringRadius].B=B;
//pickup background

                    if ((i * i + j * j) >= pow((4*(nodeRadius + 20)/scale),2) &&
                        (i * i + j * j) <= pow((4*(nodeRadius + 20)/scale)+((highlightRadius-nodeRadius)),2)) {
                        Plot.plotPixel(i+xx, j+yy, 255, 255, 0);
                    }
//place ring
                }
            }
            Plot.update();
            //update
            for(int i=-ringRadius; i<ringRadius; i++) {
                for (int j = -ringRadius; j < ringRadius; j++) {
                    if ((i * i + j * j) >= pow((4*(nodeRadius + 20)/scale),2) &&
                        (i * i + j * j) <= pow((4*(nodeRadius + 20)/scale)+((highlightRadius-nodeRadius)),2)) {
                        Plot.plotPixel(i+xx, j+yy, ground[i+ringRadius][j+ringRadius]);
                    }
                }
            }
        }
        //Place background,
        // move

    }

    /*
     * Description: Reads instructions for animating rotations
     * Return: nothing
     * Precondition: RedBlackTree and SDL_Plotter object made
     * Post condition: animate rotate called
     */
    void readInstructions(){
        while(!treeInstructions.empty()){
            animateRotate();
            treeInstructions.pop();
        }
    }

    struct movingNode{
        int depth, breadth, dir, x, y, x2, y2;
        color **pixels;
        double t;
        int ringRadius;
        int pivotX, pivotY;

        movingNode(int d, int b, int di, int scale,int pivX, int pivY):depth(d),breadth(b),dir(di),pivotX(pivX),pivotY(pivY){
            x = (1920 * (2 * breadth + 1)) / (pow(2, depth + 1));
            y = (1000 * (depth + 1))/(scale+1);
            t=0;
            ringRadius = (4*(nodeRadius + 20)/(scale))+1;
            Uint32 cc = 0;

            switch (dir) {
                case 0://Up
                    x2 =(1920 * (2 * (breadth/2) + 1)) / (pow(2, (depth-1) + 1));
                    y2 =(1000 * ((depth-1) + 1))/(scale+1);
                    break;
                case 1://Left
                    x2 =((1920 * (2 * (breadth*2)+1)) / (pow(2, ((depth)+1) + 1)));
                    y2 =(1000 * ((depth+1) + 1))/(scale+1);
                    break;
                case 2://Right
                    x2 =(1920 * (2 * (2*breadth+1) + 1)) / (pow(2, (depth+1) + 1));
                    y2 =(1000 * ((depth+1) + 1))/(scale+1);
                    break;
                case 3://Left Across
                    x2 =(1920 * (2 * (breadth - pow(2,depth-2) + pivY) + 1)) / pow(2, depth + 1);
                    y2 =(1000 * ((depth) + 1))/(scale+1);
                    break;
                case 4://Right Across
                    x2 =(1920 * (2 * (breadth + 1 - pivY ) + 1)) / (pow(2, depth + 1));
                    y2 =(1000 * ((depth) + 1))/(scale+1);
                    break;
                case 5://Left Diagonal
                    x2 =(1920 * (2 * (breadth/2) - 1)) / (pow(2, (depth-1) + 1));
                    y2 =(1000 * ((depth-1) + 1))/(scale+1);
                    break;
                case 6://Right Diagonal
                    x2 =(1920 * (2 * (breadth) + 1)) / (pow(2, (depth-1) + 1));
                    y2 =(1000 * ((depth-1) + 1))/(scale+1);
                    break;
            }

            pixels = new color*[2*ringRadius];
            for(int i=0; i<2*ringRadius; i++){
                pixels[i] = new color[2*ringRadius];
                for(int j=0; j<2*ringRadius; j++){
                    int R,G,B;

                    if (i + x - ringRadius < 1920 && j + y - ringRadius < 1080) {
                        cc = Plot.getColor(i + x - ringRadius, j + y - ringRadius);
                    } else {
                        cc = Plot.getColor(1, 1);
                    }

                    B=cc%256;
                    cc = cc/256;
                    G=cc%256;
                    cc = cc/256;
                    R=cc%256;
                    pixels[i][j] = {R,G,B};
                }
            }
        };

        void move(double dt){
            int xx,yy;

            t=dt/100;
            xx = x + t * (x2 - x);
            yy = y + t * (y2 - y);

            for(int i=0; i<2*ringRadius; i++){
                for(int j=0; j<2*ringRadius; j++){

                    Plot.plotPixel(xx+i-ringRadius,yy+j-ringRadius,255,255,255);
                }
            }
            t+=0.01;
            xx = x + t * (x2 - x);
            yy = y + t * (y2 - y);

            for(int i=0; i<2*ringRadius; i++){
                for(int j=0; j<2*ringRadius; j++){

                    Plot.plotPixel(xx+i-ringRadius,yy+j-ringRadius,pixels[i][j]);
                }
            }

        }

    };

    /*
     * Description: Animates a rotations of nodes
     * Return: nothing
     * Precondition: movingNode struct made and readInstructions function called
     * Post condition: rotation visualized on the plot
     */
    void animateRotate(){
        //RedBlackTree t = treeInstructions.front().treeBefore;
        //RedBlackTree t = tree;
        Plot.playSound("swap.wav");

        Node *node = treeInstructions.front().treeBefore->getRoot();
        int b = treeInstructions.front().breadth;
        bool *path;
        path = new bool[treeInstructions.front().depth+1];

        vector<pair<int,int> > upSide, leftSide, rightSide, leftAcrossSide, rightAcrossSide, leftDiagSide, rightDiagSide;
        vector<movingNode> moveableNodes;


        for(int i=0; i<treeInstructions.front().depth; i++){
            path[i] = b%2;
            b/=2;
        }
        for(int i=treeInstructions.front().depth-1; i>=0; i--){
            if(path[i]){
                node = node->right;
            }else{
                node = node->left;
            }
        }

        if(treeInstructions.front().right){
            rightSide.push_back({treeInstructions.front().depth,treeInstructions.front().breadth});
        }
        else{
            leftSide.push_back({treeInstructions.front().depth,treeInstructions.front().breadth});
        }

        addNodes(&upSide, &leftSide, &rightSide, &leftAcrossSide, &rightAcrossSide,
                 &leftDiagSide, &rightDiagSide,node->right, treeInstructions.front().depth+1,
                 (treeInstructions.front().breadth*2)+1, treeInstructions.front().right, treeInstructions.front().depth, treeInstructions.front().breadth);

        addNodes(&upSide, &leftSide, &rightSide, &leftAcrossSide, &rightAcrossSide,
                 &leftDiagSide, &rightDiagSide,node->left, treeInstructions.front().depth+1,
                 (treeInstructions.front().breadth*2), treeInstructions.front().right, treeInstructions.front().depth, treeInstructions.front().breadth);

        for(auto i : upSide){
            movingNode temp(i.first,i.second,0,treeInstructions.front().treeBefore->maxDepth(),treeInstructions.front().depth,treeInstructions.front().breadth);
            moveableNodes.push_back(temp);
        }
        for(auto i : rightSide){
            movingNode temp(i.first,i.second,2,treeInstructions.front().treeBefore->maxDepth(),treeInstructions.front().depth,treeInstructions.front().breadth);
            moveableNodes.push_back(temp);
        }
        for(auto i : rightAcrossSide){
            movingNode temp(i.first,i.second,4,treeInstructions.front().treeBefore->maxDepth(),treeInstructions.front().depth,treeInstructions.front().breadth);
            moveableNodes.push_back(temp);
        }
        for(auto i : rightDiagSide){
            movingNode temp(i.first,i.second,6,treeInstructions.front().treeBefore->maxDepth(),treeInstructions.front().depth,treeInstructions.front().breadth);
            moveableNodes.push_back(temp);
        }

        for(auto i : leftSide){
            movingNode temp(i.first,i.second,1,treeInstructions.front().treeBefore->maxDepth(),treeInstructions.front().depth,treeInstructions.front().breadth);
            moveableNodes.push_back(temp);
        }
        for(auto i : leftAcrossSide){
            movingNode temp(i.first,i.second,3,treeInstructions.front().treeBefore->maxDepth(),treeInstructions.front().depth,treeInstructions.front().breadth);
            moveableNodes.push_back(temp);
        }
        for(auto i : leftDiagSide){
            movingNode temp(i.first,i.second,5,treeInstructions.front().treeBefore->maxDepth(),treeInstructions.front().depth,treeInstructions.front().breadth);
            moveableNodes.push_back(temp);
        }




        for(int time=0; time<100; time++){
            for(auto n : moveableNodes){
                n.move(time);
            }
            cout << "rotating\n";
            Plot.update();
            Plot.Sleep(10);
        }
        Plot.Sleep(500);

    }

    /*
     * Description: helper function for animate rotate
     * Return: nothing
     * Precondition: animate rotate called
     * Post condition: filled vector pairs
     */
    void addNodes(vector<pair<int, int> > *up, vector<pair<int, int> > *left, vector<pair<int, int> > *right,
                  vector<pair<int, int> > *leftAcross, vector<pair<int, int> > *rightAcross,
                  vector<pair<int, int> > *leftDiag, vector<pair<int, int> > *rightDiag, Node* n, int d, int b, bool r, int dinit, int binit){
        if(n) {
            if (n->data != -1) {
                if(r){
                    if((b*1) > (((2*binit+1)*(pow(2,(d-dinit))))-1)/2.0){
                        right->push_back({d,b});
                    }else if((b*1) == binit*pow(2,d-dinit)){
                        up->push_back({d,b});
                    }else if((b*1) > ((4*binit+1)*pow(2,(d-dinit))-1)/4.0){
                        rightAcross->push_back({d,b});
                    }else{
                        rightDiag->push_back({d,b});
                    }
                }else{
                    if((b*1) < (((2*binit+1)*(pow(2,(d-dinit))))-1)/2.0){
                        left->push_back({d,b});
                    }else if((b*1) == (binit+1)*pow(2,(d-dinit))-1){
                        up->push_back({d,b});
                    }else if((b*1) < ((((4*binit/3.0)+1)*pow(2,(d-dinit)))-1)*3/4.0){
                        leftAcross->push_back({d,b});
                    }else{
                        leftDiag->push_back({d,b});
                    }
                }
                addNodes(up, left, right, leftAcross, rightAcross, leftDiag, rightDiag, n->left, d+1, b*2, r, dinit, binit);
                addNodes(up, left, right, leftAcross, rightAcross, leftDiag, rightDiag, n->right, d+1, (b*2)+1, r, dinit, binit);
            }
        }
    }


};


#endif //JINGLE_BALLERS_DISPLAY_H
