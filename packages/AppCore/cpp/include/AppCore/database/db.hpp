#pragma once

#include <cpprealm/sdk.hpp>
#include "MMKV.h"
#include <string>

using namespace realm;

class DB
{
public:
  DB(DB const&) = delete;
  DB& operator=(DB const&) = delete;

  static std::shared_ptr<DB> instance(const std::string& path)
  {
    static std::shared_ptr<DB> s{new DB(path)};
    return s;
  }

  std::unique_ptr<realm::db> REALM;
  MMKV* KV;

private:
  DB(const std::string& path);
};
