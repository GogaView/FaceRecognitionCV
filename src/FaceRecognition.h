//
//  FaceRecognition.h
//  OpenCV_Detection
//
//  Created by MacBook on 20.02.16.
//  Copyright (c) 2016 kosa. All rights reserved.
//

#ifndef __OpenCV_Detection__FaceRecognition__
#define __OpenCV_Detection__FaceRecognition__

//std
#include <stdio.h>
#include <vector>

//opencv
#include <opencv2/opencv.hpp>



class CFaceRecognition
{
    cv::VideoCapture            m_cam;
    
    std::vector<cv::Mat>        m_vFaces;
    std::vector<std::string>    m_vNames;
    std::vector<int>            m_vLables;
    
    cv::Ptr<cv::FaceRecognizer> m_ptrModel;
    cv::CascadeClassifier       m_HaarCascade;
    
    int                         m_iWidth;
    int                         m_iHeight;
    
    bool                        m_bIsValid;
    
    
public:
                                CFaceRecognition();
    
public:
    bool                        isValid();
    cv::Mat                     getFrame();
    
private:
    bool                        _init();
    bool                        _readPreson();
    bool                        _initRecognition();
    bool                        _initCam();
    bool                        _initHaarCascade();
    void                        _initSize();
    
    
};


#endif /* defined(__OpenCV_Detection__FaceRecognition__) */
