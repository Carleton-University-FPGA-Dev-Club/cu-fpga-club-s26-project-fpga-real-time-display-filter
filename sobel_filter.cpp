
/*
To move from code to your Zybo board, follow this loop:

Vitis HLS: Run "C Simulation." The testbench will use your input.png to generate output.png. Check the output to ensure the Sobel edges look correct.

Synthesis: Run "C Synthesis." This creates the Verilog/VHDL code and the AXI-Stream ports.

Export: Click "Export RTL" to generate an IP block.

Vivado: Open your Block Design, add your new IP from the local repository, and connect it between the HDMI_RX and HDMI_TX cores.

Build: Generate Bitstream and export the hardware (.xsa file) to Vitis IDE to write your C code for the Zynq ARM processor.

Note on Dependencies: For the testbench to work, you must have OpenCV installed on your host computer (Windows or Linux) and link the include paths in your Vitis HLS project settings under Project > Project Settings > Simulation > C Simulation.
*/

#include "common/xf_common.hpp"
#include "imgproc/xf_sobel.hpp"

// Define dimensions (use dynamic parameters if you want, 
// but fixed is better for HLS optimization)
#define HEIGHT 720
#define WIDTH  1280

void sobel_filter_top(xf::cv::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1>& img_in,
                      xf::cv::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1>& img_out) {
    
    // Defines the AXI-Stream interface (Standard for Xilinx VDMA)
    #pragma HLS INTERFACE axis port=img_in
    #pragma HLS INTERFACE axis port=img_out
    #pragma HLS INTERFACE s_axilite port=return bundle=control

    // Internal line buffer configuration for the Sobel kernel
    // The library handles the 3x3 window creation automatically
    xf::cv::Sobel<XF_FILTER_3X3, XF_BORDER_CONSTANT, XF_8UC1, XF_8UC1, HEIGHT, WIDTH, XF_NPPC1>(img_in, img_out);
}
