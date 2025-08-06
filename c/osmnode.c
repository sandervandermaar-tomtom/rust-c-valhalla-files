#include "osmnode.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct OSMNode * osmnode_new(uint64_t count)
{
    struct OSMNode * output = malloc(sizeof(struct OSMNode) * count);
    memset(output, 0, sizeof(struct OSMNode) * count);
    return output;
}

void osmnode_free(struct OSMNode * s)
{
    free(s);
}

void osmnode_clear(struct OSMNode * s, uint64_t count)
{
    memset(s, 0, sizeof(struct OSMNode) * count);
}

uint64_t osmnode_export(const struct OSMNode * s, int count, const char * fileName)
{
    // TODO: error checking
    FILE * outFile = fopen(fileName, "wb");
    fwrite(s, sizeof(struct OSMNode), count, outFile);
    fclose(outFile);
    return 1;
}

void osmnode_import(const char * fileName, struct OSMNode ** buffer, uint64_t * count)
{
    // TODO: error checking
    FILE * inFile = fopen(fileName, "rb");
    fseek(inFile, 0, SEEK_END);
    *count = ftell(inFile) / sizeof(struct OSMNode);
    // TODO: make sure file size is exactly a multiple of sizeof(struct OSMNode)
    fseek(inFile, 0, SEEK_SET);
    *buffer = malloc(sizeof(struct OSMNode) * (*count));
    fread(*buffer, sizeof(struct OSMNode), *count, inFile);
    fclose(inFile);
}
