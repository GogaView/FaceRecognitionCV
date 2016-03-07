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

//proj
#include "FaceRecognition.h"

//boost
#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

namespace boost
{
class thread;
}
typedef boost::shared_ptr<boost::thread> thread_ptr;
class CRecognThread;
typedef boost::shared_ptr<CRecognThread> recognt_ptr;

class CMainFrameAnalyzerThread : public boost::noncopyable
{
    typedef std::list<recognt_ptr> recognt_list;

    recognt_list        m_lRecognList;
    thread_ptr          m_pThread;
    CFaceRecognition    m_faceRecog;
    boost::mutex        m_mutex;
    
public:
    CMainFrameAnalyzerThread();
    
    void    start();
    
    bool    isComplite();
    void    waitEnd();
    
private:
    void    thread_proc();
    
public:
    void    addFrame(const QImage&);
    QImage  getFrame();
};

#endif /* defined(__OpenCV_Detection__MainFrameAnalyzerThread__) */
