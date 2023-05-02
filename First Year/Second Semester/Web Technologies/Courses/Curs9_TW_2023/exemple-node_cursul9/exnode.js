const http = require('http');
//const url = require('url');
const querystring = require('querystring');
const fs = require('fs');
const server=http.createServer(function(request, response){
   var body="";
   console.log(request.url);
   var url_parts= new URL(request.url,'http://localhost:8030/');
   
   if(url_parts.pathname =='/salveaza'){
    request.on('data', function(date){
        body+=date; console.log(body);
        });
   request.on('end', function(){
        console.log("Am primit o cerere");
        console.log(body);
        var ob_body=querystring.parse(body);
        //console.log(ob_body);
        response.statusCode = 200;
        response.setHeader('Content-Type', 'text/html');
        response.write("<html><body><p> " + ob_body.nume + " din grupa " + ob_body.grupa + " are nota " + ob_body.nota + " </p> </body></html>");
        response.end();
        //adaugare in fisier
        if (fs.existsSync("studenti.json"))
		{
	var date= fs.readFileSync("studenti.json");
	ob=JSON.parse(date);
		}
	else
	ob=[];
        ob.push(ob_body);
	fs.writeFileSync("studenti.json",JSON.stringify(ob));

    });
 }

if(url_parts.pathname =='/afiseaza'){
        fs.readFile("studenti.json",function(err,date){
         if(err) throw err;
        var studenti=JSON.parse(date);
        response.statusCode=200;
	response.write('<html><body><table style="border:1px solid black"><tr><td style="border:1px solid black">Student</td><td style="border:1px solid black">Grupa</td><td style="border:1px solid black">Nota</td></tr>');
	for(s of studenti) {
		response.write('<tr><td style="border:1px solid black">');
		response.write(s.nume);
		response.write('</td><td style="border:1px solid black">');
		response.write(s.grupa);
		response.write('</td><td style="border:1px solid black">');
		response.write(s.nota);
		response.write('</td></tr>');
	}
	response.write('</table></body></html>');
	response.end();

    });
 }
});

server.listen(8030, function(){console.log("serverul asculta pe portul 8030");});
