//
//  RecognThread.cpp
//  OpenCV_Detection
//
//  Created by MacBook on 21.02.16.
//
//

#include "RecognThread.h"


CRecognThread::CRecognThread(const cv::Mat& frame, const CFaceRecognition            faceRecog)
    :m_matOriginFrame(frame),
    m_faceRecog(faceRecog)
{
//    m_faceRecog.init();
//    m_faceRecog.fastInit();
}

CRecognThread::~CRecognThread()
{
    delete m_pThread;
}

void CRecognThread::start()
{
    m_pThread = new boost::thread(boost::bind(&CRecognThread::thread_proc, this));
}

void CRecognThread::thread_proc()
{
    cv::Mat frame = m_faceRecog.recognFrame(m_matOriginFrame);
    
    m_outImage = QImage((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);

}

QImage CRecognThread::getFrame()
{
    return m_outImage;
}


void CRecognThread::waitEnd()
{
    m_pThread->join();
}