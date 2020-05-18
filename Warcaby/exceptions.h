#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>

class Exceptions
{
public:
    virtual std::string what();
};

class ResourcesError : public Exceptions
{
public:
    std::string what();
};

class graphicsLoadError : public ResourcesError
{
public:
    std::string what();
};

class musicLoadError : public ResourcesError
{
public:
    std::string what();
};

class fileSaveError : public ResourcesError
{
    public:
        std::string what();
};

class fileLoadError : public ResourcesError
{
    public:
        std::string what();
};



#endif // EXCEPTIONS_H
