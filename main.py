import sys

import keyboard
from PyQt5 import QtWidgets

from crosshair import Crosshair

options = {
    "parent": None,
    "window_size": 16,
    "stroke_width": 2,
    "rgba": (234, 54, 255, 255),
    "distance": 3
}


def main():
    app = QtWidgets.QApplication(sys.argv)

    crh = Crosshair(**options)
    crh.show()

    # Detect hotkey and terminate app
    keyboard.add_hotkey('alt + shift + p', app.quit)

    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
