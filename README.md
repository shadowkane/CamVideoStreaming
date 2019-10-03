# CamVideoStreaming
Streaming the Rasberry Pi camera (c++ program) over the network (TCP/IP) to a QT server application.

to run the project you need to install opencv and raspicam in your raspberry pi. I used the IDE codeblocks to build the client application that capture the image from the raspberry pi camera and send it to the server using the TCP/IP protocol.
to run properly this program you need to configure the IP address of your server and the Port number.
The QT application, which represent the server side, is a simple gui interface where you can change the port number to much the one you used in your raspberry pi and then click the button to start the server. keep in mind, the server need to run first.
The QT application has a drop box for the image/video format, for now it support the BGR(opencv) format. maybe later i will add more formats.