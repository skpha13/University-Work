import numpy as np
import matplotlib.pyplot as plt
import skimage as ski
import tensorflow as tf
from sklearn.utils import shuffle
from sklearn.metrics import accuracy_score
from sklearn.metrics import confusion_matrix
from sklearn.metrics import ConfusionMatrixDisplay

print(tf.__version__)

train_images = []
train_labels = []

# base path of the input folder
base_path = "/kaggle/input/realistic-image-classification"

################# LOAD TRAIN DATA #################
filename = open(f"{base_path}/train.csv")
filename.readline()

row = filename.readline()
while row:
    image_path, label = row.split(",")
    # read images and transform them to numpy array
    image = np.asarray(ski.io.imread(f"{base_path}/train/{image_path}.png"))

    train_images.append(image)
    train_labels.append(int(label))

    row = filename.readline()

# Checked for images which didn't have the same shape
shapes = [arr.shape for arr in train_images]
unique_shapes = set(shapes)
print(unique_shapes)

# Turns out black images had shape 80 x 80 x 1
# because those didn't have all 3 color channels = RGB
# so I fixed every black image by copying the single value 3 times
for index, arr in enumerate(train_images):
    if arr.shape != (80, 80, 3):
        train_images[index] = np.stack((train_images[index],) * 3, axis=-1)
        print(f"Array at index {index} has shape {arr.shape}")

# normalized the values by dividing each pixel with 255
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
    image = np.asarray(ski.io.imread(f"{base_path}/validation/{image_path}.png"))

    validation_images.append(image)
    validation_labels.append(int(label))

    row = filename.readline()


shapes = [arr.shape for arr in validation_images]
unique_shapes = set(shapes)
print(unique_shapes)

for index, arr in enumerate(validation_images):
    if arr.shape != (80, 80, 3):
        validation_images[index] = np.stack((validation_images[index],) * 3, axis=-1)
        print(f"Array at index {index} has shape {arr.shape}")

validation_images = np.array(validation_images) / 255.0
validation_labels = np.array(validation_labels)
print(validation_images.shape)
ski.io.imshow(validation_images[604])
########################################################

################# LOAD TEST DATA #################
test_images = []
test_images_ids = []

filename = open(f"{base_path}/test.csv")
filename.readline()

row = filename.readline()
while row:
    image_path = row.strip()
    image = np.asarray(ski.io.imread(f"{base_path}/test/{image_path}.png"))

    test_images_ids.append(image_path)
    test_images.append(image)

    row = filename.readline()


shapes = [arr.shape for arr in test_images]
unique_shapes = set(shapes)
print(unique_shapes)

for index, arr in enumerate(test_images):
    if arr.shape != (80, 80, 3):
        test_images[index] = np.stack((test_images[index],) * 3, axis=-1)
        print(f"Array at index {index} has shape {arr.shape}")


test_images = np.array(test_images) / 255.0
print(test_images.shape)
##################################################

################# SHUFFLE DATA #################
train_images, train_labels = shuffle(train_images, train_labels)
validation_images, validation_labels = shuffle(validation_images, validation_labels)
################################################

################# CREATE FULL DATASET #################
train_validation_images = np.concatenate((train_images, validation_images))
train_validation_labels = np.concatenate((train_labels, validation_labels))
print(train_validation_images.shape)
#######################################################

################# MODEL #################
model = tf.keras.Sequential()

model.add(tf.keras.layers.Conv2D(128, kernel_size=(3,3), padding='same', activation='relu6', input_shape=(80, 80, 3)))
model.add(tf.keras.layers.BatchNormalization())
model.add(tf.keras.layers.MaxPooling2D())

model.add(tf.keras.layers.Conv2D(256, kernel_size=(3,3), padding='same', activation='relu6'))
model.add(tf.keras.layers.BatchNormalization())
model.add(tf.keras.layers.MaxPooling2D())

model.add(tf.keras.layers.Conv2D(256, kernel_size=(3,3), padding='same', activation='relu6'))
model.add(tf.keras.layers.BatchNormalization())
model.add(tf.keras.layers.MaxPooling2D())

model.add(tf.keras.layers.Flatten())

model.add(tf.keras.layers.Dropout(0.8))
model.add(tf.keras.layers.Dense(256, activation='relu', kernel_regularizer=tf.keras.regularizers.L1(0.005)))
model.add(tf.keras.layers.BatchNormalization())

model.add(tf.keras.layers.Dropout(0.2))
model.add(tf.keras.layers.Dense(3, activation='softmax'))

model.compile(optimizer=tf.keras.optimizers.Adam(learning_rate=0.0001),
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])
#########################################

# created 2 callbacks one for use on the training data, and one for the train and validation data
# the only difference is the monitor, because on train and validation data there is no validation loss
reduce_lr_val = tf.keras.callbacks.ReduceLROnPlateau(monitor='val_loss', factor=0.2, patience=5, min_lr=1e-7)
reduce_lr_test = tf.keras.callbacks.ReduceLROnPlateau(monitor='loss', factor=0.2, patience=5, min_lr=1e-7)

################# VALIDATION PERFORMANCE #################
history = model.fit(train_images,
                    train_labels,
                    batch_size=16,
                    callbacks=[reduce_lr_val],
                    epochs=100)

# evaluate model and print loss/accuracy on validation data
result = model.evaluate(validation_images, validation_labels)
loss = result[0]
accuracy = result[1]
print(f"Loss: {loss}\nAccuracy: {accuracy}")

# create confusion matrix and plot it

# here our predictions come in vectors of size 3 where
# v[i] is probability that the image belongs to label i
predictions = model.predict(validation_images)
pred = np.argmax(predictions, axis=1)
cm = confusion_matrix(validation_labels, pred)
plot = ConfusionMatrixDisplay(cm)
plot.plot()
plt.show()
##########################################################

################# SUBMIT #################
model.fit(train_validation_images,
          train_validation_labels,
          batch_size=16,
          callbacks=[reduce_lr_test],
          epochs=100)

predictions = model.predict(test_images)
predictions = np.argmax(predictions, axis=1)

with open("submission14.csv", "w") as out:
    out.write("image_id,label\n")
    for index in range(len(test_images)):
        out.write(f"{test_images_ids[index]},{predictions[index]}\n")
##########################################