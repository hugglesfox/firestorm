src = [
  '../test.cpp',
  'test_form.cpp'
]

test_form = executable('test_form', src, link_with : firestorm, dependencies : deps, include_directories : test_inc)

test('test_form', test_form)
