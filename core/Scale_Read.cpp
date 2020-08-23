/**
 * @file HoughCircle_Demo.cpp
 * @brief Demo code for Hough Transform
 * @author OpenCV team
 */

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

namespace
{
    // windows and trackbars name
    const std::string windowName = "Hough Circle Detection Demo";
    const std::string cannyThresholdTrackbarName = "Canny threshold";
    const std::string accumulatorThresholdTrackbarName = "Accumulator Threshold";
     
    const std::string standard_name = "Standard Hough Lines Demo";
    const std::string probabilistic_name = "Probabilistic Hough Lines Demo";
	
	bool is_print=false;	

    // initial and max values of the parameters of interests.
    const int cannyThresholdInitialValue = 82;
    const int accumulatorThresholdInitialValue = 20;
    const int maxAccumulatorThreshold = 200;
    const int maxCannyThreshold = 255;

    Mat standard_hough, probabilistic_hough;
    int min_threshold = 50;
    int max_trackbar = 150;
    int min_scale = 141;
    int max_scale = 42;
	
    inline float sqr(float x)
{
    return x * x;
}

    void HoughDetection(const Mat& src_gray, const Mat& src_display, int cannyThreshold, int accumulatorThreshold)
    {
        // will hold the results of the detection
        std::vector<Vec3f> circles;
        // runs the actual detection
        HoughCircles( src_gray, circles, HOUGH_GRADIENT, 1, src_gray.rows/8, cannyThreshold, accumulatorThreshold, 100, 200 );

        // clone the colour, input image for displaying purposes
        Mat display = src_display.clone();
        for( size_t i = 0; i < circles.size(); i++ )
        {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            // circle center
            circle( display, center, 3, Scalar(0,255,0), -1, 8, 0 );
            // circle outline
            circle( display, center, radius, Scalar(0,0,255), 3, 8, 0 );
        }

        // shows the results
        imshow( windowName, display);
    }
	
   

	void Standard_Hough(const Mat& edges, const Mat& src_display,int s_trackbar)
	{
  	vector<Vec2f> s_lines;
	  
  	/// 1. Use Standard Hough Transform
	  HoughLines( edges, s_lines, 1, CV_PI/180, min_threshold + s_trackbar, 0, 0 );
	Mat display = src_display.clone();

	  /// Show the result
	  for( size_t i = 0; i < s_lines.size(); i++ )
	     {
	      float r = s_lines[i][0], t = s_lines[i][1];
	      double cos_t = cos(t), sin_t = sin(t);
	      double x0 = r*cos_t, y0 = r*sin_t;
      		double alpha = 1000;

	       Point pt1( cvRound(x0 + alpha*(-sin_t)), cvRound(y0 + alpha*cos_t) );
	       Point pt2( cvRound(x0 - alpha*(-sin_t)), cvRound(y0 - alpha*cos_t) );
	       line( display, pt1, pt2, Scalar(255,0,0), 3, LINE_AA);
	     }

	   imshow( windowName, display );
	}


