/**
* This file is part of ORB-SLAM2.
*
* Copyright (C) 2014-2016 Raúl Mur-Artal <raulmur at unizar dot es> (University of Zaragoza)
* For more information see <https://github.com/raulmur/ORB_SLAM2>
*
* ORB-SLAM2 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM2 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ORB-SLAM2. If not, see <http://www.gnu.org/licenses/>.
*/


#include<iostream>
#include<algorithm>
#include<fstream>
#include<chrono>

#include<opencv2/core/core.hpp>

#include<System.h>

using namespace std;

bool getImages(cv::Mat& left_image, cv::Mat& right_image,cv::VideoCapture& cap);

int main(int argc, char **argv)
{
    if(argc != 4)
    {
        cerr << endl << "Usage: ./mono_tum path_to_vocabulary path_to_settings path_to_sequence" << endl;
        return 1;
    }

    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ORB_SLAM2::System SLAM(argv[1],argv[2],ORB_SLAM2::System::MONOCULAR,true);

    // Main loop
    cv::VideoCapture cap(0);
    cv::Mat left_image;
    cv::Mat right_image;
    int i = 1;
    while (1)
    {
        if(getImages(left_image, right_image, cap))
        {
            SLAM.TrackMonocular(left_image,i++);
        }
        usleep(10*1e3);
    }

    // Stop all threads
    SLAM.Shutdown();

    // Save camera trajectory
    SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory.txt");

    return 0;
}
bool getImages(cv::Mat& left_image, cv::Mat& right_image,cv::VideoCapture& cap)
{
	cv::Mat raw;
	if (cap.grab())
    {
		cap.retrieve(raw);
        // std::cout << cap.get(3) <<" x "<< cap.get(4) << std::endl;
		// cv::Rect left_rect(0, 0, 640 / 2, 480);
		cv::Rect left_rect(0, 0, 640, 480);
		cv::Rect right_rect(640 / 2, 0, 640 / 2, 480);
		left_image = raw(left_rect);
		right_image = raw(right_rect);
		return true;
	} else
    {
		return false;
    }
}
