# setup.py
import os
import pkg_resources

from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext
from distutils.sysconfig import customize_compiler
from Cython.Build.Dependencies import cythonize

data_dir = pkg_resources.resource_filename("autowrap", "data_files")
include_dir = os.path.join(data_dir, "autowrap")

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

        #https://groups.google.com/forum/#!topic/cython-users/y6y36Eiu7DE
        #Extension("doxa", sources=["doxa/bin_cod_x.cpp"], language="c++", 
        #            include_dirs = [include_dir, data_dir, '/usr/local/include', '/home/paul/PycharmProjects/doxa_cython/doxa', '/home/paul/PycharmProjects/doxa_cython/include'],
        #            library_dirs=['.'],
        #            extra_link_args=["-lm","-lc++abi", "-lstdc++fs", "-lstdc++", "-Wl,-rpath=$ORIGIN/."],) #"-Wl,--no-undefined"
setup(
    name='doxa_cython',
    ext_modules=cythonize([
                Extension("doxa", sources=["bin.pyx"], language="c++", 
                    extra_link_args=["-lm","-lc++abi", "-lstdc++fs", "-lstdc++"],)
    ]),
    #cmdclass = {'build_ext': build_ext },
    cmdclass = {'build_ext': my_build_ext },
)