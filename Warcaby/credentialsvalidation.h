#ifndef CREDENTIALSVALIDATION_H
#define CREDENTIALSVALIDATION_H

#include <QWidget>
#include <fstream>
#include <QtDebug>

class CredentialsValidation
{
public:
    static bool Validate(QString login, QString password);
    static bool Register(QString login, QString password);
};

#endif // CREDENTIALSVALIDATION_H
