from bin_cod cimport Binarize

def transform(source, method, output):
    bin_ptr = new Binarize()
    try:
        bin_ptr.transform(source, method, output)
    finally:
        del bin_ptr  # delete heap allocated object