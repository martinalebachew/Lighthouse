// interface.hpp
// (C) Martin Alebachew, 2023

#pragma once
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

json parseObjectFromStdin();
void flushObjectToStdout(json &object);
int main();