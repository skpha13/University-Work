import numpy as np
import matplotlib.pyplot as plt
import sklearn.metrics
from sklearn.naive_bayes import MultinomialNB

train_images = np.loadtxt('data/train_images.txt')
train_labels = np.loadtxt('data/train_labels.txt', 'int')
test_images = np.loadtxt('data/test_images.txt')
test_labels = np.loadtxt('data/test_labels.txt', 'int')

num_bins = 8
bins = np.linspace(start=0, stop=256, num=num_bins)
def values_to_bins(matrix, capete_interval):
    return np.subtract(np.digitize(matrix, capete_interval), 1)

train_images_binned = values_to_bins(train_images, bins)
test_images_binned = values_to_bins(test_images, bins)

naive_bayes_model = MultinomialNB()
naive_bayes_model.fit(train_images_binned, train_labels)

predictions = naive_bayes_model.predict(test_images_binned)
misclassed = (predictions != test_labels)
confusion_matrix = np.zeros((10, 10))

for index in range(len(predictions)):
    confusion_matrix[predictions[index]][test_labels[index]] += 1

def print_ten_images():
    count = 10
    for imgIndex in range(len(misclassed)):
        if misclassed[imgIndex]:
            image = train_images[imgIndex, :]
            image = np.reshape(image, (28,28))
            plt.imshow(image.astype(np.uint8), cmap='gray')
            plt.show()
            count -= 1

        if count == 0:
            break

scikit_confusion_matrix = sklearn.metrics.confusion_matrix(test_labels, predictions)
print(scikit_confusion_matrix)

# print(confusion_matrix)
print(naive_bayes_model.score(test_images_binned, test_labels))