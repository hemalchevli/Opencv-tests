#include "cv.h"
#include "highgui.h"
#include <stdio.h>

using namespace cv;
using namespace std;



/** @function main */
int main(int argc, char** argv)
{
  Mat src, src_gray,tmp,dst;

  /// Read the image
  src = imread( argv[1], 1 );

pyrDown( src, dst, Size( tmp.cols/2, tmp.rows/2 ));
pyrDown( dst, tmp, Size( dst.cols/2, dst.rows/2 ));
src = dst;
 namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );

  if( !src.data )
    { return -1; }

  /// Convert it to gray
  cvtColor( src, src_gray, CV_BGR2GRAY );
 imshow( "Hough Circle Transform Demo", src_gray );

  //waitKey(0);
  /// Reduce the noise so we avoid false circle detection
  GaussianBlur( src_gray, src_gray, Size(9, 9), 1, 1 );

  vector<Vec3f> circles;

  /// Apply the Hough Transform to find the circles
  HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 5, src_gray.rows/8, 200, 200, 0,0.1 );

  /// Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);
      // circle center
      circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );
      // circle outline
      circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );
   }

  /// Show your results

  imshow( "Hough Circle Transform Demo", src );

  waitKey(0);
  return 0;
}

