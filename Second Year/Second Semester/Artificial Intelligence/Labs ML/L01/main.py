import numpy as np
from skimage import io

images = np.array([np.load(f"images/car_{x}.npy") for x in range(0,9)])
sum_of_each_image = [np.sum(x) for x in images]
print("C: ")
print(*sum_of_each_image)

print("B: ")
print(np.sum(sum_of_each_image))

print("D: ")
print(np.argmax(sum_of_each_image))

print("F: ")
standard_deviation = np.std(images)
print(standard_deviation)

mean_image = np.mean(images, axis=0)
io.imshow(mean_image.astype(np.uint8))
io.show()

normalized_images = np.divide(np.subtract(images, mean_image), standard_deviation).astype(np.uint8)
io.imshow(normalized_images[0])
io.show()

cropped_images = [img[200:300, 280:400] for img in images]
io.imshow(cropped_images[0])
io.show()

# flipped_images = [np.flip(np.flip(img, axis=0), axis=1) for img in images]
# print(images.shape)
flipped_images = np.flip(images, axis=(1,2))
io.imshow(flipped_images[0])
io.show()

