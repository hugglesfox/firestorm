src = [
  'test_string_splitting.cpp',
  'test_utils.cpp'
]

test_utils = executable('test_utils', src, link_with : firestorm, dependencies : deps, include_directories : test_inc)

test('test_utils', test_utils)
