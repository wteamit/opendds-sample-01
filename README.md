# First OpenDDS example #

## Build ##

In order to build the project, a CMake installation is needed on the pc.

In a command prompt, create a new folder and enter it. for building the application
run the following command:

```
> cmake -DDDS_ROOT_DIR=path/to/dds/folder /path/to/this/folder
```
If you want to build for a specific compiler/configuration, you need to add the -G flag:

```
> cmake -G"Visual Studio 14 2015 Win64" -DDDS_ROOT_DIR=path/to/dds/folder /path/to/this/folder
```

For a list of cmake supported compiler:

```
> cmake --help
```

After the cmake generation, build the project with:

```
> cmake --build .
```

## Running ##

### Start DCPSInfoRepo ###

Open a console, go to the DDS_ROOT/bin folder, and then

```
> ..\setenv.cmd
> .\DCPSInfoRepo -ORBEndpoint iiop://localhost:12345 -d domain_ids
```

This will start the server.

### Start publisher ###

Open another console, go to the bin/ folder where you've built the project and then:

```
> .\publisher -DCPSConfigFile configuration.ini
```

This will start the publisher. After some second you should be able to see messages
that are published in DDS.

### Start subscriber ###

Open Another console, go to the bin/ folder where you've built the project and then:

```
> .\subscriber -DCPSConfigFile configuration.ini
```

After some second the subscriber will be connected and messages received from the
publisher should be printed.

## Linux users

For linux users commands are the same, except that `setenv.cmd` becomes `setenv.sh`,
obviously.
