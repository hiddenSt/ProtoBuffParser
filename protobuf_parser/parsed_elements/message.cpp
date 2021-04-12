#include "message.hpp"

namespace protobuf_parser {

Message::Message(const std::string& name, File* file, Message* parent_message)
    : name_(name), file_(file), parent_message_(parent_message) {
}

Message::Message(const std::string& name, File* file)
    : name_(name), file_(file), parent_message_(nullptr) {
}

Package* Message::GetPackage() const noexcept {
  return file_->GetPackage();
}

File* Message::GetFile() const noexcept {
  return file_;
}

Message* Message::GetParentMessage() const noexcept {
  return parent_message_;
}

const std::string& Message::GetName() const {
  return name_;
}

bool Message::operator==(const Message& other) {
  if (name_ != other.name_) {
    return false;
  }

  if (file_ != other.file_) {
    return false;
  }

  if (parent_message_ != other.parent_message_) {
    return false;
  }

  return true;
}

bool Message::operator!=(const Message& other) {
  return !(*this == other);
}

Directory* Message::GetDirectory() {
  return file_->GetDirectory();
}
void Message::AddField(const Field& field) {
  fields_.push_back(field);
}

const std::vector<Field>& Message::GetFields() const {
  return fields_;
}

const std::vector<Message>& Message::GetNestedMessages() const {
  return nested_messages_;
}

Message* Message::AddNestedMessage(const Message& message) {
  nested_messages_.push_back(message);
  nested_messages_[nested_messages_.size() - 1].SetParentMessage(this);
  return &nested_messages_[nested_messages_.size() - 1];
}

void Message::AddReservedName(const std::string& name) {
  reserved_names_.push_back(name);
}

void Message::AddReservedNumber(std::size_t number) {
  reserved_numbers_.push_back(number);
}

const std::vector<std::string>& Message::GetReservedNames() const {
  return reserved_names_;
}

const std::vector<std::size_t>& Message::GetReservedNumbers() const {
  return reserved_numbers_;
}

void Message::SetParentMessage(Message* message) noexcept {
  parent_message_ = message;
}

}  // namespace protobuf_parser