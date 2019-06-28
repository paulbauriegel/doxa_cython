# setup.py
from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext
from distutils.sysconfig import customize_compiler

class my_build_ext(build_ext):
    def build_extensions(self):
        customize_compiler(self.compiler)
        try:
            # Workaround Cython gcc warning
            # https://stackoverflow.com/a/36293331
            # https://bugs.python.org/issue1222585
            self.compiler.compiler_so.remove("-Wstrict-prototypes")
            # Woraround Link errors using <filesystem> members in C++17
            # https://stackoverflow.com/a/48729403
            self.compiler.compiler_so +=["-std=c++17","-lstdc++fs"]
        except (AttributeError, ValueError) as e:
            print("########################################")
            print(e)
        build_ext.build_extensions(self)

setup(
    name='doxa_cython',
    ext_modules=[
        Extension("doxa", ["doxa/bin_cod_x.pyx", "doxa/bin_cod_x.cpp"], language="c++",)
    ],
    #cmdclass = {'build_ext': build_ext },
    cmdclass = {'build_ext': my_build_ext },
)