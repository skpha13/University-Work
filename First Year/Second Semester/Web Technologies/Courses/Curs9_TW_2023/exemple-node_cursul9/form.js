var http = require('http');
var fs= require('fs');
var server = http.createServer(function (req, res)
{
   console.log("O cerere;");
   var url_parts=new URL(req.url,'http://localhost:8080/');
   console.log(url_parts);
   if(url_parts.pathname =='/cale'){
    var query=url_parts.searchParams;
     fs.appendFileSync('date.txt', query.get('name') + ',' + query.get('age') + ',' + query.get('city')+ '\n');
     res.writeHead(200, {'Content-Type': 'text/plain'});
     res.end(query.get('name') + ' din ' + query.get('city') + ' are ' + query.get('age') + ' ani ');}
  }).listen(8080);
console.log ('Serverul creat asteapta cereri la http://localhost:8080/');
