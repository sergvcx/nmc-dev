import matplotlib.pyplot as plt
import numpy

img64 = plt.imread('./image_sources/marcie64.tif')
numpy.savetxt("./image_sources_txt/image64.txt", img64, fmt='%d')

img128 = plt.imread('./image_sources/marcie128.tif')
numpy.savetxt("./image_sources_txt/image128.txt", img128, fmt='%d')

img256 = plt.imread('./image_sources/marcie256.tif')
numpy.savetxt("./image_sources_txt/image256.txt", img256, fmt='%d')

figure, axis = plt.subplots(1, 3)
axis[0].imshow(img64, cmap='gray', vmin=0, vmax=255)
axis[1].imshow(img128, cmap='gray', vmin=0, vmax=255)
axis[2].imshow(img256, cmap='gray', vmin=0, vmax=255)
plt.show()
