import cv2

#print(cv2.__version__)

imagen = cv2.imread('Fantasma-windows.jpg',cv2.IMREAD_COLOR)


#(medida izquierda) (medida derecha) (color) (grosor de linea)
cv2.rectangle(imagen,(384,0),(510,128),(0,0,255),10)

#Second flag:
#cv2.IMREAD_COLOR : Loads a color image. Any transparency of image will be neglected. It is the default flag.
#cv2.IMREAD_GRAYSCALE : Loads image in grayscale mode
#cv2.IMREAD_UNCHANGED : Loads image as such including alpha channel

cv2.namedWindow('Fantasmin', cv2.WINDOW_NORMAL)
cv2.imshow('Fantasmin',imagen)

K = cv2.waitKey(0) & 0xFF

if : k = 27
	cv2.destroyAllWindows()
