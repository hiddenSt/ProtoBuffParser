#ifndef PROTOBUFPARSER_PROTOBUF_PARSER_PACKAGE_HPP_
#define PROTOBUFPARSER_PROTOBUF_PARSER_PACKAGE_HPP_

#include <string>

namespace protobuf_parser {

class Package {
 public:
  Package() = delete;
  explicit Package(const std::string& name);
  explicit Package(const std::string& name, Package* parent_package);
  explicit Package(std::string&& name) noexcept;
  explicit Package(std::string&& name, Package* parent_package) noexcept;

  bool operator==(const Package& other);
  bool operator!=(const Package& other);

  Package* GetParentPackage() noexcept;
  void SetParentPackage(Package* parent) noexcept;
  const std::string& GetName() const;

 private:
  std::string name_;
  Package* parent_package_;
};

}  // namespace protobuf_parser

#endif  // PROTOBUFPARSER_PROTOBUF_PARSER_PACKAGE_HPP_