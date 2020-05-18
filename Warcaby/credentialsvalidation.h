#ifndef CREDENTIALSVALIDATION_H
#define CREDENTIALSVALIDATION_H

#include <QWidget>
#include <fstream>
#include <QtDebug>
#include <regex>
#include <QMessageBox>

#include "exceptions.h"

class CredentialsValidationError : public Exceptions
{
public:
    std::string what()
    {
        return "Wczytanie lub zapisanie danych nie powiodlo sie";
    }
};

class PasswordValidation
{
public:
    static bool ValidatePasswordWithRegex(std::string password);
};

class CredentialsValidation : public PasswordValidation
{
public:
    static bool Validate(QString login, QString password) throw(CredentialsValidationError);
    static bool Register(QString login, QString password) throw(CredentialsValidationError);
};


#endif // CREDENTIALSVALIDATION_H
