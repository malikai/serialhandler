# Introduction #

Used to manage complex input to control an arduino by serial


# Details #

Main feature
  * Both way managed communication
  * Recive command line and parameters easily
  * Send command and wait for answer

Create an instance with :

`SerialHandler InstanceName(available,read,write,Error);`

`uint8_t available(){`
`  //return how many byte are available to be read`
`}`

`int read(){`
`  //return one read byte from the other device`
`}`

`void write(uint8_t Buf){`
`  //How to write to the other device`
`}`

`void Error(uint8_t Buffer[]){`
`  //What to do on error`
`}`