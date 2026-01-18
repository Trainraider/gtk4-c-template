## GTK4 C Template

The project is meant to be a minimal yet complete starting point for any GTK 4 project. Initial setup is just setting your project name and other info in `config.mk` and swapping the LICENSE file. Resources are integrated into the executable using GResource. The UI is in the new blueprint (.blp) file format, and is convenient to edit in Workbench.

___
### Getting Started:
#### Requirements:
* GTK4 library headers
* blueprint-compiler
* make
* pkg-config
* GCC
* Workbench (Optional)
* clang-format (Optional)

Workbench is only officially available on flathub:  

https://flatpak.org/setup/  

https://flathub.org/apps/re.sonny.Workbench  

```
flatpak install flathub re.sonny.Workbench
```

Debian or Ubuntu based linux distro:

```
sudo apt install libgtk-4-dev blueprint-compiler build-essential pkg-config clang-format
```

The project can be configured in `config.mk` to set the project's version, name etc. These are then made available to the program as macros, so you never need these things listed in multiple places.

The following macros are available to the C source files:

    VERSION     //The project's version number
	TARGET      //Name without spaces/ executable name
    NAME        //The project's name
    AUTHOR      //Your name
	APP_ID      //Your email/website and app name in reverse url format
	            //  e.g. com.gmail.johndoe.myapp
	APP_PREFIX  //APP_ID with forward slashes instead of periods. Used for
	            //  getting resources
		    //  e.g. /com/gmail/johndoe/myapp
    COPYRIGHT   //A copyright message e.g. "Copyright (c) 2026"


___
#### To build the project, simply run:

	$ make
___
#### To build a debug version with lots of warnings and protections enabled:

	$ make debug
___
#### To install the resulting application run (as root):

	$ sudo make install
___
#### To uninstall (as root):
	
	$ sudo make uninstall
___
#### You are encouraged to format your code (clang-format required) by running:

	$ make format
___
#### You can clean up project files with:

	$ make clean
