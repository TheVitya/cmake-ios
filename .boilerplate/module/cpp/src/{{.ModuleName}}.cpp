#include "{{.ModuleName}}/{{.ModuleName}}.hpp"

std::shared_ptr<{{.ModuleName}}> {{.ModuleName}}::s_instance = nullptr;

// Initialization method
void {{.ModuleName}}::initialize() {
  if (!s_instance) {
    s_instance = std::shared_ptr<{{.ModuleName}}>(new {{.ModuleName}}());
  }
}

std::shared_ptr<{{.ModuleName}}> {{.ModuleName}}::instance() {
  if (!s_instance) {
    throw std::runtime_error("{{.ModuleName}}: {{.ModuleName}}::initialize must be called before {{.ModuleName}}::instance.");
  }
  return s_instance;
}
