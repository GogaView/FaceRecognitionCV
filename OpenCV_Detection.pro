


CONFIG += qt

LIBS += -L/usr/local/lib
INCLUDEPATH = /usr/local/include


LIBS += -lopencv_video \
        -lopencv_ml \
        -lopencv_imgproc \
        -lopencv_highgui \
        -lopencv_core \
        -lopencv_legacy \
        -lopencv_contrib \
        -lopencv_objdetect



HEADERS = \
        src/FaceRecognition.h\
        src/recognition_consts.h

SOURCES = \
        src/main.cpp \
        src/FaceRecognition.cpp