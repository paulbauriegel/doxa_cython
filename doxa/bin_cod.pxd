cdef extern from "bin_cod.hpp":
    cdef cppclass BinCod:
        int i_
        BinCod(int i)
        BinCod(BinCod & i)
        int add(BinCod o)
