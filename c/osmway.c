#include "osmway.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct OSMWay * osmway_new(uint64_t count)
{
    struct OSMWay * output = malloc(sizeof(struct OSMWay) * count);
    memset(output, 0, sizeof(struct OSMWay) * count);
    return output;
}

void osmway_free(struct OSMWay * s)
{
    free(s);
}

void osmway_clear(struct OSMWay * s, uint64_t count)
{
    memset(s, 0, sizeof(struct OSMWay) * count);
}

int osmway_export(const struct OSMWay * s, int count, const char * fileName)
{
    // TODO: error checking
    FILE * outFile = fopen(fileName, "wb");
    fwrite(s, sizeof(struct OSMWay), count, outFile);
    fclose(outFile);
    return 1;
}

void osmway_import(const char * fileName, struct OSMWay ** buffer, uint64_t * count)
{
    // TODO: error checking
    // TODO: move this to a common function (similar to osmnode_import etc)
    FILE * inFile = fopen(fileName, "rb");
    fseek(inFile, 0, SEEK_END);
    *count = ftell(inFile) / sizeof(struct OSMWay);
    // TODO: make sure file size is exactly a multiple of sizeof(struct OSMWay)
    fseek(inFile, 0, SEEK_SET);
    *buffer = malloc(sizeof(struct OSMWay) * (*count));
    fread(*buffer, sizeof(struct OSMWay), *count, inFile);
    fclose(inFile);
}
