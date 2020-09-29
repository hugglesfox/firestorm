test_inc = include_directories('include')
test_inc = [inc, test_inc]

subdir('cookie')
subdir('form')
subdir('headers')
subdir('html')
subdir('response')
subdir('router')
subdir('static_file')
subdir('utils')

src = [
  'test.cpp',
  'test_firestorm.cpp'
]

test_firestorm = executable('test_firestorm', src, link_with : firestorm, dependencies : deps, include_directories : test_inc)
test('test_firestorm', test_firestorm)

