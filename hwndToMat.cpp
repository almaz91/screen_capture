#include "hwndToMat.h"

HwndToMat::HwndToMat(HWND hwindow, float scale)
{
    this->hwnd = hwindow;
    this->hwindowDC = GetDC(this->hwnd);                                        
    this->hwindowCompatibleDC = CreateCompatibleDC(this->hwindowDC);           
    SetStretchBltMode(this->hwindowCompatibleDC, COLORONCOLOR);

    RECT windowsize;    // get the height and width of the screen
    GetClientRect(this->hwnd, &windowsize);

    this->srcheight = windowsize.bottom;
    this->srcwidth = windowsize.right;
    this->height = (int)(windowsize.bottom * scale);
    this->width = (int)(windowsize.right * scale);

    this->image.create(this->height, this->width, CV_8UC4);

    this->hbwindow = CreateCompatibleBitmap(this->hwindowDC, this->width, this->height);

    this->bi.biSize = sizeof(BITMAPINFOHEADER);
    this->bi.biWidth = this->width;
    this->bi.biHeight = -this->height;
    this->bi.biPlanes = 1;
    this->bi.biBitCount = 32;
    this->bi.biCompression = BI_RGB;
    this->bi.biSizeImage = 0;
    this->bi.biXPelsPerMeter = 0;
    this->bi.biYPelsPerMeter = 0;
    this->bi.biClrUsed = 0;
    this->bi.biClrImportant = 0;

    SelectObject(this->hwindowCompatibleDC, this->hbwindow);
    this->Read();
};

void HwndToMat::Read()
{
    // copy from the window device context to the bitmap device context
    StretchBlt(this->hwindowCompatibleDC, 0, 0, this->width, this->height, this->hwindowDC, 0, 0, this->srcwidth, this->srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
    GetDIBits(this->hwindowCompatibleDC, this->hbwindow, 0, this->height, this->image.data, (BITMAPINFO*)&(this->bi), DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow
};

cv::Mat HwndToMat::GetImage()
{
    return this->image;
}

HwndToMat::~HwndToMat()
{
    DeleteObject(this->hbwindow);
    DeleteDC(this->hwindowCompatibleDC);
    ReleaseDC(this->hwnd, this->hwindowDC);
};
