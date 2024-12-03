#include "AppCore/AppCore.hpp"
#include "AppCore/database/db.hpp"
#include "spdlog/spdlog.h"
#include <cpprealm/sdk.hpp>
#include <iostream>
// #include <cpr/cpr.h>

#if defined(__ANDROID__)
#include "spdlog/sinks/android_sink.h"
#endif



// Constructor
AppCore::AppCore(const char* path) : appName("MyApp"), version("1.0"), isRunning(false), system_path(path) {
  spdlog::info("AppCore Initializing...");

#if defined(__ANDROID__)
    std::string tag = "spdlog-android";
    auto android_logger = spdlog::android_logger_mt("android", tag);
    spdlog::set_default_logger(android_logger);
#endif

  spdlog::info("AppCore system_path: {}", system_path);

  spdlog::info("AppCore Initialized");
}

// Destructor
AppCore::~AppCore() {
  spdlog::info("AppCore shutting down.");
}

// Initialization method
bool AppCore::initialize() {
  std::cout << "Initializing application..." << std::endl;

  auto db = DB::instance(system_path);

  // auto realm = db.REALM.get();
  // Use them like regular objects.

  // spdlog::info("Welcome to spdlog!");
  // cpr::Response r = cpr::Get(cpr::Url{"https://api.github.com/repos/whoshuu/cpr/contributors"},
  //                            cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
  //                            cpr::Parameters{{"anon", "true"}, {"key", "value"}});
  // r.status_code;                  // 200
  // r.header["content-type"];       // application/json; charset=utf-8
  // r.text;                         // JSON text string
  // spdlog::info(r.text);
  isRunning = true;
  return isRunning;
}

// Shutdown method
void AppCore::shutdown() {
  std::cout << "Shutting down application..." << std::endl;
  isRunning = false;
}

// Event handling
void AppCore::onEvent(const std::string& event) {
  events.push_back(event);
  std::cout << "Event triggered: " << event << std::endl;
}

// Getter methods
const std::string& AppCore::getAppName() const {
  return appName;
}

const std::string& AppCore::getVersion() const {
  return version;
}

bool AppCore::isAppRunning() const {
  return isRunning;
}
