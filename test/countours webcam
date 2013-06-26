#include "cv.h"
#include "highgui.h"
#include <stdio.h>


using namespace cv;
using namespace std;

//////

Mat src;
Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);
int sigma = 1;

//////
/// Function header
void thresh_callback(int, void* );

int main( int argc, char** argv )
{

    int c;
    CvCapture* capture = 0;
    Mat image,gray_image;

    if( argc == 1 || (argc == 2 && strlen(argv[1]) == 1 && isdigit(argv[1][0])))
        capture = cvCaptureFromCAM( 0 );

    cvNamedWindow( "Input", CV_WINDOW_AUTOSIZE );




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

    for(;;)
    {

        src = cvQueryFrame( capture );
        //Get ROI
         src = src(cvRect(190,180,250,250));
        //Downsample image if needed
        //pyrDown( dst, tmp, Size( dst.cols/2, dst.rows/2 ));
        ///Do processign here


        /// Create Window
        char* source_window = "Source";
        namedWindow( source_window, CV_WINDOW_AUTOSIZE );
        imshow( source_window, src );

        cvCreateTrackbar("Blur", "Source", &sigma, 20, NULL);
        createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
        thresh_callback( 0, 0 );


        ///processing end

        //  imshow( "Input", image );
        //c = cvWaitKey(10);
        c = cvWaitKey(30);
        if( (char)c == 27 )
            break;
    }

    return 0;
}

void thresh_callback(int, void* )
{
    /*
    1 - grayscale - done src_gray

    2- low pass filter (gaussian blur)

    3- canny edge detection

    4- find contours and list their areas.

    5- draw min enclosing circles to your contours.

    6- select the contour which has min enclosing circle area closest to contour area.

    7- find center of mass of the contour using moments F3 type "mass centers"
    */
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    cvtColor( src, src_gray, CV_BGR2GRAY );
    //blur( src_gray, src_gray, Size(3,3) );
    GaussianBlur( src_gray,src_gray, Size(9,9), sigma, sigma );



    /// Detect edges using canny
    Canny( src_gray, canny_output, thresh, thresh*2, 3 );
    /// Find contours
    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    /// Draw contours
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
    }
    ///List contours
    ///draw


    /// Show in a window
    namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    namedWindow( "Gray", CV_WINDOW_AUTOSIZE );
    imshow( "Contours", drawing );
    imshow( "Gray", src_gray );
}
