CS365-Checkers
==============

A simple, web-based two player checker game made for a Northern Michigan University web programming class.  Checkers was developed by Cohen Adair, Nate Schreiner, and Kyle Lefeevre.

#### Required Node.js modules
The required Node.js modules aren't included in this repository simply because they take up too much space.  Each module can be installed with the `npm install <package-name>` command.
* body-parser
* express
* mongodb
* socket.io

#### Running on OSX
* Download and unzip [MongoDB](https://www.mongodb.org/downloads#production)
* Open a Terminal and create the `data` folder

  ```
  sudo mkdir -p /data/db
  ```
* Run `mongod`

  ```
  sudo <path to where you unzipped MongoDB>/bin/mongod
  ```
* Run the server

  ```
  node <path to server>server.js
  ```
* Open in browser

  ```
  http://127.0.0.1:8026/
  ```
