#ifndef PROTOBUF_PARSER_PROTOBUF_PARSER_SERIALIZERS_JSON_SERIALIZER_HPP_
#define PROTOBUF_PARSER_PROTOBUF_PARSER_SERIALIZERS_JSON_SERIALIZER_HPP_

#include <string>

#include <nlohmann/json.hpp>

#include <protobuf_parser/elements/message.hpp>

namespace protobuf_parser {
namespace serializers {

template <typename View>
class JsonSerializer {
 public:
  JsonSerializer(const View& view);
  std::string SerializeMessages();

  std::string SerializeFiles();
  std::string SerializePackages();
  std::string SerializeDirectories();
  std::string SerializeEnums();

 private:
  nlohmann::json SerializeFields(const Message& message);
  nlohmann::json SerializeNestedMessages(const Message& message);

  nlohmann::json messages_json_representation_;
  nlohmann::json files_json_representation_;
  nlohmann::json packages_json_representation_;
  nlohmann::json directories_json_representation_;
  nlohmann::json enums_json_representation_;
  View view_;
};

template <typename View>
std::string JsonSerializer<View>::SerializeMessages() {
  auto messages_json_array = nlohmann::json::array();
  for (auto& message : view_) {
    auto message_json_object = nlohmann::json{};
    for (auto& data : message.Serialize()) {
      message_json_object[data.first] = data.second;
    }

    message_json_object["fields"] = SerializeFields(message);
    message_json_object["nested_messages"] = SerializeNestedMessages(message);
    messages_json_array.push_back(message_json_object);
  }
  messages_json_representation_["messages"] = messages_json_array;
  return messages_json_representation_.dump(4);
}

template <typename View>
JsonSerializer<View>::JsonSerializer(const View& view) : view_(view) {
}

template <typename View>
nlohmann::json JsonSerializer<View>::SerializeFields(const Message& message) {
  nlohmann::json fields = nlohmann::json::array();
  for (auto& field : message.GetFields()) {
    fields.push_back(field->Serialize());
  }
  return fields;
}

template <typename View>
nlohmann::json JsonSerializer<View>::SerializeNestedMessages(const Message& message) {
  nlohmann::json nested_messages = nlohmann::json::array();

  for (auto& nested_message : message.GetNestedMessages()) {
    nlohmann::json nested_message_object;
    for (auto& data : nested_message.Serialize()) {
      nested_message_object[data.first] = data.second;
    }

    nested_message_object["fields"] = SerializeFields(nested_message);
    nested_message_object["nested_messages"] = SerializeNestedMessages(nested_message);
    nested_messages.push_back(nested_message_object);
  }
  return nested_messages;
}

template <typename View>
std::string JsonSerializer<View>::SerializeFiles() {
  auto files_json_array = nlohmann::json::array();
  for (auto& file : view_.GetFiles()) {
    auto serialized_file = file->Serialize();
    auto file_json_object = nlohmann::json{};
    for (auto& field : serialized_file) {
      file_json_object[field.first] = field.second;
    }
    files_json_array.push_back(file_json_object);
  }

  files_json_representation_["files"] = files_json_array;
  return files_json_representation_.dump(4);
}

template <typename View>
std::string JsonSerializer<View>::SerializePackages() {
  auto packages_json_array = nlohmann::json::array();
  for (auto& package: view_.GetPackages()) {
    auto serialized_package = package->Serialize();
    auto package_json_object = nlohmann::json{};
    for (auto& field : serialized_package) {
      package_json_object[field.first] = field.second;
    }
    packages_json_array.push_back(package_json_object);
  }

  packages_json_representation_["packages"] = packages_json_array;
  return packages_json_representation_.dump(4);
}

template <typename View>
std::string JsonSerializer<View>::SerializeDirectories() {
  auto directories_json_array = nlohmann::json::array();
  for (auto& directory : view_.GetDirectories()) {
    auto serialized_directory = directory->Serialize();
    auto directory_json_object = nlohmann::json{};
    for (auto& field: serialized_directory) {
      directory_json_object[field.first] = field.second;
    }
    directories_json_array.push_back(directory_json_object);
  }

  directories_json_representation_["directories"] = directories_json_array;
  return directories_json_representation_.dump(4);
}

template <typename View>
std::string JsonSerializer<View>::SerializeEnums() {
  return std::string();
}

}  // namespace serializers
}  // namespace protobuf_parser

#endif  // PROTOBUF_PARSER_PROTOBUF_PARSER_SERIALIZERS_JSON_SERIALIZER_HPP_
