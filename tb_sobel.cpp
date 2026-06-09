#include "common/xf_common.hpp"
#include "hls_opencv.h" 

#define HEIGHT 720
#define WIDTH  1280

int main() {
    // 1. Read your test image from the project folder
    cv::Mat img = cv::imread("input.png", 0); 
    
    // 2. Instantiate HLS Mat objects
    xf::cv::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1> img_in(HEIGHT, WIDTH);
    xf::cv::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1> img_out(HEIGHT, WIDTH);
    
    // 3. Move data from OpenCV to HLS stream format
    img_in.copyTo((void*)img.data);
    
    // 4. Call the hardware function
    sobel_filter_top(img_in, img_out);
    
    // 5. Convert output back to viewable format
    cv::Mat res(HEIGHT, WIDTH, CV_8UC1, (void*)img_out.data);
    cv::imwrite("output.png", res);
    
    return 0;
}