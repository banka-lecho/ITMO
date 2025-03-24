#!/usr/bin/python
# -*- coding: UTF-8 -*-

import matplotlib.pyplot as plt
import math
import time
import pylab


def dFdx(x, y):
    return (2 * x * (y ** 2) * math.log(x ** 2 + 5 * y ** 2)) + (2 * x ** 3 * y ** 2 / (x ** 2 + 5 * y ** 2))


def dFdy(x, y):
    return (2 * (x ** 2) * y * math.log(x ** 2 + 5 * y ** 2)) + (10 * x ** 2 * y ** 3 / (x ** 2 + 5 * y ** 2))


def gradient(x, y):
    return dFdx(x, y), dFdy(x, y)


def funcZ(x, y):
    return x ** 2 * y ** 2 * math.log(x ** 2 + 5 * y ** 2)


def nextPoint(x, y, aK):
    gx, gy = gradient(x, y)
    return x - aK * gx, y - aK * gy


def checking_of_epsila(result, nextresult, epsila):
    return abs(result - nextresult) < epsila


def checking_of_delta(x, y, nextX, nextY, delta):
    return abs(nextX - x) ** 2 + abs(nextY - y) ** 2 < delta


def changeA(a):
    if parametrA == "const":
        return a
    elif parametrA == "progression":
        return a * q
    elif parametrA == "linear":
        return a - d


def findExtremum(epsila, delta, startX, startY, aK, parametrA, criteria):
    p = (startX, startY)
    result = funcZ(*p)
    fig, ax = plt.subplots()
    ax.grid()
    ax.scatter(*p)
    ind = 0
    startTime = time.time()
    while True:
        ind += 1
        nextP = nextPoint(*p, aK)
        nextresult = funcZ(*nextP)
        ax.scatter(*nextP)
        if criteria == "epsila" and checking_of_epsila(result, nextresult, epsila):
            break
        if criteria == "delta" and checking_of_delta(*p, *nextP, delta):
            break
        if time.time() - startTime > 10:
            break
        aK = changeA(aK)
        p = nextP
        result = nextresult

    pylab.text(0.55, 0.95, u'Criteria = ' + str(criteria), family="monospace", size="small", weight="roman")
    pylab.text(0.55, 0.90, u'Number of iterations = ' + str(ind), family="monospace", size="small", weight="roman")
    pylab.text(0.55, 0.85, u'Time = ' + str(time.time() - startTime), family="monospace", size="small", weight="roman")
    pylab.text(0.55, 0.80, u'The found point = ' + str(p), family="monospace", size="small", weight="roman")
    pylab.text(0.55, 0.75, u'Value = ' + str(result), family="monospace", size="small", weight="roman")

    plt.show()


criteria = "delta"
parametrA = "progression"
epsila = 10 ** -5
delta = 10 ** -6
startX, startY = 1, 1
aK = 75 * 10 ** -3
d = 10 ** -7
q = 0.999

findExtremum(epsila, delta, startX, startY, aK, parametrA, criteria)
