#include "cv.h"
#include "highgui.h"
#include <stdio.h>
using namespace cv;
using namespace std;

/// Global variables
Mat src, dst, tmp;
int MAX_KERNEL_LENGTH = 31;

const char* window_name = "Pyramids Demo";


/**
 * @function main
 */
int main( void )
{

    src = imread("1.jpg");
    if( !src.data )
    {
        printf(" No data! -- Exiting the program \n");
        return -1;
    }

    tmp = src;
    dst = tmp;

    pyrDown( tmp, dst, Size( tmp.cols/2, tmp.rows/2 ) );


    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        //GaussianBlur( dst, tmp, Size( i, i ), 0, 0 );
        blur( dst, tmp, Size( i, i ), Point(-1,-1) );
       // medianBlur ( dst, tmp, i );
         //bilateralFilter ( dst, tmp, i, i*2, i/2 );
    }

/// Create window
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );

    imshow(window_name, tmp );

    tmp = dst;


    waitKey(0);

    return 0;
}







