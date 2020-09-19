project('FireStorm', 'cpp')

cc = meson.get_compiler('cpp')

lib_splashkitcpp = cc.find_library('SplashKitCPP', dirs : ['~/.splashkit/g++/lib/linux'])
lib_splashkit = cc.find_library('SplashKit', dirs : ['~/.splashkit/source'])
inc_splashkit = include_directories('include/splashkit')

src = [
  'src/cookie.cpp',
  'src/error.cpp',
  'src/firestorm.cpp',
  'src/form.cpp',
  'src/headers.cpp',
  'src/html.cpp',
  'src/logging.cpp',
  'src/middleware.cpp',
  'src/outcome.cpp',
  'src/response.cpp',
  'src/route.cpp',
  'src/router.cpp',
  'src/static_file.cpp',
  'src/utils.cpp'
]

library('FireStorm', src, dependencies : [lib_splashkit, lib_splashkitcpp], include_directories : inc_splashkit)
