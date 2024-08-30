Pod::Spec.new do |s|
  s.name         = "Test"
  s.version      = "1.0.0"
  s.summary      = "Test"
  s.homepage     = "Test"
  s.license      = "MIT"
  s.authors      = "Author"
  s.source       = { :path => "." }

  s.platform     = :ios, '13.0'

  s.vendored_frameworks = 'Frameworks/Test.framework'
end