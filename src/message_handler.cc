#include "message_handler.h"

msgid message_handler::next_msg = 0;
msgid message_handler::msgid_add_child = message_handler::get_next_msgid();
msgid message_handler::msgid_remove_child = message_handler::get_next_msgid();

bool message_handler::has_parent() {
  return parent;
}


bool message_handler::send_message(msgid msg, void *param1, void *param2, 
                  void *param3, void *param4) {
  // try to handle message
  if (on_message(msg, param1, param2, param3, param4)) {
    return true;
  } else {
    // if parent - see if it can handle the message
    if (parent->send_message(msg, param1, param2, param3, param4)) {
      return true;
    }
  }
  return false;
}


bool message_handler::on_message(msgid msg, void *param1, void *param2, 
                                 void *param3, void *param4) {
  if (msg == message_handler::msgid_remove_child) {
    on_remove_child((message_handler*)param1);
    return true;
  } else if (msg == message_handler::msgid_add_child) {
    on_add_child((message_handler*)param1);
    return true;
  }
  return false;
}


void message_handler::on_add_child(message_handler *child) {}
void message_handler::on_remove_child(message_handler *child) {}
