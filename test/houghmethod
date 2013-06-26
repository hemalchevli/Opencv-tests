#include "cv.h"
#include "highgui.h"
#include <stdio.h>

//fps clac
#define h 280
#define w 320

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{

    int c;
    CvCapture* capture = 0;
    Mat image,gray_image,sub_Image,dst;


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

        cvtColor( image,image, CV_BGR2GRAY );
        equalizeHist( image,dst );

        imshow( "Input", dst);
        c = cvWaitKey(10);
        if( (char)c == 27 )
            break;
    }

    for(;;)
    {

        image = cvQueryFrame( capture );
        //if( !image ) break;

        //subImage = image(cvRect(10,10,50,50));
        //x y width and height
        image = image(cvRect(190,180,250,250)); //make roi smaller

        //Downsample image if needed
        //pyrDown( dst, tmp, Size( dst.cols/2, dst.rows/2 ));
        ///Do processign here

        //Flip image optional
        //flip(image,image,1);
        //convert to grayscale
        cvtColor( image, gray_image, CV_BGR2GRAY );

        //histogram equlization
      //  cvtColor( image,image, CV_BGR2GRAY );
       // equalizeHist( image,dst );

        //blur to remove noise
        GaussianBlur( image, image, Size(9,9), sigma, sigma );

        ///Detect circles Start
        vector<Vec3f> circles;

        // Apply the Hough Transform to find the circles
        HoughCircles( gray_image, circles, CV_HOUGH_GRADIENT, 2, gray_image.rows/4, param1,param2, min,max );
        //HoughCircles( gray_image, circles, CV_HOUGH_GRADIENT, 2, gray_image.rows/8, 200, 100, 0,0 );

        // Draw the circles detected
        for( size_t i = 0; i < circles.size(); i++ )
        {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            // circle center
            circle( image, center, 3    , Scalar(0,255,0), -1, 8, 0 );
            // circle outline
            circle( image, center, radius, Scalar(0,0,255), 3, 8, 0 );
        }
        ///Circle detect end

        ///processing end
        imshow( "Input", image );
        //c = cvWaitKey(10);
        c = cvWaitKey(15);
        if( (char)c == 27 )
            break;
    }

    return 0;
}
