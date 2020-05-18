#include "exceptions.h"

std::string Exceptions::what()
{
    return "Nastąpił nieoczekiwany błąd";
}

std::string ResourcesError::what()
{
    return "Nastąpił błąd ładowania zasobów";
}

std::string graphicsLoadError::what()
{
    return "Nastąpił błąd ładowania grafiki tła lub splash arta";
}

std::string musicLoadError::what()
{
    return "Nastąpił błąd ładowania muzyki";
}

std::string fileSaveError::what()
{
    return "Nastąpił błąd odczytywania z pliku";
}

std::string fileLoadError::what()
{
    return "Nastąpił błąd zapisywania do pliku";
}
