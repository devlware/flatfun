# flatfun
Simple example on how to use FlatBuffers to save and read data to a file.


Compiled with:

g++ -std=c++11 sensors.cpp -o sensors -I /usr/local/include/flatbuffers


The output should be:

sensors.mon saved to file, written 88 bytes.

Id: 1

Light: 88.00

Sensor name: Sensor1


Next step should be exchange data between process or client/server.