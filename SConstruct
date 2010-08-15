
env = Environment( tools=['mingw'] )

ccflags = ['-Wall', '-pedantic', '-Werror']

# debug
ccflags  = ccflags + ['-O0', '-g']

env.Append(CPPPATH=['C:/MinGW/include/SDL', './include']
	      ,CPPDEFINES={'_GNU_SOURCE':'1','REENTRANT':''}
		  ,LIBS=['mingw32','SDLmain','SDL','SDL_image','SDL_ttf','pthread']
		  ,LINKFLAGS=['-mwindows']
		  ,CCFLAGS=ccflags)
SOURCES = [
        # Base Components
        'src/canvas.cc',          \
        'src/color.cc',           \
        'src/picture.cc',         \
        'src/picture_set.cc',     \
        'src/point.cc',           \
        'src/rect.cc',            \
        'src/vector.cc',          \

        'src/message_handler.cc', \
        'src/timer.cc',           \

        # Application Components
        'src/application.cc',     \
        'src/main_canvas.cc',     \
        'src/event_handler.cc',   \

        # UI Components
        'src/ui/button.cc',       \
        'src/ui/control.cc',      \
        'src/ui/frame.cc',        \
        'src/ui/label.cc',        \
        'src/ui/text_ctrl.cc',    \

        # Game Components
        'src/game/animation.cc',  \
        'src/game/sprite.cc',     \
        'src/game/sprite_set.cc', \
        'src/game/sprite_manager.cc', \
		]
		
library = env.Library('projectg', SOURCES)