	void Probabilistic_Hough(const Mat& edges, const Mat& src_display,int p_trackbar)
	{
	  vector<Vec4f> p_lines;
	  Vec4f l;
  	/// 2. Use Probabilistic Hough Transform
	  HoughLinesP( edges, p_lines, 1, CV_PI/180, min_threshold + p_trackbar, 30, 10 );
	Mat display = src_display.clone();
	  /// Show the result

//cout << min_threshold + p_trackbar << endl;
  	for( size_t i = 0; i < p_lines.size(); i++ )
	     {
	       l = p_lines[i];
	       line( display, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
            //  if(!is_print){ cout << l[0] << "," << l[1] << ";" << l[2] << "," <<l[3] << " thresh:"<< min_threshold + p_trackbar << endl; }
	     }
		//is_print=true;

	   imshow( windowName, display );
	}

   	int ComputeScale(const Mat& edges, const Mat& edges_ln, int cannyThreshold, int accumulatorThreshold, int lineThreshold, float* x, float* y, float* r)
	{
		int result=0;
		std::vector<Vec3f> circles;
		HoughCircles( edges, circles, HOUGH_GRADIENT, 1, edges.rows/8, cannyThreshold, accumulatorThreshold, 100, 200 );
		
		for( size_t i = 0; i < circles.size(); i++ )
        		{
			vector<Vec4f> p_lines;
	  		HoughLinesP( edges_ln, p_lines, circles[i][2], CV_PI/180, lineThreshold, 30, 10 );
			cout << "Окружность " << i << "Центр " << circles[i][0] << " " << circles[i][1] << " радиус " << circles[i][2]  << endl;	
			//cout << lineThreshold << endl;

			*x = circles[i][0]; *y=circles[i][1] ;*r= circles[i][2];
			
			for( size_t j = 0; j < p_lines.size(); j++ )
	     		{
	    	   		Vec4i l = p_lines[j];
	    	   		//line( display, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);

	Point center(circles[i][0],circles[i][1]);
	Point pa(l[0],l[1]);
	Point pb(l[2],l[3]);

	const float eps = 1e-10;
    	float x1, y1, x2, y2, x0, y0, r,xx,yx;
 	x1=(float)l[0];
	y1=(float)l[1];
	x2=(float)l[2];
	y2=(float)l[3];
	x0=(float)circles[i][0];	
	y0=(float)circles[i][1];
	r=(float)circles[i][2];
	//cout << norm(center - pa) << "," << fabs(y1-y0) << ";" << norm(center-pb) << "," << fabs(y2-y0) << endl;
	if ( ((fabs(x1-x0) > 25) || (fabs(y1-y0) > 25)) && ((fabs(x2-x0) > 25) || (fabs(y2-y0) > 25))) continue;
  	cout << "соответствие" <<endl;
	cout << x1 << "," << y1 << ";" << x2 << "," << y2 << ";" << x0 << "," <<y0 << endl;
    float dx01 = x1 - x0, dy01 = y1 - y0, dx12 = x2 - x1, dy12 = y2 - y1;
    float a = sqr(dx12) + sqr(dy12);
    if (fabs(a) < eps)
    {
        cout << "Начало и конец отрезка совпадают!" << endl;
        
    }
    float k = dx01 * dx12 + dy01 * dy12;
    float c = sqr(dx01) + sqr(dy01) - sqr(r);
    float d1 = sqr(k) - a * c;
    if (d1 < 0)
        cout << "Прямая не пересекается с окружностью - отрезок снаружи" << endl;
    else if (fabs(d1) < eps)
    {
        float t = -k / a;
        float xi = x1 + t * dx12, yi = y1 + t * dy12;
        cout << "Прямая касается окружности в точке "
            "(" << xi << "; " << yi << ")" << endl;
        if (t > 0 - eps && t < 1 + eps)
            cout << "Отрезок снаружи, имеет общую точку с окружностью" << endl;
        else
            cout << "Отрезок строго снаружи" << endl;
    }
    else
    {
        float t1 = (-k + sqrt(d1)) / a, t2 = (-k - sqrt(d1)) / a;
        if (t1 > t2)
            swap(t1, t2);
        float xi1 = x1 + t1 * dx12, yi1 = y1 + t1 * dy12;
        float xi2 = x1 + t2 * dx12, yi2 = y1 + t2 * dy12;
        cout << "Прямая пересекает окружность в двух точках: "
            "(" << xi1 << "; " << yi1 << ")" << " и " <<
            "(" << xi2 << "; " << yi2 << ")" << endl;
	if( (labs(x1 - x0) <25) || (labs(y1 - y0) < 25)) {xx=xi1;yx=yi1;}
		else {xx = xi2; yx = yi2;}
	cout << "Точка шкалы:" << xx << "," << yx << endl; 

	
        if (t1 >= 0 - eps && t2 <= 1 + eps)
            if (t1 > 0 - eps && t2 < 1 + eps)
                cout << "Отрезок строго внутри" << endl;
            else
                cout << "Отрезок внутри, имеет как минимум одну общую точку с окружностью" << endl;
        else if (t2 <= 0 + eps || t1 >= 1 - eps)
            if (t2 < 0 + eps || t1 > 1 - eps)
                cout << "Отрезок строго снаружи" << endl;
            else
                cout << "Отрезок снаружи, имеет общую точку с окружностью" << endl;
        else
            cout << "Отрезок пересекает окружность в двух точках" << endl;
    }
	    		 }
			}


		
	}

}




int main(int argc, char** argv)
{
    Mat src, src_gray,src_gray2;

    // Read the image
    String imageName("stuff.jpg"); // by default
    if (argc > 1)
    {
       imageName = argv[1];
    }
    src = imread( samples::findFile( imageName ), IMREAD_COLOR );

    if( src.empty() )
    {
        std::cerr << "Invalid input image\n";
        std::cout << "Usage : " << argv[0] << " <path_to_input_image>\n";;
        return -1;
    }

    // Convert it to gray
    cvtColor( src, src_gray, COLOR_BGR2GRAY );
    cvtColor( src, src_gray2, COLOR_BGR2GRAY );	

    // Reduce the noise so we avoid false circle detection
    GaussianBlur( src_gray, src_gray, Size(5, 5), 0, 0 );
    //GaussianBlur( src_gray2, src_gray2, Size(5, 5), 0, 0 );

    //operator Laplasa
    Mat dst,cdst,cdstP;
//    Sobel( src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT );
    //Laplacian( src_gray2, cdst, CV_16S, 3, 1, 0, BORDER_DEFAULT );
	
    Canny( src_gray, src_gray2, 50, 200, 3 );


    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    /// Gradient X
    Sobel(src_gray, grad_x, CV_16S, 1, 0, 1, 2, 0, BORDER_DEFAULT);

    /// Gradient Y
    Sobel(src_gray, grad_y, CV_16S, 0, 1, 1, 2, 0, BORDER_DEFAULT);
    //![sobel]

    //![convert]
    // converting back to CV_8U
    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);
    //![convert]

