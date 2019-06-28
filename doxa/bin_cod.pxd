from libcpp.string cimport string as libcpp_string

cdef extern from "Binarize.hpp":   
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
    cdef cppclass BinCod:
        BinCod() except +
        void transform(libcpp_string source, BinarizeMethod m, libcpp_string output)