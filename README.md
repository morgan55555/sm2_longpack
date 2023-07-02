# Arduino Snapmaker 2 Longpack library
### by [morgan55555](https://github.com/morgan55555)

With this library you can easily pack and unpack Longpack format for DIY SM2 Modules.
First of all you have to include the library.
~~~
#include <Longpack.h>
~~~
You can unpack data from a Longpack or pack data to a Longpack.
To unpack data you have to create an LongpackReader. 
~~~
LongpackReader reader;
~~~
Now you can unpack the data from incoming CAN packages.
E_TRUE - data is complete, E_FALSE - data is damaged, E_DOING - data is incomplete, 
need more CAN packets for completion.
~~~
ERR_E doing = reader.read(canBusData0, CAN_PACK_1_SIZE);
~~~
To pack data you have to create an LongpackPacker packer, and send data to pack.
Then you can use buffer functions: available, read and peek, for filling your CAN packets.
~~~
LongpackPacker packer;
packer.pack(cmdData1, index);
~~~
Now you can pack and unpack Longpack data.  
You can see a pack and unpack examples in the [examples directory](https://github.com/morgan55555/sm2_longpack/tree/master/examples).
