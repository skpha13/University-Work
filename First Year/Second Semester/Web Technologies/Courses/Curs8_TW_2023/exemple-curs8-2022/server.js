var http = require('http');
var url = require('url');

http.createServer(function (req, res) {
    var url_parts = url.parse(req.url, true);
    var query = url_parts.query;

    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.end("Buna " + query.name + ' din ' + query.city);
}).listen(8080); 
