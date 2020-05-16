#include "credentialsvalidation.h"


bool CredentialsValidation::Validate(QString login, QString password)
{
    std::string got_login = login.toStdString();
    std::string got_pass = password.toStdString();
    std::fstream passwords_file;
    passwords_file.open("credentials.txt", std::ios::in | std::ios::app);
    //loginy i hasla sa zapisanwe w postaci:
    //login haslo
    //login haslo
    //itd...
    std::string loginstd, haslostd;
    if (passwords_file.good())
    {
        while(passwords_file.eof() != true)
        {
            passwords_file >> loginstd;
            passwords_file >> haslostd;
            if (loginstd == got_login && haslostd == got_pass)
                return true;
        }
    }
    passwords_file.close();
    return false;
}

bool CredentialsValidation::Register(QString login, QString password)
{
    std::string got_login = login.toStdString();
    std::string got_pass = password.toStdString();
    std::fstream passwords_file;
    passwords_file.open("credentials.txt", std::ios::out | std::ios::app);
    //loginy i hasla sa zapisanwe w postaci:
    //login haslo
    //login haslo
    //itd...
    if (passwords_file.good())
    {
        passwords_file << got_login;
        passwords_file << " ";
        passwords_file << got_pass;
        passwords_file << "\n";
    }
    else
        return false;
    passwords_file.close();
    return true;
}
