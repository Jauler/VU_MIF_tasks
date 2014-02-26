from scipy import misc
import numpy as np
import matplotlib.pyplot as plt
import Image

#Open the image
img = Image.open('test0.jpg')
img = img.convert('L')
img = np.asarray(img);
img.flags.writeable = True


def calcPixelValue(pix, x, y):
	poses = [(-1,-1),
		(-1,0),
		(-1,1),
		(0,1),
		(1, 1),
		(1,0),
		(1,-1),
		(0,-1)]
	index = 0;
	num = 0;
	for p in poses:
		if pix[x][y] > pix[x + p[0]][y + p[1]]:
			num = num + (1 << index)
		index = index + 1;

	return num

def calcAllPixels(cell):
	res = np.zeros(cell.shape)
	for coord, y in np.ndenumerate(cell):
			if coord[0] == 0 or coord[0] == cell.shape[0] - 1:
				continue
			if coord[1] == 0 or coord[1] == cell.shape[1] - 1:
				continue

			res[coord[0]][coord[1]] = calcPixelValue(cell, coord[0], coord[1])
	return res


tst = calcAllPixels(img)




#plt.imshow(img, cmap=plt.cm.gray, interpolation='nearest')
plt.imshow(tst, cmap=plt.cm.gray, interpolation='nearest')
plt.show()
