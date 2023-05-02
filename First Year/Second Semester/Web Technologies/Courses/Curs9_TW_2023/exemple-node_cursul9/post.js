
var http = require('http');
var x = require('querystring');

var server = http.createServer((req, res) => {
    if (req.method === 'POST') {
        collectRequestData(req, result => {
            console.log(result);
            res.end('Ati introdus numele: '+  result.name);
        });
    }
});
server.listen(8080);
console.log ('Serverul creat asteapta cereri la http://localhost:8080/');

function collectRequestData(request, callback) {
    const FORM_URLENCODED = 'application/x-www-form-urlencoded';
    if(request.headers['content-type'] === FORM_URLENCODED) {
        let body = '';
        request.on('data', chunk => {
            body += chunk.toString();      
        });

        request.on('end', () => {
            callback(x.parse(body));
        });
    }
    else {
        callback(null);
    }
}

