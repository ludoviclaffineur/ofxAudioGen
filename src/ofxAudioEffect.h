//
//  ofxAudioEffect.h
//  AudioGenTest
//
//  Created by Ludovic Laffineur on 7/05/15.
//
//

#pragma once

#include "ofxAudioGenConstants.h"

class ofxAudioEffect{
public:
    virtual samples process(samples sample) = 0;
    void byPass(bool byPass){
        mByPass = byPass;
    }

protected:
    bool mByPass = false;
};