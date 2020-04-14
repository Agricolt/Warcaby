#ifndef CREDENTIALSVALIDATION_H
#define CREDENTIALSVALIDATION_H

#include <QWidget>

class CredentialsValidation
{
public:
    static bool validate(QString login, QString password);
};

#endif // CREDENTIALSVALIDATION_H
