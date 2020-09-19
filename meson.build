project('FireStorm', 'cpp')

cc = meson.get_compiler('cpp')

lib_splashkitcpp = cc.find_library('SplashKitCPP', dirs : ['~/.splashkit/g++/lib/linux'])
lib_splashkit = cc.find_library('SplashKit', dirs : ['~/.splashkit/source'])

inc = [include_directories('include'), include_directories('include/splashkit')]
deps = [lib_splashkit, lib_splashkitcpp]

subdir('src')
subdir('examples')
