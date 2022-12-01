import matplotlib.pyplot as plt
import numpy as np
import time


deltaArray = [0.1, 0.01, 0.001]
R = 2
analyticAns = 16 / 3


def f(x, y, dx, dy):
    return (x**2 + y**2) * dx + x * y * dy


def getAngle(delta):
    return 2 * np.arcsin(delta / (2 * R))


def getChord(alpha):
    return 2 * R * np.sin(alpha / 2)


def drawSemiCircle():   # рисую полуокружность
    x = np.linspace(-2, 2, 100)
    y = lambda x: np.sqrt(4 - x**2)
    plt.axes().set_aspect('equal')
    plt.plot(x, y(x), color="blue")
    plt.plot(x, [0]*100, color="blue")


def getCoords(alpha, delta):    # считаю координаты ломаной
    startCoord = (-2, 0)
    curveX = [startCoord[0]]
    curveY = [startCoord[1]]
    curAlpha = alpha
    alphas = [alpha]
    while curAlpha < np.pi:
        phi = (np.pi - curAlpha) / 2
        c = getChord(curAlpha)
        xStep = c * np.cos(phi)
        yStep = c * np.sin(phi)
        newX = startCoord[0] + xStep
        newY = startCoord[1] + yStep
        curAlpha += alpha
        curveX.append(newX)
        curveY.append(newY)
        alphas.append(curAlpha)
    startX = 2
    lineX = []
    lineY = []
    while startX >= -2:
        lineX.append(startX)
        lineY.append(0)
        startX -= delta

    drawLine(curveX, curveY)
    drawLine(lineX, lineY)

    startTime = time.time()

    ans2D = 0
    ans1D = 0
    for i in range(1, len(curveX)):
        ans2D += f(curveX[i], curveY[i], curveX[i] - curveX[i - 1], curveY[i] - curveY[i - 1])
    for i in range(1, len(lineX)):
        ans2D += f(lineX[i], lineY[i], lineX[i] - lineX[i - 1], lineY[i] - lineY[i - 1])

    dl = alpha * R
    for i in range(len(curveX)):
        l = alphas[i] * R
        ans1D += (4 * np.sin(np.pi - l / 2) - 4 * np.cos(np.pi - l / 2)**2 * np.sin(np.pi - l / 2)) * dl
    dl = delta
    for i in range(len(lineX)):
        l = 2 - lineX[i]
        ans1D += -(2 - l)**2 * dl
    print("Интегральная сумма по ломаной:")
    print("КИ-2: sum = ", ans2D, ", отклонение = ", abs(analyticAns - ans2D), sep="")
    print("КИ-1: sum = ", ans1D, ", отклонение = ", abs(analyticAns - ans1D), sep="")
    print("Время работы:", time.time() - startTime, "\n")


def drawLine(x, y):
    plt.plot(x, y, color="orange")


def checkIfInside(x, y):
    return x**2 + y**2 <= R**2


def getGridCoords(delta):
    x = []
    startX = -2
    while startX <= 2:
        x.append(startX)
        startX += delta
    y = []
    startY = 0
    while startY <= 2:
        y.append(startY)
        startY += delta
    # drawGrid(x, y)

    startTime = time.time()
    ans = 0
    ansMin = 0
    ansMax = 0
    for i in x:
        for j in y:
            center = (i + delta / 2, j + delta / 2)
            if checkIfInside(*center):
                ans += center[1] * delta**2
            leftUp = (i, j + delta)
            rightUp = (i + delta, j + delta)
            if checkIfInside(*leftUp) and checkIfInside(*rightUp):
                ansMin += center[1] * delta**2
            leftLow = (i, j)
            rightLow = (i + delta, j)
            if checkIfInside(*leftLow) or checkIfInside(*rightLow):
                ansMax += center[1] * delta**2
    print("Интегральная сумма по сетке:")
    print("Центры содержатся в D: sum = ", ans, ", отклонение = ", abs(analyticAns - ans), sep="")
    print("Квадрат полностью в D: sum = ", ansMin, ", отклонение = ", abs(analyticAns - ansMin), sep="")
    print("Квадрат частично в D: sum = ", ansMax, ", отклонение = ", abs(analyticAns - ansMax), sep="")
    print("Время работы:", time.time() - startTime, "\n")


def drawGrid(x, y):
    for elem in x:
        plt.plot([elem, elem], [0, 2], color="green", linewidth=0.5, linestyle="--")
    for elem in y:
        plt.plot([-2, 2], [elem, elem], color="green", linewidth=0.5, linestyle="--")


def main():
    drawSemiCircle()
    for delta in deltaArray:
        print("delta =", delta)
        getCoords(getAngle(delta), delta)
        getGridCoords(delta)
    plt.show()


if __name__ == '__main__':
    main()
