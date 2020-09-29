src = [
  '../test.cpp',
  'test_response.cpp'
]

test_response = executable('test_response', src, link_with : firestorm, dependencies : deps, include_directories : test_inc)

test('test_response', test_response)
