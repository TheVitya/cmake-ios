#include "AppCore/AppCore.hpp"
#include "AppCore/database/db.hpp"
#include "AppCore/macros.hpp"
#include "AppCore/database/schemas.hpp"
#include "cpprealm/types.hpp"
#include "spdlog/spdlog.h"
#include <cpprealm/sdk.hpp>
#include <cstddef>

#if defined(__ANDROID__)
#include "spdlog/sinks/android_sink.h"
#endif

std::shared_ptr<AppCore> AppCore::s_instance = nullptr;
AppCoreConfig AppCore::CONFIG = core_default_config;

// Initialization method
void AppCore::initialize(AppCoreConfig config) {
  spdlog::info("AppCore: initializing application...");

#if defined(__ANDROID__)
  std::string tag = "spdlog-android";
  auto android_logger = spdlog::android_logger_mt("android", tag);
  spdlog::set_default_logger(android_logger);
#endif

  spdlog::info("AppCore: system_path: {}", config.system_path);

  DB::initialize({ .path = config.system_path });
  User::initialize();

  auto users = User::getAll();

  for (int i = 0; i < 100; i++) {
    User a = {
      .username= "Pityu",
      .last_sync = 123,
      .last_boot = 123,
      ._id = object_id().generate()
    };
    User::create(a);
  }

  for (auto user: users) {
    std::string useranem = user.username;
    spdlog::info("AppCore user: {}", useranem);
  }

  if (!s_instance) {
    s_instance = std::shared_ptr<AppCore>(new AppCore());
    CONFIG = config;
  }
}

AppCore AppCore::instance() {
  if (!s_instance) {
    spdlog::error("AppCore: AppCore::initialize must be called before AppCore::instance.");
    throw std::runtime_error("AppCore: AppCore::initialize must be called before AppCore::instance.");
  }
  return *s_instance.get();
}

const std::string AppCore::string(const char* key, const char* value) const {
  auto db = DB::instance();
  std::string str;

  if (value != NULL) {
    db->KV->set(value, key);
  }

  db->KV->getString(key, str);

  return str;
}

CREATE_GET_SET_FUNC(float, Float)
CREATE_GET_SET_FUNC(bool, Bool)
CREATE_GET_SET_FUNC(int32_t, Int32)
CREATE_GET_SET_FUNC(int64_t, Int64)
CREATE_GET_SET_FUNC(uint32_t, UInt32)
CREATE_GET_SET_FUNC(uint64_t, UInt64)
CREATE_GET_SET_FUNC(double, Double)
