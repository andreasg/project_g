
#include "application.h"

application *application::app = NULL;
bool application::running = true;

msgid application::msgid_exit_application = message_handler::get_next_msgid();

application::application() : message_handler(NULL) {
  application::set_application(this);
}


application::~application() {}


void application::set_application(application *a) {
  if (application::app) {
    fprintf(stderr, "application::set_application(): already inited");
    exit(1);
  } else {
    application::app = a;
  }
}


bool application::on_init(int argc, char **argv) {
  return true;
  //
}

void application::on_event(SDL_Event *e) {}

void application::on_idle() {}

void application::on_exit() {}

int application::exec(int argc, char **argv) {
  if (application::app == NULL) {
    fprintf(stderr, "application::exec(): app not instanced yet.");
    exit(1);
  }

  if (application::app->on_init(argc, argv) == false) {
    exit(1);
  }

  // main-loop
  SDL_Event e;
  application::running = true;
  while(application::running) {
    if (SDL_PollEvent(&e) == 0) {
      if (e.type == SDL_QUIT) {
        break;
      }
      application::app->on_idle();
    } else {
      application::app->on_event(&e);
    }
  }
  
  application::app->on_exit();
  return 0;
}


bool application::on_message(msgid msg, void *param1, void *param2, void *param3, void *param4) {
  if (msg == application::msgid_exit_application) {
    application::running = false;
    return true;
  }
  return message_handler::on_message(msg, param1, param2, param3, param4);;
}
