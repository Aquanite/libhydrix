# libhydrix

**libhydrix** is a powerful, modular C++ library designed to provide various utilities and functionalities essential for building a Limine OS. The library is organized into several distinct modules, each focusing on a specific aspect of OS development. This modular design allows developers to easily include only the components they need, ensuring a lightweight and efficient implementation.

## Modules

### hcon (Hydrix Console)
This module handles console input and output operations.
- `console.cpp`: Implementation of console functionalities.
- `console.h`: Header file for console operations.

### hgl (Hydrix Graphics Library)
The hgl module provides basic graphics and color manipulation capabilities.
- `color.cpp`: Implementation of color-related functionalities.
- `color.h`: Header file for color operations.
- `graphics.cpp`: Implementation of graphics-related functionalities.
- `graphics.h`: Header file for graphics operations.

### hinteger (Hydrix Integer)
Dedicated to integer-based mathematical operations.
- `hinteger.cpp`: Implementation of integer math functionalities.
- `hinteger.h`: Header file for integer operations.

### hmath (Hydrix Math)
The hmath module offers various mathematical utilities, both for floating-point and integer calculations.
- `floatmath.cpp`: Implementation of floating-point math functionalities.
- `floatmath.h`: Header file for floating-point math operations.
- `intmath.cpp`: Implementation of integer math functionalities.
- `intmath.h`: Header file for integer math operations.

### hrand (Hydrix Random)
Provides random number generation functionalities.
- `rand.h`: Header file for random number generation.

### hstring (Hydrix String)
Handles string manipulation and related operations.
- `string.cpp`: Implementation of string functionalities.
- `string.h`: Header file for string operations.

## Getting Started

To use libhydrix in your project, include the necessary header files from the modules you need.

## License

libhydrix is licensed under the GPL v3 License. See [LICENSE](https://github.com/AzureianGH/libhydrix/blob/main/LICENSE) for more information.
