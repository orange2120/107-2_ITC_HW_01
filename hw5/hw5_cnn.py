import numpy as np
import os
os.environ['KERAS_BACKEND'] = 'tensorflow'
import sys
import csv
from reader import load_fashion_mnist

from keras.callbacks import ModelCheckpoint, EarlyStopping
from keras.models import Sequential, load_model
from keras.layers import Dense, Dropout, Activation
from keras.layers import Conv2D, MaxPooling2D, Flatten
from keras.optimizers import SGD, Adam
from keras.utils import np_utils
from keras.layers.normalization import BatchNormalization

num_classes = 10
img_size = 28 # mnist size = 28*28
channel = 1

data_dir = sys.argv[1]
output_file = sys.argv[2]


def load_data():
    # load fashion mnist data
    x_train, y_train = load_fashion_mnist(data_dir, kind='train')
    x_test, _ = load_fashion_mnist(data_dir, kind='t10k')

    # preprocess data, let pixel between 0~1
    x_train = x_train.astype('float32')/255
    x_train = np.reshape(x_train, (-1, img_size, img_size, channel))
    y_train = np_utils.to_categorical(y_train, num_classes)

    x_test = x_test.astype('float32')/255
    x_test = np.reshape(x_test, (-1, img_size, img_size, channel))

    print(x_train.shape, x_test.shape)
    return x_train, y_train, x_test

if __name__ == '__main__':
    x_train, y_train, x_test = load_data()

    # build model
    model = Sequential()
    
    # Do not modify code before this line
    # TODO: build your network.
    
    # Convolution layer 1
    model.add(Conv2D(filters=32, kernel_size=(3,3),
        padding='same', input_shape=(28, 28, 1),
        activation='relu'))
    model.add(BatchNormalization())
    
    model.add(Conv2D(filters=64, kernel_size=(3,3),
        padding='same', activation='relu'))
    model.add(BatchNormalization())
    model.add(MaxPooling2D(pool_size=(2, 2)))
    
    # Convolution layer 2
    model.add(Conv2D(filters=64, kernel_size=(3,3),
        padding='same', activation='relu'))
    model.add(BatchNormalization())
    
    model.add(Conv2D(filters=128, kernel_size=(3,3),
        padding='same', activation='relu'))
    model.add(BatchNormalization())
    model.add(MaxPooling2D(pool_size=(2, 2)))

    model.add(Dropout(0.5))
   
    # Flatten layer
    model.add(Flatten())
    model.add(Dense(512, input_dim=784, activation='relu'))
    #model.add(BatchNormalization())
    model.add(Dropout(0.5))
    # Hidden layer 1 
    model.add(Dense(512, activation='relu'))
    #model.add(BatchNormalization())
    model.add(Dropout(0.5))
    # Output layer
    model.add(Dense(10, activation='softmax'))
    
    checkpoint = ModelCheckpoint('best_cnn.h5', monitor = 'val_acc', verbose = 1, save_best_only = True, mode = 'max')
    opt = Adam(lr=5e-4)
    model.compile(loss='categorical_crossentropy', optimizer=opt, metrics=['accuracy'])
    model.fit(x_train, y_train, epochs=30, batch_size=128, validation_split=0.1, verbose=1, callbacks = [checkpoint])
    model = load_model('best_cnn.h5')
    
    # Do not modify code after this line
    # output model
    model.summary()
    
    # output train score and test file
    score = model.evaluate(x_train, y_train)
    print('\nTrain Acc:', score[1])
    y_pred = model.predict(x_test)
    result = np.argmax(y_pred, 1)

    f = open(output_file, 'w')
    writer = csv.writer(f)
    writer.writerow(['id', 'label'])
    for i in range(x_test.shape[0]):
        writer.writerow([str(i), int(result[i])])
    f.close()
