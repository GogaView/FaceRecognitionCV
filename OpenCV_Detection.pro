TEMPLATE = app
CONFIG += qt
QT += core gui widgets

LIBS += -L/usr/local/lib
INCLUDEPATH += /usr/local/include


LIBS += -lopencv_video \
        -lopencv_ml \
        -lopencv_imgproc \
        -lopencv_highgui \
        -lopencv_core \
        -lopencv_legacy \
        -lopencv_contrib \
        -lopencv_objdetect \
        -lboost_system \
        -lboost_thread



HEADERS = \
        src/FaceRecognition.h\
        src/recognition_consts.h \
        src/CamMainWindow.h \
        src/RecognThread.h \
        src/MainFrameAnalyzerThread.h

SOURCES = \
        src/main.cpp \
        src/FaceRecognition.cpp \
        src/CamMainWindow.cpp \
        src/RecognThread.cpp \
        src/MainFrameAnalyzerThread.cpp
