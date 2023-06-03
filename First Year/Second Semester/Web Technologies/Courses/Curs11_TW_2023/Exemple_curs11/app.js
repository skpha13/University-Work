const express = require('express');  
const app = express();   
const fs=require("fs");
const { DOMParser } =require("xmldom");

app.use(express.static('public'));
 
app.get("/xml",function(req,res){
           var date = fs.readFileSync("test.xml","utf-8"); 
           var parser = new DOMParser();
           var xmlDoc = parser.parseFromString(date,"text/xml"); //se creaza un obiect XMLDOM din stringul text 
            var per = xmlDoc.getElementsByTagName('pers'); 
            var content = "";
        for (var i=0; i < per.length; i++) {
        content = content + per[i].getAttribute("nume") + " are " + per[i].getAttribute("varsta") +  " ani \n";
   }
          
           res.send(content);
});

app.get("/mesaj", function(req,res){

  setTimeout(function(){res.send("Mesaj de la Server");console.log("Am trimis");
  },5000);
  
  });

//app.use('/post', express.json()); //parseaza datele din form (json) trimise cu post
app.use('/post', express.urlencoded({extended:true})); //parseaza datele din form (json) trimise cu post
app.post('/post',function(req, res) {
	console.log(req.body);
	res.send(req.body.nume + ' din '
 		+ req.body.city + ' are ' + req.body.age + ' (de) ani');
})


app.listen(3000, function() {console.log('serverul asculta pe portul 3000')});
