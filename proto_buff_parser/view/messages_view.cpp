#include "messages_view.hpp"

namespace proto_buff_parser {
namespace view {

MessagesView::MessagesView(const container::ProtoBuffContainer& proto_buff_container,
                           const Message& message)
    : proto_buff_container_(proto_buff_container), message_(message) {
  // TODO: need to create containers with right data
}

iterator::MessagesIterator& MessagesView::GetMessagesIterator() {
  return messages_container_->GetIterator();
}

}  // namespace view
}  // namespace proto_buff_parser