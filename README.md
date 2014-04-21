C++ Web-Server
==============

Contributors
------------
| Name                | Email                             |
| ----                | -----                             |
| Georgi Baghdasaryan | baghdasaryan@ucla.edu             |


Project Description
-------------------

A simple C++ Web Server

Usage
-----
First, we need to download and build this project. Follow the following steps
to do so:

```shell
$ git clone https://github.com/baghdasaryan/Web-Server.git
$ cd Web-Server
$ make
```

`make` will build the executable file, `server`, in the current directory.

Now, you can start the program:
```shell
$ ./server
```

By default, the program will start an HTTP server on port 2048 and uses
`public` folder (located in current directory) as the *DocumentRoot*.
*DocumentRoot* is the root folder where the server will search for requested files

This server will be  and files in `public` folder (located in current directory).

Typically, a document called index.html will be served when a directory is
requested without a file name being specified. For example, if *DocumentRoot*
is set to */var/www/html* and a request is made for *http://www.example.com/work/*,
the file */var/www/html/work/index.html* will be served to the client.

When an actual file is being requested, the server will try to find it on the
specified path relative to the DocumentRoot. If a file can be found - it will be
returned, otherwise server will return an error.

This server is capable of serving image files (\*.img, \*.jpeg, \*.jpg) HTML files (\*.html) as well as simple text files.
