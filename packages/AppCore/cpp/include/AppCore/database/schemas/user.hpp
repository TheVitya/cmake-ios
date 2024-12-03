#pragma once

#include <cpprealm/sdk.hpp>
#include "cpprealm/types.hpp"
#include "AppCore/database/base.hpp"
#include <cstdint>
#include <string>

using namespace realm;

const object_id USER_ID = object_id("000000000000000000000001");

class User: EntityBase<User> {
public:
  primary_key<object_id> _id = USER_ID;
  std::string username;
  int64_t last_sync;
  int64_t last_boot;
private:
};

REALM_SCHEMA(User, _id, username, last_sync, last_boot)
