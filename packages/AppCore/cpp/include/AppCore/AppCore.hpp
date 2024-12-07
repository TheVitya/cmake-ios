#pragma once

#include <cstddef>
#include <string>

#define CREATE_GET_SET_FUNC(TYPE) \
const TYPE get_##TYPE(const char* key, const TYPE default_value) const; \
const TYPE set_##TYPE(const char* key, const TYPE value) const;

struct AppCoreConfig {
  const char* system_path;
};

static AppCoreConfig core_default_config = {
  .system_path = "./"
};

class AppCore {
public:
  AppCore() = default;
  AppCore& operator=(AppCore const&) = delete;

  static AppCore instance();

  static void initialize(AppCoreConfig config = core_default_config);

  const std::string string(const char* key, const char* value = NULL) const;

  CREATE_GET_SET_FUNC(float)
  CREATE_GET_SET_FUNC(bool)
  CREATE_GET_SET_FUNC(int32_t)
  CREATE_GET_SET_FUNC(int64_t)
  CREATE_GET_SET_FUNC(uint32_t)
  CREATE_GET_SET_FUNC(uint64_t)
  CREATE_GET_SET_FUNC(double)

private:
  static std::shared_ptr<AppCore> s_instance;
  static AppCoreConfig CONFIG;
};

