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

    //IplImage *image = 0;
    time_t start,end;

    Mat image,gray_image;

    if( argc == 1 || (argc == 2 && strlen(argv[1]) == 1 && isdigit(argv[1][0])))
        capture = cvCaptureFromCAM( 0 );

    cvNamedWindow( "Input", CV_WINDOW_AUTOSIZE );

    int bright=128, contrast=26;
    cvCreateTrackbar("brightness", "Input", &bright, 255, NULL);
    cvCreateTrackbar("contrast", "Input", &contrast, 50, NULL);

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

//TODO: add highgui to adjust params
    //for FPS
    time(&start);
    int counter=0;

    for(;;)
    {

        image = cvQueryFrame( capture );
//        if( !image ) break;

        //Downsample image if needed
        //pyrDown( dst, tmp, Size( dst.cols/2, dst.rows/2 ));
        ///Do processign here

        //Flip image optional
        //flip(image,image,1);
        //convert to grayscale
        cvtColor( image, gray_image, CV_BGR2GRAY );
        //blur to remove noise
        GaussianBlur( image, image, Size(9, 9), 1, 1 );
        ///Detect circles Start
        vector<Vec3f> circles;

        // Apply the Hough Transform to find the circles
        HoughCircles( gray_image, circles, CV_HOUGH_GRADIENT, 2, gray_image.rows/8, 200, 100, 0,0 );

        // Draw the circles detected
        for( size_t i = 0; i < circles.size(); i++ )
        {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            // circle center
            // circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );
            circle( image, center, 3, Scalar(0,255,0), -1, 8, 0 );
            // circle outline
            circle( image, center, radius, Scalar(0,0,255), 3, 8, 0 );
        }
        ///Circle detect end



        ///processing end
//        cvShowImage( "Input", image ); //does not work with Mat


        //fps
        time(&end);
        ++counter;
        double sec=difftime(end,start);
        double fps=counter/sec;
        printf("\n%lf",fps); //prints on console
        //print on image
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

        str << "FPS: " << fps;
        putText( image,  str.str() , org, fonttype, scale, colour, thickness, lineType);
        //fps end

        imshow( "Input", image );
        c = cvWaitKey(10);
        if( (char)c == 27 )
            break;
    }

    return 0;
}
