project('FireStorm', 'cpp', version : '0.3.0', license : 'MIT')

skm_dir = get_option('skm_dir')
sk_lib_dir = join_paths(skm_dir, 'lib/linux')
sk_gcc_include_dir = join_paths(skm_dir, 'g++/include')
sk_clang_include_dir = join_paths(skm_dir, 'clang++/include')

cc = meson.get_compiler('cpp')


# Assume Splashkit is in ~/.splashkit
lib_splashkitcpp = cc.find_library('SplashKitCPP', dirs : join_paths(skm_dir, 'g++/lib/linux'))
lib_splashkit = cc.find_library('SplashKit', dirs : sk_lib_dir)

inc = [include_directories('include'), include_directories(sk_gcc_include_dir)]
deps = [lib_splashkit, lib_splashkitcpp]


subdir('include')
subdir('src')

if get_option('build_examples')
  subdir('examples')
endif
