from matplotlib.image import imread
import sys
import numpy
numpy.set_printoptions(threshold=sys.maxsize)

img64 = imread('./marcie64.tif')
# print(img64)
numpy.savetxt("./image64.txt", img64, fmt='%d', delimiter=',', newline=',\n')

img128 = imread('./marcie128.tif')
# print(img128)
numpy.savetxt("./image128.txt", img128, fmt='%d', delimiter=',', newline=',\n')

img256 = imread('./marcie256.tif')
# print(img256)
numpy.savetxt("./image256.txt", img256, fmt='%d', delimiter=',', newline=',\n')