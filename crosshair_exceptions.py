class DistanceIsTooLong(Exception):
    """
    Thrown when the distance from the center is bigger
    than the half of the full crosshair-size divided by two and subtracted one.
    Note that the stroke size will not affect the distance.

    E.g:
        windows_size = 28
        # Max size would be
        distance = windows_size / 2 - 1
    """
    pass


class WinSizeMustBeEven(Exception):
    """
    Thrown when the window_size is not an even number.
    """
    pass
