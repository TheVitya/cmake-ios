#pragma once

#include "AppCore/database/schemas/user.hpp"

managed<User> User::initialize() {
  auto user = User::getAll();

  if (!user.size()) {
    User initial_user = {
      ._id = USER_ID,
      .last_boot = 0,
      .last_sync = 0,
      .username = ""
    };

    User::create(initial_user);
  }

  return user[0];
}
