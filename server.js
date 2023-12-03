var http = require('http'); // Import Node.js core module

const hostname = '127.0.0.1';
const port = 5000;
const express = require('express');
const app = express();

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

app.get('/', (req, res) => {
    console.log('Received a request from the client website.');
    res.send('This is the sever responding to the request');
});

app.listen(port, () => {
    console.log('Server is listening at http://${hostname}:${port}/');
});

