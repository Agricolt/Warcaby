#ifndef CREDENTIALSVALIDATION_H
#define CREDENTIALSVALIDATION_H

#include <QWidget>

class CredentialsValidation
{
public:
    static bool validate(std::string login, std::string password);
};

#endif // CREDENTIALSVALIDATION_H
