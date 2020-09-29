src = [
  '../test.cpp',
  'test_headers.cpp'
]

test_headers = executable('test_headers', src, link_with : firestorm, dependencies : deps, include_directories : test_inc)

test('test_headers', test_headers)
