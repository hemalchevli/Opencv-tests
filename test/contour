#include "cv.h"
#include "highgui.h"
#include <stdio.h>

using namespace cv;
using namespace std;

Mat src,tmp,dst; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

/// Function header
void thresh_callback(int, void* );

/** @function main */
int main( int argc, char** argv )
{
  /// Load source image and convert it to gray
  src = imread( argv[1], 1 );

  ///Get ROI
  src = src(cvRect(250,190,150,150)); //make roi smaller


//pyrDown( src, dst, Size( tmp.cols/2, tmp.rows/2 ));
//pyrDown( dst, tmp, Size( dst.cols/2, dst.rows/2 ));
//src = dst;

  /// Convert image to gray and blur it
  cvtColor( src, src_gray, CV_BGR2GRAY );
  //blur( src_gray, src_gray, Size(3,3) );
   GaussianBlur( src_gray,src_gray,Size(9,9), 1,1 );

  /// Create Window
  char* source_window = "Source";
  namedWindow( source_window, CV_WINDOW_AUTOSIZE );
  imshow( source_window, src );

  createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
  thresh_callback( 0, 0 );

  waitKey(0);
  return(0);
}
  /*
    0 - Get ROI
    1 - grayscale - done src_gray

    2- low pass filter (gaussian blur) -done

    3- canny edge detection done

    4- find contours done
    list their areas . form mass moments

    5- draw min enclosing circles to your contours.

    6- select the contour which has min enclosing circle area closest to contour area.

    7- find center of mass of the contour using moments F3 type "mass centers"
    */
/** @function thresh_callback */
void thresh_callback(int, void* )
{
  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// Detect edges using canny
  Canny( src_gray, canny_output, thresh, thresh*2, 3 );
  /// Find contours
  //findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
  findContours( canny_output, contours, hierarchy, CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );


  /// Get the moments
  vector<Moments> mu(contours.size() );
  for( int i = 0; i < contours.size(); i++ )
     { mu[i] = moments( contours[i], false ); }

  ///  Get the mass centers:
  vector<Point2f> mc( contours.size() );
  for( int i = 0; i < contours.size(); i++ )
     { mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); }

  /// Draw contours
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  for( int i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
     }

  /// Show in a window
  namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );

  printf("\t Info: Area and Contour Length \n");
  for( int i = 0; i< contours.size(); i++ )
     {
       printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f \n", i, mu[i].m00, contourArea(contours[i]), arcLength( contours[i], true ) );
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
       circle( drawing, mc[i], 4, color, -1, 8, 0 );
     }
}
