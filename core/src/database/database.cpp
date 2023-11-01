// database.cpp
// (C) Martin Alebachew, 2023

/*
This file implements the XML database interface.
*/

#include "database.hpp"

Database::Database(std::string path) {
  xml_document doc;
  xml_parse_result loaded = doc.load_file(path.c_str());

  if (!loaded) {
    throw std::runtime_error("[XML] Failed to load database file.");
  }

  xml_node data = doc.child("KMSData");
  xpath_node_set sku_xpath_set = data.select_nodes("SkuItem");
  
  for (xpath_node sku_xpath_node : sku_xpath_set) {
    xml_node sku_node = sku_xpath_node.node();
    SkuIDStringToEdition[sku_node.attribute("Id").value()] =
      sku_node.attribute("DisplayName").value();
  }
}

std::string Database::getEditionBySkuID(GUID ActID) {
  return SkuIDStringToEdition.at(ActID.toString());
}
