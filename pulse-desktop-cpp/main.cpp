#include <iostream>
#include <opencv2/opencv.hpp>

#include "EvmGdownIIR.h"
#include "Window.h"

using namespace std;
using namespace cv;

static void writeVideo(VideoCapture capture, const Mat& frame);

int main(int argc, char** argv) {

    VideoCapture capture("../../vidmagSIGGRAPH2012/face_source_timecode.wmv");
//    VideoCapture capture(0);

    const double FPS = capture.get(CV_CAP_PROP_FPS);
    const int WIDTH = capture.get(CV_CAP_PROP_FRAME_WIDTH);
    const int HEIGHT = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
    cout << "FPS: " << FPS << endl;

    EvmGdownIIR evm;
    evm.load("lbpcascade_frontalface.xml");
    evm.start(WIDTH, HEIGHT);

    Window window(evm);

    Mat frame;
    while (true) {
        capture >> frame;
        if (frame.empty()) {
            break;
        }

        window.update(frame);
        
//        writeVideo(capture, frame);

        if (waitKey(1) == 27) {
            return 0;
        }
    }

    while (waitKey() != 27) {}
    return 0;
}

static void writeVideo(VideoCapture& capture, const Mat& frame) {
    static VideoWriter writer("out.avi",
            CV_FOURCC('X', 'V', 'I', 'D'),
            capture.get(CV_CAP_PROP_FPS),
            Size(capture.get(CV_CAP_PROP_FRAME_WIDTH), 
            capture.get(CV_CAP_PROP_FRAME_HEIGHT)));

    writer << frame;
}