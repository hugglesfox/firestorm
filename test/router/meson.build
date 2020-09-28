src = [
  '../test.cpp',
  'test_router.cpp'
]

test_router = executable('test_router', src, link_with : firestorm, dependencies : deps, include_directories : test_inc)

test('test_router', test_router)
