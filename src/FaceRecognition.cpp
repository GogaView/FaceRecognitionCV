//
//  FaceRecognition.cpp
//  OpenCV_Detection
//
//  Created by MacBook on 20.02.16.
//  Copyright (c) 2016 kosa. All rights reserved.
//

#include "FaceRecognition.h"
#include "recognition_consts.h"

//opencv
#include <opencv2/opencv.hpp>

//qt
#include <QtGui/QImage>

#include <iostream>
#include <stdio.h>
#include <vector>

CFaceRecognition::CFaceRecognition()
{
    m_bIsValid = _init();
}


bool CFaceRecognition::_init()
{
    if(!_readPreson())
    {
        std::cout << "ERROR: Can not load persons params!" << std::endl;
        return false;
    }
    
    if(!_initRecognition())
    {
        std::cout << "ERROR: Can not init recognitions params!" << std::endl;
        return false;
    }
    
    if(!_initCam())
    {
        std::cout << "ERROR: Can not load cam!" << std::endl;
        return false;
    }
    
    if(!_initHaarCascade())
    {
        std::cout << "ERROR: Can not load Haar cascades!" << std::endl;
        return false;
    }
    
    _initSize();
    
    return true;
    
}

bool CFaceRecognition::_readPreson()
{
    FILE* surns = fopen(rec_const::c_strNamesFile.c_str(), "rb");
    if(surns == 0)
    {
        std::cout << "No muth file: " << rec_const::c_strNamesFile << std::endl;
        
        return false;
    }
    
    for(int i = 0; true; i++)
    {
        char buf[256];
        sprintf(buf, rec_const::c_strFaceFile.c_str(), i + 1);
        
        FILE* imgChk = fopen(buf, "rb");
        if(!imgChk)
        {
            fclose(surns);
            return true;
        }
        
        m_vFaces.push_back(cv::imread(buf, 0));
        m_vLables.push_back(i);
        
        char s[256];
        fgets(s, 50, surns);
        
        fclose(imgChk);
        m_vNames.push_back(s);
    }
    
    if(m_vFaces.size() == 0)
        return false;
    else
        return true;
}

bool CFaceRecognition::_initRecognition()
{
    int num_components = m_vFaces.size();
    double threshold = rec_const::c_iUnknownLevel;
    
    //    m_ptrModel = createFisherFaceRecognizer(num_components,threshold);
    m_ptrModel = cv::createEigenFaceRecognizer(num_components,threshold);
    
    m_ptrModel->train(m_vFaces, m_vLables);
    
    return true;
}

bool CFaceRecognition::_initCam()
{
    m_cam = cv::VideoCapture(0);
    
    return m_cam.isOpened();
}

bool CFaceRecognition::_initHaarCascade()
{
    m_HaarCascade.load(rec_const::c_strHaarFace);
    return true;
}


void CFaceRecognition::_initSize()
{
    m_iWidth = m_vFaces[0].cols;
    m_iHeight = m_vFaces[0].rows;
}

bool CFaceRecognition::isValid()
{
    return m_bIsValid;
}

cv::Mat CFaceRecognition::getFrame()
{
    cv::Mat frame;
    
    m_cam >> frame;
    
//    return frame;
    
    cv::Mat original = frame.clone();
    cv::Mat gray;
    
    cvtColor(original, gray, CV_BGR2GRAY);
    
    equalizeHist(gray, gray);
    
    std::vector< cv::Rect_<int> > faces;
    
    m_HaarCascade.detectMultiScale(gray, faces, 1.1, 3, /*CASCADE_FIND_BIGGEST_OBJECT*/cv::CASCADE_DO_ROUGH_SEARCH);
    
    for(int i = 0; i < faces.size(); i++)
    {
        
        cv::Rect face_i = faces[i];
        
        cv::Mat face = gray(face_i);
        
        cv::Mat face_resized, L, R;
        cv::resize(face, face_resized, cv::Size(m_iWidth, m_iHeight), 1.0, 1.0, cv::INTER_CUBIC);
        
        int prediction = m_ptrModel->predict(face_resized);
        
        rectangle(original, face_i, CV_RGB(255,0,0), 1);
        
        std::string box_text;
        
        
        if (prediction != -1)
        {
            box_text.append("Prediction = ");
            
            box_text.append(m_vNames[prediction]);
        }
        else
        {
            box_text.append("Unknown person");
        }
        
        int pos_x = cv::max(face_i.tl().x - 10, 0);
        int pos_y = cv::max(face_i.tl().y - 10, 0);
        
        putText(original, box_text, cv::Point(pos_x, pos_y), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 2.0);
    }

    QImage img = QImage((uchar*) original.data, original.cols, original.rows, original.step, QImage::Format_RGB888);
    
    return original;
}


