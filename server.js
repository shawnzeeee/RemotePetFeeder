var http = require('http'); // Import Node.js core module

const hostname = '192.168.182.128"';
const port = 5000;
const websocketPort = 3000;
const express = require('express');
const app = express();
const WebSocket = require('ws');
const cors = require('cors');

const corsOptions = {
    origin: 'http://192.168.182.128/trigger', // Replace with the origin you are sending requests from
    optionsSuccessStatus: 200 // Some legacy browsers (IE11, various SmartTVs) choke on 204
};

app.use(cors(cors(corsOptions)));

var server = http.createServer(function (req, res) {   //create web server
    if (req.url == '/') { //check the URL of the current request
        
        // set response header
        res.writeHead(200, { 'Content-Type': 'text/html' }); 
        
        // set response content    
        res.write('<html><body><p>Welcome to the beaglebone food dispensing server.</p></body></html>');
        res.end();
    
    } else
        res.end('Invalid Request!');
    
});

const wss = new WebSocket.Server({port: websocketPort});

server.on('upgrade', function upgrade(request, socket, head) {
    console.log(request);
    if (request.url === '/ws') { // Make sure the endpoint matches the one expected by the client
        wss.handleUpgrade(request, socket, head, function done(ws) {
            wss.emit('connection', ws, request);
        });
    } else {
        socket.destroy();
    }
});


wss.on('connection', function connection(ws) {
    console.log('A WebSocket client connected.');
    
    ws.on('message', function incoming(message) {
        console.log('received: %s', message);
        
    });
    
    ws.send('Welcome to the WebSocket server!');
});

app.get('/', (req, res) => {
    console.log('Received a request from the client website.');
    res.send('This is the sever responding to the request');
});

app.get('/ws', (req, res) => {
    console.log('Received a request from the websocket client.');

    res.send('This is the sever responding to the request');
});

app.get('/trigger', (req, res) => {
    wss.clients.forEach(client => {
        if (client.readyState === WebSocket.OPEN) {
            client.send('changeVariable');
        }
    });
    res.send('Trigger sent to BeagleBone');
});

app.listen(port, '0.0.0.0', () => {
    console.log('Server is listening at http://${hostname}:${port}/');
});
