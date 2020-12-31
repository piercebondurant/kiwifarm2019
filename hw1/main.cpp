/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Pierce
 *
 * Created on August 26, 2019, 3:01 PM
 */
//DISCLAIMER: the route for the array of kiwis is something I found online. 
//Essentially creates in a 1d array but makes it accessible in a 2d manner using <(x coordinate)*(number of columns)+(y coordinate)>
//I kinda like this because you can have a 2d array for all intents and purposes but it's done without ever actually creating the array of pointers to the beginning of lists
//Everything I could find online insisted this was actually more efficient than a 2d array since it's just a larger 1d array, albeit harder to read.
//If this is false information, feel free to correct it.
//Additionally, I understand the row/col variables are redundant, but I originally planned this to work with arrays of unknown size. Oops

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;
class kiwi{
public:
    kiwi();
    kiwi(int r);
    void setAll(int r);
    void increaseRipeness();
    bool getRipe();
    bool getRotten();
    int getRipeness();
private: 
    bool ripe=false;
    bool rotten=false;
    int ripeness = 0;
};

kiwi::kiwi(){ripe = false;}
kiwi::kiwi(int r){setAll(r);}
void kiwi::increaseRipeness(){
    ripeness++;
    if(ripeness<6)
        ripe=false;
    if(ripeness>=6&&ripeness<=8)
        ripe=true;
    if(ripeness>8){
        ripe=false;
        rotten=true;
    }
}
bool kiwi::getRipe(){
    return ripe;
}
bool kiwi::getRotten(){return rotten;}
void kiwi::setAll(int r){
    ripe = (r>=6&&r<=8)?true:false; //ternary :)
    rotten = (r>8)?true:false;
    ripeness=r;
    /*if(r>=6&&r<=8){
        ripe=true;
    }
    if(r>8){
        rotten=true;
    }*/
}
int kiwi::getRipeness(){
    return ripeness;
}


class farm{
public:
    farm();
    farm(string i, string o);
    void advanceDay();
    bool harvestRow(int r);
    int getHarvestedKiwi();
    int getRottenKiwi();
    void printToConsole();
    void printToFile();
    void growKiwiRow(int r);
    void advanceWeek();
private:
    int harvestedKiwi=0,rottenKiwi=0,row=0,col=0,size=0,day=0;
    string input,output;
    kiwi* batch;
    
};

farm::farm(string i,string o){
    output = o;
    ifstream readFile(i);
    if(readFile.is_open()){
        readFile >> size;
    }
    row=size;
    col=size;
    size*=size;
    batch = new kiwi[size];
    for(int x = 0; x<row;x++){
        for(int y = 0; y<col;y++){
            int val;
            readFile >> val; 
            batch[x*col+y] = kiwi(val);
        }
    }
}
bool farm::harvestRow(int r){
    //TALLY RIPE AND ROTTEN
    int countRipe=0,countRotten=0;
    for(int i = 0;i<col;i++){
        if(batch[r*col+i].getRipe()){
            countRipe++;
            //cout << "Ripe space: " <<r*col+i << "\n";
        }
        if(batch[r*col+i].getRotten()){
            countRotten++;
            //cout << "Rotten space: " << r*col+i << "\n";
        }
        
    }
    //cout << "\n";
    //IF HARVESTABLE, CLEAR ROW
    //cout << "Row: " << r <<" Count Ripe: " << countRipe << " Count Rotten: " << countRotten << "\n";
    if((countRipe+countRotten>=(col/2))){
        harvestedKiwi+=countRipe;
        rottenKiwi+=countRotten;
        for(int i = 0;i<col;i++)
            batch[r*col+i] = 0;
        return true;
    }
    return false;
}
void farm::growKiwiRow(int r){
    for(int i =0; i<col;i++){
        batch[r*col+i].increaseRipeness();
    }
}
void farm::advanceDay(){
    for(int i = 0; i<col;i++){
        if(!harvestRow(i)){
            growKiwiRow(i);
        }
    }
    //printToConsole();
    day++;
}
void farm::advanceWeek(){
    for(int i = 0;i<7;i++)
        advanceDay();
    for(int i =0;i<col;i++)
        harvestRow(i);

}
void farm::printToConsole(){
    //TEST WHAT IT BATCH HOLDS
    for(int x = 0; x<row;x++){
        for(int y = 0; y<col;y++){
            cout << batch[x*col+y].getRipeness() << " ";
        }
        cout << "\n";
    }
    cout << "\nHarvested Kiwis: "<< getHarvestedKiwi() << "\nRotten Kiwis: " << getRottenKiwi() << "\n\n\n";
}
void farm::printToFile(){
    //TEST WHAT IT BATCH HOLDS
    ofstream writeFile(output);
    if(writeFile.is_open()){
        for(int x = 0; x<row;x++){
            for(int y = 0; y<col;y++){
                writeFile << batch[x*col+y].getRipeness() << " ";
            }
            writeFile << "\n";
        }
        writeFile << "\nHarvested Kiwis: "<< getHarvestedKiwi() << "\nRotten Kiwis: " << getRottenKiwi() << "\n\n\n";
    }
}
int farm::getHarvestedKiwi(){return harvestedKiwi;}
int farm::getRottenKiwi(){return rottenKiwi;}
/*
 * 
 */
int main(int argc, char** argv) {
    
    
    
//    kiwi x = kiwi(8);
    ArgumentManager am(argc, argv);
    const string in = am.get("input");
    const string out = am.get("output");
    farm yee = farm(in,out);
    yee.advanceWeek();
    yee.printToFile();
    yee.printToConsole();
        /*yee.printToConsole();
    yee.harvestRow(0);
    yee.printToConsole();
    yee.harvestRow(1);
    yee.printToConsole();
    yee.harvestRow(2);
    yee.printToConsole();
    yee.harvestRow(3);
    yee.printToConsole();*/
    //yee.advanceDay();
    //cout << "" << x.getRipe()<<"\n";
    //cout << "" << x.getRipeness();
    return 0;
}

