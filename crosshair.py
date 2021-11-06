import math
from PyQt5 import QtCore, QtGui, QtWidgets
from crosshair_exceptions import DistanceIsTooLong, WinSizeMustBeEven


class Crosshair(QtWidgets.QWidget):
    def __init__(self,
                 parent=None,
                 window_size=24,
                 stroke_width=2,
                 rgba: tuple = (0, 255, 0, 255),
                 distance: int = 4):
        # Init super class
        QtWidgets.QWidget.__init__(self, parent)

        # Assertions
        assert distance <= window_size / 2 - 1, DistanceIsTooLong
        assert window_size % 2 == 0, WinSizeMustBeEven

        self.ws = window_size
        self.resize(window_size + 1, window_size + 1)
        self.distance = distance
        # Assign the pen color and stroke size
        self.pen = QtGui.QPen(QtGui.QColor(*rgba))
        self.pen.setWidth(stroke_width)

        # Set windows features
        # Transparent, on top, and frameless
        self.setWindowFlags(
            QtCore.Qt.FramelessWindowHint |
            QtCore.Qt.WindowStaysOnTopHint |
            QtCore.Qt.WindowTransparentForInput |
            QtCore.Qt.Tool)

        # Set transparent bg attribute
        self.setAttribute(QtCore.Qt.WA_TranslucentBackground)

        self.center()

    def exit(self):
        self.close()

    def center(self):
        """ Move the crosshair to the center of the screen"""
        win_ = QtWidgets.QApplication.desktop().screen().rect().center() - self.rect().center() + QtCore.QPoint(1, 1)
        self.move(win_)

    def paintEvent(self, event):
        """ Override the paintEvent method """
        # Distance from the center
        # (higher the number the closer it is from the center)
        painter = QtGui.QPainter(self)
        painter.setPen(self.pen)

        # Half screen size
        half_s = int(self.ws / 2)
        m_const = 1
        dist = self.distance + math.ceil(self.pen.width() / 2)

        # Drawing the crosshair
        painter.drawLine(half_s, 0, half_s, half_s - dist)  # Top
        painter.drawLine(half_s, half_s + dist, half_s, self.ws - m_const)  # Bottom
        painter.drawLine(0, half_s, half_s - dist, half_s)  # Left
        painter.drawLine(half_s + dist, half_s, self.ws - m_const, half_s)  # Right
