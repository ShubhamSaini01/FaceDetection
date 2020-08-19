#include<iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;

int main(int argc, char const *argv[])
{
    Mat src, src_gray;
    Mat grad;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    VideoCapture cap(0);           // Creating VideoCapture object and opening webcam
    if(!cap.isOpened())                  //Checking if opened  
    {
        std::cout << "Error opening Web cam" <<std::endl;
        return -1;
    }
    std::cout<<"Hello";
    while(1)
    {

        Mat frame;                                              // Creating Mat object
        cap >> frame;                                         // Capture frame-by-frame  
        if (frame.empty())                                // If the frame is empty, break immediately
            break;
        GaussianBlur( frame, frame, Size(3,3), 0, 0, BORDER_DEFAULT );
        /// Convert it to gray
        cvtColor( frame, src_gray, COLOR_BGR2GRAY );
        /// Create window
        namedWindow( "srcSobel", WINDOW_AUTOSIZE );
        /// Generate grad_x and grad_y
        Mat grad_x, grad_y;
        Mat abs_grad_x, abs_grad_y;

        /// Gradient X
        //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
        Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
        convertScaleAbs( grad_x, abs_grad_x );

        /// Gradient Y
        //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
        Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
        convertScaleAbs( grad_y, abs_grad_y );

        /// Total Gradient (approximate)
        addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

        imshow( "srcSobel", grad );
        imshow( "VdoFrame", frame );         // Display the frame 
        char a=(char)waitKey(25);                //Press ESC on keyboard to exit/
        if(a==97)
            break;
    } 
    cap.release();                                         // When everything done, release the video capture object  
    destroyAllWindows();   
    return 0;
}
