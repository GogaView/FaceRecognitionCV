//
//  Detection.h
//  OpenCV_Detection
//
//  Created by MacBook on 19.02.16.
//  Copyright (c) 2016 kosa. All rights reserved.
//

#ifndef OpenCV_Detection_Detection_h
#define OpenCV_Detection_Detection_h

#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/opencv.hpp>

#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;
using namespace cv;

#define UNKNOWN_LEVEL 5
#define flag 9


short readPersons(char* surnameList, vector<Mat> &images1, vector <String> &surnames, vector <int> &kol){
    
    CascadeClassifier haar_lefteye, haar_righteye;
    haar_lefteye.load("/usr/local/share/OpenCV/haarcascades/haarcascade_mcs_lefteye.xml");
    haar_righteye.load("/usr/local/share/OpenCV/haarcascades/haarcascade_mcs_righteye.xml");
    
    Mat tmp;
    
    vector<Rect> lEyes, rEyes;
    Mat eyeImage;
    
    FILE* surns = fopen(surnameList, "rb");
    if(surns == 0)
    {
        return 0;
    }
    
    for(int i = 0; true; i++)
    {
        char buf[256];
        sprintf(buf, "Face%d.bmp", i + 1);
        FILE* imgChk = fopen(buf, "rb");
        if(!imgChk)
        {
            fclose(surns);
            return 1;
        }
        
        images1.push_back(imread(buf, 0));
        kol.push_back(i);
        
        char s[256];
        fgets(s, 50, surns);
        
        fclose(imgChk);
        surnames.push_back(s);
    }
}

void detectio_func()
{
    vector<Mat> images1;
    vector<int> kol;
    
    vector<String> surnames;
    
    readPersons("names.pr",images1,surnames,kol);
    
    int im_width = images1[0].cols;
    int im_height = images1[0].rows;
    
    int num_components = images1.size();
    double threshold = UNKNOWN_LEVEL;
    
//    Ptr<FaceRecognizer> model1 = createFisherFaceRecognizer(num_components,threshold);
    Ptr<FaceRecognizer> model1 = createEigenFaceRecognizer(num_components,threshold);
    
    
    kol.push_back(kol[0]);
    images1.push_back(images1[0]);
    
    model1->train(images1, kol);
    
    CascadeClassifier haar_cascade;
    haar_cascade.load("/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml");
    
    
    
    VideoCapture cap(0);
    Mat frame;
    
    for(;;)
    {
        cap >> frame;
        
        Mat original = frame.clone();
        Mat gray;
        
        cvtColor(original, gray, CV_BGR2GRAY);
        
        equalizeHist(gray, gray);
        
        vector< Rect_<int> > faces;

        haar_cascade.detectMultiScale(gray, faces, 1.1, 3, /*CASCADE_FIND_BIGGEST_OBJECT*/CASCADE_DO_ROUGH_SEARCH);
        
        for(int i = 0; i < faces.size(); i++)
        {
            
            Rect face_i = faces[i];
            
            Mat face = gray(face_i);
            
            Mat face_resized, L, R;
            cv::resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);
                
            int prediction = model1->predict(face_resized);
                
            rectangle(original, face_i, CV_RGB(255,0,0), 1);
            
            string box_text;
                
                
            if (prediction != -1)
            {
                box_text.append("Prediction = ");
                    
                box_text.append(surnames[prediction]);
            }
            else
            {
                box_text.append("Unknown person");
            }
            
            int pos_x = max(face_i.tl().x - 10, 0);
            int pos_y = max(face_i.tl().y - 10, 0);
                
            putText(original, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 2.0);
        }
        
        imshow("face_recognizer", original);
        char key = (char) waitKey(20);
        if(key == 27)
            break;
    }
}


#endif
