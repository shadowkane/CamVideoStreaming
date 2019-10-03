#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
// Camera and display image libraries
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <raspicam/raspicam_cv.h>
// networking libraries
#include <iwlib.h>
#include <arpa/inet.h>

using namespace std;
using namespace raspicam;
using namespace cv;

void setConfigMsg(char **buffer, int imageW, int imageH, int imageFormat){
    /* configuration format is imageConfig=<image width>|<image height>|<image channels> */
    //string configMsg="imageW=" + to_string(imageW) + " imageH=" + to_string(imageH) + " imageFormat=" + to_string(imageFormat);
    string configMsg="imageConfig=" + to_string(imageW) + "|" + to_string(imageH) + "|" + to_string(imageFormat);
    *buffer = (char*) malloc(configMsg.length()*sizeof(char)+1);
    //buffer = new char[configMsg.length()*sizeof(char)+1];
    memcpy(*buffer, configMsg.c_str(), configMsg.length()*sizeof(char));
    //strcpy(buffer, configMsg.c_str());
    cout<<*buffer<<endl;
}

void matToString(char **buffer, Mat image){
    vector<Mat> imageChannels;
    //split(image,imageChannels);
    int rows = image.rows;
    int cols = image.cols;
    int channels = image.channels();
    cout<<channels<<endl;
    *buffer = (char*) malloc(image.cols*image.rows*3*sizeof(char)+1);
    memcpy(*buffer, "imageData=", 10*sizeof(char));
    int32_t k=10;
    cout<<"start mat to string"<<endl;
    for(int i=0; i<rows; ++i){
        uchar *row = image.ptr<uchar>(i);
        for(int j=0; j<cols * channels; ++j){
            (*buffer)[k]=*row;     // blue
            (*buffer)[k++]=*row++; // green
            (*buffer)[k++]=*row++; // red
        }
    }
}

void imageToSend(char **buffer, Mat image){
    int32_t dataLength = image.rows * image.cols * image.channels() + 10; // 10 for the length of "imagedDta="
    *buffer = (char*) malloc(dataLength+1);
    memcpy(*buffer, "imageData=", 10);
    memcpy((*buffer)+10, image.data, dataLength-10);

    /*int32_t bufferPos = 10;
    for(int i=0; i<image.rows; ++i){
        uchar *row = image.ptr<uchar>(i);
        memcpy((*buffer)+bufferPos, row, image.cols * image.channels());
        bufferPos += image.cols * image.channels();
    }*/
}


int main()
{
    RaspiCam_Cv cam;
    Mat frame;

    int mySocket;
    struct sockaddr_in serverAddr;
    char *buffer;


    char *testBuffer;
    double long testBufferLen = 480*640*3; //65535
    testBuffer = (char*) malloc(testBufferLen*sizeof(char)+1);
    memset(testBuffer, 'A', testBufferLen*sizeof(char));

    cout<<"Start program!!"<<endl;

    // camera settings
    namedWindow("webcam", WINDOW_AUTOSIZE );
    cam.set(CAP_PROP_FORMAT, CV_8UC3);
    cam.set(CAP_PROP_FRAME_WIDTH, 640);
    cam.set(CAP_PROP_FRAME_HEIGHT, 480);

    if(!cam.open()){
        cout<<"can't opencv camera!!!"<<endl;
        return -1;
    }
    waitKey(1000);

    // network settings
    mySocket = socket(AF_INET, SOCK_STREAM, 0);
    if(mySocket<0){
        cout<<"can't open socket!!!"<<endl;
        return -1;
    }
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("192.168.1.105");
    serverAddr.sin_port = htons(27015);

    connect(mySocket, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr_in));

    setConfigMsg(&buffer, 640, 480, 3);
    send(mySocket, buffer, strlen(buffer), 0);


    while(true){
        cam.grab();
        cam.retrieve(frame);
        if(!frame.empty()){
            imageToSend(&buffer, frame);
            send(mySocket, buffer, strlen(buffer), 0);
            //imshow("webcam", frame);
        }

        waitKey(30);
    }

    cout<<"Exit program"<<endl;
    close(mySocket);
    return 0;
}
