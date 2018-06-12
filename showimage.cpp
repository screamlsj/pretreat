#include "showimage.h"
#include "HalconCpp.h"
#include "HDevThread.h"
#include <X11/Xlib.h>

ShowImage::ShowImage()
{

}
void rgb3_to_interleaved (HObject ho_ImageRGB, HObject *ho_ImageInterleaved);
void rgb3_to_interleaved (HObject ho_ImageRGB, HObject *ho_ImageInterleaved)
{

  // Local iconic variables
  HObject  ho_ImageAffineTrans, ho_ImageRed, ho_ImageGreen;
  HObject  ho_ImageBlue, ho_RegionGrid, ho_RegionMoved, ho_RegionClipped;

  // Local control variables
  HTuple  hv_PointerRed, hv_PointerGreen, hv_PointerBlue;
  HTuple  hv_Type, hv_Width, hv_Height, hv_HomMat2DIdentity;
  HTuple  hv_HomMat2DScale;

  GetImagePointer3(ho_ImageRGB, &hv_PointerRed, &hv_PointerGreen, &hv_PointerBlue,
      &hv_Type, &hv_Width, &hv_Height);
  GenImageConst(&(*ho_ImageInterleaved), "byte", hv_Width*3, hv_Height);
  //
  HomMat2dIdentity(&hv_HomMat2DIdentity);
  HomMat2dScale(hv_HomMat2DIdentity, 1, 3, 0, 0, &hv_HomMat2DScale);
  AffineTransImageSize(ho_ImageRGB, &ho_ImageAffineTrans, hv_HomMat2DScale, "constant",
      hv_Width*3, hv_Height);
  //
  Decompose3(ho_ImageAffineTrans, &ho_ImageRed, &ho_ImageGreen, &ho_ImageBlue);
  GenGridRegion(&ho_RegionGrid, 2*hv_Height, 3, "lines", hv_Width*3, hv_Height+1);
  MoveRegion(ho_RegionGrid, &ho_RegionMoved, -1, 0);
  ClipRegion(ho_RegionMoved, &ho_RegionClipped, 0, 0, hv_Height-1, (3*hv_Width)-1);
  //NOTE: Due to internal limitations, the images ImageRed, ImageGreen, and ImageBlue
  //cannot be displayed by HDevelop.Trying to display one of these images results in the
  //error message 'Internal error: number of chords too big for num_max'. However, this
  //affects by no means the continuation or the results of this example program, and
  //therefore, is no reason to be alarmed !
  ReduceDomain(ho_ImageRed, ho_RegionClipped, &ho_ImageRed);
  MoveRegion(ho_RegionGrid, &ho_RegionMoved, -1, 1);
  ClipRegion(ho_RegionMoved, &ho_RegionClipped, 0, 0, hv_Height-1, (3*hv_Width)-1);
  ReduceDomain(ho_ImageGreen, ho_RegionClipped, &ho_ImageGreen);
  MoveRegion(ho_RegionGrid, &ho_RegionMoved, -1, 2);
  ClipRegion(ho_RegionMoved, &ho_RegionClipped, 0, 0, hv_Height-1, (3*hv_Width)-1);
  ReduceDomain(ho_ImageBlue, ho_RegionClipped, &ho_ImageBlue);
  OverpaintGray((*ho_ImageInterleaved), ho_ImageRed);
  OverpaintGray((*ho_ImageInterleaved), ho_ImageGreen);
  OverpaintGray((*ho_ImageInterleaved), ho_ImageBlue);
  return;
}
void ShowImage::HtoQimage(HObject himage,QImage **qimage)
{


    ConvertImageType(himage,&himage,"byte");//将图片转化成byte类型
    CountChannels(himage,&hChannels);       //判断图像通道数


    if(hChannels[0].I()==1)//单通道图
    {
        unsigned char *ptr;

        GetImagePointer1(himage,&hpointer,&htype,&width,&height);

        ptr=(unsigned char *)hpointer[0].L();
        *(*qimage)=QImage(ptr,width,height,width,QImage::Format_Indexed8);//不知道是否已自动4字节对齐
    }
    else if(hChannels[0].I()==3)//三通道图
    {
        unsigned char *ptr3;

        HObject ho_ImageInterleaved;
        rgb3_to_interleaved(himage, &ho_ImageInterleaved);
        GetImagePointer1(ho_ImageInterleaved, &hpointer, &htype, &width, &height);

        ptr3=(unsigned char *)hpointer[0].L();
        *(*qimage)=QImage(ptr3,width/3,height,width,QImage::Format_RGB888);
    }
}
