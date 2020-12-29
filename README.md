# Command-Line-Args

## Overview

Cross platform C++ class based implementation of getopt. Requires C++17 or later.

The principle of this utility is encapsulation of argument parsing and error checking. It makes use of registering argument options specifically within a subclass of ArgumentParser and assigning callbacks to them to handle the specific needs of that argument. For example, it may need converting to a number from a string and checking that the conversion happened properly (ie the user passes in a non-numerical value).

As opposed to the client code being aware of the actual option strings and querying them, the programmer is encouraged to use custom defined properties that get set manually in the callback functions of each argument. These can then be accessed via the properties in the calling function. So, in the event that an option needs to be changed to something different, the registration is the only thing that needs to change within the subclass.

Built in error checking is also included, such as options being used multiple times or empty arguments being passed. These restrictions can be configured/disabled in the user defined subclass. There is also a default help message that can be overridden using a custom message if that is preferred.

## Usage

An example subclass and main function utilizing this parser can be found in this repository alongside the required base code. Here is a step-by-step guide on setting this up from scratch:

- Publicly subclass ArgumentParser
- Declare the properties to be queried and give them sensible default values. These are static inline members of any type.
- Declare and define one callback per argument option (including default/empty arguments if they are being used). Callbacks take a value passed in via the command line as an argument and return a boolean indicating success. The signature of these can be:
  - bool functionName(std::string value) //Single value arguments (most common usage)
  - bool functionName(std::vector\<std::string\> values) //Arguments that accept a list of arguments (less common)
- Declare and define a static Init function that will set up the relationships between the arguments and the callbacks. This is done by defining the following properties:
  - arguments //List of argument callbacks (more common)
  - functions //List of function callbacks (more common)
  - listArguments //List of arguments that accept a list as input (less common)
  - listFunctions //List of function callbacks that accept a list as input (less common)
- The corresponding argument and function lists must be the same size. The initialization will throw an error if they aren't. The number of regular and list arguments can be different. Also, arguments must be unique across both lists and cannot be reused. Doing this will also cause an error. Registering a default argument (one that does not have an option name like -i) is registered with an empty string ("").
- As well as overriding some options and string variables, you can associate descriptions with arguments. These will be used in the default --help output. Similar to the function registration, these are defined in lists that are in the same order as the argument list. However, the size of the description list and argument list need not match, but there cannot be more descriptions than arguments. This will cause an error.
- After the overriding/configuration, make sure to call Init at the end of this custom initialization function
- Call the Initialization function in main. Exit if the return value is false.
- Call parseArguments after this. Again, exit on return value of false.
