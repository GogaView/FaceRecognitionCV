//
//  recognition_consts.h
//  OpenCV_Detection
//
//  Created by MacBook on 20.02.16.
//  Copyright (c) 2016 kosa. All rights reserved.
//

#ifndef OpenCV_Detection_recognition_consts_h
#define OpenCV_Detection_recognition_consts_h

namespace rec_const {
    static const std::string c_strHaarFace  = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";
    static const std::string c_strNamesFile = "Recognition_names";
    static const std::string c_strFaceFile  = "Face%d.bmp";
    
    static const int c_iUnknownLevel        = 5;
}

#endif
