// wchar.hpp
// (C) Martin Alebachew

#pragma once
#include "../kms/winapi_types.hpp"
#include "base64.h"

std::string wcharStringToBase64(WCHAR *string, size_t length);