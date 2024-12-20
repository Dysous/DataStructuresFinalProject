//
// Created by NTMat on 4/14/2024.
//
//
// Created by NTMat on 3/19/2024.
//

#include "fullsizeAssets.h"
#include <fstream>
fullsizeAssets::fullsizeAssets(string *s, int n) {
    numAssets=n;
    asset = new colora**[n];
    for(int i=0; i<n; i++){
        asset[i] = new colora*[1080];
        for(int j=0; j<1080; j++){
            asset[i][j] = new colora[1920];
        }
    }

    for(int k=0; k<n; k++){
        //Data Abstraction
        ifstream inFile;
        string line;
        char comma;
        int width;
        int height;
        int r,g,b,a;
        //Input
        inFile.open(s[k]);
        if(inFile){
            cout << "fullsizeFile open" << endl;
        }
        //Process
        inFile >> width;
        inFile >> comma;
        inFile >> height;
        getline(inFile, line);
        inFile >> r;
        inFile >> comma;
        inFile >> g;
        inFile >> comma;
        inFile >> b;
        inFile >> comma;
        inFile >> a;
        getline(inFile,line);

        //Output

        asset[k][0][0].R = r;
        asset[k][0][1].G = g;
        asset[k][0][2].B = b;
        asset[k][0][3].A = a;
        for(int i = 0; i < 1080; i++){
            for(int j = 0; j < 1920; j++){
                inFile >> r;
                inFile >> comma;
                inFile >> g;
                inFile >> comma;
                inFile >> b;
                inFile >> comma;
                inFile >> a;
                getline(inFile,line);

                asset[k][i][j].R = r;
                asset[k][i][j].G = g;
                asset[k][i][j].B = b;
                asset[k][i][j].A = a;
            }
        }
        inFile.close();
    }
}

void fullsizeAssets::draw(SDL_Plotter &g, int frame,int x, int y) {
    for(int i = 0; i < 1920; i++){
        for(int j = 0; j < 1080; j++){
            if(asset[frame][j][i].A!=0) {
                g.plotPixel(i + x, j + y, asset[frame][j][i].R, asset[frame][j][i].G, asset[frame][j][i].B);
            }
        }
    }
}
