var http = require('http');
var date=require('./mymodule');

http.createServer(function(req, res) {
	console.log('am primit un request');
	res.writeHead(200, {'Content-Type': 'text/html'});
	res.end('<html><body>Astazi <b>' + date.myDate() + '</b> am invatat despre <b> '
		 +  date.myMessage() + '</b></body></html>');
        }).listen(8050);
console.log ('Serverul creat asteapta cereri la http://localhost:8050/');
