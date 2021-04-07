#include "field.hpp"

namespace protobuf_parser {

Field::Field(const std::string& name, std::size_t number, FieldType* type, bool repeated)
    : name_(name), number_(number), type_(type), repeated_(repeated) {
}

Field::Field(std::string&& name, std::size_t number, FieldType* type, bool repeated) noexcept
    : name_(std::move(name)), number_(number), type_(type), repeated_(repeated) {
}

const std::string& Field::GetName() const {
  return name_;
}

const FieldType& Field::GetType() const {
  return *type_;
}

std::size_t Field::GetNumber() const {
  return number_;
}

Field& Field::operator=(const Field& other) {
  name_ = other.name_;
  number_ = other.number_;
  repeated_fields_ = other.repeated_fields_;
  // TODO: type pointer copy
  return *this;
}

bool Field::IsRepeated() const noexcept {
  return repeated_;
}

}  // namespace protobuf_parser
