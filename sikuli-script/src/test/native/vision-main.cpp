/*
 *  vision-main.cpp
 *  vision
 *
 *  Created by Tom Yeh on 5/1/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include <iostream>
#include "finder.h"
#include "event-manager.h"


string screen_image_path(int screen_i){
	stringstream ss;
	ss << "testdata/images/"  << screen_i << "-screen.png";
	ss.flush();
	return ss.str();
}

string target_image_path(int screen_i, int target_i){
	stringstream ss;
	ss << "testdata/images/"  << screen_i << "-target-" << target_i<< ".png";
	ss.flush();
	return ss.str();
}

string result_image_path(int screen_i, int target_i, string testname){
	stringstream ss;
	ss << "testdata/results/" << screen_i << "-[" << testname << "]-target-" << target_i<< ".png";
	return ss.str();
}


#define DEBUG_DISPLAY
void test(int screen_i, int target_i){
  	
	string source_filename(screen_image_path(screen_i));
	string target_filename = target_image_path(screen_i,target_i);
	
	char filename[100];

	sprintf(filename,"testdata/images/%d-screen.png",screen_i);
	Mat source = imread(filename,1);
	
	sprintf(filename,"testdata/images/%d-target-%d.png",screen_i,target_i);	
	Mat target = imread(filename,1);
	
	Finder f(source);
	//source_filename.c_str());
	
	/*	int x=50;
	 int y=50;
	 int w=source.cols/2;
	 int h=source.rows/2;*/
	int x=1;
	int y=1;
	int w=source.cols-1;
	int h=source.rows-1;
	f.setROI(x,y,w,h);
	
	//f.find(target,0.0);
	f.find(target,0.9);
	
	
#ifdef DEBUG_DISPLAY	
	Mat upperLeftCorner(source, Rect(5,5,target.cols,target.rows));
	target.copyTo(upperLeftCorner);	
	
	// draw a thick border around the template image
    rectangle(source,
			  Point(5, 5),
			  Point(5+target.cols,5+target.rows),
			  Scalar(0, 0, 0), 5, 0, 0 );  
	
    rectangle(source,
			  Point(5, 5),
			  Point(5+target.cols, 5+target.rows),
			  Scalar(180, 180, 180), 2, 0, 0 );  
	
	
	// draw a thick border around the template image
    rectangle(source,
			  Point(x, y),
			  Point(x+w,x+h),
			  Scalar(0, 0, 0), 5, 0, 0 );  
#endif
	
	
	
	//for (int i=0;i<5;++i){
	int i=0;
	while (f.hasNext()){
		++i;
		
		//Match match = pm.next();	
		Match match = f.next();
		cout << match.x << " " << match.y << " " << match.score << endl;
		
#ifdef DEBUG_DISPLAY
		
		rectangle(source, 
				  Point( match.x, match.y), 
				  Point( match.x + match.w, match.y + match.h),
				  Scalar( 0, 0, (int)255*match.score, 0 ), 2, 0, 0 );  
		
		Point center;
		center.x = match.x + match.w/2;
		center.y = match.y + match.h/2;
     	
		
		/*	{
		 stringstream ss;
		 ss << match.score;  
		 Point loc = center;
		 loc.y = loc.y + 20;
		 //cvInitFont(&font,FONT_HERSHEY_SIMPLEX, 0.5,0.5,0,1);                  
		 putText(source,ss.str().c_str(),loc, FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255,0,0));
		 }
		 */	
		{
			stringstream ss;
			ss << i+1;
			//cvInitFont(&font,FONT_HERSHEY_PLAIN, 1.0,1.0,0,3);                  
			putText(source,ss.str().c_str(),center, FONT_HERSHEY_PLAIN, 1.0, Scalar(255,0,0));
		}
#endif		
		
	}
	
	
#ifdef DEBUG_DISPLAY
	
	namedWindow("matches", CV_WINDOW_AUTOSIZE);
    imshow("matches", source);
	waitKey();
#endif	
	
	
}


void  test_change_finder(){
	
	Mat before = imread("testdata/images/before.png");
	Mat after = imread("testdata/images/after.png");
	
	ChangeFinder cf = ChangeFinder(before);	
	cf.find(after);
	
	while (cf.hasNext()){
		Match match = cf.next();
		cout << match.x << " " << match.y << " " << match.score << endl;
		
		
		rectangle(after, 
				  Point( match.x, match.y), 
				  Point( match.x + match.w, match.y + match.h),
				  Scalar( 0, 0, (int)255*match.score, 0 ), 2, 0, 0 );  
		
		
	}
	
	
	namedWindow("changes", CV_WINDOW_AUTOSIZE);
    imshow("changes", after);
	waitKey();	
}

void test_finder(){
	
	test(1,1);
	test(1,2);
	test(1,3);
	test(1,4);
	test(1,5);

	test(2,1);
	test(2,2);
	test(2,3); 
	test(2,4);
	
	test(3,1);
	test(3,2);
	test(3,3); 
	test(3,4);
	test(3,5); 
	test(3,6);
	
	test(4,1);
	test(4,2);
	test(4,3);
	test(4,4);
	
	test(5,1);
	test(5,2);
	test(5,3);
	test(5,4);
	
	test(6,1);
	test(6,2);
	test(6,3);
	test(6,4);
	test(6,5);
	test(6,6);
	test(6,7);
	
	test(7,1);
	test(7,2);
	test(7,3);
	test(7,4);
	test(7,5);
	test(7,6);
	test(7,7);
	test(7,8);
	
	test(8,1);
	test(8,2);	
	test(8,3);
	test(8,4);
	test(8,5);

	test(9,1);
	test(9,2);
	test(9,3);
	test(9,4);
	
}


void test_sem(){
	
	SikuliEventManager sem;
	sem.addObserver(SIKULI_EVENT_APPEAR, "testdata/images/advanced.png", 1, 450, 300, 400, 400);
	sem.addObserver(SIKULI_EVENT_VANISH, "testdata/images/advanced.png", 2, 450, 300, 400, 400);
	sem.addObserver(SIKULI_EVENT_CHANGE, "", 3, 450, 300, 400, 400);
	sem.addObserver(SIKULI_EVENT_APPEAR, "testdata/images/firewire.png", 4, 100, 150, 250, 400);
	sem.addObserver(SIKULI_EVENT_VANISH, "testdata/images/firewire.png", 4, 100, 150, 250, 400);
	
	
	vector<Event> events;
	
	char buf[50];
	for (int i=1;i<=20;++i){
		
		cout << "frame " << i << " =======================" << endl;
		sprintf(buf,"testdata/frames/%d.png",i);
		
		
		events = sem.update(buf);  
		
		for (vector<Event>::iterator it = events.begin(); it != events.end(); it++){
			
			
			if (it->type == SIKULI_EVENT_APPEAR){
				cout << "APPEAR";
			}
			else if (it->type == SIKULI_EVENT_VANISH){
				cout << "VANISH";
			}else if (it->type == SIKULI_EVENT_CHANGE){
				cout << "CHANGE";
			}
			
			cout << " @ " << "(" << it->x << " , " << it->y <<  " , " << it->w << " , " << it->h << " ) ";
			cout << " --> handler " << it->handler_id << endl;
		}
		
		
	}
}

int main (int argc, const char * argv[]) {
	
	
	//test_change_finder();
	//test_sem();
	test_finder();
	
    return 0;
}