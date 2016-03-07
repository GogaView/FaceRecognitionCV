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
//proj
#include "FaceRecognition.h"
//boost
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

namespace boost
{
class thread;
}
typedef boost::shared_ptr<boost::thread> thread_ptr;

class CRecognThread : public boost::noncopyable
{
    cv::Mat                     m_matOriginFrame;
    QImage                      m_outImage;
    thread_ptr                  m_pThread;
    
    bool                        m_bIsPrevComplite;
    
    CFaceRecognition            m_faceRecog;
    
public:
    CRecognThread(const cv::Mat&, const CFaceRecognition);
    
    void    start();
    QImage  getFrame();
    
    bool    isComplite();
    void    waitEnd();
    
private:
    void    thread_proc();
};

#endif /* defined(__OpenCV_Detection__RecognThread__) */
