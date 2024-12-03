#pragma once

#include <string>
#include <vector>

class AppCore {
public:
  // Constructor & Destructor
  AppCore(const char* path);
  ~AppCore();

  // Initialization and shutdown methods
  bool initialize();
  void shutdown();

  // Event system
  void onEvent(const std::string& event);

  // Getter methods
  const std::string& getAppName() const;
  const std::string& getVersion() const;
  bool isAppRunning() const;

private:
  // Fields
  std::string appName;
  std::string version;
  std::string system_path;
  bool isRunning;

  // Event list
  std::vector<std::string> events;
};
