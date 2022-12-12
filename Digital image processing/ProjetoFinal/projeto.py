import numpy as np
import os
import tensorflow as tf
from PIL import Image

IMG_HEIGHT = 400
IMG_WIDTH = 400
train_folder=r'D:\Documents\UFPB\projetoPDI\data\train'
test_folder=r'D:\Documents\UFPB\projetoPDI\data\test'

def create_dataset_PIL(img_folder):
    img_data_array=[]
    class_name=[]
    for dir1 in os.listdir(img_folder):
        for file in os.listdir(os.path.join(img_folder, dir1)):
            image_path= os.path.join(img_folder, dir1,  file)
            image= np.array(Image.open(image_path))
            image= np.resize(image,(IMG_HEIGHT,IMG_WIDTH,3))
            image = image.astype('float32')
            image /= 255  
            img_data_array.append(image)
            class_name.append(dir1)
    return img_data_array , class_name

PIL_img_data1, class_name1=create_dataset_PIL(train_folder)
target_dict={k: v for v, k in enumerate(np.unique(class_name1))}
target_val1=[target_dict[class_name1[i]] for i in range(len(class_name1))]

PIL_img_data2, class_name2=create_dataset_PIL(test_folder)
target_dict={k: v for v, k in enumerate(np.unique(class_name2))}
target_val2=[target_dict[class_name2[i]] for i in range(len(class_name2))]


model=tf.keras.Sequential(
        [
            tf.keras.layers.InputLayer(input_shape=(IMG_HEIGHT,IMG_WIDTH, 3)),
            tf.keras.layers.Conv2D(filters=32, kernel_size=3, strides=(2, 2), activation='relu'),
            tf.keras.layers.MaxPooling2D(pool_size=(2, 2), strides=(2, 2),padding="valid"),
            tf.keras.layers.Conv2D(filters=64, kernel_size=3, strides=(2, 2), activation='relu'),
            tf.keras.layers.Flatten(),
            tf.keras.layers.Dense(64, activation='relu'),
            tf.keras.layers.Dense(32, activation='relu'),
            tf.keras.layers.Dense(2, activation='softmax')
        ])

model.summary()
model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])

history = model.fit(x=np.array(PIL_img_data1, np.float32), y=np.array(list(map(int,target_val1)), np.float32), epochs=5)
test_loss, test_acc = model.evaluate(np.array(PIL_img_data2, np.float32), np.array(list(map(int,target_val2)), np.float32), verbose=2)