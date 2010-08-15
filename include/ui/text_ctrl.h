
#ifndef PG_UI_TEXT_CTRL_H
#define PG_UI_TEXT_CTRL_H


#include <string>

#include "timer.h"


#include "ui/control.h"

#include <iostream>


/** Text Control.
 * A text control is a small box into which we can enter some text, 
 * which we then can send to a parent control for parsing. */
class text_ctrl : public control {
public:
  text_ctrl(control *parent, rect dimensions, int id=0);
  virtual ~text_ctrl() {if(text_canvas) delete text_canvas;}

  /** Draw the text control. */
  virtual void on_draw();

  /** Called when clicked - will grab keyboard focus. */
  virtual bool on_lbutton_down(int x, int y);

  /** Called on keypress. */
  virtual bool on_key_down(SDLKey k, SDLMod m, Uint16 unicode);

  /** Get the text within the text control. */
  std::string get_text() {return text;}

  /** Message.
   * Sent when the return key is pressed. Params (in order) are:
   *    -# id
   *    -# text
   *    -# NULL
   *    -# NULL
   */
  static msgid msgid_text_ctrl_text;

private:

  /** Carret Timer.
   * A simple timer used by text_ctrl for blinking the 
   * carret. 
   * @see text_ctrl */
  class carret_timer : public timer {
  public: 
    carret_timer() {blink = false;}
    virtual void on_timer() {blink = !blink;}
  
    /** incicate if blinking or not */
    bool blink;
  };

  /** global timer used to control the carret blinking. */
  static carret_timer *blinker;

  /** Canvas that the text is rendered to. */
  canvas *text_canvas;
  std::string text;
};



#endif 
