from matplotlib.image import imread
import sys
import numpy
numpy.set_printoptions(threshold=sys.maxsize)

img128 = imread('./marcie128.tif')
# print(img128)
numpy.savetxt("./image128.txt", img128, fmt='%d', delimiter=',', newline=',\n')

img256 = imread('./marcie256.tif')
# print(img256)
numpy.savetxt("./image256.txt", img256, fmt='%d', delimiter=',', newline=',\n')