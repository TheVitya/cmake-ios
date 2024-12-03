#include "AppCore/database/base.hpp"
#include "AppCore/database/db.hpp"

template <typename T>
T EntityBase<T>::getAll() {
  auto entities = DB::REALM->objects<T>();

  return entities;
}
