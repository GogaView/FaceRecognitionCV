//
//  MainFrameAnalyzerThread.h
//  OpenCV_Detection
//
//  Created by MacBook on 21.02.16.
//
//

#ifndef __OpenCV_Detection__MainFrameAnalyzerThread__
#define __OpenCV_Detection__MainFrameAnalyzerThread__

//Qt
#include <QImage>

#ifndef Q_MOC_RUN
//boost
#include <boost/thread.hpp>
#endif

//proj
#include "FaceRecognition.h"
#include "RecognThread.h"

class CMainFrameAnalyzerThread
{
    std::list<CRecognThread*>   m_lRecognList;
    
    boost::thread*              m_pThread;
    CFaceRecognition            m_faceRecog;
    
    boost::mutex                m_mutex;
    
public:
                                CMainFrameAnalyzerThread();
    
    void                        start();
    
    bool                        isComplite();
    void                        waitEnd();
    
private:
    void                        thread_proc();
    
public:
    void                        addFrame(const QImage&);
    QImage                      getFrame();
};





#endif /* defined(__OpenCV_Detection__MainFrameAnalyzerThread__) */
