#include "cv.h"
#include "highgui.h"
#include <stdio.h>

//fps clac
#define h 280
#define w 320

using namespace cv;
using namespace std;

//////
Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Edge Map";
//////


/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
void CannyThreshold(int, void*)
{
    /// Reduce noise with a kernel 3x3
    blur( src_gray, detected_edges, Size(3,3) );

    /// Canny detector
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

    /// Using Canny's output as a mask, we display our result
    dst = Scalar::all(0);

    src.copyTo( dst, detected_edges);
    imshow( window_name, dst );
}

int main( int argc, char** argv )
{

    int c;
    CvCapture* capture = 0;
    Mat image,gray_image;
    //FPS variables
    time_t start,end;
    Point org;
    org.x = 10;
    org.y = 50;
    int fonttype = 2; //0 to 8  FONT_HERSHEY_SIMPLEX , FONT_HERSHEY_PLAIN , FONT_HERSHEY_DUPLEX ,
    //        FONT_HERSHEY_COMPLEX , FONT_HERSHEY_TRIPLEX , FONT_HERSHEY_COMPLEX_SMALL ,
    //        FONT_HERSHEY_SCRIPT_SIMPLEX or FONT_HERSHEY_SCRIPT_COMPLEX
    int scale = 1; //0.1 to 5
    int colour = 0; //0 to 255
    int thickness = 2; //0 to 10
    int lineType = 8;
    ostringstream str;
    double sec;//perviously double
    double fps;//perviously double
    //fps end


    if( argc == 1 || (argc == 2 && strlen(argv[1]) == 1 && isdigit(argv[1][0])))
        capture = cvCaptureFromCAM( 0 );

    cvNamedWindow( "Input", CV_WINDOW_AUTOSIZE );

    int param1=200, param2=100,min=0,max=0,sigma=1;
    //createTrackbar(trackbarname, windowname, int* value, int count, TrackbarCallback onChange CV_DEFAULT(0), void* userdata CV_DEFAULT(0))
    cvCreateTrackbar("Parameter1", "Input", &param1, 500, NULL);
    cvCreateTrackbar("Parameter2", "Input", &param2, 500, NULL);
    cvCreateTrackbar("Min Raduis", "Input", &min, 10, NULL);
    cvCreateTrackbar("Max Radius", "Input", &max, 10, NULL);
    cvCreateTrackbar("Blur", "Input", &sigma, 10, NULL);

    ///Wait for cam to stabilize , press ESC when ready
    for(;;)
    {
        image = cvQueryFrame( capture );
//        cvAddS(image, cvScalar(bright-128,bright-128,bright-128), image);

        //flip(image,image,1);
        imshow( "Input", image );
        c = cvWaitKey(10);
        if( (char)c == 27 )
            break;
    }
    time(&start);
    int counter=0;

    for(;;)
    {

        src = cvQueryFrame( capture );
        //Downsample image if needed
        //pyrDown( dst, tmp, Size( dst.cols/2, dst.rows/2 ));
        ///Do processign here
        dst.create( src.size(), src.type() );

        /// Convert the image to grayscale
        cvtColor( src, src_gray, CV_BGR2GRAY );

        /// Create a window
        namedWindow( window_name, CV_WINDOW_AUTOSIZE );

        /// Create a Trackbar for user to enter threshold
       // createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );


        /// Show the image
        CannyThreshold(0, 0);

        ///processing end
        //fps
        time(&end);
        ++counter;
        sec=difftime(end,start);
        fps=counter/sec;
        //printf("\n%lf",fps); //prints on console
        ostringstream str; //prints on itself
        str << "FPS: " << (int)fps;
        putText( src,  str.str() , org, fonttype, scale, colour, thickness, lineType);
        //fps end


      //  imshow( "Input", image );
        //c = cvWaitKey(10);
        c = cvWaitKey(30);
        if( (char)c == 27 )
            break;
    }

    return 0;
}

