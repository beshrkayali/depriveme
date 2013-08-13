# Deprive Me

A [Pebble](http://getpebble.com) app that deprives you from sleeping. Set the timer (5 to 60 minutes) and Pebble will pulse on each occurrence.

The is the first time I develop for Pebble and C in general.

## Running the App

- Clone this repo and CD to the directory
- Create a symlink:

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