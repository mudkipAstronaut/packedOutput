# packedOutput
A simple packer and depacker of bit data into a desired format in order to communicate and unpack data from an I2C slave

I2C slaves might have data packet in the following format:
| Length        | Offset        | Data          |
| ------------- | ------------- | ------------- |
| 2 bits        | 0             | parameter1    |
| 2 bits        | 2             | parameter2    |
| 2 bits        | 4             | parameter3    |
| 2 bits        | 6             | parameter4    |

With the whole data of the I2C trasnfer being 1 byte.

The program, once compiled and ran will decode the original
1 byte variable containing 4 parameters into an array of
length 4 which contains the parameter values.
Conversely if this is a setter function to the I2C slave,
an array of length 4 containing the values for each
of the 4 parameters can be converted into a 1 byte 
value to send over to the I2C device.
