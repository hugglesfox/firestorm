src = [
  '../test.cpp',
  'test_cookie.cpp'
]

test_cookie = executable('test_cookie', src, link_with : firestorm, dependencies : deps, include_directories : test_inc)

test('test_cookie', test_cookie)
