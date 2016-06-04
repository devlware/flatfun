// Simple example on how to use FlatBuffers to save and read data to a file.
// Next step should be exchange data between process or client/server.
//
// Compiled with:
// g++ -std=c++11 sensors.cpp -o sensors -I /usr/local/include/flatbuffers
//
// The output should be:
// sensors.mon saved to file, written 88 bytes.
// Id: 1
// Light: 88.00
// Sensor name: Sensor1

#include "sensors_generated.h"
#include <cstdio>

int main(int argc, const char * [])
{
    flatbuffers::FlatBufferBuilder builder;

    auto name = builder.CreateString("Sensor1");
    auto s1 = CreateSensors(builder, 1, name, 88.98, 21.9, 1002.15, 88, 97.32, 11, 2);
    builder.Finish(s1);

    FILE *outfile = fopen("sensors.mon", "wb");
    if (outfile != NULL) {
        size_t w_size = fwrite(builder.GetBufferPointer(), sizeof(char), builder.GetSize(), outfile);
        fclose(outfile);
        printf("sensors.mon saved to file, written %zu bytes.\r\n", w_size);
    } else {
        printf("Could not save data to file.\r\n");
        exit(-1);
    }

    FILE *file = fopen("sensors.mon", "rb");
    if (outfile == NULL) {
        printf("Could not open data file.\r\n");
        exit(-1);
    }

    fseek(file, 0L, SEEK_END);
    int length = ftell(file);
    fseek(file, 0L, SEEK_SET);
    char *data = new char[length];
    fread(data, sizeof(char), length, file);
    fclose(file);

    auto asensor = GetSensors(data);

    printf("Id: %lld\n", asensor->id());
    printf("Light: %.2f\n", asensor->light());
    printf("Sensor name: %s\n", asensor->name()->c_str());

    fclose(file);

    return 0;
}
