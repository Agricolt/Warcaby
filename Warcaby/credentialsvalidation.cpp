#include "credentialsvalidation.h"


bool CredentialsValidation::Validate(QString login, QString password) throw(CredentialsValidationError)
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
        throw CredentialsValidationError();
    }
    passwords_file.close();
    return false;
}

bool CredentialsValidation::Register(QString login, QString password) throw(CredentialsValidationError)
{
    std::string got_login = login.toStdString();
    std::string got_pass = password.toStdString();
    if(PasswordValidation::ValidatePasswordWithRegex(got_pass))
    {

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
        {
            throw CredentialsValidationError();
            return false;
        }
        passwords_file.close();
        return true;
    }
    else
    {
        QMessageBox msg;
        msg.setText("Hasło musi spełnić następujące warunki: \n długość hasła od 6 do 20 znaków \n składa się z liter a-z, A-Z i cyfr 0-9 oraz wybranych znaków specjalnych \n musi zawierać co najmniej jedną małą literę, jedną dużą, jedną cyfrę i jeden znak specjalny");
        msg.setWindowTitle("Błąd!");
        msg.exec();
        throw CredentialsValidationError();
    }
}

bool PasswordValidation::ValidatePasswordWithRegex(std::string password)
{
    std::regex r_haslo("^(?=.*[A-Z])(?=.*[a-z])(?=.*\\d)(?=.*[!_$?-])[A-Za-z\\d!_$?-]{6,20}$");
    return std::regex_match(password, r_haslo);
}
