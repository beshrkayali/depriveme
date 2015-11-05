# Deprive Me

[![Join the chat at https://gitter.im/beshrkayali/depriveme](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/beshrkayali/depriveme?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

![Deprive Me](http://i.imgur.com/9uaWi7r.jpg)


A [Pebble](http://getpebble.com) app that deprives you from sleeping. Set the timer (5 to 60 minutes) and Pebble will pulse on each occurrence.

The is the first time I develop for Pebble and C in general.

## Download the App

- You can download a pbw file from [My Pebble Faces](http://www.mypebblefaces.com/apps/6940/5557/)

## Running the App

- Clone this repo and CD to the directory
- Symlink the project:

		create_pebble_project.py --symlink-only ~/path/to/pebble/sdk .

- Run waf configure and waf build:
	
		./waf configure
		./waf build

- Create a simple python server to install the app:
	
		python -m SimpleHTTPServer 8000

- On your iPhone or Android phone:

		http://your.computer.ip.address:8000/build/DepriveMe.pbw

- That's it!


### Pictures

Here are some pictures of the app:

![Home Screen](http://i.imgur.com/q9r9FNz.jpg)

![Pulsing](http://i.imgur.com/zClp9Zz.jpg)