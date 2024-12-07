#pragma once

#include "AppCore/database/base.hpp"
#include <cpprealm/sdk.hpp>
#include "cpprealm/managed_primary_key.hpp"
#include "cpprealm/types.hpp"
#include <cstdint>
#include <string>

using namespace realm;

const object_id USER_ID = object_id("000000000000000000000001");

class User: public EntityBase<User> {
public:
  primary_key<object_id> _id = USER_ID;
  std::string username;
  int64_t last_sync;
  int64_t last_boot;

  static managed<User> initialize();
};

REALM_SCHEMA(User, _id, username, last_sync, last_boot)

