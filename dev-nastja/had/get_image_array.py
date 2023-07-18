import matplotlib.pyplot as plt
import sys
import numpy
numpy.set_printoptions(threshold=sys.maxsize)

img64 = plt.imread('./marcie64.tif')
# print(img64)
numpy.savetxt("./image64.txt", img64, fmt='%d', delimiter=',', newline=',\n')

img128 = plt.imread('./marcie128.tif')
# print(img128)
numpy.savetxt("./image128.txt", img128, fmt='%d', delimiter=',', newline=',\n')

img256 = plt.imread('./marcie256.tif')
# print(img256)
numpy.savetxt("./image256.txt", img256, fmt='%d', delimiter=',', newline=',\n')

figure, axis = plt.subplots(1, 3)
axis[0].imshow(img64, cmap='gray', vmin=0, vmax=255)
axis[1].imshow(img128, cmap='gray', vmin=0, vmax=255)
axis[2].imshow(img256, cmap='gray', vmin=0, vmax=255)
plt.show()

interpolated_image = numpy.loadtxt("./interpolated_image.txt", dtype=int)
plt.imshow(interpolated_image, cmap='gray', vmin=0, vmax=255)
plt.show()