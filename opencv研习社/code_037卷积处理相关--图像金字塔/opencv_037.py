import cv2 as cv


def pyramid_down(pyramid_images):
    level = len(pyramid_images)
    print("level = ",level)
    for i in range(level-1, -1, -1):
        expand = cv.pyrUp(pyramid_images[i])
        cv.imshow("pyramid_down_"+str(i), expand)


def pyramid_up(image, level=3):
    temp = image.copy()
    # cv.imshow("input", image)
    pyramid_images = []
    for i in range(level):
        dst = cv.pyrDown(temp)
        pyramid_images.append(dst)
        # cv.imshow("pyramid_up_" + str(i), dst)
        temp = dst.copy()
    return pyramid_images


src = cv.imread("D:/images/master.jpg")
cv.namedWindow("input", cv.WINDOW_AUTOSIZE)
cv.imshow("input", src)
# pyramid_up(src)
pyramid_down(pyramid_up(src))

cv.waitKey(0)
cv.destroyAllWindows()
