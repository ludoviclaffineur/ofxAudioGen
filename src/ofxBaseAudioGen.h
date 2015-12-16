#pragma once

#include <ofSoundStream.h>

#include <stdio.h>
#include <string.h>
#include <deque>
#include <math.h>
#include <algorithm>

#ifndef M_PI
#define M_PI  (3.1415926535897932)
#endif


const int       BUFFER_SIZE		= 512;
const int       SAMPLE_RATE     = 44100;
const float     SQRT2           = 1.4142135623730951;

struct samples{
    float left  = 0;
    float right = 0;
};

enum ButterworthFilterType {LP, HP, BP, BR };


