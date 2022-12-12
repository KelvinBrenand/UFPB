import os
from PIL import Image

folder_dir = "D:\\Documents\\UFPB\\projetoPDI\\data\\train\\benign\\"
count = 0
for image in os.listdir(folder_dir):
    path = folder_dir+image
    old_im = Image.open(path)
    old_size = old_im.size
    new_size = (400, 400)
    new_im = Image.new("RGB", new_size)
    box = tuple((n - o) // 2 for n, o in zip(new_size, old_size))
    new_im.paste(old_im, box)
    new_im.save(f'D:\\data\\train\\benign\\{count}.jpg')
    count +=1