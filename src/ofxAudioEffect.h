#pragma once

#include "ofxBaseAudioGen.h"

class ofxAudioEffect{
public:
    virtual samples process(samples sample) = 0;
    void byPass(bool byPass){
        mByPass = byPass;
    }

protected:
    bool mByPass = false;
};