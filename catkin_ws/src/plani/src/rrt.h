#include <stdlib.h>
#include <stdio.h>
/*

#include <opencv2/highgui/highgui.hpp>*/
#include <iostream>
//#include "opencv/cv.h"
//#include "btree.h"
#include "opencv2/core/version.hpp"
#if CV_MAJOR_VERSION == 2
// do opencv 2 code
#elif CV_MAJOR_VERSION == 3
// do opencv 3 code
#endif

#include <opencv2/opencv.hpp>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <ctime>

using namespace cv;
using namespace std;

int loadimage(char* chemin);
