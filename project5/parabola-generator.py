import math

class Point():
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, other):
        if isinstance(other, Point):
            return Point(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        if isinstance(other, Point):
            return Point(self.x - other.x, self.y - other.y)

    def __mul__(self, scalar):
        return Point(self.x * scalar, self.y * scalar)

    def __div__(self, scalar):
        return Point(self.x / scalar, self.y / scalar)

    def __str__(self):
        return str((self.x, self.y))

    def __repr__(self):
        return self.__str__()


class Line():
    def __init__(self, p1, p2):
        self.p1 = p1
        self.p2 = p2

    def __str__(self):
        return str((self.p1, self.p2))

    def __repr__(self):
        return self.__str__()


# def calcDiff(point1, point2):
#     return (point1[0] - point2[0], point1[1] - point2[1])

def saveSVG(size, lines):
    padding = 10
    offset = padding / 2

    with open('cube_parabola.svg', 'w') as outFile:
        outFile.write('''<svg version="1.1"
            baseProfile="full"
            width="''' + str(size + padding) + '''" height="''' + str(size + padding) + '''"
            xmlns="http://www.w3.org/2000/svg">
            ''')

        for line in lines:
            outFile.write('''
                <line
                    x1="''' + str(line.p1.x + offset) + '''" y1="''' + str(line.p1.y + offset) + '''" 
                    x2="''' + str(line.p2.x + offset) + '''" y2="''' + str(line.p2.y + offset) + '''" 
                    stroke="black" 
                    stroke-width="1"/>
                ''')

        outFile.write('</svg>')

def createSVG():
    pointsPerLine = 100
    xBound = 2000
    yBound = xBound

    edgeLength = xBound / 2
    yDiff = edgeLength / 2
    xDiff = math.sqrt(edgeLength ** 2 - yDiff ** 2)

    slope = math.tan(math.pi / 6)

    pointMid = Point(xBound / 2, yBound / 2)

    pointA = Point(pointMid.x + xDiff, yBound - (pointMid.y + yDiff))
    pointB = Point(pointMid.x + xDiff, yBound - (pointMid.y - yDiff))
    pointC = Point(pointMid.x,         yBound - (pointMid.y - edgeLength))
    pointD = Point(pointMid.x - xDiff, yBound - (pointMid.y - yDiff))
    pointE = Point(pointMid.x - xDiff, yBound - (pointMid.y + yDiff))
    pointF = Point(pointMid.x,         yBound - (pointMid.y + edgeLength))

    points = [pointMid, pointA, pointB, pointC, pointD, pointE, pointF]

    lines = [
        Line(pointA, pointB),
        Line(pointB, pointC),
        Line(pointC, pointD),
        Line(pointD, pointE),
        Line(pointE, pointF),
        Line(pointF, pointA),
        Line(pointMid, pointA),
        Line(pointMid, pointC),
        Line(pointMid, pointE)
    ]

    linePairs = [
        (Line(pointA, pointB),   Line(pointB, pointC)),
        (Line(pointC, pointD),   Line(pointD, pointE)),
        (Line(pointE, pointF),   Line(pointF, pointA)),

        (Line(pointA, pointMid), Line(pointMid, pointC)),
        (Line(pointC, pointMid), Line(pointMid, pointE)),
        (Line(pointE, pointMid), Line(pointMid, pointA)),

        (Line(pointMid, pointC), Line(pointC, pointD)),
        (Line(pointD, pointE), Line(pointE, pointMid)),

        (Line(pointMid, pointE), Line(pointE, pointF)),
        (Line(pointF, pointA), Line(pointA, pointMid)),

        (Line(pointMid, pointA), Line(pointA, pointB)),
        (Line(pointB, pointC), Line(pointC, pointMid))
    ]

    for pair in linePairs:
        # stepper = []

        # stepper.append((pair[0].p1 - pair[0].p2) / pointsPerLine)
        # stepper.append((pair[1].p1 - pair[1].p2) / pointsPerLine)

        # print pair
        # print stepper

        for i in xrange(pointsPerLine):
            lines.append(
                Line(
                    pair[0].p1 - ((pair[0].p1 - pair[0].p2) * i / pointsPerLine),
                    pair[1].p1 - ((pair[1].p1 - pair[1].p2) * i / pointsPerLine)
                )
            )


    saveSVG(xBound, lines)


createSVG()