window.onload=generare;

function generare(){
  var culori=[];
  for(var i=0;i<10;i++){
    var buton=document.createElement("button");
    buton.innerHTML=i;
    buton.classList.add("copil","cifra"+i);
  //  alert(buton.style.backgroundColor);
    culori.push(getComputedStyle(buton).backgroundColor);
    document.body.appendChild(buton);
  }
document.body.onkeydown=function(event){
  var buton=document.querySelector(".cifra"+ event.key);
  buton.style.backgroundColor="black";
  }
document.body.onkeyup=function(event){
  var buton=document.querySelector(".cifra"+ event.key);
  buton.classList.add("cifra"+event.key);
  buton.style.backgroundColor=culori[event.key];
}
 
}