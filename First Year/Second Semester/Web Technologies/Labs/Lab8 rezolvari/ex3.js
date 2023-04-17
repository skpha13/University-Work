window.onload=function(){

  var buton=document.getElementById("start");
  var intrebare=document.getElementById("intrebare");
  var raspuns=document.getElementById("raspuns");
  var form=document.getElementById("form");
  var butoane=document.getElementsByTagName("input");
  intrebare.style.visibility="hidden";
  form.style.visibility="hidden";
  buton.onclick=function(){
    intrebare.style.visibility="visible";
    intrebare.style.color="blue";
    form.style.visibility="visible";
   var t=setTimeout(function(){
      alert("Timpul a expirat");
     // form.style.visibility="hidden";
      for(var b of butoane)
       b.disabled=true;
    },5000);
    form.onchange=function(){
      for(var b of butoane)
        if (b.checked==true) raspuns.innerHTML="Raspuns " + b.value;
      clearTimeout(t);
    }
  
  }  
}