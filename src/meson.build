cc = meson.get_compiler('cpp')

lib_splashkitcpp = cc.find_library('SplashKitCPP', dirs : ['~/.splashkit/g++/lib/linux'])
lib_splashkit = cc.find_library('SplashKit', dirs : ['~/.splashkit/source'])

src = [
  'cookie.cpp',
  'error.cpp',
  'firestorm.cpp',
  'form.cpp',
  'headers.cpp',
  'html.cpp',
  'logging.cpp',
  'middleware.cpp',
  'outcome.cpp',
  'response.cpp',
  'route.cpp',
  'router.cpp',
  'static_file.cpp',
  'utils.cpp'
]

deps = [lib_splashkit, lib_splashkitcpp]

firestorm = library('FireStorm', src, dependencies : deps, include_directories : inc)