    //![blend]
    /// Total Gradient (approximate)
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);


    convertScaleAbs( dst, src_gray );
   // convertScaleAbs( cdst, src_gray2 );


//mediannoe razm.
    medianBlur(src_gray, src_gray, 9);

    //declare and initialize both parameters that are subjects to change
    int cannyThreshold = cannyThresholdInitialValue;
    int accumulatorThreshold = accumulatorThresholdInitialValue;
    int p_trackbar = 66;//min_threshold;
    int s_trackbar = min_threshold;

    // create the main window, and attach the trackbars
    namedWindow( windowName, WINDOW_AUTOSIZE );
    createTrackbar(cannyThresholdTrackbarName, windowName, &cannyThreshold,maxCannyThreshold);
    createTrackbar(accumulatorThresholdTrackbarName, windowName, &accumulatorThreshold, maxAccumulatorThreshold);

    createTrackbar(standard_name, windowName, &s_trackbar,max_trackbar);
    createTrackbar(probabilistic_name, windowName, &p_trackbar, max_trackbar);

    createTrackbar("Min_calibration", windowName , &min_scale, 179);
    createTrackbar("Max_calibration", windowName , &max_scale, 359);


    // infinite loop to display
    // and refresh the content of the output image
    // until the user presses q or Q
//    char key = 0;
//    while(key != 'q' && key != 'Q')
//    {
        // those parameters cannot be =0
        // so we must check here
//        cannyThreshold = std::max(cannyThreshold, 1);
//        accumulatorThreshold = std::max(accumulatorThreshold, 1);

        //runs the detection, and update the display
//        HoughDetection(src_gray, src, cannyThreshold, accumulatorThreshold);

        // get user key
//        
//    }

     cannyThreshold = std::max(cannyThreshold, 1);
        accumulatorThreshold = std::max(accumulatorThreshold, 1);
	float calx,caly,calr;
int res = ComputeScale(src_gray,src_gray2,cannyThreshold, accumulatorThreshold,66+min_threshold,&calx,&caly,&calr);
	
     
    char key = 0;
    while(key != 'q' && key != 'Q')
    {
        // those parameters cannot be =0
        // so we must check here
        cannyThreshold = std::max(cannyThreshold, 1);
        accumulatorThreshold = std::max(accumulatorThreshold, 1);

        //runs the detection, and update the display
       
	Point center(cvRound(calx), cvRound(caly));
            int radius = cvRound(calr);
            // circle center
            circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );
            // circle outline
            circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );
	int xmin1 = cvRound(calx) + radius * cos((min_scale * CV_PI/180));
	int xmin2 = cvRound(calx) + (radius-20) * cos((min_scale * CV_PI/180));
	int ymin1 = cvRound(caly) + radius * sin((min_scale * CV_PI/180));
	int ymin2 = cvRound(caly) + (radius-20) * sin((min_scale * CV_PI/180));


	int xmax1 = cvRound(calx) + radius * cos((max_scale * CV_PI/180));
	int xmax2 = cvRound(calx) + (radius-20) * cos((max_scale * CV_PI/180));
	int ymax1 = cvRound(caly) + radius * sin((max_scale * CV_PI/180));
	int ymax2 = cvRound(caly) + (radius-20) * sin((max_scale * CV_PI/180));

	line( src, Point(xmin1, ymin1), Point(xmin2, ymin2), Scalar(0,255,0), 3, LINE_AA);
	line( src, Point(xmax1, ymax1), Point(xmax2, ymax2), Scalar(255,0,0), 3, LINE_AA);

	//HoughDetection(src_gray, src, cannyThreshold, accumulatorThreshold);
	//Standard_Hough(src_gray, src, s_trackbar);
	//Probabilistic_Hough(src_gray2, src, p_trackbar);
	
	imshow( windowName, src);
	key = (char)waitKey(10);
    }



    return 0;
}
