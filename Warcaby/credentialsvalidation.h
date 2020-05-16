#ifndef CREDENTIALSVALIDATION_H
#define CREDENTIALSVALIDATION_H

#include <QWidget>
#include <fstream>
#include <QtDebug>

class CredentialsValidationError
{
public:
    std::string what()
    {
        return "Wczytanie lub zapisanie danych nie powiodlo sie";
    }
};

class CredentialsValidation
{
public:
    static bool Validate(QString login, QString password) throw(CredentialsValidationError);
    static bool Register(QString login, QString password) throw(CredentialsValidationError);
};

#endif // CREDENTIALSVALIDATION_H
