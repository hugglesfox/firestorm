project('FireStorm', 'cpp', version : '0.3.0', license : 'MIT')

cc = meson.get_compiler('cpp')

# Assume Splashkit is in ~/.splashkit
lib_splashkitcpp = cc.find_library('SplashKitCPP', dirs : ['~/.splashkit/g++/lib/linux'])
lib_splashkit = cc.find_library('SplashKit', dirs : ['~/.splashkit/source'])

inc = [include_directories('include'), include_directories('include/splashkit')]
deps = [lib_splashkit, lib_splashkitcpp]


subdir('include')
subdir('src')

if get_option('build_examples')
  subdir('examples')
endif
