window.onload=creare;

function creare(){

  window.onclick=generare;
  
}

function generare(event)
{

  var x=event.clientX;
  var y=event.clientY;
  var div=document.createElement("div");
  div.classList.add("animat");
  document.body.appendChild(div);
  div.style.position="absolute";
  div.style.left=x-parseInt(getComputedStyle(div).width)/2 +"px";
  div.style.top=y-parseInt(getComputedStyle(div).height)/2+"px";
  div.style.animationName="miscare"+ (Math.random()<0.5 ? 1:2);
  div.onclick=function(event){
     event.stopPropagation();
    
  }
  
}