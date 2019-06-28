from setuptools import setup, Extension
from Cython.Build import cythonize

VERSION = '0.0.1'

threefry_ext = cythonize(Extension("*",
                                   sources=["doxa/threefry.pyx",
                                            "doxa/_threefry.c"],
                                   extra_compile_args=['-std=c99'],
                                   ),
                         include_path=["threefry"],
                         )

with open('threefry/version.py', 'w') as version_f:
    version_f.write(
        "__version__ = '{__version__}'".format(__version__=VERSION)
    )


setup(name='doxa_cython',
      version=VERSION,
      description='Threefry random number generator',
      author='Paul Bauriegel',
      author_email='paul.bauriegel@web.de',
      url='',
      license='BSD',
      packages=['doxa'],
      ext_modules=threefry_ext,
      setup_requires=['cython'],
      package_data={'doxa': ['__init__.pxd',
                                 'doxa.pxd', 'Rectangle.h']},
      )
