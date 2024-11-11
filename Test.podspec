Pod::Spec.new do |s|
  s.name         = "Test"
  s.version      = "1.0.0"
  s.summary      = "Test"
  s.homepage     = "Test"
  s.license      = "MIT"
  s.authors      = "Author"
  s.source       = { :path => "." }

  s.vendored_frameworks = "Test.xcframework"

  s.xcconfig = {
    "ENABLE_USER_SCRIPT_SANDBOXING" => "NO",
    "CLANG_CXX_LANGUAGE_STANDARD" => "c++20",
    "DEFINES_MODULE" => "YES",
    "CLANG_CXX_LIBRARY" => "libc++"
  }

  s.libraries = "c++"
end
