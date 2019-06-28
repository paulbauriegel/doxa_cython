# cython: language_level=3, boundscheck=False
from libcpp.string cimport string

cdef extern from "bin_cod.hpp" namespace "binarize": 
    cdef enum BinarizeMethod:
        otsu 
        bernsen 
        niblack 
        sauvola 
        wolf 
        nick 
        gatos 
        su 
        trsingh 
        wan 
        isauvola
    cdef void transform(string source, BinarizeMethod m, string output) except +