// database.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the XML database interface.
*/

#pragma once
#include "../kms/winapi_types.hpp"
#include <map>
#include <string>
#include <tinyxml2.h>

using namespace tinyxml2;

class Database {
private:
  std::map<std::string, std::string> SkuIDStringToEdition;

public:
  Database(std::string path);
  std::string getEditionBySkuID(GUID ActID);
};
