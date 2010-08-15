#ifndef PG_MESSAGEHANDLER_H
#define PG_MESSAGEHANDLER_H

#include <SDL.h>

/** messages */
typedef unsigned int msgid;


/**
 * Basic functionality for passing messages between classes.
 */
class message_handler {
public:

  /** Default constructor.
   * @param p the parent.
   */
  message_handler(message_handler *p) {parent = p;}

  /** Defualt destructor. */
  virtual ~message_handler() {}

  /** @return true if the instace have a parent, else false. */
  bool has_parent();

  /** @return the parent. */
  message_handler *get_parent();

  /** @param p the (new) parent. */
  void set_parent(message_handler *p) {parent = p;}

  /** Send a message to parent.
   * @param msg the msgid
   * @param param1-4 pointer to our message-data.
   * @return true if parent took care of our message, else false.
   */
  bool send_message(msgid msg, void *param1=NULL, void *param2=NULL, 
                    void *param3=NULL, void *param4=NULL);

  /** Handle a message, if we can't, send it to the parent.
   * @param msg the msgid
   * @param param1-4 pointer to our message-data.
   * @return true if we took care of the msg, else false.
   */
  virtual bool on_message(msgid msg, void  *param1, void *param2, 
                          void *param3, void *param4);

  /** Get the next available message id. 
   * @return A new message id.
   */
  static msgid get_next_msgid() {return message_handler::next_msg++;}

  /** Message.
   * Send this to add a child to our parent. 
   * use param1=child to add. */
  static msgid msgid_add_child;

  /** Message.
   * Send this to remove a child from our parent.
   * use param1=child to remove. */
  static msgid msgid_remove_child;

  /** Add a child.
   * @param child child to add.
   */
  virtual void on_add_child(message_handler *child);

  /** Remove a child.
   * @param child child to remove.
   */
  virtual void on_remove_child(message_handler *child);

private:
  message_handler *parent;
  static msgid next_msg;
};



#endif
