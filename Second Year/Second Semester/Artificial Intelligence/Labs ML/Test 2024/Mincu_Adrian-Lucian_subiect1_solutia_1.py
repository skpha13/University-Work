from sklearn.neural_network import MLPClassifier
import numpy as np
from sklearn.preprocessing import MinMaxScaler
from sklearn.metrics import accuracy_score
from sklearn.utils import shuffle
from sklearn.model_selection import train_test_split

trainX = []
trainY = []
testX = []
testX_files = []

# DATA LOADING

with open("./train.txt") as train_file:
    # get rid of first row
    line = train_file.readline()
    line = train_file.readline()

    while line:
        file, label = line.strip().split(",")

        trainY.append(int(label))
        temp_arr = []

        with open(f"./{file}") as f:
            line_file = f.readline()

            while line_file:
                arr = np.asarray([np.float32(x) for x in  line_file.strip().split(",")])

                if arr.shape != (3,):
                    print(arr.shape)

                temp_arr.append(arr)
                line_file = f.readline()

        # Some files didnt come with the same size so i duplicated the last array
        # until they all had the same size
        while len(temp_arr) != 154:
            temp_arr.append(temp_arr[-1])

        trainX.append(temp_arr)
        line = train_file.readline()

with open("./test.txt") as test_file:
    # get rid of first row
    line = test_file.readline().strip()
    line = test_file.readline().strip()
    while line:
        file = line
        temp_arr = []
        testX_files.append(file)

        with open(f"./{file}") as f:
            line_file = f.readline()

            while line_file:
                arr = np.asarray([np.float32(x) for x in  line_file.strip().split(",")])

                temp_arr.append(arr)
                line_file = f.readline()

        # Some files didnt come with the same size so i duplicated the last array
        # until they all had the same size
        while len(temp_arr) != 154:
            temp_arr.append(temp_arr[-1])

        testX.append(temp_arr)
        line = test_file.readline().strip()

sizes = []
for it in trainX:
    sizes.append(len(it))

print(max(sizes))

trainX = np.array(trainX)
trainY = np.array(trainY)
testX = np.array(testX)

print(trainX.shape)
print(trainY.shape)
print(testX.shape)


## DATA PROCESSING

scaler = MinMaxScaler()
trainX_flattened = np.array([x.flatten() for x in trainX])
testX_flattened = np.array([x.flatten() for x in testX])

print(trainX_flattened.shape)
print(testX_flattened.shape)

trainX_preproccesed = scaler.fit_transform(trainX_flattened)
testX_preproccesed = scaler.transform(testX_flattened)

print(trainX_preproccesed[0][:3])

## DATA PREPARATION

X_train_prep, X_test_prep = shuffle(trainX_preproccesed, trainY)

X_train, X_test, y_train, y_test = train_test_split(X_train_prep, X_test_prep, test_size=0.25)

## MLP CLASSIFIER ON TRAIN TEST SPLIT

mlp = MLPClassifier(activation='relu')
mlp.fit(X_train, y_train)
predictions = mlp.predict(X_test)
accuracy = accuracy_score(y_test, predictions)
print(accuracy)

## MLP CLASSIFIER ON FULL TRAIN WITH OUTPUT PREDICTIONS

mlp.fit(X_train_prep, X_test_prep)
test_predictions = mlp.predict(testX_preproccesed)
print(test_predictions[:10])

## OUTPUT TO FILE

print(len(test_predictions))
print(len(testX_files))
with open(f"./output/Mincu_Adrian-Lucian_232_subiect1_solutia_1.txt", "w") as g:
    g.write(f"filename,label\n")
    for i in range(len(test_predictions)):
        g.write(f"{testX_files[i]},{test_predictions[i]}\n")