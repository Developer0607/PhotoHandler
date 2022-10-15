/*Photo Handler v1.0.0.0
  Copyright (C) Wang Jianlin
*/

#include<fstream>
#include<iostream>
#include<cstring>
using namespace std;

#define DEBUG 0

//bitmap head struct
struct tagBITMAPFILEHEADER 
{  
    short bfType;
    int bfSize;
    short bfReserved1;
    short bfReserved2;
    int bfOffBits;
}; 

struct BMPINFOHEAD{
    int biSize;
    int biWidth;
    int biHeight;
    short biPlanes;
    short biBitCount;
    int biCompression;
    int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    int biClrUsed;
    int biClrImportant;
} bmpinfohead;

struct pel{
    unsigned char R;
    unsigned char G;
    unsigned char B;
}Pel,map[100000005];

int main(int argc, char **argv){
    char ifpath[1005], ofpath[1005];
    if(!DEBUG){
        if(argc < 2 || argc > 3){
        return -1;
    }
    
    if(argc == 3){
        strcpy(ifpath, argv[1]);
        strcpy(ofpath, argv[2]);
    }else{
        strcpy(ifpath, argv[0]);
        strcpy(ofpath, argv[1]);
    }}
    if(DEBUG){
        strcpy(ifpath, "page1.bmp");
        strcpy(ofpath, "test.bmp");
    }
    tagBITMAPFILEHEADER bmphead;

    ifstream fin (ifpath, ios::in  | ios::binary);
    ofstream fout(ofpath, ios::out | ios::binary);

    //read file head

    fin.read((char *) & bmphead,     14);
    fin.read((char *) & bmpinfohead, 40);

    if(bmpinfohead.biCompression != 0){
        cout << "not support yet!\n";
        //if(!DEBUG)return -2;
    }

    

    int xpels = bmpinfohead.biHeight;
    int ypels = bmpinfohead.biWidth;
    if(DEBUG){
        cout << sizeof(bmphead) << '\n' << sizeof(bmpinfohead) << '\n' << bmpinfohead.biCompression << '\n'
        << bmphead.bfOffBits << '\n';
        cout << bmpinfohead.biHeight <<'\n' <<bmpinfohead.biWidth<<'\n';
    }
    //pel ;
    int x;
    for(int i = 0;i < xpels;i ++){
        for(int j = 0;j < ypels;j ++){
            
            fin.read((char *) & Pel, 3);
            /*if(DEBUG){
                map[i * ypels + j] = Pel;
                continue;
            }*/
            if((Pel.B + Pel.G + Pel.R) <= 384){
                map[i * ypels + j]={0,0,0};
            }else{
                map[i * ypels + j]={(unsigned char)255,(unsigned char)255,(unsigned char)255};
            }
        }
    }

    fout.write((const char *) & bmphead, 14);
    fout.write((const char *) & bmpinfohead, sizeof(bmpinfohead));
    fout.write((char *) & map, xpels * ypels * 3);

    return 0;

}