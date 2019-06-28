# setup.py
from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext
from distutils.sysconfig import customize_compiler
from Cython.Build.Dependencies import cythonize


class my_build_ext(build_ext):
    def build_extensions(self):
        customize_compiler(self.compiler)
        
        # Workaround Cython gcc warning
        # https://stackoverflow.com/a/36293331
         # https://bugs.python.org/issue1222585
        try:
            self.compiler.compiler_so.remove("-Wstrict-prototypes")
        except (AttributeError, ValueError) as e:
            pass
       
        # Woraround Link errors using <filesystem> members in C++17
        # https://stackoverflow.com/a/48729403
        self.compiler.compiler_so +=["-std=c++17", "-lstdc++fs"]
        build_ext.build_extensions(self)

setup(
    name='doxa_cython',
    ext_modules=cythonize([
                Extension("bin_cod", sources=['bin_cod.pyx'], language="c++", 
                    extra_link_args=["-lm","-lc++abi", "-lstdc++fs", "-lstdc++"],)
    ]),
    cmdclass = {'build_ext': my_build_ext },
)