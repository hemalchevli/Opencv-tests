
int main (int argc, const char * argv[])
{
    CvCapture *capture;
    IplImage  *img;
    int       key = 0;
    CvVideoWriter *writer;

    // initialize camera
    capture = cvCaptureFromCAM( 0 );
    // capture = cvCaptureFromAVI("AVIFile");

    // always check
    assert( capture );

    // create a window
    cvNamedWindow( "video", 1 );

    int color = 1; // 0 for black and white

    // get the frame size
    CvSize size = cvSize((int)cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH),(int)cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT));

    writer = cvCreateVideoWriter(argv[1], -1 , 10 , size, color);

    while( key != 'q' ) {
        // get a frame
        img = cvQueryFrame( capture );

        // always check
        if( !img ) break;

        cvWriteFrame( writer, img );
        cvShowImage("video", img );

        // quit if user press 'q'
        key = cvWaitKey( 5 );
    }

    // free memory
    cvReleaseVideoWriter( &writer );
    cvReleaseCapture( &capture );
    cvDestroyWindow( "video" );

    return 0;
}
