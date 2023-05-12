const express = require('express');
const cookieParser = require('cookie-parser');
const fs = require('fs');
const formidable=require('formidable');
const session = require('express-session');
const events = require('events');
const eventEmitter = new events.EventEmitter();
const crypto  = require('crypto'); 


const app = express();


app.set('view engine', 'ejs');
app.use(express.static('resurse'));
app.use(express.static('poze'));
app.use(express.static('public'));
app.use(express.static('html'));


app.use(cookieParser());

app.use('/formpost',express.urlencoded({extended:true}));

app.use(session({
  secret: 'abcdefg', // folosit pentru criptarea session ID-ului
  resave: true, //sa nu stearga sesiunile idle
  saveUninitialized: false //nu salveaza obiectul sesiune daca nu am setat un camp
}));

app.use('/post', express.urlencoded({extended:true})); //parseaza datele din form trimise cu post

app.post('/post',function(req, res) {
	console.log(req.body);
	res.send(req.body.persoane.name + ' din '
 		+ req.body.city + ' are ' + req.body.age + ' (de) ani');
})


app.get('/post',function(req, res) {
	console.log(req.query);
	res.send(req.query.persoane.name + ' din '
 		+ req.query.city + ' are ' + req.query.age + ' (de) ani');
})


app.use("/ajax",express.urlencoded({extended:true}));

app.post('/ajax', function(req,res){
res.send(req.body.name + " are media " + req.body.media);
});


app.get('/index', function(req,res){
res.render('pagini/index');});

app.get('/ex1', function(req,res){
res.render('pagini/ex1',{title:'Template cu EJS', continut:'Pagina generata cu EJS'});});

app.get('/ex23', function(req,res){
res.render('pagini/ex2&3')});


app.get('/for_vector', function(req, res) {
    aranjamente_flori=["buchet mic","buchet mare", "coroana", "salba","ghiveci"]
    flori=[
   	 { nume:"lalele", culoare:"rosu", nr_fire_buchet: 5, imagine:"lalele.jpg" },
   	 { nume:"orhidee", culoare:"roz", nr_fire_buchet: 10, imagine:"orhidee.jpg" },
   	 { nume:"garoafe", culoare:"alb", nr_fire_buchet: 9, imagine:"garoafe.jpg" }
    ];
    res.render('pagini/for_vector', {vector_simplu: aranjamente_flori, vector_obiecte:flori});
});


app.get('/form', function(req,res){
res.render('pagini/form',{selectedLang:req.cookies.limba, langs : "['romana', 'franceza', 'greaca', 'spaniola']"});
});

app.post('/formpost', function(req,res){
	res.cookie('limba', req.body.limba);
res.send('saved');
});




app.get('/event', function(req, res) {
     eventEmitter.on('event1',function(arg1,arg2){
	for(i=0;i<arg1;i++) console.log(arg2);
        });
     eventEmitter.emit('event1',10,'a');
        res.send("Ai facut o cerere GET");

});



app.get('/astept', function(req, res) {
  console.log('astept');
  eventEmitter.once('event2', function(arg) {
    console.log('primit ' + arg);
    res.send('Am primit ' + arg);
  });

});

app.get('/trimit', function(req, res) {
  let val = req.query['mesaj'];
  console.log('trimit ' + val);
  eventEmitter.emit('event2', val);
  res.send('Am trimis ' + val);
});



app.get('/cv',function(req,res){
res.redirect("cv.html");});


app.post('/salveaza',function(req,res){
        var ob;
	if (fs.existsSync("persoane.json"))
		{
	var date= fs.readFileSync("persoane.json");
	ob=JSON.parse(date);
		}
	else
	ob=[];
	var form = new formidable.IncomingForm({uploadDir:'upload', keepExtensions:true});
        form.keepFileName=true;
        form.parse(req,function(err,fields,files){
	//var ob_form={'nume':fields.nume,'cv':files.cv.name,'poza':files.poza.name};
	var ob_form={nume:fields.nume,cv:files.cv.name,poza:files.poza.name};
        ob.push(ob_form);
        fs.writeFileSync("persoane.json",JSON.stringify(ob));
	});
	res.send("Salvat:");
});


//--------------------------------------------------------------------------------
app.get('/carti',function(req,res){
res.redirect("carti.html");});

app.post('/adauga',function(req,res){

	var ob;
	if (fs.existsSync("carti.json"))
		{
	var date= fs.readFileSync("carti.json");
	ob=JSON.parse(date);
		}
	else
	ob=[];
	var form = new formidable.IncomingForm();
	form.on("fileBegin", function(name,file){
    console.log(file);  //se seteaza calea de upload
     	file.path='poze/' + file.name;  //ca sa păstram numele initial al fisierului din file.name
     	});

	form.parse(req,function(err,fields,files){
      //  console.log(files);
	var ob_form={titlu:fields.titlu,autor:fields.autor,pret:fields.pret,descriere:fields.descriere,poza:files.poza.name};
       //console.log(ob_form);

	ob.push(ob_form);

	fs.writeFileSync("carti.json",JSON.stringify(ob));
	});

	res.send("Produs adaugat:");
});



app.get('/afiseaza', function(req, res) {
	var date = fs.readFileSync("carti.json");
	var comenzi = JSON.parse(date);
        res.render("pagini/form_carti",{carti:comenzi});

});

//------------------------------------------------------------------



app.get('/pagina1', function(req, res){
  console.log(req.session.id);
   if(req.session.vizitat){
      req.session.vizitat++;
   } else {
      req.session.vizitat = 1;
   }
 res.send('Esti pe pagina 1');
 console.log(req.session.vizitat);});

app.get('/pagina2', function(req, res){
      res.send("Ai vizitat pagina 1  de " + req.session.vizitat + " ori");});





app.get('/login', function(req,res){

 res.render('pagini/login',{'mesaj': 'Login'});
});

app.post('/login_post', function(req, res) {
    var user;
    var form = new formidable.IncomingForm();
    form.parse(req, function(err, fields, files) {

     var useri= JSON.parse(fs.readFileSync("useri.json"));
     
     var cipher = crypto.createCipheriv('aes128','passwordpassword', 'vectorvector1234');
     var parolacriptata = cipher.update(fields.parola, 'utf8',"hex");
     parolacriptata += cipher.final("hex");
     
      for(var x of useri){                    //verificarea datelor de login
   	 	if (fields.username == x.username && parolacriptata==x.parola)
			user=fields.username;
			}
   
   	 if(user){
   		 req.session.username=user;//setez userul ca proprietate a sesiunii
                 	res.redirect('/logat');}
   	 else {
		req.session.username=false;

	       res.redirect('/incorect');}
   	 });
    });

app.get('/logat', function(req, res) {
   	 res.render('pagini/logout',{'nume': req.session.username});
    });

app.get('/incorect', function(req, res) {
   	 res.render('pagini/login',{'mesaj': 'Username/parola gresita'});
    });

app.get('/logout', function(req, res) {
req.session.destroy();  //distrugem sesiunea cand se intra pe pagina de logout
res.render('pagini/login',{'mesaj': 'Login'});

//    res.write('<p>Ai fost delogat</p>');
  //  res.write("<a href=" + '/login' + ">Inapoi la login</a>");
    //res.end();
});

app.use(function(req,res){

res.redirect("404.html");

});

app.listen(8020, function() {console.log('serverul asculta pe portul 8020')});
