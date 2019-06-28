import bin_cod
from PIL import Image
im = Image.open("test/2JohnC1V3.ppm")
new_img = bin_cod.transform(im, 2)
new_img.show()