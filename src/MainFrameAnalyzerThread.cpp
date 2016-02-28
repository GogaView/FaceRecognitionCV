//
//  MainFrameAnalyzerThread.cpp
//  OpenCV_Detection
//
//  Created by MacBook on 21.02.16.
//
//

#include "MainFrameAnalyzerThread.h"



CMainFrameAnalyzerThread::CMainFrameAnalyzerThread()
{
    m_faceRecog.init();
}

void CMainFrameAnalyzerThread::start()
{
    if(m_pThread != 0)
    {
        if(m_pThread->joinable())
        {
            return;
        }
    }
    
    m_pThread = new boost::thread(boost::bind(&CMainFrameAnalyzerThread::thread_proc, this));
    
    
    
}

void CMainFrameAnalyzerThread::thread_proc()
{
    while(true)
    {
        boost::unique_lock<boost::mutex> lock(m_mutex);
//        m_mutex.lock();
        
        if(m_lRecognList.size() >= 2)
        {
//            m_mutex.unlock();
            continue;
            
        }
        
        cv::Mat frame = m_faceRecog.getFrame();
        
        CRecognThread* newThread = new CRecognThread(frame,m_faceRecog);
        newThread->start();
        
        m_lRecognList.push_back(newThread);
     
//        m_mutex.unlock();
    }
}

QImage CMainFrameAnalyzerThread::getFrame()
{
    boost::unique_lock<boost::mutex> lock(m_mutex);
    
    QImage img;
    
//    m_mutex.lock();
    
    if(m_lRecognList.size() != 0)
    {
        CRecognThread* pTh = m_lRecognList.front();
        if(pTh == 0)
        {
            return img;
        }
        
        pTh->waitEnd();
        img = pTh->getFrame();
        m_lRecognList.pop_front();
    }
//    m_mutex.unlock();
    
    return img;
}

void CMainFrameAnalyzerThread::waitEnd()
{
    m_pThread->join();
}