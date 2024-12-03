#include "AppCore/database/db.hpp"
#include "MMKV.h"
#include "spdlog/spdlog.h"
#include "realm/exceptions.hpp"

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

