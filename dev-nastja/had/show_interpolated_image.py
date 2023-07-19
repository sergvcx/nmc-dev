import matplotlib.pyplot as plt
import numpy

interpolated_image = numpy.loadtxt("./interpolated_image.txt", dtype=int)
# plt.imshow(interpolated_image, cmap='gray', vmin=0, vmax=255)
plt.imshow(interpolated_image)
plt.show()