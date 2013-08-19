//
//  Tile.cpp
//  imageCompressionExample
//
//  Created by Nick on 2/28/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "Tile.h"


Tile::Tile() {
    
}

Tile::~Tile() {
    
}

void Tile::setup(ofImage _img, int _x, int _y, int _w, int _h) {
    
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    img = _img;
    
}

void Tile::draw() {
    
    img.draw(x, y, w, h);
    
}


