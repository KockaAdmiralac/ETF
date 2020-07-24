#!/usr/bin/env python
import html
import os
import pathspec
import sys
import urllib.parse

if len(sys.argv) < 2:
    print('Prvi argument komandne linije mora biti direktorijum')
    exit(1)

def format(filename):
    return '<li><a href="{0}">{1}</a></li>'.format(urllib.parse.quote(filename), html.escape(filename))

spec = None
with open('.gitignore') as gitignore:
    spec = pathspec.PathSpec.from_lines('gitwildmatch', gitignore)

def is_excluded(path):
    return spec.match_file(path) or path.endswith('index.html')

with open('_site/template.html') as template_file:
    template = ''.join(template_file.readlines())
    for (dirpath, dirnames, filenames) in os.walk(sys.argv[1]):
        with open(f'{dirpath}/index.html', 'w', encoding='utf-8') as index_file:
            index_file.write(
                template.format(
                    dirname=dirpath,
                    listing='\n'.join(
                        [format(f'{d}/') for d in dirnames if not is_excluded(f'{dirpath}/{d}')] +
                        [format(f) for f in filenames if not is_excluded(f'{dirpath}/{f}')]
                    )
                )
            )
