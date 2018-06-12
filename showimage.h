#ifndef SHOWIMAGE_H
#define SHOWIMAGE_H

#include "HalconCpp.h"
#include "HDevThread.h"
#include <QImage>

using namespace HalconCpp; // !!!

class ShowImage //: public HalconCpp
{
public:
    ShowImage();
    void HtoQimage(HObject himage,QImage **qimage);
private:
    HTuple hc;
    HTuple hChannels;
    HTuple   width,height;
//    width=height=0;
    HTuple htype;
    HTuple hpointer;
};

#endif // SHOWIMAGE_H
