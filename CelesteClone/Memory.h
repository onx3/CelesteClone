#pragma once
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "CelesteLib.h"

//----------------------------------------------------------------------------------------------------------------------------
// Bump Allocator
//----------------------------------------------------------------------------------------------------------------------------

struct BumpAllocator
{
    size_t mCapacity;
    size_t mUsed;
    char * mpMemory;
};

//----------------------------------------------------------------------------------------------------------------------------

BumpAllocator MakeBumbAllocator(size_t size)
{
    BumpAllocator ba = {};
    ba.mpMemory = (char *)malloc(size);
    if (ba.mpMemory)
    {
        ba.mCapacity = size;
        memset(ba.mpMemory, 0, size);
    }
    else
    {
        ASSERT(false, "Failed to allocate Memory!");
    }

    return ba;
}

//----------------------------------------------------------------------------------------------------------------------------

void FreeBumpAllocator(BumpAllocator * pBumpAllocator)
{
    free(pBumpAllocator->mpMemory);
    pBumpAllocator->mpMemory = nullptr;
    pBumpAllocator->mUsed = 0;
    pBumpAllocator->mCapacity = 0;
}

//----------------------------------------------------------------------------------------------------------------------------

char * BumpAlloc(BumpAllocator * pBumpAllocator, size_t size)
{
    char * result = nullptr;
    size_t allignedSize = (size + 7) & ~7;

    if (pBumpAllocator->mUsed + allignedSize <= pBumpAllocator->mCapacity)
    {
        result = pBumpAllocator->mpMemory + pBumpAllocator->mUsed;
        pBumpAllocator->mUsed += allignedSize;
    }
    else
    {
        ASSERT(false, "BumpAllocator is full");
    }
    return result;
}

//----------------------------------------------------------------------------------------------------------------------------
// FILE I/O
//----------------------------------------------------------------------------------------------------------------------------

long long get_timestamp(const char * pFile)
{
    struct stat file_stat = {};
    stat(pFile, &file_stat);
    return file_stat.st_mtime;
}

//----------------------------------------------------------------------------------------------------------------------------

bool file_exists(const char * pFilePath)
{
    ASSERT(pFilePath, "No filePath supplied!");

    auto file = fopen(pFilePath, "rb");
    if (!file)
    {
        return false;
    }
    fclose(file);

    return true;
}

//----------------------------------------------------------------------------------------------------------------------------

long get_file_size(const char * pFilePath)
{
    ASSERT(pFilePath, "No filePath supplied!");

    long fileSize = 0;
    auto file = fopen(pFilePath, "rb");
    if (!file)
    {
        SM_ERROR("Failed opening File: %s", pFilePath);
        return 0;
    }

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    fclose(file);

    return fileSize;
}

//----------------------------------------------------------------------------------------------------------------------------

/*
* Reads a file into a supplied buffer. We manage our own
* memory and therefore want more control over where it
* is allocated
*/
char * read_file(const char * pFilePath, int * pFileSize, char * pBuffer)
{
    ASSERT(pFilePath, "No filePath supplied!");
    ASSERT(pFileSize, "No fileSize supplied!");
    ASSERT(pBuffer, "No buffer supplied!");

    *pFileSize = 0;
    auto file = fopen(pFilePath, "rb");
    if (!file)
    {
        SM_ERROR("Failed opening File: %s", pFilePath);
        return nullptr;
    }

    fseek(file, 0, SEEK_END);
    *pFileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    memset(pBuffer, 0, *pFileSize + 1);
    fread(pBuffer, sizeof(char), *pFileSize, file);

    fclose(file);

    return pBuffer;
}

//----------------------------------------------------------------------------------------------------------------------------

char * read_file(const char * pFilePath, int * pFileSize, BumpAllocator * pBumpAllocator)
{
    char * file = nullptr;
    long fileSize2 = get_file_size(pFilePath);

    if (fileSize2)
    {
        char * buffer = BumpAlloc(pBumpAllocator, fileSize2 + 1);

        file = read_file(pFilePath, pFileSize, buffer);
    }

    return file;
}

//----------------------------------------------------------------------------------------------------------------------------

void write_file(const char * pFilePath, char * pBuffer, int size)
{
    ASSERT(pFilePath, "No filePath supplied!");
    ASSERT(pBuffer, "No buffer supplied!");
    auto file = fopen(pFilePath, "wb");
    if (!file)
    {
        SM_ERROR("Failed opening File: %s", pFilePath);
        return;
    }

    fwrite(pBuffer, sizeof(char), size, file);
    fclose(file);
}

//----------------------------------------------------------------------------------------------------------------------------

bool copy_file(const char * pFileName, const char * pOutputName, char * pBuffer)
{
    int fileSize = 0;
    char * data = read_file(pFileName, &fileSize, pBuffer);

    auto outputFile = fopen(pOutputName, "wb");
    if (!outputFile)
    {
        SM_ERROR("Failed opening File: %s", pOutputName);
        return false;
    }

    int result = fwrite(data, sizeof(char), fileSize, outputFile);
    if (!result)
    {
        SM_ERROR("Failed opening File: %s", pOutputName);
        return false;
    }

    fclose(outputFile);

    return true;
}

//----------------------------------------------------------------------------------------------------------------------------

bool copy_file(const char * pFileName, const char * pOutputName, BumpAllocator * pBumpAllocator)
{
    char * file = 0;
    long fileSize2 = get_file_size(pFileName);

    if (fileSize2)
    {
        char * buffer = BumpAlloc(pBumpAllocator, fileSize2 + 1);

        return copy_file(pFileName, pOutputName, buffer);
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------------
// EOF
//----------------------------------------------------------------------------------------------------------------------------