// database.hpp
// (C) Martin Alebachew, 2023

#pragma once
#include "../kms/winapi_types.hpp"
#include <tinyxml2.h>
#include <string>
#include <map>

using namespace tinyxml2;

class Database {
private:
  std::map<std::string, std::string> SkuIDStringToEdition;

public:
  Database(std::string path);
  std::string getEditionBySkuID(GUID ActID);
};