import Image
import matplotlib.pyplot as plt
import numpy as np
import math

#Open image file
img = Image.open('test0.jpg')
img = img.convert('L')
img = np.asarray(img)
img.flags.writeable = True


def calcXYVectors(img):
	Gx = np.zeros(img.shape)
	Gy = np.zeros(img.shape)
	imgDup = img.copy()
	for c, tmp in np.ndenumerate(img):
		if c[0] - 1 >= 0:
			Gx[c[0]][c[1]] = Gx[c[0]][c[1]] - img[c[0]-1][c[1]]
		if c[0] + 1 < img.shape[0]:
			Gx[c[0]][c[1]] = Gx[c[0]][c[1]] + img[c[0]+1][c[1]]

		if c[1] - 1 >= 0:
			Gy[c[0]][c[1]] = Gy[c[0]][c[1]] - img[c[0]][c[1]-1]
		if c[1] + 1 < img.shape[1]:
			Gy[c[0]][c[1]] = Gy[c[0]][c[1]] + img[c[0]][c[1]+1]

		imgDup[c[0]][c[1]] = Gx[c[0]][c[1]] + Gy[c[0]][c[1]]
	return (Gx, Gy, imgDup)


def doHist(img, Gx, Gy, x, y):
	poses = [[x, y] for y in range(0, 3) for x in range(0, 3)]
	vect = np.zeros(10)
	for i in poses:
		if(x + i[0] >= img.shape[0]):
			continue
		if(x + i[1] >= img.shape[1]):
			continue

		#get degrees for direction and all positive values
		deg = 180 +  math.degrees(math.atan2(Gy[x+i[0]][y+i[1]], Gx[x+i[0]][y+i[1]]))
		#find a bin for our degrees value
		for tmp in range(1, 11):
			if deg < tmp * 36:
				break;
		vect[tmp - 1] = vect[tmp - 1] + Gx[x+i[0]][y+i[1]] + Gy[x+i[0]][y+i[1]]
	return vect

def calcHists(img, Gx, Gy):
	hists = []
	for x in range(0, img.shape[0]/3):
		hists.append([])
		for y in range(0, img.shape[1]/3):
			hists[x].append(doHist(img, Gx, Gy, x*3, y*3))
	return hists

def normaliseHist(hist):
	e = 0.1
	for i in range(0, len(hist)):
		hist[i] = hist[i] * (hist[i]/np.linalg.norm(np.array(hist)) + e)

	return hist


def normaliseHists(hists):
	myHists = []
	for hist in hists:
		myHists.append(normaliseHist(hist))

	return myHists

print img.shape
G = calcXYVectors(img)
hists = np.array(calcHists(img, G[0], G[1]))
print hists


plt.imshow(img, cmap=plt.cm.gray, interpolation='nearest')
plt.show()
