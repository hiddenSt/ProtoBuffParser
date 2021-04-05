#include <gtest/gtest.h>

#include <protobuf_parser/field.hpp>
#include <protobuf_parser/message.hpp>
#include <protobuf_parser/message_field_type.hpp>
#include <protobuf_parser/file.hpp>
#include <protobuf_parser/package.hpp>

#include <tests/util/container/test_fields_container.hpp>

namespace tests {


TEST(FieldTests, CanGetFieldType) {
  std::string message_name{"simple_name"};
  std::string file_name{"file_name"};
  std::string path_name{"path_name"};
  std::string package_name{"package_name"};
  std::string field_name{"Hello world"};
  std::size_t number = 1;

  container::TestFieldsContainer test_fields_container{};
  protobuf_parser::File file{file_name, path_name};
  protobuf_parser::Package package{path_name};
  protobuf_parser::Message message{message_name, file, package, test_fields_container};
  protobuf_parser::MessageFieldType message_field_type{message};
  protobuf_parser::Field field{field_name, number, message_field_type};

  ASSERT_NO_THROW(field.GetType());
}


TEST(FieldTests, ReturnsCorrectMessageTypeName) {
  std::string message_name{"simple_name"};
  std::string file_name{"file_name"};
  std::string path_name{"path_name"};
  std::string package_name{"package_name"};
  std::string field_name{"Hello world"};
  std::size_t number = 1;

  container::TestFieldsContainer test_fields_container{};
  protobuf_parser::File file{file_name, path_name};
  protobuf_parser::Package package{path_name};
  protobuf_parser::Message message{message_name, file, package, test_fields_container};
  protobuf_parser::MessageFieldType message_field_type{message};
  protobuf_parser::Field field{field_name, number, message_field_type};

  ASSERT_EQ(field.GetType().GetName(), message.GetName());
}

TEST(FieldTests, ReturnsCorrectNumber) {
  std::string message_name{"simple_name"};
  std::string file_name{"file_name"};
  std::string path_name{"path_name"};
  std::string package_name{"package_name"};
  std::string field_name{"Hello world"};
  std::size_t number = 1;

  container::TestFieldsContainer test_fields_container{};
  protobuf_parser::File file{file_name, path_name};
  protobuf_parser::Package package{path_name};
  protobuf_parser::Message message{message_name, file, package, test_fields_container};
  protobuf_parser::MessageFieldType message_field_type{message};
  protobuf_parser::Field field{field_name, number, message_field_type};

  ASSERT_EQ(field.GetNumber(), number);
}

TEST(FieldTests, ReturnsCorrectName) {
  std::string message_name{"simple_name"};
  std::string file_name{"file_name"};
  std::string path_name{"path_name"};
  std::string package_name{"package_name"};
  std::string field_name{"Hello world"};
  std::size_t number = 1;

  container::TestFieldsContainer test_fields_container{};
  protobuf_parser::File file{file_name, path_name};
  protobuf_parser::Package package{path_name};
  protobuf_parser::Message message{message_name, file, package, test_fields_container};
  protobuf_parser::MessageFieldType message_field_type{message};
  protobuf_parser::Field field{field_name, number, message_field_type};

  ASSERT_EQ(field.GetName(), field_name);
}

TEST(FieldTests, ReturnsCorrectEnumName) {
  ASSERT_TRUE(false);
}

TEST(FieldTests, ReturnsCorrectBuiltinTypeName) {
  ASSERT_TRUE(false);
}

}  // namespace tests