# Introduction #

Use to be sure the next send byte is the FunctionByte


# Details #

When the Abord byte is recived by SerialHandler and `GetSerial(0)` is called, Flush is executed to clear the buffer so the next byte will be in `Buffer[0]`.