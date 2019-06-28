# Cython Wrapper for Doxa

A quick and dirty cython wrapper for the Doxa Binarization Framework.

## Installation

```bash
git clone https://github.com/brandonmpetty/Doxa.git
git clone https://github.com/paulbauriegel/doxa_cython.git
cd doxa_cython
CPPFLAGS=-I$PWD/../Doxa/Doxa python3 setup.py build_ext --inplace
```

## Usage

```python
import bin_cod
from PIL import Image
im = Image.open("test/2JohnC1V3.ppm")
new_img = bin_cod.transform(im, 2)
new_img.show()
```
