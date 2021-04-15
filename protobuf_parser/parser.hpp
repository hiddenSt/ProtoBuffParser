#ifndef PROTOBUF_PARSER_PROTOBUF_PARSER_PARSER_HPP_
#define PROTOBUF_PARSER_PROTOBUF_PARSER_PARSER_HPP_

#include <string>
#include <filesystem>
#include <set>
#include <exception>

#include <protobuf_parser/storage.hpp>
#include <protobuf_parser/view/view.hpp>
#include <google/protobuf/compiler/importer.h>

#include <protobuf_parser/stub_multiple_error_collector.hpp>

namespace protobuf_parser {

template <typename Serializer>
class Parser {
 public:
  Parser() = default;
  ~Parser() = default;
  explicit Parser(const std::filesystem::path& root_path);

  std::string SerializeDirectory(const std::filesystem::path& relative_to_root_directory_path);
  std::string SerializePackage(const std::string& package_name);

 private:
  std::string GetPathRelativeToRootDirectory(const std::string& full_path);

  google::protobuf::compiler::DiskSourceTree disk_source_tree_;
  StubMultipleErrorCollector error_collector_;
  std::filesystem::path root_path_;
  Serializer serializer_;
  Storage storage_;
};

template <typename Serializer>
Parser<Serializer>::Parser(const std::filesystem::path& root_path)
    : root_path_(root_path) {
  // Add empty string argument as virtual_path parameter to indicate DiskSourceTree to map
  // root_path_ as a root
  // (https://developers.google.com/protocol-buffers/docs/reference/cpp/google.protobuf.compiler.importer#DiskSourceTree.MapPath.details)
  disk_source_tree_.MapPath(std::string{}, root_path_.string());
  google::protobuf::compiler::Importer importer{&disk_source_tree_, &error_collector_};
  std::filesystem::recursive_directory_iterator recursive_directory_iterator{root_path_};

  std::set<std::string> directories_names;
  std::set<std::string> packages_names;
  std::set<std::string> files_names;

  for (auto& dir_entry : recursive_directory_iterator) {
    if (dir_entry.is_regular_file() && dir_entry.path().extension() == ".proto") {
      std::string relative_to_root_file_path =
          GetPathRelativeToRootDirectory(dir_entry.path().string());
      auto* file_descriptor = importer.Import(relative_to_root_file_path);
      directories_names.insert(
          GetPathRelativeToRootDirectory(dir_entry.path().parent_path().string()));
      packages_names.insert(file_descriptor->package());
      files_names.insert(relative_to_root_file_path);
    }
  }

  storage_.StoreDescriptorPool(importer.pool(), files_names, directories_names, packages_names);
}

template <typename Serializer>
std::string Parser<Serializer>::SerializeDirectory(
    const std::filesystem::path& relative_to_root_directory_path) {
  auto* directory = storage_.FindDirectory(relative_to_root_directory_path.string());
  if (directory == nullptr) {
    throw std::runtime_error{"No such directory"};
  }
  view::View<Directory, Serializer> directory_view{directory, storage_, serializer_};
  return directory_view.Serialize();
}

template <typename Serializer>
std::string Parser<Serializer>::SerializePackage(const std::string& package_name) {
  auto* package = storage_.FindPackage(package_name);
  if (package == nullptr) {
    throw std::runtime_error{"No such package"};
  }
  view::View<Package, Serializer> package_view{package, storage_, serializer_};
  return package_view.Serialize();
}

template <typename Serializer>
std::string Parser<Serializer>::GetPathRelativeToRootDirectory(
    const std::string& full_path) {
  std::string changed_path{};
  std::size_t i = 0;
  std::string root_path = root_path_.string();
  while (full_path[i] == root_path[i]) {
    ++i;
  }
  ++i;
  for (std::size_t j = i; j < full_path.size(); ++j) {
    changed_path += full_path[j];
  }
  return changed_path;
}

}  // namespace protobuf_parser

#endif  // PROTOBUF_PARSER_PROTOBUF_PARSER_PARSER_HPP_