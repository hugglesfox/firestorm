project('FireStorm', 'cpp', version : '0.3.1', license : 'MIT')

skm_dir = get_option('skm_dir')
sk_lib_dir = join_paths(skm_dir, 'lib/linux')
sk_gcc_include_dir = join_paths(skm_dir, 'g++/include')
sk_clang_include_dir = join_paths(skm_dir, 'clang++/include')

cc = meson.get_compiler('cpp')

lib_splashkitcpp = cc.find_library('SplashKitCPP', dirs : join_paths(skm_dir, 'g++/lib/linux'))
lib_splashkit = cc.find_library('SplashKit', dirs : sk_lib_dir)

include = [
  'include',
  sk_gcc_include_dir
]

deps = [lib_splashkit, lib_splashkitcpp]
inc = include_directories(include)

subdir('include')
subdir('src')
subdir('test')

if get_option('build_examples')
  subdir('examples')
endif
