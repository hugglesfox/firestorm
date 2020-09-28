src = [
  '../test.cpp',
  'test_html.cpp'
]

test_html = executable('test_html', src, link_with : firestorm, dependencies : deps, include_directories : test_inc)

test('test_html', test_html)
