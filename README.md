# LoRa test device

## Dependencies
The following components are needed
## test node
- Node & Node-RED

## server node
- Node-RED
- mongodb instance

## Setup test node
### Clone repo
    $ git clone https://github.com/guitar-hero/lora-post
    $ cd lora-post
    $ cd lora-post-test-node
### Run Node-RED app
    $ cd lora-post
    $ cd lora-post-test-node
    $ npm install
    $ npm start

The node-RED instance will be served on port 1882  
The UI to run the test cases will be accessible at ```http://localhost:1882/ui```

## Setup server node
### Clone repo
    $ git clone https://github.com/guitar-hero/lora-post
### Run Node-RED app
    $ cd lora-post
    $ cd lora-post-test-node
    $ npm install
    $ npm start
The node-RED instance will be served on port 1881
### Configuration
Configure Loriot WebSocket URL in Backend (via Node-RED UI)




   

