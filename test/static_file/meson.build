src = [
  'test_file_type.cpp',
  'test_static_file.cpp'
]

test_static_file = executable('test_static_file', src, link_with : firestorm, dependencies : deps, include_directories : test_inc)

test('test_static_file', test_static_file)
