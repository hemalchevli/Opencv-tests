#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Mat src;
Mat original;
Mat src_gray;
int thresh = 119;
int max_thresh = 255;
RNG rng(12345);

/// Function header
void thresh_callback(int, void* );

void MyFilledCircle( Mat img, Point center );

/** @function main */
int main( int argc, char** argv )
{

////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////
    /// Load source image and convert it to gray
    //src = imread( argv[1], 1 );
   // original = imread( argv[1], 1 );
    ///Get ROI
    //src = src(cvRect(250,190,150,150)); //make roi smaller
  //  src = original(cvRect(250,190,150,150)); //make roi smaller

    /// Convert image to gray and blur it
    cvtColor( src, src_gray, CV_BGR2GRAY );
    blur( src_gray, src_gray, Size(5,5) );

    /// Create Window
//    char* source_window = "Source";
    String source_window = "Source";
    namedWindow( source_window, CV_WINDOW_AUTOSIZE );
    imshow( source_window, src );

    createTrackbar( " Threshold:", "Source", &thresh, max_thresh, thresh_callback );
    thresh_callback( 0, 0 );

  c = cvWaitKey(300);
        if( (char)c == 27 )
            break;
    }
    return(0);
}

/** @function thresh_callback */
void thresh_callback(int, void* )
{
    Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    /// Detect edges using Threshold
    threshold( src_gray, threshold_output, thresh, 255, THRESH_BINARY );
    /// Find contours
    findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    /// Approximate contours to polygons + get bounding rects and circles
    vector<vector<Point> > contours_poly( contours.size() );
    vector<Rect> boundRect( contours.size() );
    vector<Point2f>center( contours.size() );
    vector<float>radius( contours.size() );


    for( uint i = 0; i < contours.size(); i++ )
    {

        approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
        //boundRect[i] = boundingRect( Mat(contours_poly[i]) );
        minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );

    }


    /// Draw polygonal contour + bonding rects + circles
    printf ("\n----------------\n");
    Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
    for( uint i = 0; i< contours.size(); i++ )
    {

        if((int)radius[i]>35 && (int)radius[i] < 70)
        {
            Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
            drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
            //  rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
            circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );

            printf ("Radius %d: %f \n",i,radius[i]);

///print centers
            //printf("point values %f %f\n", x.at<cv::Point2f>(0).x,x.at<cv::Point2f>(0).y);
     //       printf ("Center %d: %f %f \n",i,x.at<Point2f>(center[i]).x,x.at<Point2f>(center[i]).y);

            MyFilledCircle(drawing,center[i]);
        }
    }
    printf ("\n----------------\n");

    /// Show in a window
    namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    imshow( "Contours", drawing );
}


void MyFilledCircle( Mat img, Point center )
{
    int thickness = -1;
    int lineType = 8;

    circle( img,
            center,
            //w/32.0,
            1,
            Scalar( 0, 0, 255 ),
            thickness,
            lineType );
}
