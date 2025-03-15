// sudo apt install opencv-dev

#include <iostream>
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <unistd.h> // usleep


const std::string YOUTUBE_URL = "rtmp://b.rtmp.youtube.com/live2";
const std::string YOUTUBE_KEY = "vxhv-sap7-uf1r-m9eu-8y7q";

// const std::string ffmpeg_cmd = "ffmpeg -ar 44100 -ac 2 -acodec pcm_s16le -f s16le -ac 2 -i /dev/zero -f h264 -i - -vcodec copy -acodec aac -ab 128k -g 50 -strict experimental -f flv "
//                               + YOUTUBE_URL + "/" + YOUTUBE_KEY;

const std::string ffmpeg_cmd = "raspivid -t 0 -w 1280 -h 720 -fps 30 -b 1500000 -o - | "
                               "ffmpeg -re -f h264 -i - -vcodec copy -f flv "
                               + YOUTUBE_URL + "/" + YOUTUBE_KEY;

int main(int argc, char* argv[])
{
 // step one: initialize camera
 cv::VideoCapture camera(0);
 if (!camera.isOpened()) {
   std::cout << "Cannot connect to camera" << std::endl;
   return -1;
 }

 // step two: set camera settings
 camera.set(cv::CAP_PROP_FRAME_WIDTH, 640);
 camera.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
 camera.set(cv::CAP_PROP_FPS, 24);

 // step three: open ffmpeg process
 FILE* ffmpeg = popen(ffmpeg_cmd.c_str(), "w");
 if (!ffmpeg) {
   std::cout << "Error opening ffmpeg process" << std::endl;
   camera.release();
   return -1;
}

 // step four: send frames to ffmpeg
 cv::Mat frame;
 while (true) {
   camera >> frame;
   if (frame.empty()) {
       continue;
   }

   // We write to ffmpeg stdin and if it identifies a failure, we stop the process
   // Later id like to add function for it to restart on its own if this happens so we dont have it end unexpectedly.
   if (fwrite(frame.data, 1, frame.total() * frame.elemSize(), ffmpeg) <= 0) {
       break;
   }
   usleep(5000); // wait 5ms so cpu isn’t crushed by while(true)
}

 // step five: cleanup
 pclose(ffmpeg);
 camera.release();

 return 0;
}
