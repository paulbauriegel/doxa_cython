# cython: language_level=3, boundscheck=False
from bin_cod cimport transform as transform_
import tempfile
from PIL import Image

def transform(img, m):
    result_image = None
    with tempfile.NamedTemporaryFile(suffix='.ppm') as tf_input:
        img.save(tf_input.name, "PPM")
        with tempfile.NamedTemporaryFile(suffix='.ppm') as tf_output:
            transform_(tf_input.name.encode('ascii'), m, tf_output.name.encode('ascii'))
            result_image = Image.open(tf_output.name)
    if not result_image:
        raise RuntimeError("Image encoding problem")
    return result_image
