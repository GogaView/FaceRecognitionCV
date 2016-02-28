//
//  RecognThread.h
//  OpenCV_Detection
//
//  Created by MacBook on 21.02.16.
//
//

#ifndef __OpenCV_Detection__RecognThread__
#define __OpenCV_Detection__RecognThread__

//opencv
#include <opencv2/opencv.hpp>

//Qt
#include <QImage>

#ifndef Q_MOC_RUN
//boost
#include <boost/thread.hpp>
#endif

//proj
#include <FaceRecognition.h>

class CRecognThread
{
    cv::Mat                     m_matOriginFrame;
    QImage                      m_outImage;
    boost::thread*              m_pThread;
    
    bool                        m_bIsPrevComplite;
    
    CFaceRecognition            m_faceRecog;
    
public:
                                CRecognThread(const cv::Mat&, const CFaceRecognition);
    ~CRecognThread();
    
    void                        start();
    QImage                      getFrame();
    
    bool                        isComplite();
    void                        waitEnd();
    
private:
    void                        thread_proc();
};

#endif /* defined(__OpenCV_Detection__RecognThread__) */
