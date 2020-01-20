#include <stdlib.h>
#include <stdio.h>
#include <iostream>
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
