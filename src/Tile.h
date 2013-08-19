//
//  Tile.h
//  imageCompressionExample
//
//  Created by Nick on 2/28/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"



class Tile {
    
    
public:
    Tile();
    ~Tile();
    
    void draw();
    void setup(ofImage _img, int _x, int _y, int _w, int _h);
    
    int x;
    int y;
    int w;
    int h;
    ofImage img;
    
    


};
