from scipy import misc
import numpy as np
import matplotlib.pyplot as plt
import Image

#Open the image
img = Image.open('test0.jpg')
img = img.convert('L')
img = np.asarray(img);
img.flags.writeable = True


def calcPixel(pix, x, y):
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
		if x+p[0] < 0 or x+p[0] >= pix.shape[0]:
			continue
		if y+p[1] < 0 or y+p[1] >= pix.shape[1]:
			continue

		if pix[x][y] > pix[x + p[0]][y + p[1]]:
			num = num + (1 << index)
		index = index + 1;

	return num

def calcPixels(cell):
	res = np.zeros(cell.shape)
	for coord, y in np.ndenumerate(cell):
			res[coord[0]][coord[1]] = calcPixel(cell, coord[0], coord[1])
	return res

def calcHist(pix, posx, posy):
	hist = np.zeros((256))
	for x in range(0, 15):
		for y in range(0, 15):
			hist[pix[posx + x][posy + y]] = hist[pix[posx + x][posy + y]] + 1
	return hist

def calcHists(vals):
	histsVect = []
	for coord, y in np.ndenumerate(vals):
		if coord[0] + 15 >= vals.shape[0]:
			continue
		if coord[1] + 15 >= vals.shape[1]:
			continue

		histsVect = [histsVect, calcHist(vals, coord[0], coord[1])]
	return histsVect

myVals = calcPixels(img)
print calcHists(myVals)




#plt.imshow(img, cmap=plt.cm.gray, interpolation='nearest')
plt.imshow(myVals, cmap=plt.cm.gray, interpolation='nearest')
plt.show()
