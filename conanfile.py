# vim: set ts=2 sw=2 tw=0 et :

from conans import ConanFile, CMake, tools

class TaygeteConan(ConanFile):
  name = "taygete"
  version = "0.1"
  license = "BSD 2-clause \"Simplified\" License"
  author = "Ruan Evangelista Formigoni ruanformigoni@gmail.com"
  url = "https://gitlab.com/formigoni/taygete"
  description = "C++ Generic Data-Structures Collection"
  topics = ("C++", "STL", "Template","Data Structures", "Generic")
  generators = "cmake"
  requires = "range-v3/0.10.0@ericniebler/stable", \
             "functionalplus/v0.2.8-p0@ruanformigoni/stable", \
             "lorina/0.2@epfl/testing", \
             "doctest/2.4.0"
  exports_sources = "include/*", "cmake/*", "LICENSE", "CMakeLists.txt"
  no_copy_source = True

  def source(self):
    self.run("git clone https://gitlab.com/formigoni/taygete.git")

    # Remove testing
    tools.replace_in_file(
      "CMakeLists.txt",
      "add_subdirectory(test)",
      '',
      strict=True
    )

  def package(self):
    cmake = CMake(self)
    cmake.configure()
    cmake.install()
    self.copy("*.hpp", dst="include", src="include")
    self.copy("LICENSE", ignore_case=True, keep_path=False)

  def package_id(self):
    self.info.header_only()
