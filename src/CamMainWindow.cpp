//
//  MainWindow.cpp
//  OpenCV_Detection
//
//  Created by MacBook on 20.02.16.
//
//

#include "CamMainWindow.h"

#include <QPixmap>
#include <QObject>
#include <QGridLayout>



CCamMainWindow::CCamMainWindow(QWidget* parent, Qt::WindowFlags f)
    :QWidget(parent,f)
{

    initGui();
    m_analyser.start();
}

void CCamMainWindow::initGui()
{
    m_pLabel = new QLabel(this);
    QGridLayout* grid = new QGridLayout(this);
    grid->addWidget(m_pLabel);
    setLayout(grid);
//    m_pLabel->resize(400, 300);
    m_pLabel->setFixedSize(900,600);
    m_timer.start(33);
    createConnect();
}

void CCamMainWindow::createConnect()
{
    connect(&m_timer, SIGNAL(timeout()),this, SLOT(startShow()));
}

void CCamMainWindow::startShow()
{
    QImage img = m_analyser.getFrame();
    if(!img.isNull())
    {
        m_pLabel->setPixmap(QPixmap::fromImage(img));
    }
    
    repaint();
//    msleep(200);

    
    
}