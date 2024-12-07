#pragma once

#include "AppCore/database/db.hpp"
#include "cpprealm/results.hpp"

template <typename T>
class EntityBase {
public:
  static results<T> getAll() {
    auto db = DB::instance();
    return db->REALM->objects<T>();
  }

  static managed<T> create(T& entity) {
    auto db = DB::instance();
    auto realm = db->REALM.get();

    auto new_entity = realm->write([&] {
      return realm->add(std::move(entity));
    });

    return new_entity;
  }

  static std::vector<managed<T>> createMany(std::vector<T>& entities) {
    auto db = DB::instance();
    auto realm = db->REALM.get();

    std::vector<managed<T>> managed_entities;

    realm->write([&] {
      for (auto entity: entities) {
        managed<T> managed_entity = realm->add(std::move(entity));

        managed_entities.push_back(managed_entity);
      }
    });

    return managed_entities;
  }


  static void remove(managed<T>& entity) {
    auto db = DB::instance();
    auto realm = db->REALM.get();

    realm->write([&] {
      realm->remove(entity);
    });
  }

  static void removeMany(results<T>& entities) {
    auto db = DB::instance();
    auto realm = db->REALM.get();

    realm->write([&] {
      while (entities.size()) {
        auto entity = entities[0];

        realm->remove(entity);
      }
    });
  };

  static void removeMany(std::vector<managed<T>>& entities) {
    auto db = DB::instance();
    auto realm = db->REALM.get();

    realm->write([&] {
      for (auto& entity: entities) {
        realm->remove(entity);
      }
    });

    entities.clear();
  };

  static void removeAll() {
    auto entities = getAll();

    removeMany(entities);
  };
};
