#include "AppCore/database/db.hpp"
#include "MMKV.h"
#include "spdlog/spdlog.h"
#include "realm/exceptions.hpp"

std::shared_ptr<DB> DB::s_instance = nullptr;
DBConfig DB::CONFIG = default_config;

DB::DB(const std::string& path) {
  try {
    std::string full_path = path + "/main.realm";

    spdlog::info("DB: opening realm at: {}", full_path);

    realm::db_config config;
    config.set_path(full_path);
    REALM = std::make_unique<realm::db> (std::move (config));

    spdlog::info("DB: realm opened");
  } catch (realm::Exception e) {
    spdlog::error("DB: realm initialization failed: {}", e.reason());
    throw e;
  }

  spdlog::info("DB: opening MMKV at: {}", path);

  MMKV::initializeMMKV(path);
  KV = MMKV::defaultMMKV();

  spdlog::info("DB: MMKV opened");
}

void DB::initialize(DBConfig config) {
  if (!s_instance) {
    s_instance = std::shared_ptr<DB>(new DB(config.path));
    CONFIG = config;
  }
}

std::shared_ptr<DB> DB::instance() {
  if (!s_instance) {
    throw std::runtime_error("DB: DB::initialize must be called before DB::instance.");
  }
  return s_instance;
}
