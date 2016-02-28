//
//  MainWindow.h
//  OpenCV_Detection
//
//  Created by MacBook on 20.02.16.
//
//

#ifndef __OpenCV_Detection__MainWindow__
#define __OpenCV_Detection__MainWindow__

#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include <QTimer>

#include "FaceRecognition.h"
#include "MainFrameAnalyzerThread.h"


class CCamMainWindow : public QWidget
{
    Q_OBJECT
    
    CMainFrameAnalyzerThread m_analyser;
    QLabel*                 m_pLabel;
    QTimer                  m_timer;
    
    QList<QImage>           m_lFrams;
    
public:
    CCamMainWindow(QWidget* parent = 0, Qt::WindowFlags f = 0);
    
    void                    initGui();
    
public slots:
    void                    startShow();
    
private:
    void                    createConnect();
    
};

#endif /* defined(__OpenCV_Detection__MainWindow__) */
