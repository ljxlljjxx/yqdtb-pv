class PV_55p8:
    """Wrapper for the pvc_PV_55p8 C structure."""
    
    def __init__(self, value: int = 0) -> None:
        """
        Create a new PV_55p8 object.
        :param value: Initial integer value (clamped to unsigned 64-bit range).
        """
        ...
    
    def strvalue(self) -> str:
        """
        Return a decimal string representation of the value.
        The string is produced by pvc_PV_55p8_tostring().
        """
        ...
