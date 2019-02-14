#include <iostream>
#include <fstream>
#include <string>
#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"

#include "opencv2/video.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;
using namespace cv::cuda;


int main(int argc, const char** argv)
{

    cv::CommandLineParser cmd(argc, argv,

        "{ f file   |  | input video file }"
        "{ i video_id   |   | video identifier }"
        "{ h help   |                    | print help message }");

    if (cmd.has("help") || !cmd.check())
    {
        cmd.printMessage();
        cmd.printErrors();
        return 0;
       }

    
    string file = cmd.get<string>("file");
    string video_id = cmd.get<string>("video_id");
    VideoCapture cap;
    Mat frame;
    
    if (file=="" || video_id==""){
        cmd.printMessage();
        cmd.printErrors();
        return 0;
    }
        
    else
        cap.open(file);

    if (!cap.isOpened())
    {
        cerr << "can not open camera or video file" << endl;
        return -1;
    }

    ofstream file_dataset_bboxes;

    namedWindow("image", WINDOW_AUTOSIZE);
    int nb_vehicles = 0;
    string name_img = "";
    string msg = "";
    string vehicle_type = "";
    

    for(int frame_count=1 ; ; frame_count++)
    {	
    	
        cap >> frame;
        if (frame.empty())
            break;
        
        imshow("image", frame);
        waitKey(1);

        if (frame_count % 25 == 00 )
        {
           	std::cout << "Please enter the number of vehicules ";
           	std::cout << "(0 = no vehicle , -1 = bad frame) : " ;
           	std::cin >> nb_vehicles;
           	name_img = video_id+'_'+std::to_string(frame_count)+".png";
            int c_v_type = 0;
            string vehicle_type = "";
            if (nb_vehicles > 0)
            {	
            	cv::imwrite("../../dataset_howdrive/"+name_img,frame);
            	cout << name_img << " frame saved " <<endl;
            		
            	
            	for (int i = 0; i < nb_vehicles; i++)
            	{
            		cout << "select the "<<i+1<<" vehicle" <<endl;
            		Rect2d roi=cv::selectROI("select a vehicle" ,frame);
                    std::cout << " vehicle type : car:0, bus:1 , truck:2 , pickup:3 , motorcycle:4 , trike:5 , other : 6 " <<endl;
                    std::cin >> c_v_type ;
                    
                    switch (c_v_type) {
                        case 0: vehicle_type = "car" ;break;
                        case 1: vehicle_type = "bus";break;
                        case 2: vehicle_type = "truck";break;   //execution starts at this case label
                        case 3: vehicle_type = "pickup" ;break;
                        case 4: vehicle_type = "motorcycle" ;break;
                        case 5: vehicle_type = "trike";break;
                        default: std::cout << "type error , frame_count : "<<frame_count<<endl<<"enter the type as string ! "<<endl;
                        std::cin >> vehicle_type ;break;
                    }
            		msg = name_img + ';' +to_string(nb_vehicles)+ ';'+ to_string(int(roi.x)) + ';' + to_string(int(roi.y)) +';'+ to_string(int(roi.height + roi.x)) +';'+ to_string(int(roi.width +roi.y)) +';'+vehicle_type+'\n';
            		file_dataset_bboxes.open ("../../labels.txt", ios::app );
            		file_dataset_bboxes << msg;
            		file_dataset_bboxes.close();
            		cout << "bbox saved : " << msg  << endl;

            	}

                	cv::destroyWindow("select a vehicle");
            }
        }
        
        char key = (char)waitKey(30);
        if (key == 27)
            break;
    }

    return 0;
}
