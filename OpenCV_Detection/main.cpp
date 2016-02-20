#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>

#include <unistd.h>
#include "FaceRecognition.h"

using namespace std;
using namespace cv;

int main( int argc, const char** argv )
{
    CFaceRecognition* face = new CFaceRecognition();
    
    if(face->isValid())
    {
        cv::Mat frame;
        
        while(true)
        {
            frame = face->getFrame();
            cv::imshow("face",frame);
            
//            usleep(1000000);
            char key = (char) waitKey(1);
            if(key == 27)
                break;
            
        }
    }
    
    
}
