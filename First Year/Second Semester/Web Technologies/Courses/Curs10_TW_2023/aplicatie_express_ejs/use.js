var express = require('express');
var app = express();


//functie middleware care se executa la fiecare request catre '/pagina1’, înaintea functiei handler

app.use(function(req, res, next){
   var data=new Date();
   console.log("O cerere catre pagina1 a fost primita in " + data);
  next();

});

app.use('/pagina1', function(req, res, next){
   console.log("pagina1");
   next();

});

app.get('/pagina1', function(req, res){ //functie handler care trimite raspunsul
   res.send('Pagina 1');
   console.log("raspuns final");
});


app.listen(3000, function(){console.log("serverul a pornit pe portul 3000");});
