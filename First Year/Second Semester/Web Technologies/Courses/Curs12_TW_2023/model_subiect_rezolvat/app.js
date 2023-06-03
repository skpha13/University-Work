const express = require("express");
const app = express();

/*app.get("/ex4", function(req,res){
  res.sendFile(__dirname + "/ex4.html");
});*/

app.use(express.static("html"));

app.get('/range',function(req, res){
  
  let obiecte = [{nume:"agenda", greutate:"0.5"}, {nume:"telefon", greutate:"1"}, {nume:"rucsac", greutate:"2.3"}, {nume:"caiet", greutate:"0.8"},{nume:"carte", greutate:"1"}, {nume:"tobe", greutate:"4"}];
  console.log(req.query);
  
  let greutate = req.query.greutate;
  var a=[];
  
  for(var o of obiecte){
    if ((o.greutate <= greutate) && (o.nume.indexOf("t")!=-1))
    a.push(o.nume);
  }
  
  res.send(a);
});

app.listen(5000, ()=>{
  console.log("Server listening on port 5000");
})
