# Command-Line-Args

## Overview

Cross platform C++ object oriented implementation of getopt. Requires C++17 or later.

The principle of this utility is encapsulation of argument parsing and error checking. It makes use of registering argument options specifically within a subclass of ArgumentParser and assigning callbacks to them to handle the specific needs of that argument. For example, it may need converting to a number from a string and checking that the conversion happened properly (ie the user passes in a non-numerical value).

As opposed to the client code being aware of the actual option strings and querying them, the programmer is encouraged to use custom defined properties that get set manually in the callback functions of each argument. These can then be accessed via the properties in the calling function. So, in the event that an option needs to be changed to something different, the registration is the only thing that needs to change within the subclass.

## Usage

An example subclass and main function utilizing this parser can be found in this repository.

To register custom arguments you must first publicly subclass ArgumentParser. You can then define your properties that go along with the argument that you will query after parsing. These need to be static inline members. You can choose to use getters for these or simply declare them as public.

You then need to define the callbacks for these functions. These need to take an std::string as an argument and return a boolean. These functions are also static (not inline). A return value of true indicates success (ie a valid argument for this option) and false will indicate failure. If any argument fails, the parsing will immediately stop and return false to the calling function.

Finally just declare a static Init function that will initialize the properties with their default values and register the arguments against the callbacks.

The actual registration is done with the registerArgument function that is defined in ArgumentParser. Pass it a string such as "-i" and a function you have defined for that option such as setInputFile.

In your main function, call the Init function of the subclass and then run parseArguments (again of the subclass). Take not that the latter function will return a boolean indicating success and will also print error messages regarding general parsing errors or specific errors defined and printed in the callback functions.

If a value of false is returned, it is recommended that the program gracefully exists at this point. Upon success, simply query the properties as you need them and proceed as normal.

## TODO

- Re-document restructured registration as well as other features
