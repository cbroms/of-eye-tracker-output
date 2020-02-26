from PIL import Image

from resizeimage import resizeimage

from os import listdir
from os.path import isfile, join

path = "C:\\Users\\Christian Broms\\Documents\\NarrativeMaker\\NarrativeMaker\\bin\\data\\output\\"

outputPath = "C:\\Users\\Christian Broms\\Documents\\NarrativeMaker\\NarrativeMaker\\bin\\data\\outputResized\\"

files = [f for f in listdir(path) if isfile(join(path, f))]

for file in files:
    with open(path + file, 'r+b') as f:
        with Image.open(f) as image:
            cover = resizeimage.resize_cover(image, [1000, 600], validate=False)
            newPath = outputPath + file
            cover.save(newPath, image.format)
            print("resized " + file)