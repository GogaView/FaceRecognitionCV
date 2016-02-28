#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>

#include <QtCore>
#include <QtGui>

//#include "FaceRecognition.h"
#include "CamMainWindow.h"


int main( int argc, char** argv )
{
    QApplication app(argc, argv);
    CCamMainWindow window;
//    window.initGui();
    
    window.show();
    
    return app.exec();    
    
}
