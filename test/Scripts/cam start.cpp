
#include "cv.h"
#include "highgui.h"
#include <stdio.h>
int main( int argc, char** argv ) {
    CvCapture* capture = 0;
    IplImage *image = 0;
    if( argc == 1 || (argc == 2 && strlen(argv[1]) == 1 && isdigit(argv[1][0])))
        capture = cvCaptureFromCAM( 0 );

    cvNamedWindow( "Input", CV_WINDOW_AUTOSIZE );
    for(;;)    {
        int c;
        image = cvQueryFrame( capture );
        if( !image )
            break;
        cvShowImage( "Input", image );
        c = cvWaitKey(10);
        if( (char)c == 27 )
            break;
    }
    cvReleaseCapture( &capture );
    cvDestroyAllWindows();

    return 0;
}

///////////////////////
//Using Mat
//////////////////////

#include "cv.h"
#include "highgui.h"
#include <stdio.h>
using namespace cv;
using namespace std;


int main( int argc, char** argv ) {
    CvCapture* capture = 0;
    //IplImage *image = 0;
    Mat image;
    if( argc == 1 || (argc == 2 && strlen(argv[1]) == 1 && isdigit(argv[1][0])))
        capture = cvCaptureFromCAM( 0 );

    cvNamedWindow( "Input", CV_WINDOW_AUTOSIZE );
    for(;;)    {
        int c;
        image = cvQueryFrame( capture );
//        if( !image ) break;
        //Do processign here



        //flip(image,image,1);
        //cvSmooth(image,image,CV_GAUSSIAN,7,7);
        //processing end
//        cvShowImage( "Input", image );
        imshow( "Input", image );
        c = cvWaitKey(10);
        if( (char)c == 27 )
            break;
    }

    return 0;
}
