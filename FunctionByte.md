# Introduction #

Byte at `Buffer[0]` is called the FunctionByte.

# Details #

When GetSerial(0) is lunched and the last received byte is the Ack the FunctionByte at `Buffer[0]` trigger it's AttachFunction. If the byte is not attached the ErrorFunc is lunched.