#pragma once

#include <cpprealm/sdk.hpp>
#include "MMKV.h"
#include <string>

using namespace realm;

struct DBConfig {
  const char* path;
};

static DBConfig default_config = {
  .path = "."
};

class DB {
public:
  DB(DB const&) = delete;
  DB& operator=(DB const&) = delete;

  static std::shared_ptr<DB> instance();

  static void initialize(DBConfig config = default_config);

  std::unique_ptr<realm::db> REALM;
  MMKV* KV;

private:
  DB(const std::string& path);

  static std::shared_ptr<DB> s_instance;
  static DBConfig CONFIG;
};

