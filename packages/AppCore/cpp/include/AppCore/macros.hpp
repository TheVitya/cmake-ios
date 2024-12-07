#include "AppCore/database/db.hpp"

#define DECLARE_REALM_SCHEMA(cls, is_embedded_object, is_asymmetric_object, obj_type, ...) \
    template <> struct managed<cls> : public cls { \
        managed() = default; \
        static constexpr ObjectType object_type = obj_type;     \
        FOR_EACH(DECLARE_PERSISTED, cls, __VA_ARGS__) \
        static constexpr auto schema = realm::schema(#cls, object_type, std::tuple{ FOR_EACH(DECLARE_PROPERTY, cls, __VA_ARGS__) }  ); \
        static constexpr auto managed_pointers() { \
            return std::tuple{FOR_EACH(DECLARE_MANAGED_PROPERTY, cls, __VA_ARGS__)};  \
        }                                                                                          \
        template <typename PtrType> static constexpr auto unmanaged_to_managed_pointer(PtrType ptr) {           \
           FOR_EACH(DECLARE_COND_UNMANAGED_TO_MANAGED, cls, __VA_ARGS__);                                       \
        }                                                                                                       \
        static constexpr auto managed_pointers_names() {                                                        \
            constexpr auto managed_pointers_names = std::array<std::string_view, std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value>{FOR_EACH(DECLARE_MANAGED_PROPERTY_NAME, cls, __VA_ARGS__)}; \
            return internal::array_to_tuple(managed_pointers_names);                                            \
        }                                                                                                       \
                                                                                                                \
        static constexpr bool is_object = true;                                                                 \
        explicit managed(const internal::bridge::obj& obj,                                                      \
                         internal::bridge::realm realm)                                                         \
        : m_obj(std::move(obj))                                                                                 \
        , m_realm(std::move(realm))                                                                             \
        {                                                                                                       \
            auto zipped = internal::zip_tuples(managed_pointers(), managed_pointers_names());                   \
            std::apply([&](auto& ...pair) {                                                                     \
                ((*this.*pair.first).assign(&m_obj, &m_realm, m_obj.get_table().get_column_key(pair.second)), ...); \
            }, zipped);                                                                                         \
        }                                                                                                       \
        managed(const managed& other) {                                                                         \
            m_obj = other.m_obj;                                                                                \
            m_realm = other.m_realm;                                                                            \
            m_rbool_query = other.m_rbool_query;                                                                \
            auto zipped = internal::zip_tuples(managed_pointers(), managed_pointers_names());                   \
            if (m_rbool_query) {                                                                                \
                auto schema = m_realm.schema().find(other.schema.name);                                         \
                auto group = m_realm.read_group();                                                              \
                auto table_ref = group.get_table(schema.table_key());                                           \
                std::apply([&](auto& ...pair) {                                                                 \
                    ((*this.*pair.first).prepare_for_query(&m_realm, table_ref, pair.second, m_rbool_query), ...);  \
                }, zipped);                                                                                     \
            } else {                                                                                            \
                std::apply([&](auto& ...pair) {                                                                 \
                    ((*this.*pair.first).assign(&m_obj, &m_realm, m_obj.get_table().get_column_key(pair.second)), ...); \
                }, zipped);                                                                                     \
            }                                                                                                   \
        }                                                                                                       \
        managed& operator=(const managed& other) {                                                              \
            m_obj = other.m_obj;                                                                                \
            m_realm = other.m_realm;                                                                            \
            m_rbool_query = other.m_rbool_query;                                                                \
            auto zipped = internal::zip_tuples(managed_pointers(), managed_pointers_names());                   \
            if (m_rbool_query) {                                                                                \
                auto schema = m_realm.schema().find(other.schema.name);                                         \
                auto group = m_realm.read_group();                                                              \
                auto table_ref = group.get_table(schema.table_key());                                           \
                std::apply([&](auto& ...pair) {                                                                 \
                    ((*this.*pair.first).prepare_for_query(&m_realm, table_ref, pair.second, m_rbool_query), ...);  \
                }, zipped);                                                                                     \
            } else {                                                                                            \
                std::apply([&](auto& ...pair) {                                                                 \
                    ((*this.*pair.first).assign(&m_obj, &m_realm, m_obj.get_table().get_column_key(pair.second)), ...); \
                }, zipped);                                                                                     \
            }                                                                                                   \
            return *this;                                                                                       \
        }                                                                                                       \
        managed(managed&& other) {                                                                              \
            m_obj = std::move(other.m_obj);                                                                     \
            m_realm = std::move(other.m_realm);                                                                 \
            m_rbool_query = std::move(other.m_rbool_query);                                                     \
            auto zipped = internal::zip_tuples(managed_pointers(), managed_pointers_names());                   \
            if (m_rbool_query) {                                                                                \
                auto schema = m_realm.schema().find(other.schema.name);                                         \
                auto group = m_realm.read_group();                                                              \
                auto table_ref = group.get_table(schema.table_key());                                           \
                std::apply([&](auto& ...pair) {                                                                 \
                    ((*this.*pair.first).prepare_for_query(&m_realm, table_ref, pair.second, m_rbool_query), ...);  \
                }, zipped);                                                                                     \
             } else {                                                                                           \
                std::apply([&](auto& ...pair) {                                                                 \
                    ((*this.*pair.first).assign(&m_obj, &m_realm, m_obj.get_table().get_column_key(pair.second)), ...); \
                }, zipped);                                                                                     \
             }                                                                                                  \
        }                                                                                                       \
        managed& operator=(managed&& other) {                                                                   \
            m_obj = std::move(other.m_obj);                                                                     \
            m_realm = std::move(other.m_realm);                                                                 \
            m_rbool_query = std::move(other.m_rbool_query);                                                     \
            auto zipped = internal::zip_tuples(managed_pointers(), managed_pointers_names());                   \
            if (m_rbool_query) {                                                                                \
                auto schema = m_realm.schema().find(other.schema.name);                                         \
                auto group = m_realm.read_group();                                                              \
                auto table_ref = group.get_table(schema.table_key());                                           \
                std::apply([&](auto& ...pair) {                                                                 \
                    ((*this.*pair.first).prepare_for_query(&m_realm, table_ref, pair.second, m_rbool_query), ...);  \
                }, zipped);                                                                                     \
            } else {                                                                                            \
                std::apply([&](auto& ...pair) {                                                                 \
                    ((*this.*pair.first).assign(&m_obj, &m_realm, m_obj.get_table().get_column_key(pair.second)), ...); \
                }, zipped);                                                                                     \
            }                                                                                                   \
            return *this;                                                                                       \
        }                                                                                                       \
        static managed prepare_for_query(const internal::bridge::realm& r, realm::rbool* q) {                   \
            managed<cls> m;                                                                                     \
            m.m_realm = r;                                                                                      \
            m.m_rbool_query = q;                                                                                \
            auto schema = m.m_realm.schema().find(m.schema.name);                                               \
            auto group = m.m_realm.read_group();                                                                \
            auto table_ref = group.get_table(schema.table_key());                                               \
            auto zipped = internal::zip_tuples(managed_pointers(), managed_pointers_names());                   \
            std::apply([&m, &table_ref](auto& ...pair) {                                                        \
                ((m.*pair.first).prepare_for_query(&m.m_realm, table_ref, pair.second, m.m_rbool_query), ...);  \
            }, zipped);                                                                             \
            return m;                                                                               \
        }                                                                                           \
        cls detach() const {                                                                        \
            cls v;                                                                                  \
            auto assign = [&v, this](auto& pair) {                                                  \
                v.*(std::decay_t<decltype(pair.first)>::ptr) = ((*this).*(pair.second)).detach();   \
            };                                                                                      \
            auto zipped = internal::zip_tuples(managed<cls>::schema.ps, managed<cls>::managed_pointers()); \
            std::apply([&assign](auto& ...pair) {                                                   \
                (assign(pair), ...);                                                                \
            }, zipped);                                                                             \
            return v;                                                                               \
        }                                                                                           \
        auto observe(std::function<void(realm::object_change<managed>&&)>&& fn) {                   \
            auto m_object = std::make_shared<internal::bridge::object>(m_realm, m_obj);             \
            auto wrapper = realm::object_change_callback_wrapper<managed>{                          \
            std::move(fn), this, m_object};                                                         \
            return m_object->add_notification_callback(                                             \
            std::make_shared<realm::object_change_callback_wrapper<managed>>(wrapper));             \
        }                                                                                           \
        bool is_invalidated() {                                                                     \
            return !m_obj.is_valid();                                                               \
        }                                                                                           \
        bool is_frozen() {                                                                          \
            return m_realm.is_frozen();                                                             \
        }                                                                                           \
        managed<cls> freeze() {                                                                     \
            auto realm = m_realm.freeze();                                                          \
            return managed<cls>(realm.import_copy_of(m_obj), realm);                                \
        }                                                                                           \
        managed<cls> thaw() {                                                                       \
            if (is_invalidated()) {                                                                 \
                throw std::runtime_error("Invalid objects cannot be thawed.");                      \
            }                                                                                       \
            if (!is_frozen()) {                                                                     \
                return *this;                                                                       \
            }                                                                                       \
            auto thawed_realm = m_realm.thaw();                                                     \
            return managed<cls>(thawed_realm.import_copy_of(m_obj), thawed_realm);                  \
        }                                                                                           \
        db get_realm() {                                                                            \
            return db(m_realm);                                                                     \
        }                                                                                           \
        bool operator ==(const managed<cls>& other) const {                                        \
            if (m_rbool_query != nullptr)                                                           \
                throw std::runtime_error("This comparison operator is not valid inside of `where`");    \
            auto& a = m_obj;                                                                        \
            auto& b = other.m_obj;                                                                  \
            if (m_realm != other.m_realm) {                                                         \
                return false;                                                                       \
            }                                                                                       \
            return a.get_table() == b.get_table()                                                   \
                   && a.get_key() == b.get_key();                                                   \
        }                                                                                           \
        bool operator ==(const managed<cls*>& other) const {                                        \
            if (m_rbool_query != nullptr)                                                           \
                throw std::runtime_error("This comparison operator is not valid inside of `where`");    \
            auto& a = m_obj;                                                                        \
            auto& b = other.m_obj;                                                                  \
            if (m_realm != other->m_realm) {                                                        \
                return false;                                                                       \
            }                                                                                       \
            return a.get_table() == b->get_table()                                                  \
                   && a.get_key() == b->get_key();                                                  \
        }                                                                                           \
        bool operator !=(const managed<cls>& other) const {                                         \
           return !this->operator ==(other);                                                        \
        }                                                                                           \
        bool operator !=(const managed<cls*>& other) const {                                        \
            return !this->operator ==(other);                                                       \
        }                                                                                           \
        bool operator < (const managed<cls>& rhs) const {                                           \
            return m_obj.get_key() < rhs.m_obj.get_key();                                           \
        }                                                                                           \
        void to_json(std::ostream& out) const noexcept {                                            \
            m_obj.to_json(out);                                                                     \
        }                                                                                           \
    private:                                                                                        \
        internal::bridge::obj m_obj;                                                                \
        internal::bridge::realm m_realm;                                                            \
        rbool* m_rbool_query = nullptr;                                                             \
        friend struct db;                                                                           \
        template <typename, typename> friend struct managed;                                        \
        template <typename, typename> friend struct box;                                            \
        template <typename> friend struct ::realm::thread_safe_reference;                           \
        template <typename T> friend rbool* ::realm::internal::get_rbool(const T&);                 \
                                                                                                    \
    };                                                                                              \
    struct meta_schema_##cls {                                                                      \
        meta_schema_##cls() {                                                                       \
            auto s = managed<cls>::schema.to_core_schema();                                         \
          auto it = std::find(std::begin(realm::db::schemas), std::end(realm::db::schemas), s);   \
            if (it == std::end(realm::db::schemas))                                                 \
                realm::db::schemas.push_back(s);                                                    \
        }                                                                                           \
    };                                                                                              \
    static inline meta_schema_##cls _meta_schema_##cls{};

#define CREATE_GET_SET_FUNC(TYPE, TYPE_NAME)                                      \
    const TYPE AppCore::set_##TYPE(const char* key, const TYPE value) const {  \
        auto db = DB::instance();                                                 \
        db->KV->set(value, key);                                             \
        return value;                                       \
    } \
    const TYPE AppCore::get_##TYPE(const char* key, TYPE default_value) const {  \
        auto db = DB::instance();                                                 \
        return db->KV->get##TYPE_NAME(key, default_value);                                       \
    }
