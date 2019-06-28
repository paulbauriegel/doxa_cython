#cython: c_string_encoding=ascii  # for cython>=0.19
#cython: embedsignature=False
#cython: language_level=3
from  libcpp.string  cimport string as libcpp_string
from  libcpp.string  cimport string as libcpp_utf8_string
from  libcpp.string  cimport string as libcpp_utf8_output_string
from  libcpp.set     cimport set as libcpp_set
from  libcpp.vector  cimport vector as libcpp_vector
from  libcpp.pair    cimport pair as libcpp_pair
from  libcpp.map     cimport map  as libcpp_map
from  libcpp cimport bool
from  libc.string cimport const_char
from cython.operator cimport dereference as deref, preincrement as inc, address as address
from  AutowrapRefHolder cimport AutowrapRefHolder
from  AutowrapPtrHolder cimport AutowrapPtrHolder
from  AutowrapConstPtrHolder cimport AutowrapConstPtrHolder
from  smart_ptr cimport shared_ptr
from bin_cod cimport BinarizeMethod as _BinarizeMethod
from bin_cod cimport Binarize as _Binarize

cdef extern from "autowrap_tools.hpp":
    char * _cast_const_away(char *) 

cdef class Binarize:
    """
    Cython implementation of _Binarize
    """

    cdef shared_ptr[_Binarize] inst

    def __dealloc__(self):
         self.inst.reset()

    
    def __init__(self):
        """Cython signature: void Binarize()"""
        self.inst = shared_ptr[_Binarize](new _Binarize())
    
    def transform(self, bytes source , int m , bytes output ):
        """Cython signature: void transform(libcpp_string source, BinarizeMethod m, libcpp_string output)"""
        assert isinstance(source, bytes), 'arg source wrong type'
        assert m in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 'arg m wrong type'
        assert isinstance(output, bytes), 'arg output wrong type'
    
    
    
        self.inst.get().transform((<libcpp_string>source), (<_BinarizeMethod>m), (<libcpp_string>output)) 

cdef class BinarizeMethod:
    otsu = 0
    bernsen = 1
    niblack = 2
    sauvola = 3
    wolf = 4
    nick = 5
    gatos = 6
    su = 7
    trsingh = 8
    wan = 9
    isauvola = 10 
