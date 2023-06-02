// database.cpp
// (C) Martin Alebachew, 2023

/*
This file implements the XML database interface.
*/

#include "database.hpp"

Database::Database(std::string path) {
  XMLDocument data;
  data.LoadFile(path.c_str());

  XMLElement* Windows = data.FirstChildElement("KmsData")
    ->FirstChildElement("AppItems")->FirstChildElement("AppItem");

  XMLElement* KmsItem = Windows->FirstChildElement();

  while (KmsItem) {
    XMLElement* SkuItem = KmsItem->FirstChildElement();

    while (SkuItem) {
      SkuIDStringToEdition[SkuItem->Attribute("Id")] = SkuItem->Attribute("DisplayName");
      SkuItem = SkuItem->NextSiblingElement();
    }

    KmsItem = KmsItem->NextSiblingElement();
  }
}

std::string Database::getEditionBySkuID(GUID ActID) {
  return SkuIDStringToEdition.at(ActID.toString());
}
