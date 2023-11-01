// database.hpp
// (C) Martin Alebachew, 2023

/*
This file defines the XML database interface.
*/

#pragma once
#include "../kms/winapi_types.hpp"
#include <map>
#include <pugixml.hpp>
#include <string>

using namespace pugi;

class Database {
private:
  std::map<std::string, std::string> SkuIDStringToEdition;

public:
  Database(std::string path);
  std::string getEditionBySkuID(GUID ActID);
};
