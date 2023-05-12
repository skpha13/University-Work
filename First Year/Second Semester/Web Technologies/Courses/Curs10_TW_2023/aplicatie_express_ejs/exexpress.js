const express = require('express');
const fs = require('fs');
const app = express();

app.use(express.static('html'));
app.use('/salveaza',express.urlencoded({extended:true}));


app.post('/salveaza',function(request,response){
   
        response.status(200);
        response.write("<html><body><p> " + request.body.nume + " din grupa " 
	+ request.body.grupa + " are nota " + request.body.nota + " </p> </body></html>");
        response.end();
        //adaugare in fisier
        if (fs.existsSync("studenti.json"))
		{
	var date= fs.readFileSync("studenti.json");
	ob=JSON.parse(date);
		}
	else 
	ob=[];
        ob.push(request.body);
	fs.writeFileSync("studenti.json",JSON.stringify(ob));
	
    });
 

app.get('/afiseaza', function(request,response){

        fs.readFile("studenti.json",function(err,date){
         if(err) throw err;
        var studenti=JSON.parse(date);
        response.status(200);
        response.write('<html><body><head><link rel="stylesheet" href="stil.css"></head><table><tr><td>Student</td><td>Grupa</td><td>Nota</td></tr>');
	for(s of studenti) {
	        response.write('<tr><td>');
	        response.write(s.nume);
	        response.write('</td><td>');
	        response.write(s.grupa);
	        response.write('</td><td>');
	        response.write(s.nota);
	        response.write('</td></tr>');
	        }
	response.write('</table></body></html>');
	response.end();
        
    });
 
});

app.listen(8030, function(){console.log("serverul asculta pe portul 8030");}); 
