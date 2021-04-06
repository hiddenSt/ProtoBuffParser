#ifndef PROTOBUFPARSER_PROTOBUF_PARSER_FIELD_TYPE_HPP_
#define PROTOBUFPARSER_PROTOBUF_PARSER_FIELD_TYPE_HPP_

#include <string>

namespace protobuf_parser {

class FieldType {
 public:
  virtual const std::string& GetTypeName() const = 0;
  virtual ~FieldType() = default;
};

}  // namespace protobuf_parser

#endif  // PROTOBUFPARSER_PROTOBUF_PARSER_FIELD_TYPE_HPP_
