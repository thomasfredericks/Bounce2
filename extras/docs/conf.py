import sys
import os
import shlex
import subprocess

read_the_docs_build = os.environ.get('READTHEDOCS', None) == 'True'

if read_the_docs_build:
    subprocess.call('doxygen', shell=True)

extensions = ['breathe']
breathe_projects = { 'Bounce2': 'xml' }
breathe_default_project = "Bounce2"
templates_path = ['_templates']
source_suffix = '.rst'
master_doc = 'index'
project = u'Bounce2'
copyright = u'2015, Bounce2'
author = u'Bounce2'
version = '1.0'
release = '1.0'
language = None
exclude_patterns = ['_build']
pygments_style = 'sphinx'
todo_include_todos = False
html_static_path = ['_static']
htmlhelp_basename = 'Bounce2doc'
latex_elements = {
}
latex_documents = [
  (master_doc, 'Bounce2.tex', u'Bounce2 Documentation',
   u'Bounce2', 'manual'),
]
