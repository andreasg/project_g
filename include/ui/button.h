
#ifndef PG_UI_BUTTON_H
#define PG_UI_BUTTON_H

#include <string>
#include <cstdio>


#include "color.h"
#include "ui/control.h"


/** Button.
 * A button is clickable interface-comonent.
 * When a button is clicked a button_clicked message
 * is sent to it's parent. */
class button : public control {
public:
  button(control *parent, std::string text, rect dimensions, int id=0,
         color fg_col=control::default_fg_color, color bg_col=control::default_bg_color);
  virtual ~button();

  /** Set the text that is rendered onto the button. 
   * @param t the new button-text. */
  void set_text(std::string t);

  /** Draw the button. */
  virtual void on_draw();

  /** Focus on the button. */
  virtual bool on_lbutton_down(int x, int y);
  
  /** If coord within button - it will send button_clicked message. */
  virtual bool on_lbutton_up(int x, int y);

  /** If key is return, a button_click message is dispatched. */
  virtual bool on_key_down(SDLKey k, SDLMod m, Uint16 unicode);

  /** Message.
   * Send when the button is clicked. Params (in order) are:
   *    -# id
   *    -# this
   *    -# parent
   *    -# NULL
   */
  static msgid msgid_button_click;

private:
  canvas *text_canvas;
  std::string text;
  color fg_color;
  color bg_color;
};

#endif 
