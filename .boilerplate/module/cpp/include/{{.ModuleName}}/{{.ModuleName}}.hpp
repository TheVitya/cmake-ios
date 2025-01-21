#pragma once

#include <iostream>

class {{.ModuleName}} {
public:
  {{.ModuleName}}() = default;
  {{.ModuleName}}& operator=({{.ModuleName}} const&) = delete;

  static std::shared_ptr<{{.ModuleName}}> instance();

  static void initialize();

private:
  static std::shared_ptr<{{.ModuleName}}> s_instance;
};

void c_fn();
