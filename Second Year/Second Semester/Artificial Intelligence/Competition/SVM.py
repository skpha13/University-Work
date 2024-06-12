import numpy as np
import skimage as ski
from sklearn.utils import shuffle
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score
from sklearn.metrics import confusion_matrix
from sklearn.metrics import ConfusionMatrixDisplay

new_image_size = (1, 1)

train_images = []
train_labels = []

base_path = "/kaggle/input/realistic-image-classification"

################# LOAD TRAIN DATA #################
filename = open(f"{base_path}/train.csv")
filename.readline()

row = filename.readline()
while row:
    image_path, label = row.split(",")
    # read image, resize it to 1x1 and make it numpy array
    image = np.asarray(ski.transform.resize(ski.io.imread(f"{base_path}/train/{image_path}.png"), new_image_size, anti_aliasing=True))

    train_images.append(image)
    train_labels.append(int(label))

    row = filename.readline()

shapes = [arr.shape for arr in train_images]
unique_shapes = set(shapes)
print(unique_shapes)

# Fix black images with shape 80 x 80 x 1
for index, arr in enumerate(train_images):
    if arr.shape != (new_image_size[0], new_image_size[1], 3):
        train_images[index] = np.stack((train_images[index],) * 3, axis=-1)
        print(f"Array at index {index} has shape {arr.shape}")

train_images = np.array(train_images) / 255.0


train_labels = np.array(train_labels)
print(train_images.shape)
print()
###################################################

################# LOAD VALIDATION DATA #################
validation_images = []
validation_labels = []

filename = open(f"{base_path}/validation.csv")
filename.readline()

row = filename.readline()
while row:
    image_path, label = row.split(",")
    image = np.asarray(ski.transform.resize(ski.io.imread(f"{base_path}/validation/{image_path}.png"), new_image_size, anti_aliasing=True))

    validation_images.append(image)
    validation_labels.append(int(label))

    row = filename.readline()


shapes = [arr.shape for arr in validation_images]
unique_shapes = set(shapes)
print(unique_shapes)

for index, arr in enumerate(validation_images):
    if arr.shape != (new_image_size[0], new_image_size[1], 3):
        validation_images[index] = np.stack((validation_images[index],) * 3, axis=-1)
        print(f"Array at index {index} has shape {arr.shape}")


validation_images = np.array(validation_images) / 255.0
validation_labels = np.array(validation_labels)
print(validation_images.shape)
########################################################

################# LOAD TEST DATA #################
test_images = []
test_images_ids = []

filename = open(f"{base_path}/test.csv")
filename.readline()

row = filename.readline()
while row:
    image_path = row.strip()
    image = np.asarray(ski.transform.resize(ski.io.imread(f"{base_path}/test/{image_path}.png"), new_image_size, anti_aliasing=True))

    test_images_ids.append(image_path)
    test_images.append(image)

    row = filename.readline()


shapes = [arr.shape for arr in test_images]
unique_shapes = set(shapes)
print(unique_shapes)

for index, arr in enumerate(test_images):
    if arr.shape != (new_image_size[0], new_image_size[1], 3):
        test_images[index] = np.stack((test_images[index],) * 3, axis=-1)
        print(f"Array at index {index} has shape {arr.shape}")


test_images = np.array(test_images) / 255.0
print(test_images.shape)
##################################################

################# CREATE FULL DATASET #################
train_validation_images = np.concatenate((train_images, validation_images))
train_validation_labels = np.concatenate((train_labels, validation_labels))
#######################################################

################# SHUFFLE DATA #################
train_images, train_labels = shuffle(train_images, train_labels)
validation_images, validation_labels = shuffle(validation_images, validation_labels)
################################################

def submit(model):
    predictions = model.predict(test_images)

    with open("submission.csv", "w") as out:
        out.write("image_id,label\n")
        for index in range(len(test_images)):
            out.write(f"{test_images_ids[index]},{predictions[index]}\n")

################# DATA FLATTENING #################
# for the SVC to work it expects a matrix, we need to
# flatten our images to an array of size 3
train_images = train_images.reshape(10500, -1)
validation_images = validation_images.reshape(3000, -1)
test_images = test_images.reshape(4500, -1)
train_validation_images = train_validation_images.reshape(13500, -1)

print(train_images.shape)
print(validation_images.shape)
print(test_images.shape)
print(train_validation_images.shape)
###################################################

################# MODEL #################
model = SVC()
model.fit(train_images, train_labels)
predictions = model.predict(validation_images)
accuracy = accuracy_score(validation_labels, predictions)
print(f"Accuracy: {accuracy}")

cm = confusion_matrix(validation_labels, predictions)
plot = ConfusionMatrixDisplay(cm)
plot.plot()

model.fit(train_validation_images, train_validation_labels)
submit(model)
#########################################