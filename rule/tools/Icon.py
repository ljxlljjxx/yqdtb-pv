import turtle as t
from typing import Self

screen = t.Screen()
screen.setup(width=800, height=800)  # 图标尺寸
screen.bgcolor("white")

sqrt2 = 1.41421

class Point:
    drawer: t.Turtle
    def __init__(self, x: float = 0, y: float = 0) -> None:
        self.x = x
        self.y = y
    
    def __getitem__(self, index):
        if index == 0:
            return self.x
        elif index == 1:
            return self.y
        else:
            raise IndexError()
        
    def __str__(self) -> str:
        return str(tuple(self))
    
    def __truediv__(self, B: Self | int) -> Self:
        if B == 0:
            return self
        return Point(self.x, B.y)
    
    def __rshift__(self, B: Self) -> Self:
        pen = Point.drawer
        pen.up()
        pen.goto(self)
        pen.down()
        pen.goto(B)
        return B
    
    def semicircle(self, r):
        pen = Point.drawer
        pen.up()
        pen.goto(self)
        pen.setheading(0)
        pen.down()
        pen.circle(r, -180, r * 360)
        pen.up()

    def circle(self, r, color: str = 'red'):
        pen = Point.drawer
        pen.up()
        pen.goto(self.x, self.y - r)
        pen.setheading(0)
        pen.down()
        pen.circle(r, 360, r * 360)
        pen.up()


Point.drawer = drawer = t.Turtle()
drawer.speed(0)  # 最快绘制速度
drawer.hideturtle()  # 隐藏画笔光标
drawer.pensize(2)  # 基础线条宽度
drawer.color("black")
    
def line_segment(A: Point, B: Point):
    A >> B

def rectangle(A: Point, B: Point):
    A >> A / B >> B >> B / A >> A

rectangle(Point(-120, 250), Point(-40, -200))
rectangle(Point(+120, 250), Point(+40, -200))

(Point(-40, -200) >> Point(-40, -280) >> Point(-120, -280)).semicircle(40)
(Point(120, -200) >> Point(120, -280) >> Point(40  , -280)).semicircle(40)
# pen.up()

Point(-80, 80).circle(30)
Point(-80 + 15 * sqrt2, 80 + 15 * sqrt2) >> Point(-200 + 30 * sqrt2, 200)
Point(-80 - 15 * sqrt2, 80 - 15 * sqrt2) >> Point(-200, 200 - 30 * sqrt2)

Point(80, 80).circle(30)
Point(80 + 15 * sqrt2, 80 + 15 * sqrt2) >> Point(-40 + 30 * sqrt2, 200)
Point(80 - 15 * sqrt2, 80 - 15 * sqrt2) >> Point(-40, 200 - 30 * sqrt2)

leftup, rightdown = Point(-250, 300), Point(250, -300)
leftup >> leftup / rightdown >> rightdown >> rightdown / leftup >> leftup

t.done()
